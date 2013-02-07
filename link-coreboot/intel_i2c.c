

struct gmbus_port {
	const char *name;
	int reg;
};

static const struct gmbus_port gmbus_ports[] = {
	{ "ssc", GPIOB },
	{ "vga", GPIOA },
	{ "panel", GPIOC },
	{ "dpc", GPIOD },
	{ "dpb", GPIOE },
	{ "dpd", GPIOF },
};

/* Intel GPIO access functions */

#define I2C_RISEFALL_TIME 10

inline struct intel_gmbus *
to_intel_gmbus(struct i2c_adapter *i2c)
{
	return container_of(i2c, struct intel_gmbus, adapter);
}

void
intel_i2c_reset(struct drm_device *dev)
{
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;
	I915_WRITE(dev_priv->gpio_mmio_base + GMBUS0, 0);
}

void intel_i2c_quirk_set(struct drm_i915_private *dev_priv, bool enable)
{
	u32 val;

	/* When using bit bashing for I2C, this bit needs to be set to 1 */
	if (!IS_PINEVIEW(dev_priv->dev))
		return;

	val = I915_READ(DSPCLK_GATE_D);
	if (enable)
		val |= DPCUNIT_CLOCK_GATE_DISABLE;
	else
		val &= ~DPCUNIT_CLOCK_GATE_DISABLE;
	I915_WRITE(DSPCLK_GATE_D, val);
}

u32 get_reserved(struct intel_gmbus *bus)
{
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;
	extern struct drm_device *i915;
	struct drm_device *dev = i915;
	u32 reserved = 0;

	/* On most chips, these bits must be preserved in software. */
	if (!IS_I830(dev) && !IS_845G(dev))
		reserved = I915_READ_NOTRACE(bus->gpio_reg) &
					     (GPIO_DATA_PULLUP_DISABLE |
					      GPIO_CLOCK_PULLUP_DISABLE);

	return reserved;
}

int get_clock(void *data)
{
	struct intel_gmbus *bus = data;
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;
	u32 reserved = get_reserved(bus);
	I915_WRITE_NOTRACE(bus->gpio_reg, reserved | GPIO_CLOCK_DIR_MASK);
	I915_WRITE_NOTRACE(bus->gpio_reg, reserved);
	return (I915_READ_NOTRACE(bus->gpio_reg) & GPIO_CLOCK_VAL_IN) != 0;
}

int get_data(void *data)
{
	struct intel_gmbus *bus = data;
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;
	u32 reserved = get_reserved(bus);
	I915_WRITE_NOTRACE(bus->gpio_reg, reserved | GPIO_DATA_DIR_MASK);
	I915_WRITE_NOTRACE(bus->gpio_reg, reserved);
	return (I915_READ_NOTRACE(bus->gpio_reg) & GPIO_DATA_VAL_IN) != 0;
}

void set_clock(void *data, int state_high)
{
	struct intel_gmbus *bus = data;
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;
	u32 reserved = get_reserved(bus);
	u32 clock_bits;

	if (state_high)
		clock_bits = GPIO_CLOCK_DIR_IN | GPIO_CLOCK_DIR_MASK;
	else
		clock_bits = GPIO_CLOCK_DIR_OUT | GPIO_CLOCK_DIR_MASK |
			GPIO_CLOCK_VAL_MASK;

	I915_WRITE_NOTRACE(bus->gpio_reg, reserved | clock_bits);
	POSTING_READ(bus->gpio_reg);
}

void set_data(void *data, int state_high)
{
	struct intel_gmbus *bus = data;
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;
	u32 reserved = get_reserved(bus);
	u32 data_bits;

	if (state_high)
		data_bits = GPIO_DATA_DIR_IN | GPIO_DATA_DIR_MASK;
	else
		data_bits = GPIO_DATA_DIR_OUT | GPIO_DATA_DIR_MASK |
			GPIO_DATA_VAL_MASK;

	I915_WRITE_NOTRACE(bus->gpio_reg, reserved | data_bits);
	POSTING_READ(bus->gpio_reg);
}

int
intel_gpio_pre_xfer(struct i2c_adapter *adapter)
{
	struct intel_gmbus *bus = container_of(adapter,
					       struct intel_gmbus,
					       adapter);
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;

	intel_i2c_reset(dev_priv->dev);
	intel_i2c_quirk_set(dev_priv, true);
	set_data(bus, 1);
	set_clock(bus, 1);
	udelay(I2C_RISEFALL_TIME);
	return 0;
}

void
intel_gpio_post_xfer(struct i2c_adapter *adapter)
{
	struct intel_gmbus *bus = container_of(adapter,
					       struct intel_gmbus,
					       adapter);
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;

	set_data(bus, 1);
	set_clock(bus, 1);
	intel_i2c_quirk_set(dev_priv, false);
}

void
intel_gpio_setup(struct intel_gmbus *bus, u32 pin)
{
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;
	struct i2c_algo_bit_data *algo;

	algo = &bus->bit_algo;

	/* -1 to map pin pair to gmbus index */
	bus->gpio_reg = dev_priv->gpio_mmio_base + gmbus_ports[pin - 1].reg;

	bus->adapter.algo_data = algo;
	algo->setsda = set_data;
	algo->setscl = set_clock;
	algo->getsda = get_data;
	algo->getscl = get_clock;
	algo->pre_xfer = intel_gpio_pre_xfer;
	algo->post_xfer = intel_gpio_post_xfer;
	algo->udelay = I2C_RISEFALL_TIME;
	algo->timeout = usecs_to_jiffies(2200);
	algo->data = bus;
}

int
gmbus_xfer_read(struct drm_i915_private *dev_priv, struct i2c_msg *msg,
		u32 gmbus1_index)
{
	int reg_offset = dev_priv->gpio_mmio_base;
	u16 len = msg->len;
	u8 *buf = msg->buf;

	I915_WRITE(GMBUS1 + reg_offset,
		   gmbus1_index |
		   GMBUS_CYCLE_WAIT |
		   (len << GMBUS_BYTE_COUNT_SHIFT) |
		   (msg->addr << GMBUS_SLAVE_ADDR_SHIFT) |
		   GMBUS_SLAVE_READ | GMBUS_SW_RDY);
	while (len) {
		int ret;
		u32 val, loop = 0;
		u32 gmbus2;

		ret = wait_for((gmbus2 = I915_READ(GMBUS2 + reg_offset)) &
			       (GMBUS_SATOER | GMBUS_HW_RDY),
			       50);
		if (ret)
			return -ETIMEDOUT;
		if (gmbus2 & GMBUS_SATOER)
			return -ENXIO;

		val = I915_READ(GMBUS3 + reg_offset);
		do {
			*buf++ = val & 0xff;
			val >>= 8;
		} while (--len && ++loop < 4);
	}

	return 0;
}

int
gmbus_xfer_write(struct drm_i915_private *dev_priv, struct i2c_msg *msg)
{
	int reg_offset = dev_priv->gpio_mmio_base;
	u16 len = msg->len;
	u8 *buf = msg->buf;
	u32 val, loop;

	val = loop = 0;
	while (len && loop < 4) {
		val |= *buf++ << (8 * loop++);
		len -= 1;
	}

	I915_WRITE(GMBUS3 + reg_offset, val);
	I915_WRITE(GMBUS1 + reg_offset,
		   GMBUS_CYCLE_WAIT |
		   (msg->len << GMBUS_BYTE_COUNT_SHIFT) |
		   (msg->addr << GMBUS_SLAVE_ADDR_SHIFT) |
		   GMBUS_SLAVE_WRITE | GMBUS_SW_RDY);
	while (len) {
		int ret;
		u32 gmbus2;

		val = loop = 0;
		do {
			val |= *buf++ << (8 * loop);
		} while (--len && ++loop < 4);

		I915_WRITE(GMBUS3 + reg_offset, val);

		ret = wait_for((gmbus2 = I915_READ(GMBUS2 + reg_offset)) &
			       (GMBUS_SATOER | GMBUS_HW_RDY),
			       50);
		if (ret)
			return -ETIMEDOUT;
		if (gmbus2 & GMBUS_SATOER)
			return -ENXIO;
	}
	return 0;
}

/*
 * The gmbus controller can combine a 1 or 2 byte write with a read that
 * immediately follows it by using an "INDEX" cycle.
 */
bool
gmbus_is_index_read(struct i2c_msg *msgs, int i, int num)
{
	return (i + 1 < num &&
		!(msgs[i].flags & I2C_M_RD) && msgs[i].len <= 2 &&
		(msgs[i + 1].flags & I2C_M_RD));
}

int
gmbus_xfer_index_read(struct drm_i915_private *dev_priv, struct i2c_msg *msgs)
{
	int reg_offset = dev_priv->gpio_mmio_base;
	u32 gmbus1_index = 0;
	u32 gmbus5 = 0;
	int ret;

	if (msgs[0].len == 2)
		gmbus5 = GMBUS_2BYTE_INDEX_EN |
			 msgs[0].buf[1] | (msgs[0].buf[0] << 8);
	if (msgs[0].len == 1)
		gmbus1_index = GMBUS_CYCLE_INDEX |
			       (msgs[0].buf[0] << GMBUS_SLAVE_INDEX_SHIFT);

	/* GMBUS5 holds 16-bit index */
	if (gmbus5)
		I915_WRITE(GMBUS5 + reg_offset, gmbus5);

	ret = gmbus_xfer_read(dev_priv, &msgs[1], gmbus1_index);

	/* Clear GMBUS5 after each index transfer */
	if (gmbus5)
		I915_WRITE(GMBUS5 + reg_offset, 0);

	return ret;
}

int
gmbus_xfer(struct i2c_adapter *adapter,
	   struct i2c_msg *msgs,
	   int num)
{
	struct intel_gmbus *bus = container_of(adapter,
					       struct intel_gmbus,
					       adapter);
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;
	int i, reg_offset;
	int ret = 0;
	u32 gmbus0;

	if (bus->force_bit) {
		ret = i2c_bit_algo.master_xfer(adapter, msgs, num);
		goto out;
	}

	reg_offset = dev_priv->gpio_mmio_base;

	/* Hack to use 400kHz only for touch i2c devices on ddc ports */
	gmbus0 = bus->reg0;
	if (((gmbus0 & GMBUS_PORT_MASK) == GMBUS_PORT_VGADDC &&
	     (msgs[0].addr == 0x4b || msgs[0].addr == 0x67 ||
	      msgs[0].addr == 0x25)) ||
	    ((gmbus0 & GMBUS_PORT_MASK) == GMBUS_PORT_PANEL &&
	     (msgs[0].addr == 0x4a || msgs[0].addr == 0x26))) {
		gmbus0 = (gmbus0 & ~GMBUS_RATE_MASK) | GMBUS_RATE_400KHZ;
	}
	I915_WRITE(GMBUS0 + reg_offset, gmbus0);

	for (i = 0; i < num; i++) {
		u32 gmbus2;

		if (gmbus_is_index_read(msgs, i, num)) {
			ret = gmbus_xfer_index_read(dev_priv, &msgs[i]);
			i += 1;  /* set i to the index of the read xfer */
		} else if (msgs[i].flags & I2C_M_RD) {
			ret = gmbus_xfer_read(dev_priv, &msgs[i], 0);
		} else {
			ret = gmbus_xfer_write(dev_priv, &msgs[i]);
		}

		if (ret == -ETIMEDOUT)
			goto timeout;
		if (ret == -ENXIO)
			goto clear_err;

		ret = wait_for((gmbus2 = I915_READ(GMBUS2 + reg_offset)) &
			       (GMBUS_SATOER | GMBUS_HW_WAIT_PHASE),
			       50);
		if (ret)
			goto timeout;
		if (gmbus2 & GMBUS_SATOER)
			goto clear_err;
	}

	/* Generate a STOP condition on the bus. Note that gmbus can't generata
	 * a STOP on the very first cycle. To simplify the code we
	 * unconditionally generate the STOP condition with an additional gmbus
	 * cycle. */
	I915_WRITE(GMBUS1 + reg_offset, GMBUS_CYCLE_STOP | GMBUS_SW_RDY);

	/* Mark the GMBUS interface as disabled after waiting for idle.
	 * We will re-enable it at the start of the next xfer,
	 * till then let it sleep.
	 */
	if (wait_for((I915_READ(GMBUS2 + reg_offset) & GMBUS_ACTIVE) == 0,
		     10)) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "GMBUS [%s] timed out waiting for idle\n",
			 adapter->name);
		ret = -ETIMEDOUT;
	}
	I915_WRITE(GMBUS0 + reg_offset, 0);
	ret = ret ?: i;
	goto out;

clear_err:
	/*
	 * Wait for bus to IDLE before clearing NAK.
	 * If we clear the NAK while bus is still active, then it will stay
	 * active and the next transaction may fail.
	 *
	 * If no ACK is received during the address phase of a transaction, the
	 * adapter must report -ENXIO. It is not clear what to return if no ACK
	 * is received at other times. But we have to be careful to not return
	 * spurious -ENXIO because that will prevent i2c and drm edid functions
	 * from retrying. So return -ENXIO only when gmbus properly quiescents -
	 * timing out seems to happen when there _is_ a ddc chip present, but
	 * it's slow responding and only answers on the 2nd retry.
	 */
	ret = -ENXIO;
	if (wait_for((I915_READ(GMBUS2 + reg_offset) & GMBUS_ACTIVE) == 0,
		     10)) {
		fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
		fprintf(stderr, "GMBUS [%s] timed out after NAK\n",
			      adapter->name);
		ret = -ETIMEDOUT;
	}

	/* Toggle the Software Clear Interrupt bit. This has the effect
	 * of resetting the GMBUS controller and so clearing the
	 * BUS_ERROR raised by the slave's NAK.
	 */
	I915_WRITE(GMBUS1 + reg_offset, GMBUS_SW_CLR_INT);
	I915_WRITE(GMBUS1 + reg_offset, 0);
	I915_WRITE(GMBUS0 + reg_offset, 0);

	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "GMBUS [%s] NAK for addr: %04x %c(%d)\n",
			 adapter->name, msgs[i].addr,
			 (msgs[i].flags & I2C_M_RD) ? 'r' : 'w', msgs[i].len);

	goto out;

timeout:
	fprintf(stderr, "[000000.0] [drm:%s], ", __func__);
	fprintf(stderr, "GMBUS [%s] timed out, falling back to bit banging on pin %d\n",
		 bus->adapter.name, bus->reg0 & 0xff);
	I915_WRITE(GMBUS0 + reg_offset, 0);

	/* Hardware may not support GMBUS over these pins? Try GPIO bitbanging instead. */
	bus->force_bit = true;
	ret = i2c_bit_algo.master_xfer(adapter, msgs, num);

out:
	return ret;
}

u32 gmbus_func(struct i2c_adapter *adapter)
{
	return i2c_bit_algo.functionality(adapter) &
		(I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
		/* I2C_FUNC_10BIT_ADDR | */
		I2C_FUNC_SMBUS_READ_BLOCK_DATA |
		I2C_FUNC_SMBUS_BLOCK_PROC_CALL);
}

static const struct i2c_algorithm gmbus_algorithm = {
	.master_xfer	= gmbus_xfer,
	.functionality	= gmbus_func
};

/**
 * intel_gmbus_setup - instantiate all Intel i2c GMBuses
 * @dev: DRM device
 */
int intel_setup_gmbus(struct drm_device *dev)
{
	extern struct drm_device *i915;
	struct drm_i915_private *dev_priv = i915->dev_private;
	int ret, i;

		dev_priv->gpio_mmio_base = PCH_GPIOA - GPIOA;

	for (i = 0; i < GMBUS_NUM_PORTS; i++) {
		struct intel_gmbus *bus = &dev_priv->gmbus[i];
		u32 port = i + 1; /* +1 to map gmbus index to pin pair */

		snprintf(bus->adapter.name,
			 sizeof(bus->adapter.name),
			 "i915 gmbus %s",
			 gmbus_ports[i].name);

		bus->dev_priv = dev_priv;

		bus->adapter.algo = &gmbus_algorithm;
		ret = 0;
		if (ret)
			goto err;

		/* By default use a conservative clock rate */
		bus->reg0 = port | GMBUS_RATE_100KHZ;

		intel_gpio_setup(bus, port);
	}

	intel_i2c_reset(dev_priv->dev);

	return 0;

err:
	while (--i) {
		struct intel_gmbus *bus = &dev_priv->gmbus[i];
	}
	return ret;
}

struct i2c_adapter *intel_gmbus_get_adapter(struct drm_i915_private *dev_priv,
					    unsigned port)
{
	WARN_ON(!intel_gmbus_is_port_valid(port));
	/* -1 to map pin pair to gmbus index */
	return (intel_gmbus_is_port_valid(port)) ?
		&dev_priv->gmbus[port - 1].adapter : NULL;
}

void intel_gmbus_set_speed(struct i2c_adapter *adapter, int speed)
{
	struct intel_gmbus *bus = to_intel_gmbus(adapter);

	bus->reg0 = (bus->reg0 & ~(0x3 << 8)) | speed;
}

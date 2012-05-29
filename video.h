/* cocci issues ;-( */
#ifndef VIDEO_H
#define VIDEO_H 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#include <pci/pci.h>
#include <sys/io.h>
#include <sys/time.h>
#include <linux/types.h>
#include <errno.h>

/* constants from coreboot */
/* Chipset types */
#define SANDYBRIDGE_MOBILE	0
#define SANDYBRIDGE_DESKTOP	1
#define SANDYBRIDGE_SERVER	2

/* Device ID for SandyBridge and IvyBridge */
#define BASE_REV_SNB	0x00
#define BASE_REV_IVB	0x50
#define BASE_REV_MASK	0x50

/* SandyBridge CPU stepping */
#define SNB_STEP_D0	(BASE_REV_SNB + 5) /* Also J0 */
#define SNB_STEP_D1	(BASE_REV_SNB + 6)
#define SNB_STEP_D2	(BASE_REV_SNB + 7) /* Also J1/Q0 */

/* IvyBridge CPU stepping */
#define IVB_STEP_A0	(BASE_REV_IVB + 0)
#define IVB_STEP_B0	(BASE_REV_IVB + 2)
#define IVB_STEP_C0	(BASE_REV_IVB + 4)
#define IVB_STEP_K0	(BASE_REV_IVB + 5)
#define IVB_STEP_D0	(BASE_REV_IVB + 6)

/* something we're not ready to totally remove yet */
#define BUG_ON(x) assert(!(x))

enum {
	DUMP_PREFIX_OFFSET, 
	DUMP_PREFIX_ADDRESS, 
	DUMP_PREFIX_NONE
};

/* stuff we can't get coccinelle to do yet */
#define __iomem
#define __read_mostly
#define __always_unused
#define module_param_named(a, b, c, d)
#define MODULE_PARM_DESC(a, b)
#define module_param(a, b, c)
#define DRM_DEBUG_KMS printf
#define CONFIG_DRM_I915_KMS 1
#define module_init(x);
#define module_exit(x);
#define le16_to_cpu(x)  le16toh((x))
#define cpu_to_le16(x)  htole16((x))

#define MODULE_AUTHOR(x)
#define MODULE_DESCRIPTION(x)
#define MODULE_LICENSE(a)
#define MODULE_DEVICE_TABLE(a, b)
struct drm_file {};

/* constants that will never change from linux/vga.h */
/* Legacy VGA regions */
#define VGA_RSRC_NONE          0x00
#define VGA_RSRC_LEGACY_IO     0x01
#define VGA_RSRC_LEGACY_MEM    0x02
#define VGA_RSRC_LEGACY_MASK   (VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM)
/* Non-legacy access */
#define VGA_RSRC_NORMAL_IO     0x04
#define VGA_RSRC_NORMAL_MEM    0x08


/* defined in pci.h! */
#include <pci/pci.h>
/* idiocy. how many names to we need for a type? */
typedef u8 uint8_t;
typedef u16 uint16_t;
typedef u32 uint32_t;
typedef u64 uint64_t;
typedef long long s64;
typedef u32 resource_size_t;
/* WTF */
typedef int bool;
enum {false = 0, true};

/* we don't want the complex one */
struct idr {
	int val;
};

struct list_head {
	struct list_head *next, *prev;
};
#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
        list->next = list;
        list->prev = list;
}

#define list_first_entry(ptr, type, member) \
        list_entry((ptr)->next, type, member)
#define list_entry(ptr, type, member) \
        container_of(ptr, type, member)
/* and other kernel stuff wrapped heavily in ifdefs */
#define PAGE_SIZE 4096
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, typeof(*pos), member))
#define list_for_each_entry_safe(a,ignore, b,c) list_for_each_entry(a,b,c)

static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
#ifndef CONFIG_DEBUG_LIST
static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}
#else
extern void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next);
#endif

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}


/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

/* we're going to have to have a hook for this somehow. It will vary between 
 * user mode and coreboot
 */
struct i2c_algorithm;
struct i2c_adapter;
struct i2c_msg;
union i2c_smbus_data;

struct i2c_algorithm {
	/* If an adapter algorithm can't do I2C-level access, set master_xfer
	   to NULL. If an adapter algorithm can do SMBus access, set
	   smbus_xfer. If set to NULL, the SMBus protocol is simulated
	   using common I2C messages */
	/* master_xfer should return the number of messages successfully
	   processed, or a negative value on error */
	int (*master_xfer)(struct i2c_adapter *adap, struct i2c_msg *msgs,
			   int num);
	int (*smbus_xfer) (struct i2c_adapter *adap, u16 addr,
			   unsigned short flags, char read_write,
			   u8 command, int size, union i2c_smbus_data *data);

	/* To determine what the adapter supports */
	u32 (*functionality) (struct i2c_adapter *);
};

struct i2c_adapter {
	unsigned int class;		  /* classes to allow probing for */
	const struct i2c_algorithm *algo; /* the algorithm to access the bus */
	void *algo_data;

	int timeout;			/* in jiffies */
	int retries;

	int nr;
	char name[48];
};
/**
 * struct i2c_msg - an I2C transaction segment beginning with START
 * @addr: Slave address, either seven or ten bits.  When this is a ten
 *	bit address, I2C_M_TEN must be set in @flags and the adapter
 *	must support I2C_FUNC_10BIT_ADDR.
 * @flags: I2C_M_RD is handled by all adapters.  No other flags may be
 *	provided unless the adapter exported the relevant I2C_FUNC_*
 *	flags through i2c_check_functionality().
 * @len: Number of data bytes in @buf being read from or written to the
 *	I2C slave address.  For read transactions where I2C_M_RECV_LEN
 *	is set, the caller guarantees that this buffer can hold up to
 *	32 bytes in addition to the initial length byte sent by the
 *	slave (plus, if used, the SMBus PEC); and this value will be
 *	incremented by the number of block data bytes received.
 * @buf: The buffer into which data is read, or from which it's written.
 *
 * An i2c_msg is the low level representation of one segment of an I2C
 * transaction.  It is visible to drivers in the @i2c_transfer() procedure,
 * to userspace from i2c-dev, and to I2C adapter drivers through the
 * @i2c_adapter.@master_xfer() method.
 *
 * Except when I2C "protocol mangling" is used, all I2C adapters implement
 * the standard rules for I2C transactions.  Each transaction begins with a
 * START.  That is followed by the slave address, and a bit encoding read
 * versus write.  Then follow all the data bytes, possibly including a byte
 * with SMBus PEC.  The transfer terminates with a NAK, or when all those
 * bytes have been transferred and ACKed.  If this is the last message in a
 * group, it is followed by a STOP.  Otherwise it is followed by the next
 * @i2c_msg transaction segment, beginning with a (repeated) START.
 *
 * Alternatively, when the adapter supports I2C_FUNC_PROTOCOL_MANGLING then
 * passing certain @flags may have changed those standard protocol behaviors.
 * Those flags are only for use with broken/nonconforming slaves, and with
 * adapters which are known to support the specific mangling options they
 * need (one or more of IGNORE_NAK, NO_RD_ACK, NOSTART, and REV_DIR_ADDR).
 */
struct i2c_msg {
	__u16 addr;	/* slave address			*/
	__u16 flags;
#define I2C_M_TEN		0x0010	/* this is a ten bit chip address */
#define I2C_M_RD		0x0001	/* read data, from slave to master */
#define I2C_M_NOSTART		0x4000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_REV_DIR_ADDR	0x2000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK	0x1000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NO_RD_ACK		0x0800	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_RECV_LEN		0x0400	/* length will be first received byte */
	__u16 len;		/* msg length				*/
	__u8 *buf;		/* pointer to msg data			*/
};

/* To determine what functionality is present */

#define I2C_FUNC_I2C			0x00000001
#define I2C_FUNC_10BIT_ADDR		0x00000002
#define I2C_FUNC_PROTOCOL_MANGLING	0x00000004 /* I2C_M_NOSTART etc. */
#define I2C_FUNC_SMBUS_PEC		0x00000008
#define I2C_FUNC_SMBUS_BLOCK_PROC_CALL	0x00008000 /* SMBus 2.0 */
#define I2C_FUNC_SMBUS_QUICK		0x00010000
#define I2C_FUNC_SMBUS_READ_BYTE	0x00020000
#define I2C_FUNC_SMBUS_WRITE_BYTE	0x00040000
#define I2C_FUNC_SMBUS_READ_BYTE_DATA	0x00080000
#define I2C_FUNC_SMBUS_WRITE_BYTE_DATA	0x00100000
#define I2C_FUNC_SMBUS_READ_WORD_DATA	0x00200000
#define I2C_FUNC_SMBUS_WRITE_WORD_DATA	0x00400000
#define I2C_FUNC_SMBUS_PROC_CALL	0x00800000
#define I2C_FUNC_SMBUS_READ_BLOCK_DATA	0x01000000
#define I2C_FUNC_SMBUS_WRITE_BLOCK_DATA 0x02000000
#define I2C_FUNC_SMBUS_READ_I2C_BLOCK	0x04000000 /* I2C-like block xfer  */
#define I2C_FUNC_SMBUS_WRITE_I2C_BLOCK	0x08000000 /* w/ 1-byte reg. addr. */

#define I2C_FUNC_SMBUS_BYTE		(I2C_FUNC_SMBUS_READ_BYTE | \
					 I2C_FUNC_SMBUS_WRITE_BYTE)
#define I2C_FUNC_SMBUS_BYTE_DATA	(I2C_FUNC_SMBUS_READ_BYTE_DATA | \
					 I2C_FUNC_SMBUS_WRITE_BYTE_DATA)
#define I2C_FUNC_SMBUS_WORD_DATA	(I2C_FUNC_SMBUS_READ_WORD_DATA | \
					 I2C_FUNC_SMBUS_WRITE_WORD_DATA)
#define I2C_FUNC_SMBUS_BLOCK_DATA	(I2C_FUNC_SMBUS_READ_BLOCK_DATA | \
					 I2C_FUNC_SMBUS_WRITE_BLOCK_DATA)
#define I2C_FUNC_SMBUS_I2C_BLOCK	(I2C_FUNC_SMBUS_READ_I2C_BLOCK | \
					 I2C_FUNC_SMBUS_WRITE_I2C_BLOCK)

#define I2C_FUNC_SMBUS_EMUL		(I2C_FUNC_SMBUS_QUICK | \
					 I2C_FUNC_SMBUS_BYTE | \
					 I2C_FUNC_SMBUS_BYTE_DATA | \
					 I2C_FUNC_SMBUS_WORD_DATA | \
					 I2C_FUNC_SMBUS_PROC_CALL | \
					 I2C_FUNC_SMBUS_WRITE_BLOCK_DATA | \
					 I2C_FUNC_SMBUS_I2C_BLOCK | \
					 I2C_FUNC_SMBUS_PEC)

/*
 * Data for SMBus Messages
 */
#define I2C_SMBUS_BLOCK_MAX	32	/* As specified in SMBus standard */
union i2c_smbus_data {
	__u8 byte;
	__u16 word;
	__u8 block[I2C_SMBUS_BLOCK_MAX + 2]; /* block[0] is used for length */
			       /* and one more for user-space compatibility */
};

/* i2c_smbus_xfer read or write markers */
#define I2C_SMBUS_READ	1
#define I2C_SMBUS_WRITE	0

/* SMBus transaction types (size parameter in the above functions)
   Note: these no longer correspond to the (arbitrary) PIIX4 internal codes! */
#define I2C_SMBUS_QUICK		    0
#define I2C_SMBUS_BYTE		    1
#define I2C_SMBUS_BYTE_DATA	    2
#define I2C_SMBUS_WORD_DATA	    3
#define I2C_SMBUS_PROC_CALL	    4
#define I2C_SMBUS_BLOCK_DATA	    5
#define I2C_SMBUS_I2C_BLOCK_BROKEN  6
#define I2C_SMBUS_BLOCK_PROC_CALL   7		/* SMBus 2.0 */
#define I2C_SMBUS_I2C_BLOCK_DATA    8

/* we define our own. The kernel one is too full of stuff. */
struct drm_i915_gem_object {
	signed int fence_reg : 5;
	uint32_t gtt_offset;
	unsigned int tiling_mode : 2;
};

#include "final/drm_mode.h"
#include "final/drm_edid.h"
#include "final/drm_crtc.h"

/* For now, we define a shim layer of drm devices. The long term 
 * goal is to use coccinelle to gather up all this crap into 
 * one struct because we don't need this layer of indirection. 
 * but we need to optimize this process for automated translation
 * and it may turn out we want this layer. Anyway, one war at a time
 */
struct drm_device {
	struct pci_dev *pdev;
	u8 *bios_bin;
	struct drm_i915_private *dev_private;
	struct drm_mode_config mode_config;
	int vblank_disable_allowed;
};


/* we're willing to define our own here because it's relatively unchanging */
#define PCI_ANY_ID (~0)

struct pci_device_id {
        u32 vendor, device;           /* Vendor and device ID or PCI_ANY_ID*/
        u32 subvendor, subdevice;     /* Subsystem ID's or PCI_ANY_ID */
        u32 class, class_mask;        /* (class,subclass,prog-if) triplet */
        unsigned long driver_data;     /* Data private to the driver  -- fix with coccinelle at some point*/
};

/* random crap from kernel.h. Kernel.h is a catch-all for all kinds of junk and it's 
 * not worth using coccinelle (yet) to pull it apart. Maybe later. 
 * And, yes, gcc still does not have nelem!
 */
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0])) 
#define __ALIGN_KERNEL(x, a)		__ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#define __ALIGN_KERNEL_MASK(x, mask)	(((x) + (mask)) & ~(mask))
#define ALIGN(x, a)		__ALIGN_KERNEL((x), (a))
#define __ALIGN_MASK(x, mask)	__ALIGN_KERNEL_MASK((x), (mask))
#define PTR_ALIGN(p, a)		((typeof(p))ALIGN((unsigned long)(p), (a)))
#define IS_ALIGNED(x, a)		(((x) & ((typeof(x))(a) - 1)) == 0)
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define KERN_WARNING "warning: "
#define KERN_ERR "Error: "
#define DUMP_PREFIX_NONE ""

/* err.h, which we can't include in coreboot anyway */
#define IS_ERR_VALUE(x) ((x) >= (unsigned long)-4096)

static inline void * ERR_PTR(long error)
{
        return (void *) error;
}

static inline long PTR_ERR(const void *ptr)
{
        return (long) ptr;
}

static inline long IS_ERR(const void *ptr)
{
        return IS_ERR_VALUE((unsigned long)ptr);
}



/* coccinelle can't get this yet. */
#define uninitialized_var(x) x
/*
 * ..and if you can't take the strict
 * types, you can specify one yourself.
 *
 * Or not use min/max/clamp at all, of course.
 */
#define min_t(type, x, y) ({			\
	type __min1 = (x);			\
	type __min2 = (y);			\
	__min1 < __min2 ? __min1: __min2; })

#define max_t(type, x, y) ({			\
	type __max1 = (x);			\
	type __max2 = (y);			\
	__max1 > __max2 ? __max1: __max2; })


/* we're not sure what to do about time yet. So we turn it all into milliseconds. */
#define usecs_to_jiffies(x) ((x)/1000)

/* the EXPORT_SYMBOL syntax is invalid C, hence coccinelle can't parse it. Just rename the macro */
#define EXPORT_SYMBOL(x) 

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})


/* temporary. */
void *dmi_check_system(unsigned long);

#include "final/i915_reg.h"
#include "final/i915_drv.h"
#include "final/drm_dp_helper.h"
#include "final/drm_crtc_helper.h"
#include "final/drm_mode.h"
#include "final/drm_crtc.h"
#include "final/intel_drv.h"
#include "final/i2c-algo-bit.h"
/* another coccinelle issue :-( */
static int i2c_add_adapter(struct i2c_adapter *u) { return 0;}

#include "final/drm_edid_modes.h"
/* yuck */
#define I915_READ_NOTRACE(x) I915_READ((x))
#define I915_READ16_NOTRACE(x) I915_READ16((x))
#define I915_WRITE_NOTRACE(x, y) I915_WRITE((x), (y))

unsigned long msecs(void);
void mdelay(unsigned long ms);
void *pci_iomap(struct pci_dev *dev, int bar, unsigned long max);
struct pci_dev *pci_get_bus_and_slot(u16 bus, u16 devfn);
struct pci_dev *pci_get_class(u32 class, void *unused);

void *pci_map_rom(struct pci_dev *dev, size_t *size);
void *pci_unmap_rom(struct pci_dev *dev, void *p);
extern unsigned int i915_lvds_downclock;
extern int i915_vbt_sdvo_panel_type;
unsigned long lvds_do_not_use_alternate_frequency;
extern int i915_panel_ignore_lid;

/* common.c */
void BUG(void);
void getrawmonotonic(struct timespec *t);
void idr_init(void *v);
int idr_pre_get(void *x);
int idr_get_new_above(void *v, void *o, int unused, int *new_id);
unsigned long io_I915_READ(unsigned long addr);
void io_I915_WRITE(unsigned long addr, unsigned long val);
unsigned long msecs(void);
void mdelay(unsigned long ms);
void udelay(int i);
unsigned long I915_READ(unsigned long addr);
void I915_WRITE(unsigned long addr, unsigned long val);
void *pci_unmap_rom(struct pci_dev *dev, void *bios);
void *dmi_check_system(unsigned long ignore);
void *mapit(u32 phys, u32 size);
void devinit(void);
void init(int *argc, char ***argv);
void dumpeld(char *name, u8 *eld);
void dumpmodeconfig(void);
void *allocz(int size);
void freez(void *p);
#endif /* VIDEO_H */

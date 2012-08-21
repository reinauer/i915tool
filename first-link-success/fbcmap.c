

static u16 red2[] __read_mostly = {
    0x0000, 0xaaaa
};
static u16 green2[] __read_mostly = {
    0x0000, 0xaaaa
};
static u16 blue2[] __read_mostly = {
    0x0000, 0xaaaa
};

static u16 red4[] __read_mostly = {
    0x0000, 0xaaaa, 0x5555, 0xffff
};
static u16 green4[] __read_mostly = {
    0x0000, 0xaaaa, 0x5555, 0xffff
};
static u16 blue4[] __read_mostly = {
    0x0000, 0xaaaa, 0x5555, 0xffff
};

static u16 red8[] __read_mostly = {
    0x0000, 0x0000, 0x0000, 0x0000, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa
};
static u16 green8[] __read_mostly = {
    0x0000, 0x0000, 0xaaaa, 0xaaaa, 0x0000, 0x0000, 0x5555, 0xaaaa
};
static u16 blue8[] __read_mostly = {
    0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa
};

static u16 red16[] __read_mostly = {
    0x0000, 0x0000, 0x0000, 0x0000, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa,
    0x5555, 0x5555, 0x5555, 0x5555, 0xffff, 0xffff, 0xffff, 0xffff
};
static u16 green16[] __read_mostly = {
    0x0000, 0x0000, 0xaaaa, 0xaaaa, 0x0000, 0x0000, 0x5555, 0xaaaa,
    0x5555, 0x5555, 0xffff, 0xffff, 0x5555, 0x5555, 0xffff, 0xffff
};
static u16 blue16[] __read_mostly = {
    0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa,
    0x5555, 0xffff, 0x5555, 0xffff, 0x5555, 0xffff, 0x5555, 0xffff
};

static  struct fb_cmap default_2_colors = {
    .len=2, .red=red2, .green=green2, .blue=blue2
};
static  struct fb_cmap default_8_colors = {
    .len=8, .red=red8, .green=green8, .blue=blue8
};
static  struct fb_cmap default_4_colors = {
    .len=4, .red=red4, .green=green4, .blue=blue4
};
static  struct fb_cmap default_16_colors = {
    .len=16, .red=red16, .green=green16, .blue=blue16
};



/**
 *	fb_alloc_cmap - allocate a colormap
 *	@cmap: frame buffer colormap structure
 *	@len: length of @cmap
 *	@transp: boolean, 1 if there is transparency, 0 otherwise
 *	@flags: flags for kmalloc memory allocation
 *
 *	Allocates memory for a colormap @cmap.  @len is the
 *	number of entries in the palette.
 *
 *	Returns negative errno on error, or zero on success.
 *
 */

int fb_alloc_cmap_gfp(struct fb_cmap *cmap, int len, int transp, gfp_t flags)
{
	int size = len * sizeof(u16);
	int ret = -ENOMEM;

	if (cmap->len != len) {
		fb_dealloc_cmap(cmap);
		if (!len)
			return 0;

		cmap->red = malloc(size);
		if (!cmap->red)
			goto fail;
		cmap->green = malloc(size);
		if (!cmap->green)
			goto fail;
		cmap->blue = malloc(size);
		if (!cmap->blue)
			goto fail;
		if (transp) {
			cmap->transp = malloc(size);
			if (!cmap->transp)
				goto fail;
		} else {
			cmap->transp = NULL;
		}
	}
	cmap->start = 0;
	cmap->len = len;
	ret = fb_copy_cmap(fb_default_cmap(len), cmap);
	if (ret)
		goto fail;
	return 0;

fail:
	fb_dealloc_cmap(cmap);
	return ret;
}

int fb_alloc_cmap(struct fb_cmap *cmap, int len, int transp)
{
	return fb_alloc_cmap_gfp(cmap, len, transp, GFP_ATOMIC);
}

/**
 *      fb_dealloc_cmap - deallocate a colormap
 *      @cmap: frame buffer colormap structure
 *
 *      Deallocates a colormap that was previously allocated with
 *      fb_alloc_cmap().
 *
 */

void fb_dealloc_cmap(struct fb_cmap *cmap)
{
	freez(cmap->red);
	freez(cmap->green);
	freez(cmap->blue);
	freez(cmap->transp);

	cmap->red = cmap->green = cmap->blue = cmap->transp = NULL;
	cmap->len = 0;
}

/**
 *	fb_copy_cmap - copy a colormap
 *	@from: frame buffer colormap structure
 *	@to: frame buffer colormap structure
 *
 *	Copy contents of colormap from @from to @to.
 */

int fb_copy_cmap( struct fb_cmap *from, struct fb_cmap *to)
{
	int tooff = 0, fromoff = 0;
	int size;

	if (to->start > from->start)
		fromoff = to->start - from->start;
	else
		tooff = from->start - to->start;
	size = to->len - tooff;
	if (size > (int) (from->len - fromoff))
		size = from->len - fromoff;
	if (size <= 0)
		return -EINVAL;
	size *= sizeof(u16);

	memcpy(to->red+tooff, from->red+fromoff, size);
	memcpy(to->green+tooff, from->green+fromoff, size);
	memcpy(to->blue+tooff, from->blue+fromoff, size);
	if (from->transp && to->transp)
		memcpy(to->transp+tooff, from->transp+fromoff, size);
	return 0;
}

/**
 *	fb_set_cmap - set the colormap
 *	@cmap: frame buffer colormap structure
 *	@info: frame buffer info structure
 *
 *	Sets the colormap @cmap for a screen of device @info.
 *
 *	Returns negative errno on error, or zero on success.
 *
 */

int fb_set_cmap(struct fb_cmap *cmap, struct fb_info *info)
{
	int i, start, rc = 0;
	u16 *red, *green, *blue, *transp;
	u_int hred, hgreen, hblue, htransp = 0xffff;

	red = cmap->red;
	green = cmap->green;
	blue = cmap->blue;
	transp = cmap->transp;
	start = cmap->start;

	if (start < 0 || (!info->fbops->fb_setcolreg &&
			  !info->fbops->fb_setcmap))
		return -EINVAL;
	if (info->fbops->fb_setcmap) {
		rc = info->fbops->fb_setcmap(cmap, info);
	} else {
		for (i = 0; i < cmap->len; i++) {
			hred = *red++;
			hgreen = *green++;
			hblue = *blue++;
			if (transp)
				htransp = *transp++;
			if (info->fbops->fb_setcolreg(start++,
						      hred, hgreen, hblue,
						      htransp, info))
				break;
		}
	}
	if (rc == 0)
		fb_copy_cmap(cmap, &info->cmap);

	return rc;
}

/**
 *	fb_default_cmap - get default colormap
 *	@len: size of palette for a depth
 *
 *	Gets the default colormap for a specific screen depth.  @len
 *	is the size of the palette for a particular screen depth.
 *
 *	Returns pointer to a frame buffer colormap structure.
 *
 */

 struct fb_cmap *fb_default_cmap(int len)
{
    if (len <= 2)
	return &default_2_colors;
    if (len <= 4)
	return &default_4_colors;
    if (len <= 8)
	return &default_8_colors;
    return &default_16_colors;
}


    /*
     *  Visible symbols for modules
     */

EXPORT_SYMBOL(fb_alloc_cmap);
EXPORT_SYMBOL(fb_dealloc_cmap);
EXPORT_SYMBOL(fb_copy_cmap);
EXPORT_SYMBOL(fb_set_cmap);
EXPORT_SYMBOL(fb_default_cmap);
EXPORT_SYMBOL(fb_invert_cmaps);

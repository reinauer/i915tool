/* variables comon to all tools. 
 */
bool intel_choose_pipe_bpp_dither(struct drm_crtc *crtc,
					 unsigned int *pipe_bpp)
{

	fprintf(stderr, "(HARD-WIRED: setting pipe bpc to %d (max display bpc %d)\n",
			 6, 6);

	*pipe_bpp = 6 * 3;

	return 1;
}

void BUG(void)
{
	fprintf(stderr, "BUG!\n");
}

void
getrawmonotonic(struct timespec *t)
{
	clock_getres(CLOCK_MONOTONIC, t);
}

/* for now ... we'll keep it simple */
/* I'm almost certain we don't need these IDs but we'll see */
static int idr = 1;

void
idr_init(void *v)
{
}

int
idr_pre_get(void *x, int level)
{
	return 1;
}

int
idr_get_new_above(void *v, void *o, int unused, int *new_id)
{
	*new_id = idr++;
}

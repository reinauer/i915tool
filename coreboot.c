#include "video.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

extern int verbose;
extern int gencode;
extern struct drm_device *i915;
int cangencode = 0;

#include "generated.c"
int main(int argc, char *argv[])
{
	unsigned long long start, end;
	unsigned long usec;
	bool drm_crtc_helper_set_mode(struct drm_crtc *crtc,
                              struct drm_display_mode *mode,
                              int x, int y,
                              struct drm_framebuffer *old_fb);
	int lvds = 0;
	struct drm_encoder *encoder;
	struct intel_connector *ic;
	struct drm_i915_private *dp;
	struct drm_connector *connector = NULL;
	struct drm_display_mode *mode = NULL;
	int level = 0;
	struct intel_load_detect_pipe pipe;
	char *cmd;
	void geneld(char *, u8 *);
	gf = stdout;
	init(&argc, &argv);
	unsigned long *plp = malloc(gfxsize);
	printf("known to work: m,c,p,f, then d0 \n");
	while ((cmd = readline(">")) != NULL){
		start = rdtsc();
		switch(cmd[0]) {
		case 'd':
			intel_dp_prepare(&encoder);
			//intel_crtc_mode_set (&crtc, &crtc.mode, &crtc.hwmode,
				//0, 0, NULL);
			break;
		case 'v':
			verbose = strtoul(&cmd[1], 0, 0);
			break;
		case 'R':
			/* fill red but only use one page */
		{
			volatile unsigned long *lp = (unsigned long *)gfx;
			int i;
			setgtt(gsmgfx, 0);
			for(i = 0; i < 1024; i++)
				lp[i] = 0xff0000;
		}
		break;
		case 'G':
		{
			volatile unsigned long *lp = (unsigned long *)gfx;
			int i;
			setgtt(gsmgfx, 4096);
			for(i = 0; i < gfxsize; i++)
				lp[i] = 0x00ff00;
		}
		break;
		case 'B':
		{
			int i;
			setgtt(0x80000000, 4096);
			for(i = 0; i < gfxsize; i++)
				plp[i] = 0x00ff;
		}
		break;
			
			
		default: 
			fprintf(stderr, "This program sucks too much to tell you the commands you can do\n");
			break;
			
			}
		end = rdtsc();
		usec = microseconds(start, end);
		fprintf(stderr, "Command took %ld microseconds\n", usec);
		}
}

#include "video.h"
int cangencode = 0;
unsigned long gttarray[16384];

int main(int argc, char *argv[])
{
	int i;
	int num = 16380;
	unsigned long long start, end;
	struct timeval mstart, mend;

	init(&argc, &argv);

	start = rdtsc();
	for(gettimeofday(&mstart,NULL), gettimeofday(&mend, NULL); 
		((mend.tv_sec - mstart.tv_sec) + 
		(mend.tv_usec - mstart.tv_usec)/1000000) < 64; 
		
		gettimeofday(&mend, NULL))
		;
	end = rdtsc();
	printf("ticks per 60 seconds is %lld\n", (end - start)/64);

	for(i = 0, start = rdtsc(); i < num; i ++){
		io_I915_WRITE32(i|1,0);
	}
	end = rdtsc();
	printf("IO took %lld ticks\n", end - start);
	for(i = 0, start = rdtsc(); i < num; i ++){
		gttarray[i] = &gttarray[i];
	}
	end = rdtsc();
	printf("Memory took %lld ticks\n", end - start);
}

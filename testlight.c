int cangencode = 0;
int main(int argc, char *argv[])
{
	u32 c;
	u32 max;
	init(&argc, &argv);
	devinit();

	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0x0
#if 0
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0x0
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0x0
#endif
	I915_WRITE(PCH_PP_CONTROL /*0xc7204*/, 0xabcd0008);
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
#if 0
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
#endif
	max = I915_READ(BLC_PWM_CPU_CTL /*0x48254*/);// returns 0x10ce
#if 0
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	I915_WRITE(PCH_PP_CONTROL /*0xc7204*/, 0xabcd0008);
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	I915_WRITE(PCH_PP_CONTROL /*0xc7204*/, 0xabcd0008);
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0008
#endif
	I915_WRITE(PCH_PP_CONTROL /*0xc7204*/, 0xabcd000b);
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd000b
#if 0
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd000b
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd000b
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd000b
#endif
	I915_WRITE(PCH_PP_CONTROL /*0xc7204*/, 0xabcd0003);
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0003
#if 0
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0003
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0003
#endif
	I915_WRITE(PCH_PP_CONTROL /*0xc7204*/, 0xabcd0007);
	c = I915_READ(PCH_PP_CONTROL /*0xc7204*/);// returns 0xabcd0007
	c = I915_READ(BLC_PWM_CPU_CTL /*0x48254*/);// returns 0x10ce
	I915_WRITE(BLC_PWM_CPU_CTL /*0x48254*/, 0x10ce);
	c = I915_READ(BLC_PWM_CPU_CTL /*0x48254*/);// returns 0x10ce
	I915_WRITE(BLC_PWM_CPU_CTL /*0x48254*/, max);
}

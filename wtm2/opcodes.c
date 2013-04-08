/* things that are, strangely, not defined anywhere? */
#define PCH_PP_UNLOCK 0xabcd0000
#define WMx_LP_SR_EN (1<<31)

enum {
  Rb,
  Rw,
  Rl,
  Wb,
  Ww,
  Wl,
  RPC,
  WPC,
  P,
  I,
  V,
  M,
  /* Graphics, i.e. using indirection registers */
  GWl,
  GRl,
};
const char *opnames[] = {
  [M] "M",
  [Rb] "Rb",
  [Rw] "Rw",
  [Rl] "Rl",
  [Wb] "Wb",
  [Ww] "Ww",
  [Wl] "Wl",
  [GWl] "GWl",
  [GRl] "GRl",
  [RPC] "RPC",
  [WPC] "WPC",
  [V] "V",
  [P] "P",
  [I] "I",
};

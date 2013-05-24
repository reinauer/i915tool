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

#define I2C_M_TEN		0x0010	/* this is a ten bit chip address */
#define I2C_M_RD		0x0001	/* read data, from slave to master */
#define I2C_M_NOSTART		0x4000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_REV_DIR_ADDR	0x2000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK	0x1000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NO_RD_ACK		0x0800	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_RECV_LEN		0x0400	/* length will be first received byte */

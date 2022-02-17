#include "spi_common.h"

#define ORM_CONSTANT0        (0x102) // constant0[15:0] // 0xDEAD
#define ORM_CONSTANT1        (0x103) // constant1[15:0] // 0xBEEF
#define ORM_DUMMY_REG0       (0x104) // dummy_reg0[15:0] // writable, but does nothing
#define ORM_DUMMY_REG1       (0x105) // dummy_reg1[15:0] // writable, but does nothing

int ORM_get_constant0(void);
int ORM_get_constant1(void);
int ORM_put_constant0(int value16bits);
int ORM_get_dummy0(void);
int ORM_put_dummy0(int value16bits);
int ORM_get_dummy1(void);
int ORM_put_dummy1(int value16bits);

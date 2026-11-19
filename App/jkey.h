#ifndef __JKEY_H__
#define __JKEY_H__

#include "system.h"
#include "stm32f10x.h"
#include "systick.h"

#define H1 PCout(4)
#define H2 PCout(5)
#define H3 PCout(6)
#define H4 PCout(7)
#define L1 PCin(3)
#define L2 PCin(2)
#define L3 PCin(1)
#define L4 PCin(0)

void jkey_init(void);
u8 jkey_scan(void);


#endif
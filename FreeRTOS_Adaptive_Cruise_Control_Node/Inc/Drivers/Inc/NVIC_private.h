/****************************
 *  NVIC_PRIVATE.h          *
 *  Created on: FEB 7, 2023 *
 *  Author: MANAR EMAD      *
 ****************************/

#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

#define NVIC_BASE_ADDR   (u32)(0xE000E100)
#define SCB_BASE_ADDR    (u32)(0xE000ED00)

/* NVIC register map */
typedef struct
{
	u32  ISER[32];
	u32  ICER[32];
	u32  ISPR[32];
	u32  ICPR[32];
	u32  IAPR[32];
	u32  Reserved[32];
	u8   IPR[128];

}NVIC_MemMap_t;

#define NVIC      ((volatile NVIC_MemMap_t*)(NVIC_BASE_ADDR))

typedef struct
{

    u32 CPUID;
    u32 ICSR;
    u32 VTOR;
    u32 AIRCR;
    u32 SCR;
    u32 CCR;
    u32 SHPR1;
    u32 SHPR2;
    u32 SHPR3;
    u32 SHCSR;
    u32 CFSR;
    u32 HFSR;
    u32 RESERVED;
    u32 MMAR;
    u32 BFAR;
	u32 AFSR;

} SCB_MemMap_t;

#define SCB ((volatile SCB_MemMap_t*)(SCB_BASE_ADDR))

#endif  /* NVIC_PRIVATE_H_ */

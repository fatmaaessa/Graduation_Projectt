/*********************************************/
/*********************************************/
/*********  Author: FatmaEssa        *********/
/*********  Layer: MCAL              *********/
/*********  SWC: SPI_private         *********/
/*********  Version: 1.00            *********/
/*********************************************/

#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#define SPI1_BASE_ADD   (u32)(0x40013000)


typedef struct
{
	volatile    u32 CR1;
	//volatile 	u16 Reserved1;
	volatile 	u32 CR2;
	//volatile 	u16 Reserved2;
	volatile 	u32 SR;
	//volatile 	u16 Reserved3;
	volatile 	u32 DR;
	//volatile 	u16 Reserved4;
	volatile 	u32 CRCPR;
	//volatile 	u16 Reserved5;
	volatile 	u32 RXCRCR;
	//volatile 	u16 Reserved6;
	volatile 	u32 TXCRCR;
	//volatile 	u16 Reserved7;
	volatile 	u32 I2SCFGR;
	//volatile 	u16 Reserved8;
	volatile 	u32 I2SPR;

}SPI1_RegMap_t;

#define SPI1 ((volatile SPI1_RegMap_t*)(SPI1_BASE_ADD ))



#define  SPI_CHPA                   0
#define  SPI_CPOL                   1
#define  SPI_MSTR                   2
#define  SPI_BR0                    3
#define  SPI_BR1                    4
#define  SPI_BR2                    5
#define  SPI_SPE                    6
#define  SPI_LSBFIRST               7
#define  SPI_SSI                    8
#define  SPI_SSM                    9
#define  RXONLY                     10
#define  SPI_DFF                    11

#define  SPI1_TXEIE                 7
#define  SPI1_RXNEIE                6


#define  SPI_BSY                    7

#endif

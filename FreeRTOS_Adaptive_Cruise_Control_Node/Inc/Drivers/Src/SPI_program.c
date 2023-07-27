/*********************************************/
/*********************************************/
/*********  Author: FatmaEssa        *********/
/*********  Layer: MCAL              *********/
/*********  SWC: SPI _programme      *********/
/*********  Version: 1.00            *********/
/*********************************************/
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../Inc/GPIO_interface.h"

#include "../Inc/SPI_interface.h"
#include "../Inc/SPI_private.h"
#include "../Inc/SPI_config.h"


void (*MSPI1_CallBack) (void);

void SPI_voidInit ( void ){

#if		SPI1_CLOCK_MODE == SPI_MODE0

	CLR_BIT( SPI1 -> CR1 , SPI_CHPA );
	CLR_BIT( SPI1 -> CR1 , SPI_CPOL );

#elif	SPI1_CLOCK_MODE == SPI_MODE1

	SET_BIT( SPI1 -> CR1 , SPI_CHPA ); 
	CLR_BIT( SPI1 -> CR1 , SPI_CPOL );

#elif	SPI1_CLOCK_MODE == SPI_MODE2

	CLR_BIT( SPI1 -> CR1 , SPI_CHPA ); 
	SET_BIT( SPI1 -> CR1 , SPI_CPOL );

#elif	SPI1_CLOCK_MODE == SPI_MODE3

	SET_BIT( SPI1 -> CR1 , SPI_CHPA ); 
	SET_BIT( SPI1 -> CR1 , SPI_CPOL );

#endif

#if    SPI1_MASTER_SLAVE == SPI1_MASTER

	SET_BIT( SPI1 -> CR1 , SPI_MSTR );

#elif  SPI1_MASTER_SLAVE == SPI1_SLAVE

	CLR_BIT( SPI1 -> CR1 , SPI_MSTR );

#endif

#if    SPI1_PRESCALLER == SPI_FPCLK_DIVIDED_BY_4

	SPI1 -> CR1 &= 0xFFC7 ;
	SPI1 -> CR1 |= ( SPI1_PRESCALLER << 3 ) ;
#endif

#if  SPI1_DATA_ORDER == SPI1_MSB_FIRST

	CLR_BIT( SPI1 -> CR1 , SPI_LSBFIRST );

#elif SPI1_DATA_ORDER == SPI1_LSB_FIRST

	SET_BIT( SPI1 -> CR1 , SPI_LSBFIRST );

#endif

#if SPI1_SS_MANAGE == SW_SLAVE_MANAGEMENT

	SET_BIT( SPI1->CR1 , SPI_SSM );
	SET_BIT(SPI1->CR1,SPI_SSI);

#elif   SPI1_SS_MANAGE  == HW_SLAVE_MANAGEMENT

	CLR_BIT( SPI1-> CR1 , SPI_SSM );

#endif

#if   SPI1_DATA_SIZE == SPI1_8BIT_DATA

	CLR_BIT( SPI1->CR1 , SPI_DFF );

#elif SPI1_DATA_SIZE == SPI1_16BIT_DATA

	SET_BIT(SPI1 -> CR1 , SPI_DFF );

#endif

#if   SP1_STATUS == SPI_ENABLE
	SET_BIT( SPI1 -> CR1 , SPI_SPE );

#elif SP1_STATUS == SPI_DISABLE
	CLR_BIT(SPI1 -> CR1 , SPI_SPE );
#endif

#if   SPI1_INT_STATUS == SPI1_INT_DISABLE

	SPI1 -> CR2 = 0 ;

#elif SPI1_INT_STATUS == SPI1SPI1_TXE_INT_ENABLE

	SET_BIT( SPI1 -> CR2 , SPI1_TXEIE );

#elif SPI1_INT_STATUS == SPI1_RXNE_INT_ENABLE

	SET_BIT( SPI1 -> CR2 , SPI1_RXNEIE );

#endif

	 //set pins direction
	   PIN_st SPI_PinAF= {AF,PP,HS,NPP};
	   GPIO_voidSetPinDirection (MOSI1_PORT ,MOSI1_PIN, &SPI_PinAF);
	   GPIO_voidSetPinDirection (SCK1_PORT ,SCK1_PIN, &SPI_PinAF);
	   GPIO_voidSetPinDirection (MISO1_PORT ,MISO1_PIN, &SPI_PinAF);
	   GPIO_voidSetAlternativeFunction(MOSI1_PORT ,MOSI1_PIN, GPIO_AF_5);
	   GPIO_voidSetAlternativeFunction(SCK1_PORT ,SCK1_PIN, GPIO_AF_5);
	   GPIO_voidSetAlternativeFunction(MISO1_PORT ,MISO1_PIN,  GPIO_AF_5);
}


u8 SPI_voidTransReceiverData ( u8 Copy_u8Data ){

	SPI1 -> DR = Copy_u8Data;

	while ( GET_BIT( SPI1 -> SR , SPI_BSY) == 1 );

	return (u8) SPI1 -> DR ;

}
void SPI1_VidSetCallBack( void (*ptr) (void) ){

	MSPI1_CallBack = ptr;

}

void SPI1_IRQHandler(void){

	MSPI1_CallBack();

}




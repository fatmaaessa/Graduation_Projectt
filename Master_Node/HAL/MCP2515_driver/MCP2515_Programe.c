/*
 * MCP2515_Programe.c
 *
 *  Created on: Ù Ù¡â€�/Ù¡Ù¡â€�/Ù¢Ù Ù¢Ù¢
 *      Author: DELL
 */
/* ** Include  Section ** */

/* Include LIB */
#include "../../LIB/STD_TYPES.h"

/* Include MCAL */
#include "../../MCAL/SPI_driver/SPI_Interface.h"

/* _____________________ */


#include "../MCP2515_driver/MCP2515_Interface.h"
#include "../MCP2515_driver/MP2515_Private.h"

/**** Declaration Start  *****/
u8 REC_Message[16];

/*   ************************  *******************************
 **************** Common Function Start  **********************/

/*********** Write Section Start ****************/

void HMCP2515_voidWriteReg(u8 Copy_u8RegAddress ,u8 Copy_u8Data)
{

	MSPI_VidChipSelect(1);
	MSPI_U8MasterTransmit(MCP2515_WRITE_INST);
	MSPI_U8MasterTransmit(Copy_u8RegAddress );
	MSPI_U8MasterTransmit(Copy_u8Data);
	MSPI_VidChipSelect(0);
}
/*********** Write Section End ****************/

/*********** Read Section Start ****************/
u8 HMCP2515_U8ReadReg(u8 Copy_u8RegAddress)
{
    u8 localValue2;
	MSPI_VidChipSelect(1);
	MSPI_U8MasterTransmit(MCP2515_READ_INST);
	MSPI_U8MasterTransmit(Copy_u8RegAddress);
	localValue2 = MSPI_U8MasterTransmit(0);
	MSPI_VidChipSelect(0);
    return localValue2;
}
/*********** Read Section End ****************/

/*********** Reset Section Start ****************/
void HMCP2515_voidResetInst(void)
{
	MSPI_VidChipSelect(1);
	MSPI_U8MasterTransmit(MCP2515_RESET_INST);
	MSPI_VidChipSelect(0);
}
/*********** Reset Instruction End ****************/

/*********** Bit Modify Section Start ****************/
void  HMCP2515_voidBitModify(u8 Copy_RegAddress ,u8 Copy_u8Mask,u8 Copy_U8Data )
{

	MSPI_VidChipSelect(1);
	MSPI_U8MasterTransmit(MCP2515_BITMODIFY_INST );
	MSPI_U8MasterTransmit(Copy_RegAddress);
	MSPI_U8MasterTransmit(Copy_u8Mask);
	MSPI_U8MasterTransmit(Copy_U8Data);
	MSPI_VidChipSelect(0);

}
/*********** Bit Modify Section End ****************/

/*********** Bit Timing Section Start ****************/
void HMCP2515_voidSetBitTiming(u8 Copy_U8CNFVAL1 ,u8 Copy_U8CNFVAL2 ,u8 Copy_U8CNFVAL3)
{
    /*
     * Config bit timing
     * 16 Quanta
     * 1 TQ for Synch bit
     * 6 TQ for Phase segment 2
     * 2 TQ For Propagation Segment
     * 7 TQ For Phase segment 1
     */
	HMCP2515_voidWriteReg(CNF1,Copy_U8CNFVAL1);
	HMCP2515_voidWriteReg(CNF2,Copy_U8CNFVAL2);
	HMCP2515_voidWriteReg(CNF3,Copy_U8CNFVAL3);
}
/*********** Bit Timing Section End ****************/

/*********** Set Mode Inst Section Start ****************/
void HMCP2515_voidSetMode(u8 Copy_U8Mode)
{
    HMCP2515_voidBitModify(CANCTRL ,0XE0,(Copy_U8Mode<<5));
	//HMCP2515_voidWriteReg(CANCTRL,(Copy_U8Mode<<5));
    //u8 local1=HMCP2515_U8ReadReg(CANSTAT);
	while((HMCP2515_U8ReadReg(CANSTAT)>>5)!=Copy_U8Mode);
	/*{
		not correct(because of Rec function ) but will be execute
		HMCP2515_voidBitModify(CANCTRL ,0XE0,Copy_U8Mode<<5);
		 MCAL_DIO_voidSETBIT(PC,PC0,LOW);

	}*/

}
/*********** Set Mode Inst Section End ****************/

/************* Transmitter initialization Section Start ******************/
void HMCP2515_voidInitTransimiter(void)
{

	  MSPI_voidSpiMasterInit();
	  HMCP2515_voidResetInst();

	  /* Enable  Configuration  mode and Enable clock  To Set Bit Timing*/
	  HMCP2515_voidWriteReg(CANCTRL,0x87);
	  /*
	   * MCP2515_SETMODE(config_mode)
	     HMCP2515_voidSetMode(CONFIG_MODE);
	     HMCP2515_voidBitModify(CANCTRL ,0X04,0x04);
         u8 local =HMCP2515_U8ReadReg(CANSTAT);
       */
	 while((HMCP2515_U8ReadReg(CANSTAT)>>5) != CONFIG_MODE);

	/*  Bit rate Transmission data of CAN  is 250KHz  with  using 8MHz MIC Clock
	 * CNF1 = (2<<6)
	 * CNF2 = (1<<7)|(6<<3)|(1)
	 * CNF3 = (0x15)
	 */
	 HMCP2515_voidSetBitTiming(2<<6, (1<<7)|(6<<3)|(1), (0x15));
	// HMCP2515_voidSetBitTiming(0x80,0xB1,0x05);
    /*  return to normal mode sending and Receiving*/
	  HMCP2515_voidSetMode(NORMAL_MODE);

}
/************* Transmitter initialization Section End  ******************/

/******************Transmitter Sending Message Start ****************/
void HMCP2515_VidSendCAN_Msg(u8 Copy_u8Address ,u32 Copy_u8MsgID, u8 Copy_u8DataLen_DLC , u8*Copy_u8data)
{
	/* Take the bus
	 * Send Transmit Buffer that want to write at it
	 * TXB0CTRL
	 * TXB1CTRL
	 * TXB2CTRL
	 * */

	MSPI_VidChipSelect(1);
	MSPI_U8MasterTransmit(MCP2515_WRITE_INST);
	MSPI_U8MasterTransmit(Copy_u8Address);

	/* any data can send Highest priority  (Mandatory)*/
	MSPI_U8MasterTransmit(0x03);

	/* Full IDH EXtend Id  */
	MSPI_U8MasterTransmit((u8)(Copy_u8MsgID>>3));
	MSPI_U8MasterTransmit((u8)(Copy_u8MsgID<<5) | (0b00000001 << 3));
	MSPI_U8MasterTransmit(0);
	MSPI_U8MasterTransmit(0);

	/* DLC (Data length)
	 *  IS 1000 RTR IS 0 SO WRITE  */
	MSPI_U8MasterTransmit(Copy_u8DataLen_DLC&0x0F);

	/* Send data */
	for(int i =0; i<(Copy_u8DataLen_DLC & 0x0F);i++)
	{
		MSPI_U8MasterTransmit(Copy_u8data[i]);
	}

	/* good bye for bus */
	MSPI_VidChipSelect(0);

	/* Request to send data */
	MSPI_VidChipSelect(1);
	MSPI_U8MasterTransmit(MCP2515_MREG2SENDTXB0_INST);
	MSPI_VidChipSelect(0);


}
/******************Transmitter Sending Message End ****************/



/*************** RECIEVE PART *********************
* used when  if RXB0 contains a valid message and
another valid message is received, an overflow error
will not occur and the new message will be moved into
RXB1, regardless of the acceptance criteria of RXB1
*/

/**** Declaration End  *****/

/* ***  RollOver Function Start ** */

void HMCP2515_voidRollOver(u8 Copy_u8BUKT)
	{
	   /*
	    * BUKT: Rollover Enable bit
         1 = RXB0 message will roll over and be written to RXB1 if RXB0 is full
         0 = Rollover is disable
	    */
		HMCP2515_voidBitModify(RXB0CTRL , 1<<Copy_u8BUKT, 1<<Copy_u8BUKT );
	}

/* ***  RollOver Function End  ** */

/* ***  Set Mask Function Start ** */
void HMCP2515_voidSetMask(u8 Copy_u8address_mask_Reg ,u32 Copy_u32Mask_Value ,u8 Copy_u8Extended)
{
		  MSPI_VidChipSelect(1);
		  MSPI_U8MasterTransmit(MCP2515_WRITE_INST);
		  MSPI_U8MasterTransmit(Copy_u8address_mask_Reg);
	  if(Copy_u8Extended)
	  {
		  MSPI_U8MasterTransmit((u8)(Copy_u32Mask_Value>>3));
		  MSPI_U8MasterTransmit((u8)(Copy_u32Mask_Value<<5) | (0b00000001 << 3));
		  MSPI_U8MasterTransmit((u8)(Copy_u32Mask_Value>>3)|(u8)(Copy_u32Mask_Value>>27));
		  MSPI_U8MasterTransmit((u8)(Copy_u32Mask_Value>>11));
	  }
	  else
	  {
		  MSPI_U8MasterTransmit((u8)(Copy_u32Mask_Value>>3));
		  MSPI_U8MasterTransmit((u8)(Copy_u32Mask_Value<<5));
	  }
	    MSPI_VidChipSelect(0);
}

/* ***  Set Mask Function End ** */

/* ***  Receive Initialization   Start ** */
void HMCP2515_voidRecievInit(void)
{
	MSPI_voidSpiMasterInit();
	HMCP2515_voidResetInst();

	/* Enable  Configuration  mode and Enable clock  To Set Bit Timing*/
	HMCP2515_voidWriteReg(CANCTRL,0x87);
	/* Stuck until Enter Configuration Mode  */
	while((HMCP2515_U8ReadReg(CANSTAT)>>5) != CONFIG_MODE){}
   /*  Bit rate Transmission data of CAN  is 250KHz  with  using 8MHz MIC Clock
	 * CNF1 = (2<<6)
	 * CNF2 = (1<<7)|(6<<3)|(1)
	 * CNF3 = (0x15)
	*/

	HMCP2515_voidSetBitTiming(2<<6, (1<<7)|(6<<3)|(1), (0x15));

	HMCP2515_voidSetMask(RXM0SIDH, 0x00000000, 1) ;
	HMCP2515_voidSetMask(RXM1SIDH, 0x00000000, 1) ;

	/*
	 *  BUKT: Rollover Enable bit
		1 = RXB0 message will roll over and be written to RXB1 if RXB0 is full
		0 = Rollover is disable
	 */
	HMCP2515_voidRollOver(1);

	HMCP2515_voidBitModify(CANINTE, 1<<0, 1<<RX0IE);

	/*  return to normal mode sending and Receiving*/
	HMCP2515_voidSetMode(NORMAL_MODE);
}

/* ***  Receive Initialization  End ** */

/* ***  Receive Message   Start ** */
void HMCP2515_voidRecieveMess(u8 Copy_u8REC_Buff_addres)
{

	MSPI_VidChipSelect(1);
   /*
    * Read from Receive buffer
    */
	MSPI_U8MasterTransmit(MCP2515_READ_INST);
	MSPI_U8MasterTransmit(Copy_u8REC_Buff_addres);
	 /*
	 * Receive Message FROM
	 * RXB0CTRL Register  Until RXBOD7 Data Register
	 */
     for (u8 buff_index =0 ; buff_index <16; buff_index++)
     {
    	 REC_Message[buff_index]=MSPI_U8MasterTransmit(0);
     }

	MSPI_VidChipSelect(0);
	/*Clear Flag  */
	HMCP2515_voidWriteReg(CANINTF,0);
}
/* ***  Receive Message   End *** */

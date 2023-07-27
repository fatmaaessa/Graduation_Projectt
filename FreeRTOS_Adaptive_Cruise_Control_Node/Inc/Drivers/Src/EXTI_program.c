/********************************************************************************************/
/* 	AUTHOR  		: islam atef Mohamed 													*/
/* 	VERSION 		:	  V1 																*/
/* 	DATE    		:  9/1/2022 															*/
/*	 Discribtion  	:  This is the Program file Module For the EXTI Peripheral 				*/
/*											at ARM-CORTEX m4								*/
/********************************************************************************************/

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_Types.h"

#include "../Inc/EXTI_config.h"
#include "../Inc/EXTI_interface.h"
#include "../Inc/EXTI_private.h"
/********************************************************************************************/
#if     Multiple_Lines_Interrupt    ==      ENABLE 
	u8  LINE_ARRAY_COUNTER = 6 ;
#endif
/********************************************************************************************/
/*     Pointer to Function that Takes the main.c function and be Excuted at the Handler     */
/********************************************************************************************/
	#ifdef SYSCFG_LINE0_CONFG
		static void (* EXTI_LINE0_Handler) (void) = NULL ;
	#endif
	#ifdef	SYSCFG_LINE1_CONFG
		static void (* EXTI_LINE1_Handler) (void) = NULL ;
	#endif	
	#ifdef	SYSCFG_LINE2_CONFG
		static void (* EXTI_LINE2_Handler) (void) = NULL ;
	#endif	
	#ifdef	SYSCFG_LINE3_CONFG
		static void (* EXTI_LINE3_Handler) (void) = NULL ;
	#endif	
	#ifdef	SYSCFG_LINE4_CONFG
		static void (* EXTI_LINE4_Handler) (void) = NULL ;
	#endif	
	#ifdef	SYSCFG_LINE5_CONFG
		static void (* EXTI_LINE5_Handler) (void) = NULL ;
	#endif	
	#ifdef	SYSCFG_LINE6_CONFG
		static void (* EXTI_LINE6_Handler) (void) = NULL ;
	#endif
	#ifdef	SYSCFG_LINE7_CONFG
		static void (* EXTI_LINE7_Handler) (void) = NULL ;
	#endif	
	#ifdef	SYSCFG_LINE8_CONFG
		static void (* EXTI_LINE8_Handler) (void) = NULL ;
	#endif	
	#ifdef	SYSCFG_LINE9_CONFG
		static void (* EXTI_LINE9_Handler) (void) = NULL ;
	#endif	
	#ifdef	SYSCFG_LINE10_CONFG
		static void (* EXTI_LINE10_Handler) (void) = NULL ;
	#endif	
	#ifdef	SYSCFG_LINE11_CONFG
		static void (* EXTI_LINE11_Handler) (void) = NULL ;
	#endif
	#ifdef	SYSCFG_LINE12_CONFG
		static void (* EXTI_LINE12_Handler) (void) = NULL ;
	#endif	
	#ifdef	SYSCFG_LINE13_CONFG
		static void (* EXTI_LINE13_Handler) (void) = NULL ;
	#endif	
	#ifdef	SYSCFG_LINE14_CONFG
		static void (* EXTI_LINE14_Handler) (void) = NULL ;
	#endif
	#ifdef	SYSCFG_LINE15_CONFG
		static void (* EXTI_LINE15_Handler) (void) = NULL ;
	#endif
/********************************************************************************************/


/********************************************************************************************/
/*  Function : MEXTI_voidInit			                                					*/
/*  I/P parameters : Takes Nothing                                         					*/
/*  Returnning : Returns Nothing                                           					*/
/*  Discribtion :       This Function Initializes the EXTI Peripheral 						*/
/*								and define the port of each line		   					*/
/********************************************************************************************/
void	MEXTI_voidInit(void)
{
	/* Define Which Port is represented by The Line*/
	#ifdef  SYSCFG_LINE0_CONFG
		SYSCFG -> EXTICR1 |= ( SYSCFG_LINE0_CONFG<< (4*0) ) ;
	#endif
	#ifdef	SYSCFG_LINE1_CONFG
		SYSCFG -> EXTICR1 |= ( SYSCFG_LINE1_CONFG<< (4*1) ) ;
	#endif	
	#ifdef	SYSCFG_LINE2_CONFG
		SYSCFG -> EXTICR1 |= ( SYSCFG_LINE2_CONFG<< (4*2) ) ;
	#endif	
	#ifdef	SYSCFG_LINE3_CONFG
		SYSCFG -> EXTICR1 |= ( SYSCFG_LINE3_CONFG<< (4*3) ) ;
	#endif	
	#ifdef	SYSCFG_LINE4_CONFG
		SYSCFG -> EXTICR2 |= ( SYSCFG_LINE4_CONFG<< (4*0) ) ;
	#endif	
	#ifdef	SYSCFG_LINE5_CONFG
		SYSCFG -> EXTICR2 |= ( SYSCFG_LINE5_CONFG<< (4*1) ) ;
	#endif	
	#ifdef	SYSCFG_LINE6_CONFG
		SYSCFG -> EXTICR2 |= ( SYSCFG_LINE6_CONFG<< (4*2) ) ;
	#endif
	#ifdef	SYSCFG_LINE7_CONFG
		SYSCFG -> EXTICR2 |= ( SYSCFG_LINE7_CONFG<< (4*3) ) ;
	#endif	
	#ifdef	SYSCFG_LINE8_CONFG
		SYSCFG -> EXTICR3 |= ( SYSCFG_LINE8_CONFG<< (4*0) ) ;
	#endif	
	#ifdef	SYSCFG_LINE9_CONFG
		SYSCFG -> EXTICR3 |= ( SYSCFG_LINE9_CONFG<< (4*1) ) ;
	#endif	
	#ifdef	SYSCFG_LINE10_CONFG
		SYSCFG -> EXTICR3 |= ( SYSCFG_LINE10_CONFG << (4*2) ) ;
	#endif	
	#ifdef	SYSCFG_LINE11_CONFG
		SYSCFG -> EXTICR3 |= ( SYSCFG_LINE11_CONFG << (4*3) ) ;
	#endif
	#ifdef	SYSCFG_LINE12_CONFG
		SYSCFG -> EXTICR4 |= ( SYSCFG_LINE12_CONFG << (4*0) ) ;
	#endif	
	#ifdef	SYSCFG_LINE13_CONFG
		SYSCFG -> EXTICR4 |= ( SYSCFG_LINE13_CONFG << (4*1) ) ;
	#endif	
	#ifdef	SYSCFG_LINE14_CONFG
		SYSCFG -> EXTICR4 |= ( SYSCFG_LINE14_CONFG << (4*2) ) ;
	#endif
	#ifdef	SYSCFG_LINE15_CONFG
		SYSCFG -> EXTICR4 |= ( SYSCFG_LINE15_CONFG << (4*3) ) ;
	#endif
	/* Disable All Lines */
	EXTI -> IMR = 0x0 ;
	/* Clear All Flags */
	EXTI -> PR = 0xffffffff ;
}
/********************************************************************************************/


/********************************************************************************************/
/*  Function : MEXTI_voidEnableInterruptLine			                                	*/
/*  I/P parameters : Takes The Line-number and the Trigger-Type                             */
/*  Returning : Returns Nothing                                           					*/
/*  Discribtion : This Function Enable The Line and define The trigger Type 			   	*/
/********************************************************************************************/
void	MEXTI_voidEnableInterruptLine( u8 copy_u8LineID )
{
	SET_BIT( EXTI->IMR , copy_u8LineID );
}
/********************************************************************************************/
/********************************************************************************************/
/*  Function : MEXTI_voidDisableInterruptLine	                                			*/
/*  I/P parameters : Takes The Line-number 						                            */
/*  Returning : Returns Nothing                                           					*/
/*  Discribtion : This Function Disable The Line			 		   						*/
/********************************************************************************************/
void	MEXTI_voidDisableInterruptLine( u8 copy_u8LineID )
{
	CLR_BIT( EXTI->IMR , copy_u8LineID );
}
/********************************************************************************************/


/********************************************************************************************/
/*  Function : MEXTI_voidTriggerConfig		                                				*/
/*  I/P parameters : Takes The Line-number and the Trigger-Type                             */
/*  Returning : Returns Nothing                                           					*/
/*  Discribtion : This Function define The trigger Type of The Line						   	*/
/********************************************************************************************/
void	MEXTI_voidTriggerConfig( u8 copy_u8LineID , u8 copy_u8TriggerType )
{
	CLR_BIT( EXTI->RTSR , copy_u8LineID );
	CLR_BIT( EXTI->FTSR , copy_u8LineID );
	switch (copy_u8TriggerType)
	{
	case 	Raising_trigger		:
		/* code : SET RTSR 	             */
		SET_BIT( EXTI->RTSR , copy_u8LineID );
		break;
	case 	Falling_trigger		:
		/* code : SET FTSR 	             */
		SET_BIT( EXTI->FTSR , copy_u8LineID );
		break;
	case 	ONchange_trigger	:
		/* code : SET BOTH RTSR AND FTSR */
		SET_BIT( EXTI->RTSR , copy_u8LineID );
		SET_BIT( EXTI->FTSR , copy_u8LineID );
		break;
	}

}
/********************************************************************************************/


/********************************************************************************************/
/*  Function : MEXTI_voidSetCallBack		                                				*/
/*  I/P parameters : Takes The Line-number and the Interrupt Function                       */
/*  Returning : Returns Nothing                                           					*/
/*  Discribtion : This Function Set the Handler function pointer						   	*/
/********************************************************************************************/
void	MEXTI_voidSetCallBack( u8 copy_u8LineID , void (* prt)(void) )
{
	switch (copy_u8LineID)
	{

	#ifdef SYSCFG_LINE0_CONFG
		case EXTI_LINE0 :
			EXTI_LINE0_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE1_CONFG
		case EXTI_LINE1 :
			EXTI_LINE1_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE2_CONFG
		case EXTI_LINE2 :
			EXTI_LINE2_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE3_CONFG
		case EXTI_LINE3 :
			EXTI_LINE3_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE4_CONFG
		case EXTI_LINE4 :
			EXTI_LINE4_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE5_CONFG
		case EXTI_LINE5 :
			EXTI_LINE5_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE6_CONFG
		case EXTI_LINE6 :
			EXTI_LINE6_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE7_CONFG
		case EXTI_LINE7 :
			EXTI_LINE7_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE8_CONFG
		case EXTI_LINE8 :
			EXTI_LINE8_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE9_CONFG
		case EXTI_LINE9 :
			EXTI_LINE9_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE10_CONFG
		case EXTI_LINE10 :
			EXTI_LINE10_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE11_CONFG
		case EXTI_LINE11 :
			EXTI_LINE11_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE12_CONFG
		case EXTI_LINE12 :
			EXTI_LINE12_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE13_CONFG
		case EXTI_LINE13 :
			EXTI_LINE13_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE14_CONFG
		case EXTI_LINE14 :
			EXTI_LINE14_Handler = prt ;
			break;
	#endif

	#ifdef SYSCFG_LINE15_CONFG
		case EXTI_LINE15 :
			EXTI_LINE15_Handler = prt ;
			break;
	#endif

	}
}
/********************************************************************************************/


/********************************************************************************************/
/*  Function : MEXTI_VoidTriggerConfig		                                				*/
/*  I/P parameters : Takes The Line-number and the Trigger-Type                             */
/*  Returning : Returns Nothing                                           					*/
/*  Discribtion : This Function define The trigger Type of The Line						   	*/
/********************************************************************************************/
/***********************			EXTI0_IRQHandler			*****************************/
/********************************************************************************************/
#ifdef SYSCFG_LINE0_CONFG
	void	EXTI0_IRQHandler(void)
	{
		EXTI_LINE0_Handler(); 
		/*	Clear Pending Bit  */
		SET_BIT(EXTI -> PR , EXTI_LINE0);
	}
#endif
/********************************************************************************************/
/***********************			EXTI1_IRQHandler			*****************************/
/********************************************************************************************/

#ifdef SYSCFG_LINE1_CONFG
	void	EXTI1_IRQHandler(void)
	{
		EXTI_LINE1_Handler(); 
		/*	Clear Pending Bit  */
		SET_BIT(EXTI -> PR , EXTI_LINE1);
	}
#endif
/********************************************************************************************/
/***********************			EXTI2_IRQHandler			*****************************/
/********************************************************************************************/
#ifdef SYSCFG_LINE2_CONFG
	void	EXTI2_IRQHandler(void)
	{
		EXTI_LINE2_Handler(); 
		/*	Clear Pending Bit  */
		SET_BIT(EXTI -> PR , EXTI_LINE2);
	}
#endif
/********************************************************************************************/
/***********************			EXTI3_IRQHandler			*****************************/
/********************************************************************************************/
#ifdef SYSCFG_LINE3_CONFG
	void	EXTI3_IRQHandler(void)
	{
		EXTI_LINE3_Handler(); 
		/*	Clear Pending Bit  */
		SET_BIT(EXTI -> PR , EXTI_LINE3);
	}
#endif
/********************************************************************************************/
/***********************			EXTI4_IRQHandler			*****************************/
/********************************************************************************************/
#ifdef SYSCFG_LINE4_CONFG
	void	EXTI4_IRQHandler(void)
	{
		EXTI_LINE4_Handler(); 
		/*	Clear Pending Bit  */
		SET_BIT(EXTI -> PR , EXTI_LINE4);
	}
#endif
/********************************************************************************************/
/***********************			EXTI9_5_IRQHandler			*****************************/
/********************************************************************************************/
void	EXTI9_5_IRQHandler(void)
{
	do
	{
		/* code */
		#ifdef SYSCFG_LINE5_CONFG
			if(GET_BIT(EXTI -> PR , EXTI_LINE5))
				{
					EXTI_LINE5_Handler(); 
					/*	Clear Pending Bit  */
					SET_BIT(EXTI -> PR , EXTI_LINE5);
				}
		#endif
		#ifdef SYSCFG_LINE6_CONFG
			if(GET_BIT(EXTI -> PR , EXTI_LINE6))
				{
					EXTI_LINE6_Handler(); 
					/*	Clear Pending Bit  */
					SET_BIT(EXTI -> PR , EXTI_LINE6);
				}
		#endif
		#ifdef SYSCFG_LINE7_CONFG
			if(GET_BIT(EXTI -> PR , EXTI_LINE7))
				{
					EXTI_LINE7_Handler(); 
					/*	Clear Pending Bit  */
					SET_BIT(EXTI -> PR , EXTI_LINE7);
				}
		#endif
		#ifdef SYSCFG_LINE8_CONFG
			if(GET_BIT(EXTI -> PR , EXTI_LINE8))
				{	
					EXTI_LINE8_Handler(); 
					/*	Clear Pending Bit  */
					SET_BIT(EXTI -> PR , EXTI_LINE8);
				}		
		#endif
		#ifdef SYSCFG_LINE9_CONFG
			if(GET_BIT(EXTI -> PR , EXTI_LINE9))
				{
					EXTI_LINE9_Handler(); 
					/*	Clear Pending Bit  */
					SET_BIT(EXTI -> PR , EXTI_LINE9);
				}
		#endif
	} while ( (( GET_BIT(EXTI -> PR , EXTI_LINE5)|GET_BIT(EXTI -> PR , EXTI_LINE6)|GET_BIT(EXTI -> PR , EXTI_LINE7)\
			             |GET_BIT(EXTI -> PR , EXTI_LINE8)|GET_BIT(EXTI -> PR , EXTI_LINE9 )) == 1)				  );
}
/********************************************************************************************/
/**********************	     	 EXTI15_10_IRQHandler			*****************************/
/********************************************************************************************/
void	EXTI15_10_IRQHandler(void)
{
	do
	{
		#ifdef SYSCFG_LINE10_CONFG
			if (GET_BIT(EXTI -> PR , EXTI_LINE10))
			{
				EXTI_LINE10_Handler(); 
				/*	Clear Pending Bit  */
				SET_BIT(EXTI -> PR , EXTI_LINE10);
			}
	#endif
	#ifdef SYSCFG_LINE11_CONFG
			if (GET_BIT(EXTI -> PR , EXTI_LINE11))
			{
				EXTI_LINE11_Handler(); 
				/*	Clear Pending Bit  */
				SET_BIT(EXTI -> PR , EXTI_LINE11);
			}
	#endif
	#ifdef SYSCFG_LINE12_CONFG
			if (GET_BIT(EXTI -> PR , EXTI_LINE12))
			{
				EXTI_LINE12_Handler(); 
				/*	Clear Pending Bit  */
				SET_BIT(EXTI -> PR , EXTI_LINE12);
			}
	#endif
	#ifdef SYSCFG_LINE13_CONFG
			if (GET_BIT(EXTI -> PR , EXTI_LINE13))
			{
				EXTI_LINE13_Handler(); 
				/*	Clear Pending Bit  */
				SET_BIT(EXTI -> PR , EXTI_LINE13);
			}	
	#endif
	#ifdef SYSCFG_LINE14_CONFG
			if (GET_BIT(EXTI -> PR , EXTI_LINE14))
			{
				EXTI_LINE14_Handler(); 
				/*	Clear Pending Bit  */
				SET_BIT(EXTI -> PR , EXTI_LINE14);
			}
	#endif
	#ifdef SYSCFG_LINE15_CONFG
			if (GET_BIT(EXTI -> PR , EXTI_LINE15))
			{
				EXTI_LINE15_Handler(); 
				/*	Clear Pending Bit  */
				SET_BIT(EXTI -> PR , EXTI_LINE15);
			}
	#endif
	} while ( ( GET_BIT(EXTI -> PR , EXTI_LINE10)|GET_BIT(EXTI -> PR , EXTI_LINE11) |GET_BIT(EXTI -> PR , EXTI_LINE12)       \
			   |GET_BIT(EXTI -> PR , EXTI_LINE13)|GET_BIT(EXTI -> PR , EXTI_LINE14 )|GET_BIT(EXTI -> PR , EXTI_LINE15) ) == 1);
}
/********************************************************************************************/
/********************************************************************************************/



#if EVENT_INTERRUPT_STATE == EABLE
/********************************************************************************************/
/*  Function : MEXTI_VoidEnableLine			                                				*/
/*  I/P parameters : Takes The Line-number and the Trigger-Type                             */
/*  Returning : Returns Nothing                                           					*/
/*  Discribtion : This Function Enable The Line and define The trigger Type 			   	*/
/********************************************************************************************/
void	MEXTI_VoidEnableEventLine( u8 copy_u8LineID )
{
	SET_BIT( EXTI->EMR , copy_u8LineID );
}
/********************************************************************************************/
/********************************************************************************************/
/*  Function : MEXTI_VoidDisableEventLine	                                				*/
/*  I/P parameters : Takes The Line-number 						                            */
/*  Returning : Returns Nothing                                           					*/
/*  Discribtion : This Function Disable The Line			 		   						*/
/********************************************************************************************/
void	MEXTI_VoidDisableEventLine( u8 copy_u8LineID )
{
	CLR_BIT( EXTI->EMR , copy_u8LineID );
}
/********************************************************************************************/
#endif

#if SOFTWARE_INTERRUPT_STATE == EABLE 
/********************************************************************************************/
/*  Function : MEXTI_VoidSoftwareInterrupt	                                				*/
/*  I/P parameters : Takes The Line-number and the Trigger-Type for The SW-interrup         */
/*  Returning : Returns Nothing                                           					*/
/*  Discribtion : This Function Enable The Line and define The trigger Type 				*/
/*									for The SW-interrup 									*/
/********************************************************************************************/
void	MEXTI_VoidSoftwareInterrupt( u8 copy_u8LineID , u8 copy_u8TriggerType )
{
	SET_BIT( EXTI->IMR  , copy_u8LineID );
	CLR_BIT( EXTI->RTSR , copy_u8LineID );
	CLR_BIT( EXTI->FTSR , copy_u8LineID );
	switch (copy_u8TriggerType)
	{
	case 	Raising_trigger		:
		/* code : SET RTSR 	             */
		SET_BIT( EXTI->RTSR , copy_u8LineID );
		break;
	case 	Falling_trigger		:
		/* code : SET FTSR 	             */
		SET_BIT( EXTI->FTSR , copy_u8LineID );
		break;
	case 	ONchange_trigger	:
		/* code : SET BOTH RTSR AND FTSR */
		SET_BIT( EXTI->RTSR , copy_u8LineID );
		SET_BIT( EXTI->FTSR , copy_u8LineID );
		break;
	}
}
/********************************************************************************************/
#endif






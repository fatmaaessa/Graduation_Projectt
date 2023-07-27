#ifndef		EXTI_INTERFACE_H
#define		EXTI_INTERFACE_H

/********************************************************************************************/
/*                                  Trigger Types                                           */

#define         Raising_trigger            1    
#define         Falling_trigger            2
#define         ONchange_trigger           3
/********************************************************************************************/
/*                                       LINES IDs                                          */

#define         EXTI_LINE0                 0    
#define         EXTI_LINE1                 1
#define         EXTI_LINE2                 2
#define         EXTI_LINE3                 3    
#define         EXTI_LINE4                 4
#define         EXTI_LINE5                 5
#define         EXTI_LINE6                 6    
#define         EXTI_LINE7                 7
#define         EXTI_LINE8                 8
#define         EXTI_LINE9                 9    
#define         EXTI_LINE10                10
#define         EXTI_LINE11                11
#define         EXTI_LINE12                12    
#define         EXTI_LINE13                13
#define         EXTI_LINE14                14
#define         EXTI_LINE15                15    


/********************************************************************************************/


void	MEXTI_voidInit(void);

void	MEXTI_voidEnableInterruptLine( u8 copy_u8LineID );
void	MEXTI_voidDisableInterruptLine( u8 copy_u8LineID );

void	MEXTI_voidEnableEventLine( u8 copy_u8LineID );
void	MEXTI_voidDisableEventLine( u8 copy_u8LineID );

void	MEXTI_voidTriggerConfig( u8 copy_u8LineID , u8 copy_u8TriggerType );

void    MEXTI_voidSetCallBack( u8 copy_u8LineID , void (* prt)(void) );

void	MEXTI_voidSoftwareInterrupt( u8 copy_u8LineID , u8 copy_u8TriggerType );




#endif

#ifndef		EXTI_CONFIG_H
#define		EXTI_CONFIG_H

/*****************************************************************************************************************************************/
/*                                            Options that Can be Used   :                                                               */
/*****************************************************************************************************************************************/
#define         ENABLE                     0
#define         DISABLE                    1
/*                                                SYSCFG_PORTS Types     :                                                               */

#define         EXTI_PORTA                 0b0000    
#define         EXTI_PORTB                 0b0001
#define         EXTI_PORTC                 0b0010
//#define         EXTI_PORTD                 0b0011   /* Not Exixting In Black-Pill */
//#define         EXTI_PORTE                 0b0100   /* Not Exixting In Black-Pill */
//#define         EXTI_PORTH                 0b0111   /* Not Exixting In Black-Pill */
/*****************************************************************************************************************************************/
/*                              Software Interrupt can be Enabled or Disabled As an options   :   {ENABLE}  or  {DISABLE}                */

#define     SOFTWARE_INTERRUPT_STATE      DISABLE 

/*****************************************************************************************************************************************/
/*                              Event Interrupt can be Enabled or Disabled As an options   :   {ENABLE}  or  {DISABLE}                   */

#define     EVENT_INTERRUPT_STATE      DISABLE 

/*****************************************************************************************************************************************/

/*         Multiple Lines Interrupt {EXTI9_5} or {EXTI15_10} can be Enabled or Disabled As an options   :   {ENABLE}  or  {DISABLE}      */

#define     Multiple_Lines_Interrupt          ENABLE 

/*****************************************************************************************************************************************/
/*                              The Port of Each Line OF EXTI   :   {EXTI_PORTA}    (default)  or  {EXTI_PORTB}  or  {EXTI_PORTC}        */
/*                                                                           {EXTI_PORTD}   or  {EXTI_PORTE}  or  {EXTI_PORTH}           */
/*                                             NOTE THAT ::  You Should First Uncommant The Line First                                   */

//#define         SYSCFG_LINE0_CONFG                 EXTI_PORTA    
//#define         SYSCFG_LINE1_CONFG                 EXTI_PORTA
//#define         SYSCFG_LINE2_CONFG                 EXTI_PORTA
//#define         SYSCFG_LINE3_CONFG                 EXTI_PORTA    
//#define         SYSCFG_LINE4_CONFG                 EXTI_PORTA
//#define         SYSCFG_LINE5_CONFG                 EXTI_PORTA
//#define         SYSCFG_LINE6_CONFG                 EXTI_PORTA    
//#define         SYSCFG_LINE7_CONFG                 EXTI_PORTA
//#define         SYSCFG_LINE8_CONFG                 EXTI_PORTA
//#define         SYSCFG_LINE9_CONFG                 EXTI_PORTA   
//#define         SYSCFG_LINE10_CONFG                EXTI_PORTA
//#define         SYSCFG_LINE11_CONFG                EXTI_PORTA
//#define         SYSCFG_LINE12_CONFG                EXTI_PORTA    
//#define         SYSCFG_LINE13_CONFG                EXTI_PORTA
//#define         SYSCFG_LINE14_CONFG                EXTI_PORTA
//#define         SYSCFG_LINE15_CONFG                EXTI_PORTA

/*****************************************************************************************************************************************/
#endif

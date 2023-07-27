#ifndef		EXTI_PRIVATE_H
#define		EXTI_PRIVATE_H

/***********************************************************************/
/*                       The EXTI Declaration                          */
/***********************************************************************/

#define		EXTI_BASE_ADD			(u32)(0x40013C00)
typedef struct
{
    volatile      u32           IMR     ;
    volatile      u32           EMR     ;
    volatile      u32           RTSR    ;
    volatile      u32           FTSR    ;
    volatile      u32           SWIER   ;	
    volatile      u32           PR      ;
}MEXTI_TYPE ;

#define EXTI  ((MEXTI_TYPE * )EXTI_BASE_ADD)

/***********************************************************************/


/***********************************************************************/
/*                     The SYSCFG Declaration                          */
/***********************************************************************/

#define		SYSCFG_BASE_ADD			(u32)(0x40013800)
typedef struct
{
    volatile      u32           MEMRMP              ;
    volatile      u32           PMC                 ;
    volatile      u32           EXTICR1             ;   /* Contains EXTIx  :  x = [ 3 : 0 ]  */
    volatile      u32           EXTICR2             ;   /* Contains EXTIx  :  x = [ 7 : 4 ]  */
    volatile      u32           EXTICR3             ;   /* Contains EXTIx  :  x = [12 : 8 ]  */
    volatile      u32           EXTICR4             ;   /* Contains EXTIx  :  x = [15 : 12]  */
    volatile      u32           Reserved[12]        ;
    volatile      u32           CMPCR               ;
}MSYSCFG_TYPE ;

#define SYSCFG  ((MSYSCFG_TYPE * )SYSCFG_BASE_ADD)

/***********************************************************************/
#endif
/********************************************************************************************/
/* 	AUTHOR  		: islam atef Mohamed 													*/
/* 	VERSION 		:	  V1.0 																*/
/* 	DATE    		:  1/2023 																*/
/*	Description  	:  This is the Private file For the TIMER Peripheral                    */
/*                                       at ARM-CORTEX m4						            */
/********************************************************************************************/
#ifndef		PRIVATE_H
#define		PRIVATE_H

/*--------------------------------------Timer Register Bits---------------------------------*/

/*******************  Bit definition for CR1 register  ********************/
#define  CR1_CEN                         0            
#define  CR1_UDIS                        1            
#define  CR1_URS                         2            
#define  CR1_OPM                         3            
#define  CR1_DIR                         4                        
#define  CR1_CMS_0                       5            
#define  CR1_CMS_1                       6            
#define  CR1_ARPE                        7                       
#define  CR1_CKD_0                       8           
#define  CR1_CKD_1                       9    
/*******************  Bit definition for CR2 register  ********************/
#define  CR2_CCPC                        0            
#define  CR2_CCUS                        2            
#define  CR2_CCDS                        3                      
#define  CR2_MMS_0                       4           
#define  CR2_MMS_1                       5        
#define  CR2_MMS_2                       6    
#define  CR2_TI1S                        7    
#define  CR2_OIS1                        8      
#define  CR2_OIS1N                       9     
#define  CR2_OIS2                        10          
#define  CR2_OIS2N                       11
#define  CR2_OIS3                        12       
#define  CR2_OIS3N                       13           
#define  CR2_OIS4                        14      
/*******************  Bit definition for SMCR register  *******************/           
#define  SMCR_SMS_0                      0          
#define  SMCR_SMS_1                      1            
#define  SMCR_SMS_2                      2                             
#define  SMCR_TS_0                       4         
#define  SMCR_TS_1                       5        
#define  SMCR_TS_2                       6        
#define  SMCR_MSM                        7                            
#define  SMCR_ETF_0                      8         
#define  SMCR_ETF_1                      9         
#define  SMCR_ETF_2                      10         
#define  SMCR_ETF_3                      11                                       
#define  SMCR_ETPS_0                     12         
#define  SMCR_ETPS_1                     13        
#define  SMCR_ECE                        14         
#define  SMCR_ETP                        15        
/*******************  Bit definition for DIER register  *******************/
#define  DIER_UIE                        0            
#define  DIER_CC1IE                      1            
#define  DIER_CC2IE                      2            
#define  DIER_CC3IE                      3           
#define  DIER_CC4IE                      4            
#define  DIER_COMIE                      5            
#define  DIER_TIE                        6            
#define  DIER_BIE                        7            
#define  DIER_UDE                        8            
#define  DIER_CC1DE                      9            
#define  DIER_CC2DE                      10           
#define  DIER_CC3DE                      11            
#define  DIER_CC4DE                      12           
#define  DIER_COMDE                      13            
#define  DIER_TDE                        14            
/********************  Bit definition for SR register  ********************/
#define  SR_UIF                          0            
#define  SR_CC1IF                        1            
#define  SR_CC2IF                        2            
#define  SR_CC3IF                        3            
#define  SR_CC4IF                        4            
#define  SR_COMIF                        5            
#define  SR_TIF                          6           
#define  SR_BIF                          7            
#define  SR_CC1OF                        9            
#define  SR_CC2OF                        10            
#define  SR_CC3OF                        11           
#define  SR_CC4OF                        12           
/*******************  Bit definition for EGR register  ********************/
#define  EGR_UG                          0               
#define  EGR_CC1G                        1               
#define  EGR_CC2G                        2               
#define  EGR_CC3G                        3               
#define  EGR_CC4G                        4               
#define  EGR_COMG                        5               
#define  EGR_TG                          6               
#define  EGR_BG                          7               
/******************  Bit definition for CCMR1 register  *******************/                           
#define  CCMR1_CC1S_0                    0            
#define  CCMR1_CC1S_1                    1            
#define  CCMR1_OC1FE                     2            
#define  CCMR1_OC1PE                     3                                             
#define  CCMR1_OC1M_0                    4            
#define  CCMR1_OC1M_1                    5            
#define  CCMR1_OC1M_2                    6            
#define  CCMR1_OC1CE                     7                                             
#define  CCMR1_CC2S_0                    8            
#define  CCMR1_CC2S_1                    9             
#define  CCMR1_OC2FE                     10            
#define  CCMR1_OC2PE                     11                        
#define  CCMR1_OC2M_0                    12            
#define  CCMR1_OC2M_1                    13            
#define  CCMR1_OC2M_2                    14            
#define  CCMR1_OC2CE                     15            
/*----------------------------------------------------------------------------*/            
#define  CCMR1_IC1PSC_0                  2             
#define  CCMR1_IC1PSC_1                  3                        
#define  CCMR1_IC1F_0                    4            
#define  CCMR1_IC1F_1                    5            
#define  CCMR1_IC1F_2                    6            
#define  CCMR1_IC1F_3                    7                      
#define  CCMR1_IC2PSC_0                  10            
#define  CCMR1_IC2PSC_1                  11                       
#define  CCMR1_IC2F_0                    12            
#define  CCMR1_IC2F_1                    13            
#define  CCMR1_IC2F_2                    14            
#define  CCMR1_IC2F_3                    15            
/******************  Bit definition for CCMR2 register  *******************/          
#define  CCMR2_CC3S_0                    0            
#define  CCMR2_CC3S_1                    1            
#define  CCMR2_OC3FE                     2            
#define  CCMR2_OC3PE                     3                          
#define  CCMR2_OC3M_0                    4            
#define  CCMR2_OC3M_1                    5            
#define  CCMR2_OC3M_2                    6            
#define  CCMR2_OC3CE                     7                                          
#define  CCMR2_CC4S_0                    8            
#define  CCMR2_CC4S_1                    9            
#define  CCMR2_OC4FE                     10            
#define  CCMR2_OC4PE                     11                       
#define  CCMR2_OC4M_0                    12            
#define  CCMR2_OC4M_1                    13           
#define  CCMR2_OC4M_2                    14            
#define  CCMR2_OC4CE                     15           
/*-------------------------------------------------------------------------*/          
#define  CCMR2_IC3PSC_0                   2           
#define  CCMR2_IC3PSC_1                   3                                       
#define  CCMR2_IC3F_0                     4           
#define  CCMR2_IC3F_1                     5           
#define  CCMR2_IC3F_2                     6           
#define  CCMR2_IC3F_3                     7                                         
#define  CCMR2_IC4PSC_0                   10           
#define  CCMR2_IC4PSC_1                   11                                            
#define  CCMR2_IC4F_0                     12           
#define  CCMR2_IC4F_1                     13           
#define  CCMR2_IC4F_2                     14           
#define  CCMR2_IC4F_3                     15           
/*******************  Bit definition for CCER register  *******************/
#define  CCER_CC1E                        0            
#define  CCER_CC1P                        1           
#define  CCER_CC1NE                       2           
#define  CCER_CC1NP                       3           
#define  CCER_CC2E                        4           
#define  CCER_CC2P                        5           
#define  CCER_CC2NE                       6           
#define  CCER_CC2NP                       7           
#define  CCER_CC3E                        8           
#define  CCER_CC3P                        9           
#define  CCER_CC3NE                       10           
#define  CCER_CC3NP                       11           
#define  CCER_CC4E                        12           
#define  CCER_CC4P                        13                 
                        
/*******************  Bit definition for BDTR register  *******************/  
#define  BDTR_DTG_0                      0            
#define  BDTR_DTG_1                      1            
#define  BDTR_DTG_2                      2            
#define  BDTR_DTG_3                      3            
#define  BDTR_DTG_4                      4            
#define  BDTR_DTG_5                      5            
#define  BDTR_DTG_6                      6            
#define  BDTR_DTG_7                      7                                            
#define  BDTR_LOCK_0                     8            
#define  BDTR_LOCK_1                     9            
#define  BDTR_OSSI                       10            
#define  BDTR_OSSR                       11            
#define  BDTR_BKE                        12            
#define  BDTR_BKP                        13            
#define  BDTR_AOE                        14            
#define  BDTR_MOE                        15            
/*******************  Bit definition for DCR register  ********************/           
#define  DCR_DBA_0                       0            
#define  DCR_DBA_1                       1            
#define  DCR_DBA_2                       2            
#define  DCR_DBA_3                       3            
#define  DCR_DBA_4                       4                      
#define  DCR_DBL_0                       8            
#define  DCR_DBL_1                       9            
#define  DCR_DBL_2                       10            
#define  DCR_DBL_3                       11            
#define  DCR_DBL_4                       12                  
/*------------------------------------------------------------------------------------------*/


/*-----------------------------------------Timer MACROS-------------------------------------*/
#define     __WRITE_BIT_(__REG__ , __BIT__ , __VAL__)    (__REG__ |= (__VAL__ << __BIT__) )
/*------------------------------------------------------------------------------------------*/
#endif
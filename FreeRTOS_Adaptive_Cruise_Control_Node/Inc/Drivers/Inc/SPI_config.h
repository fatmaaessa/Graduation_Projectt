/*********************************************/
/*********************************************/
/*********  Author: FatmaEssa        *********/
/*********  Layer: MCAL              *********/
/*********  SWC: SPI_config          *********/
/*********  Version: 1.00            *********/
/*********************************************/
#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

/*configurations for spi pins*/

#define MOSI1_PORT                  GPIO_PORTA
#define MOSI1_PIN                   PIN7

#define MISO1_PORT                  GPIO_PORTA
#define MISO1_PIN                   PIN6

#define SCK1_PORT                   GPIO_PORTA
#define SCK1_PIN                    PIN5


/*
*OPTIONS FOR ENABLE OR DISABLE
*1-EMABLE
*2-DISABLE
*/
#define SP1_STATUS          SPI_ENABLE

/*
*OPTIONS FOR CLOCK PARITY AND PHASE
*1-MODE0---->CLR_2_BITS
*2-MODE1---->SET&CLR
*3-MODE2---->CLR&SET
*4-MODE3---->SET_2_BITS
*/
#define SPI1_CLOCK_MODE     SPI_MODE3
/*
*OPTIONS FOR START COMMUNICATION
*1-MASTER START
*2-SLAVE  START
*/
#define SPI1_MASTER_SLAVE   SPI_MASTER
/*
*OPTIONS FOR PRESCALLER
*1-FPCLK_DIVIDED_BY_2
*2-FPCLK_DIVIDED_BY_4
*3-FPCLK_DIVIDED_BY_8
*4-FPCLK_DIVIDED_BY_16
*5-FPCLK_DIVIDED_BY_32
*6-FPCLK_DIVIDED_BY_64
*7-FPCLK_DIVIDED_BY_128
*8-FPCLK_DIVIDED_BY_256
*/
#define SPI1_PRESCALLER     SPI_FPCLK_DIVIDED_BY_4
/*
*OPTIONS FOR transmitted first
*1-MSB
*2-LSB
*/
#define SPI1_DATA_ORDER     SPI_MSB_FIRST


#define SPI1_SS_MANAGE      SW_SLAVE_MANAGEMENT
/*options for data size
*SPI1_16BIT_DATA
*SPI1_8BIT_DATA
*/
#define SPI1_DATA_SIZE      SPI_8BIT_DATA

/*options for spi_interrupt
*1- enable
*2-disable
*/
#define SPI1_INT_STATUS     SPI_INT_DISABLE

#endif

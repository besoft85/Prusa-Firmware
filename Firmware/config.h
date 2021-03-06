#ifndef _CONFIG_H
#define _CONFIG_H


#include "Configuration_prusa.h"
#include "pins.h"

#if (defined(VOLT_IR_PIN) && defined(IR_SENSOR))
#define IR_SENSOR_ANALOG
#endif

//ADC configuration
/*RAMPS*/
#if (MOTHERBOARD == BOARD_RAMPS_14_EFB)
  #ifdef PINDA_THERMISTOR
    /* Ramps MKx with pinda thermistor */
    #define ADC_CHAN_MSK      0b1110000000000000 //used AD channels bit mask (13 = TEMP_0_PIN, 14 = TEMP_BED_PIN, 15 = TEMP_1_PIN)
    #define ADC_DIDR_MSK      0b1110000000000000 //AD channels DIDR mask (1 ~ disabled digital input)
    #define ADC_CHAN_CNT      3         //number of used channels)
    #define ADC_OVRSAMPL      16        //oversampling multiplier
    #define ADC_CALLBACK      adc_ready //callback function ()
  #else
    /* Ramps MKx without pinda thermistor */
    #define ADC_CHAN_MSK      0b0110000000000000 //used AD channels bit mask (13 = TEMP_0_PIN, 14 = TEMP_BED_PIN)
    #define ADC_DIDR_MSK      0b0110000000000000 //AD channels DIDR mask (1 ~ disabled digital input)
    #define ADC_CHAN_CNT      2         //number of used channels)
    #define ADC_OVRSAMPL      16        //oversampling multiplier
    #define ADC_CALLBACK      adc_ready //callback function ()
  #endif // PINDA_THERMISTOR
#else
  #ifndef IR_SENSOR_ANALOG
    #define ADC_CHAN_MSK      0b0000001001011111 //used AD channels bit mask (0,1,2,3,4,6,9)
    #define ADC_DIDR_MSK      0b0000001001011111 //AD channels DIDR mask (1 ~ disabled digital input)
    #define ADC_CHAN_CNT      7         //number of used channels)
  #else //!IR_SENSOR_ANALOG
    #define ADC_CHAN_MSK      0b0000001101011111 //used AD channels bit mask (0,1,2,3,4,6,8,9)
    #define ADC_DIDR_MSK      0b0000001001011111 //AD channels DIDR mask (1 ~ disabled digital input)
    #define ADC_CHAN_CNT      8         //number of used channels)
  #endif //!IR_SENSOR_ANALOG
  #define ADC_OVRSAMPL      16        //oversampling multiplier
  #define ADC_CALLBACK      adc_ready //callback function ()
#endif

//SWI2C configuration
/*RAMPS*/
#if MOTHERBOARD == BOARD_RAMPS_14_EFB
  #define SWI2C
  #define SWI2C_SDA         20 //SDA (already defined in config.h)
  #define SWI2C_SCL         21 //SCL (already defined in config.h)
  #define SWI2C_A8
  #define SWI2C_DEL         20 //2us clock delay
  #define SWI2C_TMO         2048 //2048 cycles timeout
#else
  #define SWI2C
  //#define SWI2C_SDA         20 //SDA on P3
  //#define SWI2C_SCL         21 //SCL on P3
  #define SWI2C_A8
  #define SWI2C_DEL         20 //2us clock delay
  #define SWI2C_TMO         2048 //2048 cycles timeout
#endif

//PAT9125 configuration - Filament sensor
/*RAMPS*/
#if MOTHERBOARD == BOARD_RAMPS_14_EFB
  #ifdef PAT9125
    #define PAT9125_SWI2C
    #define PAT9125_I2C_ADDR  0x75  //ID=LO
    //#define PAT9125_I2C_ADDR  0x79  //ID=HI
    //#define PAT9125_I2C_ADDR  0x73  //ID=NC
  #endif // PAT9125
  #define PAT9125_XRES      0
  #define PAT9125_YRES      240 
#else
  #define PAT9125_SWI2C
  #define PAT9125_I2C_ADDR  0x75  //ID=LO
  //#define PAT9125_I2C_ADDR  0x79  //ID=HI
  //#define PAT9125_I2C_ADDR  0x73  //ID=NC
  #define PAT9125_XRES      0
  #define PAT9125_YRES      240                   // maximum resolution (5*X cpi)
  #define PAT9124_YRES_MM   (5*PAT9125_YRES/25.4) // counts per mm
#endif

//SM4 configuration
#define SM4_DEFDELAY      500       //default step delay [us]

//TMC2130 - Trinamic stepper driver
//pinout - hardcoded
//spi:
#define TMC2130_SPI_RATE       0 // fosc/4 = 4MHz
#define TMC2130_SPCR           SPI_SPCR(TMC2130_SPI_RATE, 1, 1, 1, 0)
#define TMC2130_SPSR           SPI_SPSR(TMC2130_SPI_RATE)

//W25X20CL configuration - SERIAL FLASH MEMORY
/*RAMPS*/
#if MOTHERBOARD != BOARD_RAMPS_14_EFB
  //pinout:
  #define W25X20CL_PIN_CS        32
  //spi:
  #define W25X20CL_SPI_RATE      0 // fosc/4 = 4MHz
  #define W25X20CL_SPCR          SPI_SPCR(W25X20CL_SPI_RATE, 1, 1, 1, 0)
  #define W25X20CL_SPSR          SPI_SPSR(W25X20CL_SPI_RATE)
#endif

//LANG - Multi-language support
/*RAMPS*/
#if MOTHERBOARD == BOARD_RAMPS_14_EFB
  #define LANG_MODE              0 // primary language only
  //#define LANG_MODE              1 // sec. language support
  #define LANG_SIZE_RESERVED     0x3000 //0x2f00 // reserved space for secondary language (10240 bytes)
#else
  //#define LANG_MODE              0 // primary language only
  #define LANG_MODE              1 // sec. language support
  #define LANG_SIZE_RESERVED     0x3000 // reserved space for secondary language (12288 bytes)
#endif

#endif //_CONFIG_H

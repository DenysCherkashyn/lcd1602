/*
 * 	i2c_conf.h
 *
 *	Created on: 03 September 2023
 *      Author: D.Cherkashin
 *
 *      i2c driver configurstion header file.
 *      Contains configuration parameters for each controler i2c modules
 *      You need configure i2c work only here.
 *      For more information see readme.md file
 *
 */

#ifndef _I2C_CONF_H_
    #define _I2C_CONF_H_

    #ifdef __cplusplus
		 extern "C" {
    #endif

	#define USE_I2C1
	#define USE_I2C2

	#define USE_TX_RX_IN_MASTER_MODE		/* use Rx, Tx bits for master mode for each I2C model (if defined - use it (by default))  */


	#ifdef USE_I2C1
		 #define I2C1_SCL_PORT			GPIOB            /* Controller port for SCL (read STM32 datasheets)*/
		 #define I2C1_SCL_PIN			6               /* Controller pin for SCL (read STM32 datasheets)*/
		 #define I2C1_SDA_PORT			GPIOB            /* Controller port for SDA (read STM32 datasheets)*/
		 #define I2C1_SDA_PIN			7               /* Controller pin for SDA (read STM32 datasheets)*/

		 #define I2C1_MODE			SM		/* Fm - for fast mode; Sm - for standard mode*/
		 #define I2C1_FM_DUTY_CYCLE		0		/* SCL duty cycle duration. Uses only in FM mode. (if 0: Tlow/Thigh = 2; if 1: Tlow/Thigh = 16/9) */
		 #define I2C1_CLK_FREQ			100000		/* uint32_t, Specifies the CLK frequency, Hz. This parameter must be set to a value lower than 400kHz */

		 #define I2C1_USE_10BIT_ADDR_MODE	0		/* use 7- or 10-bit addressing mode (0 - 7 bit slave address, 1 - 10 bit slave address) */
		 #define I2C1_OWN_ADDRESS		0x01		/* Own 7-bit or 10-bit i2c-address for MCU (from 0x0001 to 0x8FFF) */
	#endif

	#ifdef USE_I2C2
		 #define I2C2_SCL_PORT			GPIOB            /* Controller port for SCL (read STM32 datasheets)*/
		 #define I2C2_SCL_PIN			10               /* Controller pin for SCL (read STM32 datasheets)*/
		 #define I2C2_SDA_PORT			GPIOB            /* Controller port for SDA (read STM32 datasheets)*/
		 #define I2C2_SDA_PIN			11               /* Controller pin for SDA (read STM32 datasheets)*/

		 #define I2C2_MODE			SM		/* Fm - for fast mode; Sm - for standard mode*/
		 #define I2C2_FM_DUTY_CYCLE		0		/* SCL duty cycle duration. Uses only in FM mode. (if 0: Tlow/Thigh = 2; if 1: Tlow/Thigh = 16/9) */
		 #define I2C2_CLK_FREQ			100000		/* uint32_t, Specifies the CLK frequency, Hz. This parameter must be set to a value lower than 400kHz */

		 #define I2C2_USE_10BIT_ADDR_MODE	0		/* use 7- or 10-bit addressing mode (0 - 7 bit slave address, 1 - 10 bit slave address) */
		 #define I2C2_OWN_ADDRESS		0x02		/* Own 7-bit or 10-bit i2c-address for MCU (from 0x0001 to 0x8FFF) */
	#endif

    #ifdef __cplusplus
		    }
    #endif

#endif /* _I2C_CONF_H_ */

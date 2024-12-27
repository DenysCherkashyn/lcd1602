/*
 * 	i2c_def.h
 *
 *	Created on: 03 September 2023
 *      Author: D.Cherkashin
 *
 *      i2c driver definitions header file.
 *      Contains main defenitions for driver class.
 *      For more information see readme.md file
 *
 */

#ifndef _I2C_DEF_H_
    #define _I2C_DEF_H_

    #ifdef __cplusplus
		 extern "C" {
    #endif

	/* I2C configuration bits (for future) */
	 #ifdef USE_I2C1
		#define I2C1_CR1_PEC_CHECKING		0x00		/* Packet error checking */
		#define I2C1_CR1_POS			0x00		/* Acknowledge/PEC Position (for data reception) */
		#define I2C1_CR1_ACK			I2C_CR1_ACK	/* Return acknowledge after receiving byte (matched address or data)*/
		#define I2C1_CR1_CLK_STRETCH_DISABLE	0x00		/* Used to disabling clock stretching in slave-mode when
									    ADDR or BTF bit is set, until it is reset by softwear */
		#define I2C1_CR1_GEN_CALL		0x00		/* General call (0 - address 0x00 is NACKed) */
		#define I2C1_CR1_PEC			0x00		/* PEC calculation (0 - PEC calculation disabled) */
		#define I2C1_CR1_ARP			0x00		/* Address Resolution Protocol  (0 - ARP disabled) */
		#define	I2C1_CR1_SMBTYPE		0x00		/* SMBus type (0 - SMBus Device; 1 - SMBus Host) */
		#define	I2C1_CR1_SMBUS			0x00		/* SMBus mode (0 - I2C mode; 1 - SMBus mode) */

		#define	I2C1_CR2_DMA			0x00		/* DMA requests enable (0 - disabled; 1 - enabled ) */
		#define	I2C1_CR2_ITBUF			0x00		/* I2C buffer interrupt (0 - disabled; 1 - enabled ) */
		#define	I2C1_CR2_ITEV			0x00		/* I2C event interrupt (0 - disabled; 1 - enabled ) */
		#define	I2C1_CR2_ITERR			0x00		/* I2C error interrupt (0 - disabled; 1 - enabled ) */

		#define I2C1_OAR1_ADDR_MODE		((I2C1_USE_10BIT_ADDR_MODE) ? I2C_OAR1_ADDMODE : 0)		/* 7-bit slave address */
		#define I2C1_ADDR_16BIT			((uint16_t) I2C1_OWN_ADDRESS)
		#define I2C1_OAR1_OWN_ADDR		((I2C1_USE_10BIT_ADDR_MODE) ? (I2C1_ADDR_16BIT & 0x03FF) : ((I2C1_ADDR_16BIT & 0x007F) << 1u))
		#define I2C1_OAR2_DUAL_ADRESSING	0x00		/* dual addressing is disabled */

		#define	I2C1_CCR_FS			((I2C1_MODE) ? I2C_CCR_FS : 0)
		#define	I2C1_CCR_DUTY			((I2C1_FM_DUTY_CYCLE) ? I2C_CCR_DUTY : 0)

		#define I2C1_CR1_CFG_MASK		(((uint16_t) I2C1_CR1_PEC_CHECKING) | \
							I2C1_CR1_POS | I2C1_CR1_ACK | \
							I2C1_CR1_CLK_STRETCH_DISABLE | \
							I2C1_CR1_GEN_CALL | I2C1_CR1_PEC | \
							I2C1_CR1_ARP | I2C1_CR1_SMBTYPE | I2C1_CR1_SMBUS)
		#define	I2C1_CR2_CFG_MASK		(((uint16_t) I2C1_CR2_DMA) | \
							I2C1_CR2_ITBUF | I2C1_CR2_ITEV | \
							I2C1_CR2_ITERR)
		#define	I2C1_OAR1_CFG_MASK		(((uint16_t) I2C1_OAR1_ADDR_MODE) | I2C1_OAR1_OWN_ADDR)
		#define	I2C1_OAR2_CFG_MASK		((uint16_t) I2C1_OAR2_DUAL_ADRESSING)
		#define	I2C1_CCR_CFG_MASK		(((uint16_t) I2C1_CCR_FS) | I2C1_CCR_DUTY)

		#define I2C1_CFG_STRUCT			{(uint32_t)I2C1_CLK_FREQ, I2C1_CR1_CFG_MASK,\
							I2C1_CR2_CFG_MASK, I2C1_OAR1_CFG_MASK,\
							I2C1_OAR2_CFG_MASK,	I2C1_CCR_CFG_MASK}
		#define I2C1_GPIO_CLK_SCL		((I2C1_SCL_PORT == GPIOA) ? RCC_APB2ENR_IOPAEN : \
							(I2C1_SCL_PORT == GPIOB) ? RCC_APB2ENR_IOPBEN : \
							(I2C1_SCL_PORT == GPIOC) ? RCC_APB2ENR_IOPCEN : \
							RCC_APB2ENR_IOPDEN)
		#define I2C1_GPIO_CLK_SDA		((I2C1_SDA_PORT == GPIOA) ? RCC_APB2ENR_IOPAEN : \
							(I2C1_SDA_PORT == GPIOB) ? RCC_APB2ENR_IOPBEN : \
							(I2C1_SDA_PORT == GPIOC) ? RCC_APB2ENR_IOPCEN : \
							RCC_APB2ENR_IOPDEN)
	#endif

	#ifdef USE_I2C2
		#define I2C2_CR1_PEC_CHECKING		0x00		/* Packet error checking */
		#define I2C2_CR1_POS			0x00		/* Acknowledge/PEC Position (for data reception) */
		#define I2C2_CR1_ACK			I2C_CR1_ACK	/* Return acknowledge after receiving byte (matched address or data)*/
		#define I2C2_CR1_CLK_STRETCH_DISABLE	0x00		/* Used to disabling clock stretching in slave-mode when
									ADDR or BTF bit is set, until it is reset by softwear */
		#define I2C2_CR1_GEN_CALL		0x00		/* General call (0 - address 0x00 is NACKed) */
		#define I2C2_CR1_PEC			0x00		/* PEC calculation (0 - PEC calculation disabled) */
		#define I2C2_CR1_ARP			0x00		/* Address Resolution Protocol  (0 - ARP disabled) */
		#define	I2C2_CR1_SMBTYPE		0x00		/* SMBus type (0 - SMBus Device; 1 - SMBus Host) */
		#define	I2C2_CR1_SMBUS			0x00		/* SMBus mode (0 - I2C mode; 1 - SMBus mode) */

		#define	I2C2_CR2_DMA			0x00		/* DMA requests enable (0 - disabled; 1 - enabled ) */
		#define	I2C2_CR2_ITBUF			I2C_CR2_ITBUFEN	/* I2C buffer interrupt (0 - disabled; 1 - enabled ) */
		#define	I2C2_CR2_ITEV			I2C_CR2_ITEVTEN	/* I2C event interrupt (0 - disabled; 1 - enabled ) */
		#define	I2C2_CR2_ITERR			0x00		/* I2C error interrupt (0 - disabled; 1 - enabled ) */

		#define I2C2_OAR1_ADDR_MODE		((I2C2_USE_10BIT_ADDR_MODE) ? I2C_OAR1_ADDMODE : 0)		/* 7-bit slave address */
		#define I2C2_ADDR_16BIT			((uint16_t) I2C2_OWN_ADDRESS)
		#define I2C2_OAR1_OWN_ADDR		((I2C2_USE_10BIT_ADDR_MODE) ? (I2C2_ADDR_16BIT & 0x03FF) : ((I2C2_ADDR_16BIT & 0x007F) << 1u))
		#define I2C2_OAR2_DUAL_ADRESSING	0x00		/* dual addressing is disabled */

		#define	I2C2_CCR_FS			((I2C2_MODE) ? I2C_CCR_FS : 0)
		#define	I2C2_CCR_DUTY			((I2C2_FM_DUTY_CYCLE) ? I2C_CCR_DUTY : 0)

		#define I2C2_CR1_CFG_MASK		(((uint16_t) I2C2_CR1_PEC_CHECKING) | \
							I2C2_CR1_POS | I2C2_CR1_ACK | \
							I2C2_CR1_CLK_STRETCH_DISABLE | \
							I2C2_CR1_GEN_CALL | I2C2_CR1_PEC | \
							I2C2_CR1_ARP | I2C2_CR1_SMBTYPE | I2C2_CR1_SMBUS)
		#define	I2C2_CR2_CFG_MASK		(((uint16_t) I2C2_CR2_DMA) | \
							I2C2_CR2_ITBUF | I2C2_CR2_ITEV | \
							I2C2_CR2_ITERR)
		#define	I2C2_OAR1_CFG_MASK		(((uint16_t) I2C2_OAR1_ADDR_MODE) | I2C2_OAR1_OWN_ADDR)
		#define	I2C2_OAR2_CFG_MASK		((uint16_t) I2C2_OAR2_DUAL_ADRESSING)
		#define	I2C2_CCR_CFG_MASK		(((uint16_t) I2C2_CCR_FS) | I2C2_CCR_DUTY)

		#define I2C2_CFG_STRUCT			{(uint32_t)I2C2_CLK_FREQ, I2C2_CR1_CFG_MASK,\
							I2C2_CR2_CFG_MASK, I2C2_OAR1_CFG_MASK,\
							I2C2_OAR2_CFG_MASK,	I2C2_CCR_CFG_MASK}
		#define I2C2_GPIO_CLK_SCL		((I2C2_SCL_PORT == GPIOA) ? RCC_APB2ENR_IOPAEN : \
							(I2C2_SCL_PORT == GPIOB) ? RCC_APB2ENR_IOPBEN : \
							(I2C2_SCL_PORT == GPIOC) ? RCC_APB2ENR_IOPCEN : \
							RCC_APB2ENR_IOPDEN)
		#define I2C2_GPIO_CLK_SDA		((I2C2_SDA_PORT == GPIOA) ? RCC_APB2ENR_IOPAEN : \
							(I2C2_SDA_PORT == GPIOB) ? RCC_APB2ENR_IOPBEN : \
							(I2C2_SDA_PORT == GPIOC) ? RCC_APB2ENR_IOPCEN : \
							RCC_APB2ENR_IOPDEN)
	#endif
	//============================
		//type definition for definition i2c configuration sets
		typedef struct {
			uint32_t clkFrq;		/*Specifies the CLK frequency, Hz.*/
			uint16_t cr1;			/*CR1 register presets*/
			uint16_t cr2;			/*CR2 register presets*/
			uint16_t oar1;			/*OAR1 register presets*/
			uint16_t oar2;			/*OAR2 register presets*/
			uint16_t ccr;			/*CCR register presets*/
		} I2C_Cfg_TypeDef;

		#define PORT_CRx(port, pin)			((pin >= 8)?(port -> CRH):(port -> CRL))
		#define CRx_MODE_AF_Clr_Msk(pin)		(0x0000000F << (pin%8)*4)
		#define CRx_I2C_Set_Msk(pin)			(GPIO_CRL_MODE0|GPIO_CRL_CNF0) << (pin%8)*4
		#define SET_MODE_AF_I2C(port,pin)  		MODIFY_REG(PORT_CRx(port,pin), CRx_MODE_AF_Clr_Msk(pin), CRx_I2C_Set_Msk(pin))

		#define I2C_SR1_FAILURES_BITS		(I2C_SR1_AF | I2C_SR1_ARLO | I2C_SR1_BERR | I2C_SR1_TIMEOUT)
		#define CRx_RESET_BITS(port, pin)	(PORT_CRx(port, pin) & ~(0x0000000F << (pin%8)*4))
		#define IS_BIT_SET(reg, bitMsk)		(READ_BIT(reg,(bitMsk)) == (bitMsk))
		#define _DEBUG_SET_MODE_OUT(port, pin)	(PORT_CRx(port, pin) = CRx_RESET_BITS(port, pin)|(GPIO_CRL_MODE0_1 << (pin%8)*4))
		#define _DEBUG_RESET_BIT(port, pin)	(port->BRR = 1u << pin)
		#define _DEBUG_SET_BIT(port, pin)	(port->BSRR |= 1u << pin)

    #ifdef __cplusplus
		    }
    #endif

#endif /* _I2C_DEF_H_ */

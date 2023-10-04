#ifndef LCD_CONF_H
#define LCD_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

//define STM device type
#include "stm32f1xx.h"

#define I2C_LCD_ADDRESS	            0x27               /* Hardware address on i2c module, if using i2c-module (read I2C-controller datasheets)*/

#ifdef I2C_LCD_ADDRESS
    #define E_PIN                       2              /* Bit number LCD_E on i2c module (according to the actual connection)*/
    #define RS_PIN                      0              /* Bit number LCD_RS on i2c module (according to the actual connection)*/

    #define D7_PIN                      7               /* Bit number LCD_D7 on i2c module (according to the actual connection)*/
    #define D6_PIN                      6               /* Bit number LCD_D6 on i2c module (according to the actual connection)*/
    #define D5_PIN                      5               /* Bit number LCD_D5 on i2c module (according to the actual connection)*/
    #define D4_PIN                      4               /* Bit number LCD_D4 on i2c module (according to the actual connection)*/

    #define BACKLIGHT_PIN			3		/* Bit number LCD_BACKLIGHT on i2c module (according to the actual connection)*/


#else
    /* E - Starts data read/write. */
    #define E_PORT					    GPIOA                	/* GPIOx port by CMSIS definitions (according to the actual connection)*/
    #define E_PIN   	 				1				        /* Pin number (according to the actual connection)*/

    /* RS - Selects registers.
     * 0:	Instruction register (for write)
     * 0:	Busy flag + address counter (for read)
     * 1:	Data register (for write and read) */
    #define RS_PORT 					GPIOA                	/* GPIOx port by CMSIS definitions (according to the actual connection)*/
    #define RS_PIN 						2           			/* Pin number (according to the actual connection)*/
    
    /* DB4 to DB7 - Four high order bidirectional tristate data bus pins.
     * Used for data transfer and receive between the MPU and the HD44780U.
     * DB7 can be used as a busy flag. */
    #define D7_PORT 					GPIOB                	/* GPIOx port by CMSIS definitions (according to the actual connection) */
    #define D7_PIN 	 					7			            /* Pin number (according to the actual connection) */
    
    #define D6_PORT 					GPIOB                	/* GPIOx port by CMSIS definitions (according to the actual connection) */
    #define D6_PIN 	 					6			            /* Pin number (according to the actual connection) */

    #define D5_PORT 					GPIOB                	/* GPIOx port by CMSIS definitions (according to the actual connection) */
    #define D5_PIN 	 					5			            /* Pin number (according to the actual connection) */

    #define D4_PORT 					GPIOB                	/* GPIOx port by CMSIS definitions (according to the actual connection) */
    #define D4_PIN 	 					4			            /* Pin number (according to the actual connection) */


    #define BACKLIGHT_PORT 					GPIOB                	/* GPIOx port by CMSIS definitions (according to the actual connection) */
    #define BACKLIGHT_PIN 	 					3			            /* Pin number (according to the actual connection) */
#endif    
 
    //-- CHARACTERS CODING CONFIG --//

    #define UTF8
    //#define CP1251

    //-- DISPLAY CONFIG MACROS --//

    #define LINE_QUANTITY			2		    /*quantity of lines in LCD screen: 1, 2 or 4*/
    #define LINE_LENGTH				16		    /*length of one LCD line */
    #define SET_COURSOR                         1                   /* Show coursor by default: 1 - ON, 0 - OFF  */
    #define SET_BLINKING                        1                   /* Enable blinking for coursor by default: 1 - ON, 0 - OFF  */
    #define SET_SHIFT_DISPLAY                   0                   /* Shift display with new symbol: 1 - ON, 0 - OFF  */
    #define SET_SHIFT_INCREMENT                 1                   /* Shift coursor for next new symbol adress: 1 - by incrementing, 0 - by decrementing */
    
    #define START_WITH_BACKLIGHT_ON		1			/*Backlight on automaticaly after LCD-initalization */

#ifdef __cplusplus
}
#endif   


#endif      /*LCD_CONF_H*/

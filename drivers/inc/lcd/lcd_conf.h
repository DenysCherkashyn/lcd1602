/*
 * 	lcd_conf.h
 *
 *	Created on: 06 November 2023
 *      Author: D.Cherkashin
 *
 *      lcd driver configuration header file.
 *      Contains configuration parameters for work with lcd display
 *      You need configure lcd work only here.
 *      For more information see readme.md file
 *
 */

#ifndef _LCD_CONF_H_
#define _LCD_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

//define STM device type here!!!
#include "stm32f1xx.h"


//------------------------------//
//-- CHARACTERS CODING CONFIG --//

    #define UTF8
    //#define CP1251					/* not working yet!!! */

    #include <lcd/lcd_charTable_winstar.h>			/*Connecting the symbols table for the corresponding LCD-сontroller*/

//------------------------------//
//-- CONNECTING CONFIGS --//

#define I2C_LCD_ADDRESS	            	0x27            /* Hardware address on i2c module, if using i2c-module (read I2C-controller datasheets)*/

#ifdef I2C_LCD_ADDRESS
    #define E_PIN                       2               /* Bit number LCD_E on i2c module (according to the actual connection)*/
    #define RS_PIN                      0               /* Bit number LCD_RS on i2c module (according to the actual connection)*/
    #define D7_PIN                      7               /* Bit number LCD_D7 on i2c module (according to the actual connection)*/
    #define D6_PIN                      6               /* Bit number LCD_D6 on i2c module (according to the actual connection)*/
    #define D5_PIN                      5               /* Bit number LCD_D5 on i2c module (according to the actual connection)*/
    #define D4_PIN                      4               /* Bit number LCD_D4 on i2c module (according to the actual connection)*/
    #define BACKLIGHT_PIN		3		/* Bit number LCD_BACKLIGHT on i2c module (according to the actual connection)*/

#else
    /* E - Starts data read/write. */
    #define E_PORT					GPIOA                	/* GPIOx port by CMSIS definitions (according to the actual connection)*/
    #define E_PIN   	 				1		        /* Pin number (according to the actual connection)*/
    /* RS - Selects registers.
     * 0:	Instruction register (for write)
     * 0:	Busy flag + address counter (for read)
     * 1:	Data register (for write and read) */
    #define RS_PORT 					GPIOA                	/* GPIOx port by CMSIS definitions (according to the actual connection)*/
    #define RS_PIN 					2     			/* Pin number (according to the actual connection)*/
    
    /* DB4 to DB7 - Four high order bidirectional tristate data bus pins.
     * Used for data transfer and receive between the MPU and the HD44780U.
     * DB7 can be used as a busy flag. */
    #define D7_PORT 					GPIOB                	/* GPIOx port by CMSIS definitions (according to the actual connection) */
    #define D7_PIN 					7			/* Pin number (according to the actual connection) */
    
    #define D6_PORT 					GPIOB                	/* GPIOx port by CMSIS definitions (according to the actual connection) */
    #define D6_PIN 	 				6			/* Pin number (according to the actual connection) */

    #define D5_PORT 					GPIOB                	/* GPIOx port by CMSIS definitions (according to the actual connection) */
    #define D5_PIN 	 				5		        /* Pin number (according to the actual connection) */

    #define D4_PORT 					GPIOB                	/* GPIOx port by CMSIS definitions (according to the actual connection) */
    #define D4_PIN 	 				4			/* Pin number (according to the actual connection) */

    #define BACKLIGHT_PORT 				GPIOB                	/* GPIOx port by CMSIS definitions (according to the actual connection) */
    #define BACKLIGHT_PIN 	 			3			/* Pin number (according to the actual connection) */
#endif    


    //------------------------------//
    //-- DISPLAY CONFIG MACROS --//

    #define LINE_QUANTITY			2		    /*quantity of lines in LCD screen: 1, 2 or 4*/
    #define LINE_LENGTH				40		    /*length of one line */
    #define SCREEN_WIDTH			16		    /*screen width*/
    #define CHAR_HEIGHT				8		    /*quantity dots for character height: 8 or 10*/
    #define SET_COURSOR                         1                   /* Show coursor by default: 1 - ON, 0 - OFF  */
    #define SET_BLINKING                        0                   /* Enable blinking for coursor by default: 1 - ON, 0 - OFF  */
    #define SET_SHIFT_DISPLAY                   1                   /* Move the display if the cursor position goes beyond the right screen border.: 1 - ON, 0 - OFF  */
    #define START_WITH_BACKLIGHT_ON		1		    /*Backlight on automaticaly after LCD-initalization */

#ifdef __cplusplus
}
#endif   


#endif      /*_LCD_CONF_H_*/

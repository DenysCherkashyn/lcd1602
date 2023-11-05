#ifndef LCD_DEF_H
#define LCD_DEF_H


#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------
// SET MCU TIMINGS
//-------------------------------
#define BUSY_CYCLE_TIME				50u					/* x 1us. See datasheet for minimal value. NOT LESS THEN 50us !!!*/
#define CLRSCR_CYCLE_TIME			1500u					/* x 1us. See datasheet for minimal value. */
#define RETHOME_CYCLE_TIME			2000u					/* x 1us. See datasheet for minimal value. */
#define INIT_CYCLE_TIME				5000u

//-------------------------------
// DISPLAY SETS
//-------------------------------
#if(LINE_QUANTITY == 1)
    #define DISPLAY_CONFIG      		0x20u                   /* Use 4-bit interface, 1 Line, 5x8 pixel resolution */

#elif(LINE_QUANTITY == 2 || LINE_QUANTITY == 4)
    #define DISPLAY_CONFIG		        0x28u                   /* Use 4-bit interface, 2 or 4 Lines, 5x8 pixel resolution */
#else
    #define LINE_QUANTITY	    		2
    #define DISPLAY_CONFIG		        0x28u                   /* Use 4-bit interface, 2 or 4 Lines, 5x8 pixel resolution */
#endif


#define	START_POSITION_LINE_1			0x00u
#define START_POSITION_LINE_2			0x40u
#define START_POSITION_LINE_3			(START_POSITION_LINE_1 + LINE_LENGTH)
#define START_POSITION_LINE_4			(START_POSITION_LINE_2 + LINE_LENGTH)
#define CURSOR_POSITION_MAX			(LINE_LENGTH-1)
#define PROGRESS_BAR_WIDTH 			(SCREEN_WIDTH - 4)
//#define END_POSITION_LINE_1			(START_POSITION_LINE_1 + (LINE_LENGTH-1))
//#define END_POSITION_LINE_2			(START_POSITION_LINE_2 + (LINE_LENGTH-2))
//#define END_POSITION_LINE_3			(START_POSITION_LINE_3 + (LINE_LENGTH-3))
//#define END_POSITION_LINE_4			(START_POSITION_LINE_4 + (LINE_LENGTH-4))


#define CLEAR_DISPLAY               0x01
#define RETURN_HOME                 0x02
#define COURSOR_SHIFT_INCREMENT     0x02                    /* I/D bit, inverse bit - enable decrement coursor shifting */
#define SHIFT_DISPLAY_WITH_COURSOR  0x01                    /* SH bit, inverse bit - display not shift */
#define DISPLAY_ON                  0x04                    /* D bit, inverse bit - display off */                    
#define COURSOR_ON                  0x02                    /* C bit, inverse bit - coursor off */
#define COURSOR_BLINKING_ON         0x01                    /* B bit, inverse bit - coursor blinking off*/
#define SHIFT_POSITION_DISPLAY      0x01                    /* S/C bit, inverse bit - enable coursor position shifting */
#define SHIFT_POSITION_RIGHT        0x01                    /* R/L bit, inverse bit - enable shifting to the left */

// user's defaults display sets
#define ENTRY_MODE_DEFAULT              (0x04 | COURSOR_SHIFT_INCREMENT)
                                      
#define DISPLAY_CONTROL_DEFAULT         (0x08 | ((SET_COURSOR)?(COURSOR_ON):0)\
                                              | ((SET_BLINKING)?(COURSOR_BLINKING_ON):0))

#ifndef I2C_LCD_ADDRESS
    #define PORT_CRx(port, pin)            ((pin >= 8)?(port -> CRH):(port -> CRL))
    #define CRx_RESET_BITS(port, pin)      (PORT_CRx(port, pin) & ~(0x0000000F << (pin%8)*4))
    //#define SET_MODE_IN(port, pin)         (PORT_CRx(port, pin) = CRx_RESET_BITS(port, pin)|(GPIO_CRL_CNF0_1 << (pin%8)*4))
    #define SET_MODE_OUT(port, pin)        (PORT_CRx(port, pin) = CRx_RESET_BITS(port, pin)|(GPIO_CRL_MODE0_1 << (pin%8)*4))
    #define PORT_PIN_SET(port, pin)        (port->BSRR |= 1u << pin)
    #define PORT_PIN_RESET(port, pin)      (port->BRR = 1u << pin)
    //#define PORT_PIN_GET(port, pin)        ((port->IDR) & (1u << pin))
#else
    #define E_PORT			nullptr
    #define RS_PORT			nullptr

    #define D4_PORT			nullptr
    #define D5_PORT			nullptr
    #define D6_PORT			nullptr
    #define D7_PORT			nullptr
    #define BACKLIGHT_PORT		nullptr
    #define BIT_READ_MASK		((1u << D4_PIN) | (1u << D5_PIN) | (1u << D6_PIN) | (1u << D7_PIN))
   // #define SET_MODE_AF_I2C(port,pin)  (PORT_CRx(port, pin) = CRx_RESET_BITS(port, pin)|((GPIO_CRL_MODE0|GPIO_CRL_CNF0) << (pin%8)*4))
#endif                                

#ifdef __cplusplus
}
#endif   

#endif      /*LCD_DEF_H*/

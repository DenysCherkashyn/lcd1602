/*
 * charTable.h
 *
 *  Created on: 20 сент. 2023 г.
 *      Author: Master
 */

#ifndef LCD_CHARTABLE_WINSTAR_H
#define LCD_CHARTABLE_WINSTAR_H


#ifdef UTF8

#define CYR_H_A			0xD090		/*А*/
#define CYR_H_B			0xD091		/*Б*/
#define CYR_H_V			0xD092		/*В*/
#define CYR_H_H			0xD093		/*Г*/
#define CYR_H_D			0xD094		/*Д*/
#define CYR_H_E			0xD095		/*Е*/
#define CYR_H_E_RU		0xD0AD		/*Э*/
#define CYR_H_YE		0xD084		/*Є*/
#define CYR_H_ZH		0xD096		/*Ж*/
#define CYR_H_Z			0xD097		/*З*/
#define CYR_H_Y			0xD098		/*И*/
#define CYR_H_Y_RU		0xD0AB		/*Ы*/
#define CYR_H_I_UA		0xD0086		/*І*/
#define CYR_H_I_RU		CYR_H_Y		/*И*/
#define CYR_H_YI		0xD087		/*Ї*/
#define CYR_H_Y_		0xD099		/*Й*/
#define CYR_H_K			0xD09A		/*К*/
#define CYR_H_L			0xD09B		/*Л*/
#define CYR_H_M			0xD09C		/*М*/
#define CYR_H_N			0xD09D		/*Н*/
#define CYR_H_O			0xD09E		/*О*/
#define CYR_H_P			0xD09F		/*П*/
#define CYR_H_R			0xD0A0		/*Р*/
#define CYR_H_S			0xD0A1		/*С*/
#define CYR_H_T			0xD0A2		/*Т*/
#define CYR_H_U			0xD0A3		/*У*/
#define CYR_H_F			0xD0A4		/*Ф*/
#define CYR_H_KH		0xD0A5		/*Х*/
#define CYR_H_TS		0xD0A6		/*Ц*/
#define CYR_H_CH		0xD0A7		/*Ч*/
#define CYR_H_SH		0xD0A8		/*Ш*/
#define CYR_H_SHCH		0xD0A9		/*Щ*/
#define CYR_H_SOFT_SIGN		0xD0AC		/*Ь*/
#define CYR_H_SOLID_SIGN	0xD0AA		/*Ъ*/
#define CYR_H_YU		0xD0AE		/*Ю*/
#define CYR_H_YA		0xD0AF		/*Я*/

#define CYR_L_A			0xD0B0		/*а*/
#define CYR_L_B			0xD0B1		/*б*/
#define CYR_L_V			0xD0B2		/*в*/
#define CYR_L_H			0xD0B3		/*г*/
#define CYR_L_D			0xD0B4		/*д*/
#define CYR_L_E			0xD0B5		/*е*/
#define CYR_L_E_RU		0xD18D		/*э*/
#define CYR_L_YE		0xD194		/*є*/
#define CYR_L_ZH		0xD0B6		/*ж*/
#define CYR_L_Z			0xD0B7		/*з*/
#define CYR_L_Y			0xD0B8		/*и*/
#define CYR_L_Y_RU		0xD18B		/*ы*/
#define CYR_L_I_UA		0xD196		/*і*/
#define CYR_L_I_RU		CYR_L_Y		/*и*/
#define CYR_L_YI		0xD197		/*ї*/
#define CYR_L_Y_		0xD0B9		/*й*/
#define CYR_L_K			0xD0BA		/*к*/
#define CYR_L_L			0xD0BB		/*л*/
#define CYR_L_M			0xD0BC		/*м*/
#define CYR_L_N			0xD0BD		/*н*/
#define CYR_L_O			0xD0BE		/*о*/
#define CYR_L_P			0xD0BF		/*п*/
#define CYR_L_R			0xD180		/*р*/
#define CYR_L_S			0xD181		/*с*/
#define CYR_L_T			0xD182		/*т*/
#define CYR_L_U			0xD183		/*у*/
#define CYR_L_F			0xD184		/*ф*/
#define CYR_L_KH		0xD185		/*х*/
#define CYR_L_TS		0xD186		/*ц*/
#define CYR_L_CH		0xD187		/*ч*/
#define CYR_L_SH		0xD188		/*ш*/
#define CYR_L_SHCH		0xD189		/*щ*/
#define CYR_L_SOFT_SIGN		0xD18C		/*ь*/
#define CYR_L_SOLID_SIGN	0xD18A		/*ъ*/
#define CYR_L_YU		0xD18E		/*ю*/
#define CYR_L_YA		0xD18F		/*я*/


#define CYR_APOSTROPHE	0x00


#define CHAR_TABLE {\
    {CYR_H_A, 0b01000001},	/*А*/\
    {CYR_H_B, 0b10100000},	/*Б*/\
    {CYR_H_V, 0b01000010},	/*В*/\
    {CYR_H_H, 0b10100001},	/*Г*/\
    {CYR_H_D, 0b11100000},	/*Д*/\
    {CYR_H_E, 0b01000101},	/*Е*/\
    {CYR_H_E_RU, 0b10101111},	/*Э*/\
    {CYR_H_YE, 0b01000101},	/*Є*/\
    {CYR_H_ZH, 0b10100011},	/*Ж*/\
    {CYR_H_Z, 0b10100100},	/*З*/\
    {CYR_H_Y, 0b10100101},	/*И*/\
    {CYR_H_Y_RU, 0b10101110},	/*Ы*/\
    {CYR_H_I_UA, 0b01001001},	/*І*/\
    {CYR_H_YI, 0b01001001},	/*Ї*/\
    {CYR_H_Y_, 0b10100110},	/*Й*/\
    {CYR_H_K, 0b01001011},	/*К*/\
    {CYR_H_L, 0b10100111},	/*Л*/\
    {CYR_H_M, 0b01001101},	/*М*/\
    {CYR_H_N, 0b01001000},	/*Н*/\
    {CYR_H_O, 0b01001111},	/*О*/\
    {CYR_H_P, 0b10101000},	/*П*/\
    {CYR_H_R, 0b01010000},	/*Р*/\
    {CYR_H_S, 0b01000011},	/*С*/\
    {CYR_H_T, 0b01010100},	/*Т*/\
    {CYR_H_U, 0b10101001},	/*У*/\
    {CYR_H_F, 0b10101010},	/*Ф*/\
    {CYR_H_KH, 0b01011000},	/*Х*/\
    {CYR_H_TS, 0b11100001},	/*Ц*/\
    {CYR_H_CH, 0b10101011},	/*Ч*/\
    {CYR_H_SH, 0b10101100},	/*Ш*/\
    {CYR_H_SHCH, 0b11100010},	/*Щ*/\
    {CYR_H_SOFT_SIGN, 0b01100010},	/*Ь*/\
    {CYR_H_SOLID_SIGN, 0b10101101},	/*Ъ*/\
    {CYR_H_YU, 0b10110000},	/*Ю*/\
    {CYR_H_YA, 0b10110001},	/*Я*/\
    {CYR_L_A, 0b01100001},	/*а*/\
    {CYR_L_B, 0b10110010},	/*б*/\
    {CYR_L_V, 0b10110011},	/*в*/\
    {CYR_L_H, 0b10110100},	/*г*/\
    {CYR_L_D, 0b11100011},	/*д*/\
    {CYR_L_E, 0b01100101},	/*е*/\
    {CYR_L_E_RU, 0b11000101},	/*э*/\
    {CYR_L_YE, 0b01100101},	/*є*/\
    {CYR_L_ZH, 0b10110110},	/*ж*/\
    {CYR_L_Z, 0b10110111},	/*з*/\
    {CYR_L_Y, 0b10111000},	/*и*/\
    {CYR_L_Y_RU, 0b11000011},	/*ы*/\
    {CYR_L_I_UA, 0b01101001},	/*і*/\
    {CYR_L_YI, 0b01101001},	/*ї*/\
    {CYR_L_Y_, 0b10111001},	/*й*/\
    {CYR_L_K, 0b10111010},	/*к*/\
    {CYR_L_L, 0b10111011},	/*л*/\
    {CYR_L_M, 0b10111100},	/*м*/\
    {CYR_L_N, 0b10111101},	/*н*/\
    {CYR_L_O, 0b01101111},	/*о*/\
    {CYR_L_P, 0b10111110},	/*п*/\
    {CYR_L_R, 0b01110000},	/*р*/\
    {CYR_L_S, 0b01100011},	/*с*/\
    {CYR_L_T, 0b10111111},	/*т*/\
    {CYR_L_U, 0b01111001},	/*у*/\
    {CYR_L_F, 0b11100100},	/*ф*/\
    {CYR_L_KH, 0b01111000},	/*х*/\
    {CYR_L_TS, 0b11100101},	/*ц*/\
    {CYR_L_CH, 0b11000000},	/*ч*/\
    {CYR_L_SH, 0b11000001},	/*ш*/\
    {CYR_L_SHCH, 0b11100110},	/*щ*/\
    {CYR_L_SOFT_SIGN, 0b11000100},	/*ь*/\
    {CYR_L_SOLID_SIGN, 0b11000010},	/*ъ*/\
    {CYR_L_YU, 0b11000110},	/*ю*/\
    {CYR_L_YA, 0b11000111},	/*я*/\
    {CYR_APOSTROPHE, 0b11100111}	/*'*/\
}
#endif

#endif /* DRIVERS_INC_CHARTABLE_H_ */

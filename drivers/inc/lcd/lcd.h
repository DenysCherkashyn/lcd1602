/*
 * 	lcd.h
 *
 *	Created on: 06 Novmber 2023
 *      Author: D.Cherkashin
 *
 *      General lcd driver header file.
 *      Defines class attributes and methods.
 *      Defines file include for definite stm32 controller type
 *      For more information see readme.md file
 *
 */


#ifndef _LCD_H_
#define _LCD_H_

#include <lcd/lcd_conf.h>
#include <lcd/lcd_def.h>
#include <unordered_map>
#include <string>




// --- CLASS DEFINITION ---//

class LCD final {
     private:
	const std::unordered_map<uint16_t, uint8_t> charTable = CHAR_TABLE;
        bool initialized = false;
        uint8_t lastTransferDataByte;
        uint8_t line;
        uint8_t cursorPosition;
        uint8_t displayPosition;
	#ifdef I2C_LCD_ADDRESS
	    void (*i2cMasterWrite) (uint16_t, uint8_t*) = nullptr;
	#endif
    
        LCD (){};
        ~LCD (){};
        LCD (const LCD&);
        const LCD& operator = (const LCD&);

    #ifdef I2C_LCD_ADDRESS
        void i2cDisconnect();
    #else
        void gpioSet ();
    #endif
        void setBit(GPIO_TypeDef *, uint8_t);
	void resetBit(GPIO_TypeDef *, uint8_t);
        void setLow (uint8_t);
        void setHigh (uint8_t);
        void strobe ();
        void delay_us (uint32_t);
        void write(uint8_t);
        void writeInstruction(uint8_t);
        void config(uint8_t);
        void init();
        uint8_t checkSym(uint16_t&);
        std::string intToStr(int);
        void alignDisplayPosition();
            
        
    public:
      #ifdef I2C_LCD_ADDRESS
	static LCD& getInstance(void (*i2cWriteFunc)(uint16_t, uint8_t*));
      #endif

	static LCD& getInstance();
	void backlightOn ();
	void backlightOff ();
	void on ();
	void off ();
	void clear ();
	void clearLine(uint8_t);
	void home ();
	void goTo (uint8_t, uint8_t);
	void shiftCursorLeft(uint8_t);
	void shiftCursorLeft();
	void shiftCursorRight(uint8_t);
	void shiftCursorRight();
	void shiftDisplayLeft(uint8_t);
	void shiftDisplayLeft();
	void shiftDisplayRight(uint8_t);
	void shiftDisplayRight();
	uint8_t getLine();
	uint8_t getCursorPosition();
	uint8_t getDisplayPosition();
	uint8_t getLineQuantity();
	uint8_t getCursorPositionMax();
	uint8_t getDisplayWidth();
	bool isEndOfLine();
	void loadCGROM(uint8_t, uint8_t*);
	void printCGROM (uint8_t data);
	void printCh (uint16_t data);
	void print (std::string, uint8_t);
	void print (std::string);
	void print (int, uint8_t);
	void print (int);
	void print (double, uint8_t);
	void print (double);
	void print (float, uint8_t);
	void print (float);
	void printHex(int data, uint8_t digits);
	void backspace();
	void progressBar(float, uint16_t);
	void progressBar(float);
};
    
#endif      /*_LCD_H_*/

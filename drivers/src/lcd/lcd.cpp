/*
 * 	lcd.cpp
 *
 *	Created on: 09 September 2023
 *      Author: D.Cherkashin
 *
 *      This lcd-driver class for work in STM32 controllers (f1xx-series) with
 *      LCD screen by  GPIOx-port or i2c connection with i2c driver/
 *      For more information see readme.md file
 *
 */

#include <lcd/lcd.h>
#include "stm32f1xx.h"


/*****************************************
 *
 * 	PRIVATE METHODS AND PROPERTIES
 *
 *****************************************/
#ifdef I2C_LCD_ADDRESS
void LCD::i2cDisconnect() {
    i2cMasterWrite(I2C_LCD_ADDRESS, nullptr);
}

#else
void LCD::gpioSet ( ) {
    RCC->AHBENR |= RCC_APB2ENR_IOPBEN;
    SET_MODE_OUT(E_PORT, E_PIN);
    resetBit(E_PORT, E_PIN);
    SET_MODE_OUT(RS_PORT, RS_PIN);
    resetBit(RS_PORT, RS_PIN);
    SET_MODE_OUT(D4_PORT, D4_PIN);
    SET_MODE_OUT(D5_PORT, D5_PIN);
    SET_MODE_OUT(D6_PORT, D6_PIN);
    SET_MODE_OUT(D7_PORT, D7_PIN);
}
#endif

void LCD::setBit(GPIO_TypeDef* port, uint8_t pin) {
    #ifdef I2C_LCD_ADDRESS
	SET_BIT(lastTransferDataByte, (0x01 << pin));
    #else
	PORT_PIN_SET(port, pin);
    #endif
}

void LCD::resetBit(GPIO_TypeDef* port, uint8_t pin) {
    #ifdef I2C_LCD_ADDRESS
	CLEAR_BIT(lastTransferDataByte, (0x01 << pin));
    #else
	PORT_PIN_RESET(port, pin);
    #endif
}

void LCD::setLow (uint8_t data) {
    (data & 0x08) ? setBit(D7_PORT, D7_PIN) : resetBit(D7_PORT, D7_PIN);
    (data & 0x04) ? setBit(D6_PORT, D6_PIN) : resetBit(D6_PORT, D6_PIN);
    (data & 0x02) ? setBit(D5_PORT, D5_PIN) : resetBit(D5_PORT, D5_PIN);
    (data & 0x01) ? setBit(D4_PORT, D4_PIN) : resetBit(D4_PORT, D4_PIN);
}

void LCD::setHigh (uint8_t data) {
    data = data >> 4;
    setLow(data);
}

void LCD::strobe ( ) {
    #ifdef I2C_LCD_ADDRESS
	i2cMasterWrite(I2C_LCD_ADDRESS, &lastTransferDataByte);
    #endif
    delay_us(BUSY_CYCLE_TIME);
    setBit(E_PORT, E_PIN);
    #ifdef I2C_LCD_ADDRESS
	i2cMasterWrite(I2C_LCD_ADDRESS, &lastTransferDataByte);
    #endif
    delay_us(BUSY_CYCLE_TIME);
    resetBit(E_PORT, E_PIN);
    #ifdef I2C_LCD_ADDRESS
	i2cMasterWrite(I2C_LCD_ADDRESS, &lastTransferDataByte);
    #endif
}

void LCD::delay_us (uint32_t us) {
    us *= (SystemCoreClock/1000000);
    while(us>0) {
	--us;
    };
}

void LCD::write (uint8_t data) {
    setHigh(data);
    strobe();
    setLow(data);
    strobe();
    delay_us(BUSY_CYCLE_TIME);
}

void LCD::writeInstruction(uint8_t data) {
    resetBit(RS_PORT, RS_PIN);
    write(data);
    #ifdef I2C_LCD_ADDRESS
	i2cDisconnect();
    #endif
}

void LCD::config (uint8_t data) {
    setHigh(data);
    strobe();
    delay_us(BUSY_CYCLE_TIME);
    strobe();
    setLow(data);
    strobe();
    delay_us(BUSY_CYCLE_TIME);
}

void LCD::init ( ) {
    #ifndef I2C_LCD_ADDRESS
	gpioSet();
    #endif
    //LCD initializing:
    delay_us(15000);
    write(0x30);
    delay_us(INIT_CYCLE_TIME);
    write(0x30);
    delay_us(100);
    write(0x30);
    delay_us(100);
    write(0x20);                        		//set 4-bit interface
    delay_us(50);
    config(DISPLAY_CONFIG);              		//display sets
    write(DISPLAY_CONTROL_DEFAULT);     		//display off and coursor set
    delay_us(50);
    write(CLEAR_DISPLAY);		    		//clear display
    write(ENTRY_MODE_DEFAULT);          		//display entry mode sets
    delay_us(50);
    if(START_WITH_BACKLIGHT_ON)  {
	backlightOn();
	write(DISPLAY_CONTROL_DEFAULT|DISPLAY_ON); 	//display on
    };
    // strobe();		`//try uncomment it if have some problem during initialization LCD
    home();
    initialized = true;
    #ifdef I2C_LCD_ADDRESS
	i2cDisconnect();
    #endif
}

uint8_t LCD::checkSym(uint16_t& in) {
    return (in<0x07B) ? (uint8_t)in : charTable.at(in);
}

std::string LCD::intToStr(int value) {
    return std::to_string(value);
}

void LCD::alignDisplayPosition() {
    if(cursorPosition < displayPosition) {
	uint8_t shift = displayPosition-cursorPosition;
	if (shift > CURSOR_POSITION_MAX/2) {
	    shift = LINE_LENGTH - shift;
	    shiftDisplayLeft(shift);
	}
	else {
	    shiftDisplayRight(shift);
	};
    }
    else if (SET_SHIFT_DISPLAY && cursorPosition > (displayPosition+SCREEN_WIDTH-1)) {
	shiftDisplayLeft(cursorPosition - (displayPosition+SCREEN_WIDTH-1));
    };
}


/*****************************************
 *
 * 	PUBLIC METHODS AND PROPERTIES
 *
 *****************************************/

#ifdef I2C_LCD_ADDRESS
LCD& LCD::getInstance(void (*i2cWriteFunc) (uint16_t, uint8_t*)) {
	static LCD instance;
	instance.i2cMasterWrite = i2cWriteFunc;
	if (!instance.initialized)
	    instance.init();
    return instance;
};
#endif

LCD& LCD::getInstance( ) {
    static LCD instance;
    if (!instance.initialized)
	instance.init();
    return instance;
}

void LCD::backlightOn( ) {
    setBit(BACKLIGHT_PORT, BACKLIGHT_PIN);
}

void LCD::backlightOff( ) {
    resetBit(BACKLIGHT_PORT, BACKLIGHT_PIN);
}

void LCD::on( ) {
    backlightOn();
    writeInstruction(DISPLAY_CONTROL_DEFAULT|DISPLAY_ON);
}

void LCD::off( ) {
    backlightOff();
    writeInstruction(DISPLAY_CONTROL_DEFAULT);
}

void LCD::clear( ) {
    writeInstruction(CLEAR_DISPLAY);
    delay_us(CLRSCR_CYCLE_TIME);
    line = 1u;
    cursorPosition = 0;
    displayPosition = 1;
}

void LCD::clearLine(uint8_t line) {
    std::string str;

    if(line == 0 || line > LINE_QUANTITY) {
	return;
    };
    for (uint8_t i = 0; i<LINE_LENGTH; ++i) {
	str +=" ";
    };
    goTo(line, 0);
    print(str);
    goTo(line, 0);
}

void LCD::home( ) {
    writeInstruction(RETURN_HOME);
    delay_us(RETHOME_CYCLE_TIME);
    line = 1u;
    cursorPosition = 0;
    displayPosition = 0;
}

void LCD::goTo(uint8_t lineNum, uint8_t position){
    if(lineNum > LINE_QUANTITY)	{
	return;
    };
    line = lineNum;
    switch (lineNum) {
	case 1u: lineNum = START_POSITION_LINE_1; break;
	case 2u: lineNum = START_POSITION_LINE_2; break;
	case 3u: lineNum = START_POSITION_LINE_3; break;
	case 4u: lineNum = START_POSITION_LINE_4; break;
    };
    position = (position > CURSOR_POSITION_MAX) ? CURSOR_POSITION_MAX : (position < 0) ? 0 : position;
    writeInstruction(0x80u | (lineNum + position));
    cursorPosition = position;
    alignDisplayPosition();
}

void LCD::shiftCursorLeft (uint8_t pos) {
    uint8_t i=0;

    while(i < pos && cursorPosition > 0) {
	writeInstruction(0x10);
	++i;
	--cursorPosition;
	if(cursorPosition < displayPosition) {
	    shiftDisplayRight();
	};
    };
}

void LCD::shiftCursorLeft () {
    shiftCursorLeft(1);
}

void LCD::shiftCursorRight (uint8_t pos) {
    uint8_t i=0;

    if(pos == 0) {
	pos = 1;
    };
    while(i < pos && cursorPosition < CURSOR_POSITION_MAX) {
	writeInstruction(0x14);
	++i;
	++cursorPosition;
	alignDisplayPosition();
    };
}

void LCD::shiftCursorRight () {
    shiftCursorRight(1);
}

void LCD::shiftDisplayLeft (uint8_t pos) {
    if(pos == 0) {
	pos = 1;
    };
    for(uint8_t i=0; i < pos; ++i) {
	writeInstruction(0x18);
	++displayPosition;
	if(displayPosition > CURSOR_POSITION_MAX)
	    displayPosition = 0;
    };
}

void LCD::shiftDisplayLeft () {
	shiftDisplayLeft(1);
}

void LCD::shiftDisplayRight (uint8_t pos) {
    if(pos == 0) {
	pos = 1;
    };
    for(uint8_t i=0; i < pos; ++i) {
	writeInstruction(0x1C);
	if(displayPosition == 0)
	    displayPosition = LINE_LENGTH;
	--displayPosition;
    };
}

void LCD::shiftDisplayRight () {
    shiftDisplayRight(1);
}

uint8_t LCD::getLine() {
    return line;
}

uint8_t LCD::getCursorPosition() {
    return cursorPosition;
}

uint8_t LCD::getDisplayPosition() {
    return displayPosition;
}

uint8_t LCD::getLineQuantity() {
    return LINE_QUANTITY;
}

uint8_t LCD::getCursorPositionMax() {
    return CURSOR_POSITION_MAX;
}

uint8_t LCD::getDisplayWidth() {
    return SCREEN_WIDTH;
}

bool LCD::isEndOfLine() {
    return (cursorPosition >= CURSOR_POSITION_MAX) ? true : false;
}

void LCD::loadCGROM(uint8_t position, uint8_t* charPattern) {
    uint8_t ch;

    #if(CHAR_HEIGHT == 10)
	if (position > 3) return;
        writeInstruction(0x40u | (position * 16));
    #else
	if (position > 7) return;
        writeInstruction(0x40u | (position * 8));
    #endif
    setBit(RS_PORT, RS_PIN);
    for(uint8_t i = 0; i < CHAR_HEIGHT; ++i) {
	ch = charPattern[i];
	write(ch);
    };
    goTo(line, cursorPosition);
}

void LCD::printCGROM (uint8_t data) {
    if(cursorPosition < CURSOR_POSITION_MAX) {
	setBit(RS_PORT, RS_PIN);
	write(data);
	++cursorPosition;
	alignDisplayPosition();
	#ifdef I2C_LCD_ADDRESS
	    i2cDisconnect();
	#endif
    };
}

 void LCD::printCh (uint16_t data) {
     printCGROM(checkSym(data));
}

void LCD::print(std::string data, uint8_t length){
    if(cursorPosition < CURSOR_POSITION_MAX) {
	uint8_t i = 0;
	uint16_t tmp = 0;
	bool readyFlag = false;

	length = (data.length()>length && length>0) ? length : data.length();
	for(const char ch : data) {
	    tmp |= ch;
	    #ifdef UTF8
		if(!readyFlag) {
		    readyFlag = true;
		    if (ch >= 0xC2) {
			tmp <<= 8u;
			continue;
		    };
		};
	    #endif
	    setBit(RS_PORT, RS_PIN);
	    write(checkSym(tmp));
	    ++cursorPosition;
	    ++i;
	    if (i >= length || cursorPosition >= CURSOR_POSITION_MAX) {
		break;
	    };
	    readyFlag = false;
	    tmp = 0;
	};
	alignDisplayPosition();
	#ifdef I2C_LCD_ADDRESS
	    i2cDisconnect();
	#endif
    };
}

void LCD::print(std::string data){
    print(data, 0);
}

void LCD::print(int value, uint8_t digits) {
    if(cursorPosition < CURSOR_POSITION_MAX) {
	std::string str;

	str = intToStr(value);
	if(digits > 0) {
	    str+=".";
	};
	while(digits>0) {
	    str+="0";
	    --digits;
	};
	print(str);
    };
}

void LCD::print(int value) {
    print(value, 0);
}

void LCD::print(double value, uint8_t digits) {
    if(value == 0) {
	print(0, digits);
    }
    else if(cursorPosition < CURSOR_POSITION_MAX) {
	int intValue = 0;
	int fractValue = 0;
	std::string str;
	std::string sign;

	if (value<0) {
	    sign="-";
	    value *=(-1);
	};
	intValue = (int) value;
	value = value - (double)intValue;
	for (uint8_t i=0; i < digits; ++i) {
	    value*=10;
	};
	fractValue = (int) value;
	if((value - (double)fractValue) >= 0.4999) {
	    ++fractValue;
	};
	str = intToStr(fractValue);
	if( fractValue>=1 && str.length() > digits) {
	    ++intValue;
	    str.erase(0, 1);
	};
	if(digits>0) {
	    while(str.length()<digits) {
		str="0"+str;
	    };
	    str = "." + str;
	}
	else {
	    str = "";
	};
	str=sign + intToStr(intValue) + str;
	print(str);
    };
}

void LCD::print(double value) {
    print(value, 0);
}

void LCD::print(float value, uint8_t digits) {
    print((double) value, digits);
}

void LCD::print(float value) {
    print(value, 0);
}

void LCD::printHex(int data, uint8_t  digits) {
    if(cursorPosition < CURSOR_POSITION_MAX) {
	uint8_t tmp = 0;
	std::string str;

	while (digits > 0) {
	    tmp = (uint8_t)data & 0x0F;
	    str = ((tmp == 0x0F) ? "F" : (tmp == 0x0E) ? "E" : (tmp == 0x0D) ? "D" : (tmp == 0x0C) ? "C" :\
		(tmp == 0x0B) ? "B" : (tmp == 0x0A) ? "A" : (tmp == 0x09) ? "9" : (tmp == 0x08) ? "8" :\
		(tmp == 0x07) ? "7" : (tmp == 0x06) ? "6" : (tmp == 0x05) ? "5" : (tmp == 0x04) ? "4" :\
		(tmp == 0x03) ? "3" : (tmp == 0x02) ? "2" : (tmp == 0x01) ? "1" : "0") + str;
	    --digits;
	    data >>= 4u;
	};
	print(str);
    };
}

void LCD::backspace() {
    shiftCursorLeft();
    print(" ");
    shiftCursorLeft();
}

void LCD::progressBar(float percentProgress, uint16_t symbol) {
    std::string str;
    uint8_t i = 0;
    uint8_t tmp;

    if (percentProgress>1) {
	percentProgress = 1;
    };
    tmp = (uint8_t)(percentProgress * (float)PROGRESS_BAR_WIDTH);
    symbol = checkSym(symbol);
    goTo(line, displayPosition);
    while(i < tmp) {
	printCGROM(symbol);
	++i;
    };
    tmp = PROGRESS_BAR_WIDTH - i;
    i = 0;
    while(i < tmp) {
	str += " ";
	++i;
    };
    tmp = (uint8_t)(percentProgress * 100);
    if (tmp < 100) {
	str += " ";
    };
    str = str + std::to_string(tmp) + "%";
    print(str);
    if (SET_SHIFT_DISPLAY && tmp == 100) {
	shiftDisplayRight(1);
    };
}

void LCD::progressBar(float percentProgress) {
    progressBar(percentProgress, 0x23);
}

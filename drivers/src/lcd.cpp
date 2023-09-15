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

#include "stm32f1xx.h"

#include "lcd.h"

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
            while(us>0) --us;
    }

    void LCD::setCommandMode ()  {
	resetBit(RS_PORT, RS_PIN);
    };

    void LCD::setWriteDataMode ()  {
	setBit(RS_PORT, RS_PIN);
    };

void LCD::write (uint8_t data) {
    setHigh(data);
    strobe();
    setLow(data);
    strobe();
    delay_us(BUSY_CYCLE_TIME);
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

        //LCD initializing
        delay_us(15000);
        write(0x30);
        delay_us(INIT_CYCLE_TIME);
        write(0x30);
        delay_us(100);
        write(0x30);
        delay_us(100);
        write(0x20);                        //set 4-bit interface
        delay_us(50);
        config(DISPLAY_CONFIG);              //display sets
        write(DISPLAY_CONTROL_DEFAULT);     //display off and coursor set
        delay_us(50);
        write(CLEAR_DISPLAY);		    //clear display
        write(ENTRY_MODE_DEFAULT);          //display entry mode sets
        delay_us(50);
        write(DISPLAY_CONTROL_DEFAULT|DISPLAY_ON); //display on
        delay_us(50);
        write(DISPLAY_CONTROL_DEFAULT);		 //display off
        if(START_WITH_BACKLIGHT_ON)  {
            backlightOn();
            write(DISPLAY_CONTROL_DEFAULT|DISPLAY_ON); //display on
        };
        initialized = true;

        #ifdef I2C_LCD_ADDRESS
            i2cDisconnect();
	#endif
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
    	    resetBit(RS_PORT, RS_PIN);
    	    backlightOn();
    	    write(DISPLAY_CONTROL_DEFAULT|DISPLAY_ON);
	    #ifdef I2C_LCD_ADDRESS
		i2cDisconnect();
	    #endif
	}

    	void LCD::off( ) {
    	    resetBit(RS_PORT, RS_PIN);
    	    backlightOff();
    	    write(DISPLAY_CONTROL_DEFAULT);
	    #ifdef I2C_LCD_ADDRESS
		    i2cDisconnect();
	    #endif
}

    	void LCD::clear( ) {
    	    resetBit(RS_PORT, RS_PIN);
    	    write(CLEAR_DISPLAY);
	    #ifdef I2C_LCD_ADDRESS
    		i2cDisconnect();
	    #endif
    	    delay_us(1500);
    	}

    void LCD::putc (uint8_t data) {
	setBit(RS_PORT, RS_PIN);
	write(data);
	#ifdef I2C_LCD_ADDRESS
	    i2cDisconnect();
	#endif
    }
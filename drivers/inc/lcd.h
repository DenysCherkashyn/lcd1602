#ifndef LCD_H
#define LCD_H



#include "lcd_conf.h"
#include "lcd_def.h"

class LCD final {
     private:
        bool initialized = false;
        uint8_t lastTransferDataByte = 0x00;
	#ifdef I2C_LCD_ADDRESS
	    void (*i2cMasterWrite) (uint16_t, uint8_t*) = nullptr;
	#endif
    
        LCD (){initialized=false;}
        ~LCD (){}
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
        void setCommandMode ();
        void setWriteDataMode ();
        void write(uint8_t);
        void config(uint8_t);
        void init();
        
            
        /*
        void home ();               //lcdReturn?
        void setMode ();
        void goTo ();
        void puts ();
        void putc ();
        void loadChar ();
        void drawChar ();
        void backSpace ();

        */
        
            
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

	void putc (uint8_t data);
        
};
    
#endif      /*LCD_H*/

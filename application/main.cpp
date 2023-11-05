/**
 ******************************************************************************
 * @file           : main.cpp
 * @author         :
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "i2c.h"
#include "lcd.h"

#include "main.h"

    I2C* i2c;


  void masterWriteX(uint16_t slaveAddr, uint8_t* buff){
        i2c = I2C::getInstance(I2C1);
        i2c->masterWriteControlled(slaveAddr,buff);
    };/**/

int main(void)
    {



 //   I2C* i2c = I2C::getInstance(I2C1);

  LCD& lcd = LCD::getInstance(masterWriteX);
  //  LCD& lcd = LCD::getInstance();

  lcd.printCGROM(0b11101101);
lcd.printCGROM(3u);
uint8_t pattern1 []={0b00011111,
	0b00001011,
	0b00010101,
	0b00001011,
	0b00010101,
	0b00001011,
	0b00010101,
	0b00001011};
lcd.loadCGROM(3, pattern1);/**/
uint8_t pattern2 []={0b00000000, 0b00010100,
	0b00001010,
	0b00010100,
	0b00001010,
	0b00010100,
	0b00001010,
	0b00010100};
lcd.loadCGROM(4, pattern2);


   //return 0;
   /**/
   /* Loop forever */
uint32_t i;
    while(1){
	lcd.shiftCursorLeft();
	lcd.printCGROM(3u);

	i= 500000;
	while(i>0) --i;
	lcd.shiftCursorLeft();
	lcd.printCGROM(4u);

	i= 500000;
	while(i>0) --i;
   }
}

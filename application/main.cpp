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

   lcd.off();

   lcd.putc(0b10101000);	// 'П'

    lcd.putc(0b01101111);	// 'о'
    lcd.putc(0b10111011);	// 'л'
    lcd.putc(0b10111000);	// 'и'
   lcd.putc(0b10111101);	// 'н'
    lcd.putc(0b01100001);	// 'а'
    lcd.on();/**/
    return 0;
	/**/
    /* Loop forever */
	while(1){

	}


}

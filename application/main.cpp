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
   lcd.on();
 /*  lcd.printChar('П');	// 'П'

    lcd.printChar('о');	// 'о'
    lcd.printChar('Л');	// 'л'
    lcd.goTo(2, 3);
    lcd.printChar('и');	// 'и'
    lcd.printChar('н');	// 'н'
    lcd.printChar('а');	// 'а'*/
  // lcd.printChar('Ж');
   lcd.print("Cлавa");
   lcd.goTo(2,4);
   lcd.print("Україні-2023");
   lcd.home();

    lcd.on();/**/
    return 0;
	/**/
    /* Loop forever */
	while(1){

	}


}

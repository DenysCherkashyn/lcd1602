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

 //  lcd.off();
//   lcd.on();
//   lcd.backlightOff();

  //lcd.print("2.25");
   //lcd.print(499999.97,1);
   lcd.print("123456789123456789");
  // lcd.printHex(-128746, 8);
   //lcd.print((double)0xFFFE0916);
  //lcd.home();
   lcd.goTo(1,17);
  // lcd.print("Україні-2023");
  // lcd.clearLine(2);
  // lcd.home();

   return 0;
   /**/
   /* Loop forever */
   while(1){

   }
}

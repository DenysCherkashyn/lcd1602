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


  lcd.print("Линий LCD:  ");
  lcd.print(lcd.getLineQuantity(), 1);
  lcd.goTo(2, 0);
  lcd.print("Поз.курсора:");
  lcd.print(lcd.getCursorPositionMax()+1, 1);

   return 0;
   /**/
   /* Loop forever */
   while(1){

   }
}

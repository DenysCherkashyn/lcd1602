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

  lcd.printCGROM(0xFF);
  lcd.printCGROM(0xFF);
  lcd.printCGROM(0xFF);
  lcd.print("Линий LCD:  ");
  lcd.print(lcd.getLineQuantity(), 1);
  lcd.shiftDisplayLeft(3);
  lcd.print(lcd.getLineQuantity(), 1);
  lcd.backspace();

  lcd.shiftDisplayLeft(15);
  lcd.goTo(2, 0);

  std::string str;
  str += "Progress " + std::to_string(10);

  lcd.print(str);

  lcd.progressBar(1.78f, 'х');

  lcd.printCGROM(0xFF);

  //lcd.print("Поз.курсора:");
  //lcd.print(lcd.getCursorPositionMax()+1, 1);


   return 0;
   /**/
   /* Loop forever */
   while(1){

   }
}

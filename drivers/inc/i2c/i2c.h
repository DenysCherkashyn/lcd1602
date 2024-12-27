/*
 * 	i2c.h
 *
 *	Created on: 03 September 2023
 *      Author: D.Cherkashin
 *
 *      General i2c driver header file.
 *      Defines class attributes and methods.
 *      Defines file include for definite stm32 controller type
 *      For more information see readme.md file
 *
 */

#ifndef _I2C_H_
	#define _I2C_H_

	#include<unordered_map>

	#ifdef __cplusplus
		extern "C" {
	#endif

	#include <stdint.h>

	//using namespace std;

	//define STM device type
	#include "stm32f1xx.h"

	#define SM 	0
	#define FM	1

	#include <i2c/i2c_conf.h>
	#include <i2c/i2c_def.h>

	//=============================




	#ifdef __cplusplus
		}
	#endif

	 // --- CLASS DEFINITION ---//



	class I2C final {

		private:
			typedef std::unordered_map<I2C_TypeDef*, I2C*> ConnectionMap;
			static ConnectionMap connections;
			I2C_TypeDef * i2cType;
			uint32_t CR1LastState;
			bool isMasterEmergencyStop;
			bool isSlaveActive;
			bool isSlaveWrongRegAddr;
			uint8_t slaveBuffCounter;
			uint8_t *slaveBuffPointer;
			uint8_t  slaveLastRegAddr;

			I2C(I2C_TypeDef *, I2C_Cfg_TypeDef*);
			~I2C();
			I2C(const I2C&);
			const I2C& operator = (const I2C&);

			void gpioInit(I2C_TypeDef *);
			void i2cInit(I2C_TypeDef *, I2C_Cfg_TypeDef*);

			void start();
			void stop();
			bool sendAddress(uint16_t, uint16_t, bool);
			bool pushDataByte(uint8_t);
			bool pullDataByte(uint8_t*);
			void delay_us(uint32_t);
			bool isAddressBitSet();
			void setMasterConnection(uint16_t, uint16_t, bool);
			bool isSetSlaveConnection(uint8_t*);
			bool isSetSlaveConnection(std::unordered_map<uint8_t, uint8_t*>*);


		public:
			static I2C* getInstance(I2C_TypeDef *, I2C_Cfg_TypeDef*);
			static I2C* getInstance(I2C_TypeDef *);

			void enable();
			void disable();
			bool isEnabled();
			bool isFailures();
			bool isStoped();
			bool isMasterWrite();
			bool isMasterRead();
			bool isMasterEmergencyStopped();
			bool isSlaveWrite();
			bool isSlaveRead();

			void masterWrite(uint16_t, uint16_t, uint8_t*, uint8_t);
			void masterWrite(uint16_t, uint8_t*, uint8_t);
			void masterWriteControlled(uint16_t, uint8_t*);
			void masterRead(uint16_t, uint16_t, uint8_t*, uint8_t);
			void masterRead(uint16_t, uint8_t*, uint8_t);
			void masterEmergencyStop();

			void slaveWrite(uint8_t*, uint8_t, bool);
			void slaveWrite(uint8_t*, bool);
			void slaveRead(uint8_t*, uint8_t, bool);
			void slaveRead(uint8_t*, bool);
			void slaveReadWrite(uint8_t*, uint8_t, bool);
			void slaveReadWrite(std::unordered_map<uint8_t, uint8_t*>*,  uint8_t, bool);
			void slaveReadWrite(uint8_t*, bool);
			void slaveReadWrite(std::unordered_map<uint8_t, uint8_t*>*,  bool);
	};

#endif /* _I2C_H_ */

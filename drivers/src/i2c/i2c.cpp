/*
 * 	i2c.cpp
 *
 *	Created on: 03 September 2023
 *      Author: D.Cherkashin
 *
 *      This i2c-driver class for work in STM32 controllers (f1xx-series).
 *      For more information see readme.md file
 *
 */


#include <i2c/i2c.h>

/*****************************************
 *
 * 	PRIVATE METHODS AND PROPERTIES
 *
 *****************************************/


typedef std::unordered_map<I2C_TypeDef*, I2C*> ConnectionMap;
ConnectionMap I2C::connections;

I2C::I2C(I2C_TypeDef * i2cType, I2C_Cfg_TypeDef* i2cCfg){
	this->i2cType = i2cType;
	gpioInit(i2cType);
	i2cInit(i2cType, i2cCfg);
	isMasterEmergencyStop = false;
	isSlaveActive = false;
	isSlaveWrongRegAddr = false;
	slaveBuffCounter = 0;
	slaveBuffPointer = nullptr;
	slaveLastRegAddr = 0;
}

I2C::~I2C(){	}

void I2C::gpioInit(I2C_TypeDef * i2cType){
	#ifdef USE_I2C1
		if(i2cType == I2C1){
			RCC->APB2ENR |= (I2C1_GPIO_CLK_SCL | I2C1_GPIO_CLK_SDA | RCC_APB2ENR_AFIOEN);
			SET_MODE_AF_I2C(I2C1_SCL_PORT, I2C1_SCL_PIN);
			SET_MODE_AF_I2C(I2C1_SDA_PORT, I2C1_SDA_PIN);
		};
	#endif

	#ifdef USE_I2C2
		if(i2cType == I2C2){
			RCC->APB2ENR |= (I2C2_GPIO_CLK_SCL | I2C2_GPIO_CLK_SDA | RCC_APB2ENR_AFIOEN);
			SET_MODE_AF_I2C(I2C2_SCL_PORT, I2C2_SCL_PIN);
			SET_MODE_AF_I2C(I2C2_SDA_PORT, I2C2_SDA_PIN);
		};
	#endif
};

void I2C::i2cInit (I2C_TypeDef * i2cType, I2C_Cfg_TypeDef* i2cCfg){
	uint32_t pclk1Frq=0;
	uint16_t tmpRegMsk=0, AHBdiv=0, APB1div=0;

	#ifdef USE_I2C1
	if(i2cType == I2C1){
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	};
	#endif

	#ifdef USE_I2C2
	if(i2cType == I2C2){
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
	};
	#endif

	//getting current PCLK1 frequency (APB1 peripherals)
	switch(READ_BIT(RCC->CFGR, RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos) {
		case 0x08U:	AHBdiv=2;	break;
		case 0x09U:	AHBdiv=4;	break;
		case 0x0AU:	AHBdiv=8;	break;
		case 0x0BU:	AHBdiv=16;	break;
		case 0x0CU:	AHBdiv=64;	break;
		case 0x0DU:	AHBdiv=128;	break;
		case 0x0EU:	AHBdiv=256;	break;
		case 0x0FU:	AHBdiv=512;	break;
		default:	AHBdiv=1;
	};
	switch(READ_BIT(RCC->CFGR, RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos) {
		case 0x04U:	APB1div=2;	break;
		case 0x05U:	APB1div=4;	break;
		case 0x06U:	APB1div=8;	break;
		case 0x07U:	APB1div=16;	break;
		default:	APB1div=1;
	};
	SystemCoreClockUpdate();
	pclk1Frq = SystemCoreClock/(uint32_t)(AHBdiv * APB1div);

	//PE=0 and configure other bits CR1
	CLEAR_REG(i2cType->CR1);

	//I2C clocking:
	tmpRegMsk = (uint16_t)(pclk1Frq/1000000);
	if(i2cCfg->ccr & I2C_CCR_FS){
		//Fast mode case

		//set CR2_FREQ
		tmpRegMsk = (tmpRegMsk < 0x04U) ? 0x04U : ((tmpRegMsk > 0x32U) ? 0x32U : tmpRegMsk);
		WRITE_REG(i2cType->CR2, (tmpRegMsk | i2cCfg->cr2));
		//set TRISE
		tmpRegMsk=((tmpRegMsk * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1;
		WRITE_REG(i2cType->TRISE, tmpRegMsk);
		//set CCR, FS=1, DUTY - optional value
		if(i2cCfg->ccr & I2C_CCR_DUTY){
			//DUTY=1 (to reach 400kHz), Thigh/Tlow = 9/16
			tmpRegMsk = (uint16_t)(pclk1Frq/(25*(i2cCfg->clkFrq)));
		}
		else {
			//DUTY=0, Thigh/Tlow = 1/2
			tmpRegMsk = (uint16_t)(pclk1Frq/(3*(i2cCfg->clkFrq)));
		};
		if (tmpRegMsk == 0) {
			tmpRegMsk = 0x0001;
		}
		WRITE_REG(i2cType->CCR, (tmpRegMsk | i2cCfg->ccr));
	}
	else {
		//Standard mode case

		//set CR2_FREQ
		tmpRegMsk = (tmpRegMsk < 0x02U) ? 0x02U : ((tmpRegMsk > 0x32U) ? 0x32U : tmpRegMsk);
		WRITE_REG(i2cType->CR2, (tmpRegMsk | i2cCfg->cr2));
		//set TRISE
		++tmpRegMsk;
		WRITE_REG(i2cType->TRISE, tmpRegMsk);
		//set CCR, FS=0, DUTY=0;
		tmpRegMsk = (uint16_t)(pclk1Frq/(2*(i2cCfg->clkFrq)));
		WRITE_REG(i2cType->CCR, (tmpRegMsk | i2cCfg->ccr));
	};
	//set address
	WRITE_REG(i2cType->OAR1, i2cCfg->oar1);
	WRITE_REG(i2cType->OAR2, i2cCfg->oar2);

	//I2C enable
	this->CR1LastState = i2cCfg->cr1;
	enable();
};

void I2C::start () {
	//wait if I2C communication bus is busy
	while(IS_BIT_SET(i2cType->SR2, I2C_SR2_BUSY)){};
	//start condition
	SET_BIT(i2cType->CR1, I2C_CR1_START);
	while ( !READ_BIT(i2cType->SR1, I2C_SR1_SB) ){};
}

void I2C::stop () {
	isMasterEmergencyStop = false;
	SET_BIT(i2cType->CR1, I2C_CR1_STOP);
	delay_us(10);
}

bool I2C::sendAddress (uint16_t slaveAddr, uint16_t regAddr, bool isMasterTransmiter = true) {
	uint16_t tmp;

	if (READ_BIT(i2cType->OAR1, I2C_OAR1_ADDMODE)) {
		//10-bit address slave
		tmp = ((slaveAddr & 0x0300) >> 7) & 0xF6;
		WRITE_REG(i2cType->DR, tmp);
		while(!IS_BIT_SET(i2cType->SR1, I2C_SR1_TXE|I2C_SR1_ADD10)){
			if(isFailures()) return false;
		};
		WRITE_REG(i2cType->DR, slaveAddr & 0xFF);

		if(!isMasterTransmiter){
			while(!IS_BIT_SET(i2cType->SR1, I2C_SR1_ADDR)){
				if(isFailures()) return false;
			};
			READ_REG(i2cType->SR2);
			//re-start condition
			SET_BIT(i2cType->CR1, I2C_CR1_START);
			tmp = ((slaveAddr & 0x0300) >> 7) & 0xF7;
			WRITE_REG(i2cType->DR, tmp);
		};
	}
	else {
		//7-bit address slave
		tmp = (isMasterTransmiter) ? ((slaveAddr << 1) & 0xFE) : ((slaveAddr << 1) | 0x01);
		WRITE_REG(i2cType->DR, tmp);
	};
	delay_us(10);
	READ_REG(i2cType->SR1);
	READ_REG(i2cType->SR2);
	//send slave register address
	if(regAddr>=0 && regAddr<0x0100){
	    WRITE_REG(i2cType->DR, 0x00FF & regAddr);
	    delay_us(10);
	};
	return true;
}

bool I2C::pushDataByte (uint8_t data) {
    #ifdef USE_TX_RX_IN_MASTER_MODE
	    while (!IS_BIT_SET(i2cType->SR1, I2C_SR1_TXE) && !isMasterEmergencyStop){};
    #endif
	if( isFailures() || isMasterEmergencyStop) return false;
	WRITE_REG(i2cType->DR, data);
	return true;
}

bool I2C::pullDataByte (uint8_t* buff) {
#ifdef	USE_TX_RX_IN_MASTER_MODE
	    while (!IS_BIT_SET(i2cType->SR1, I2C_SR1_RXNE) && !isMasterEmergencyStop){};
#endif
	if( isFailures() || isMasterEmergencyStop) return false;
	*buff = (uint8_t)READ_REG(i2cType->DR);
	return true;
}

void I2C::delay_us(uint32_t us) {
    us *= (SystemCoreClock/1000000);
    while(us>0) --us;
}

bool I2C::isAddressBitSet () {
	if ( IS_BIT_SET(i2cType->SR1, I2C_SR1_ADDR) ) {
	    READ_REG(i2cType->SR2);
	    return true;
	}
	return false;
}

void I2C::setMasterConnection (uint16_t slaveAddr, uint16_t regAddr, bool isMasterTransmiter = true) {
    start();
    if(regAddr>=0 && regAddr<0x0100) {
	sendAddress(slaveAddr, regAddr, true);	//master-transmitter
	SET_BIT(i2cType->CR1, I2C_CR1_START);
	delay_us(10);
    };
    sendAddress(slaveAddr, 0xffff, isMasterTransmiter);
}

bool I2C::isSetSlaveConnection (uint8_t* buff) {
    if( isFailures() || isStoped() ){
    	    isSlaveActive = false;
    	    slaveBuffPointer = nullptr;
    	    slaveBuffCounter = 0;
    	    return false;
    	};
    if( isAddressBitSet() || !isSlaveActive ){
	slaveBuffCounter = 0;
	isSlaveActive = true;
	return false;
    };
    if(!slaveBuffPointer) {
	slaveBuffPointer = buff;
    };
    return true;
}

bool I2C::isSetSlaveConnection (std::unordered_map<uint8_t, uint8_t*>* buff) {
    if( isFailures() || isStoped() ){
	isSlaveActive = false;
	slaveBuffPointer = nullptr;
	slaveBuffCounter = 0;
	isSlaveWrongRegAddr = false;
	return false;
    };
    if(isAddressBitSet() || !isSlaveActive){
	slaveBuffCounter = 0;
	isSlaveActive = true;
	return false;
    };
    if(!isSlaveWrongRegAddr && !slaveBuffPointer){
	uint8_t regAddr = READ_REG(i2cType->DR);
	if(buff->count(regAddr)){
	    slaveLastRegAddr = regAddr;
	}
	else {
	    isSlaveWrongRegAddr = true;
	};
	slaveBuffPointer = (*buff)[slaveLastRegAddr];
	isSlaveActive = false;			//for recieving empty restart condition
	return false;
    };
    return true;
}

/*****************************************
 *
 * 	PUBLIC METHODS AND PROPERTIES
 *
 *****************************************/

I2C* I2C::getInstance(I2C_TypeDef * i2cType, I2C_Cfg_TypeDef* i2cCfg){
	if(!IS_I2C_ALL_INSTANCE(i2cType)) return nullptr;
	if(connections.count(i2cType) == 0){
		connections[i2cType] = new I2C(i2cType, i2cCfg);
	}
	return connections[i2cType];
};

I2C* I2C::getInstance (I2C_TypeDef * i2cType){
	I2C_Cfg_TypeDef i2cCfg;
	#ifdef USE_I2C1
		if(i2cType == I2C1){
			i2cCfg = I2C1_CFG_STRUCT;
		} else
	#endif
	#ifdef USE_I2C2
		if (i2cType == I2C2){
			i2cCfg = I2C2_CFG_STRUCT;
		} else
	#endif
		{return nullptr;};
		return getInstance(i2cType, &i2cCfg);
}

void I2C::enable () {
	SET_BIT(i2cType->CR1, I2C_CR1_PE);
	SET_BIT(i2cType->CR1, CR1LastState);
}

void I2C::disable() {
	this->CR1LastState = i2cType->CR1;
	CLEAR_BIT(i2cType->CR1, I2C_CR1_PE);
}

bool I2C::isEnabled () {
	return IS_BIT_SET(i2cType->CR1, I2C_CR1_PE);
}

bool I2C::isFailures () {
	if( READ_BIT(i2cType->SR1, I2C_SR1_FAILURES_BITS) ) {
		CLEAR_BIT(i2cType->SR1, I2C_SR1_FAILURES_BITS);
		return true;
	};
	return false;
}

bool I2C::isStoped(){
    if( IS_BIT_SET(i2cType->SR1, I2C_SR1_STOPF) ) {
	SET_BIT(i2cType->CR1, CR1LastState);
	return true;
    }
    return false;
}

bool I2C::isMasterWrite () {
	return ( IS_BIT_SET(i2cType->SR2, (I2C_SR2_MSL|I2C_SR2_TRA)) ) ? true : false;
}

bool I2C::isMasterRead () {
	return ( IS_BIT_SET(i2cType->SR2, I2C_SR2_MSL) && !IS_BIT_SET(i2cType->SR2, I2C_SR2_TRA) ) ? true : false;
}

bool I2C::isMasterEmergencyStopped () {
	return (isMasterEmergencyStop) ? true : false;
}

bool I2C::isSlaveWrite () {
	return ( !IS_BIT_SET(i2cType->SR2, I2C_SR2_MSL) && IS_BIT_SET(i2cType->SR2, I2C_SR2_TRA) ) ? true : false;
}

bool I2C::isSlaveRead () {
	return ( !IS_BIT_SET(i2cType->SR2, I2C_SR2_MSL) && !IS_BIT_SET(i2cType->SR2, I2C_SR2_TRA) ) ? true : false;
}

void I2C::masterWrite (uint16_t slaveAddr, uint16_t regAddr, uint8_t* buff, uint8_t dataSize = 1) {
	uint8_t i;
	uint8_t* tmp;

	setMasterConnection (slaveAddr, regAddr, true);
	tmp = buff;
	i=0;
	while ( (i < dataSize) && pushDataByte(*tmp) && !isMasterEmergencyStop) {
		++i;
		++tmp;
		delay_us(10);
	};
	stop();
}

void I2C::masterWrite (uint16_t slaveAddr, uint8_t* buff, uint8_t dataSize = 1) {
	masterWrite(slaveAddr, 0xffff, buff, dataSize);}

void I2C::masterWriteControlled (uint16_t slaveAddr, uint8_t* buff) {
    if(!isMasterWrite()) {
	setMasterConnection (slaveAddr, 0xffff, true);
    };
    if(buff==nullptr || !pushDataByte(*buff)) {
	stop();
    };
}

void I2C::masterRead (uint16_t slaveAddr, uint16_t regAddr, uint8_t* buff, uint8_t dataSize = 1) {
	bool NACKisSet = false;
	uint16_t CR1AckCfg;
	uint8_t i;
	uint8_t* tmp;

	setMasterConnection (slaveAddr, regAddr, false);
	CR1AckCfg = READ_BIT(i2cType->CR1, I2C_CR1_ACK);
	tmp = buff;
	i=2;
	delay_us(10);
	while ( dataSize>0 && !isMasterEmergencyStop ) {
	    if( !(i < dataSize) && !(NACKisSet) ) {
		//sending NACK with the last byte
		CLEAR_BIT(i2cType->CR1, I2C_CR1_ACK);
		NACKisSet = true;
	    };
	    if ( !pullDataByte(tmp) ) break;
	    --dataSize;
	    ++tmp;
	};
	stop();
	SET_BIT(i2cType->CR1, CR1AckCfg);
}

void I2C::masterRead (uint16_t slaveAddr, uint8_t* buff, uint8_t dataSize = 1) {
    masterRead (slaveAddr, 0xffff, buff, dataSize);
}

void I2C::masterEmergencyStop () {
    isMasterEmergencyStop = true;
}

void I2C::slaveWrite (uint8_t *buff, uint8_t dataSize,  bool doOneCycle = false){
    while (isSlaveWrite()) {
	if( !isSetSlaveConnection(buff) )return;
	WRITE_REG(i2cType->DR, *slaveBuffPointer);
	++slaveBuffCounter;
	if (slaveBuffCounter < dataSize) {
	    ++slaveBuffPointer;
	}
	else {
	    slaveBuffCounter = 0;
	};
	if (doOneCycle) return;
    };
}

void I2C::slaveWrite (uint8_t *buff,  bool doOneCycle = false) {
	slaveWrite(buff,1,doOneCycle);
}

void I2C::slaveRead (uint8_t *buff, uint8_t dataSize, bool doOneCycle = false) {
    if (isSlaveRead()) {
	if( !isSetSlaveConnection(buff) )return;
	*slaveBuffPointer = READ_REG(i2cType->DR);
	++slaveBuffCounter;
	if (slaveBuffCounter < dataSize) {
	    ++slaveBuffPointer;
	}
	else {
	    slaveBuffCounter = 0;
	};
	if (doOneCycle) return;
    };
}

void I2C::slaveRead (uint8_t *buff,  bool doOneCycle = false) {
    slaveRead(buff, 1, doOneCycle);
}

void I2C::slaveReadWrite (uint8_t *buff, uint8_t dataSize, bool doOneCycle = false) {
    if(dataSize<1) dataSize = 1;
    while (isSetSlaveConnection(buff)) {
   	if (isSlaveWrite()) {
   	    WRITE_REG(i2cType->DR, *slaveBuffPointer);
   	};
   	if (isSlaveRead()) {
   	    *slaveBuffPointer = READ_REG(i2cType->DR);
   	};

   	++slaveBuffCounter;
   	if (slaveBuffCounter < dataSize) {
   	    ++slaveBuffPointer;
   	}
   	else {
   	    slaveBuffCounter = 0;
   	};

   	if (doOneCycle) return;
    };
};

void I2C::slaveReadWrite (std::unordered_map<uint8_t, uint8_t*>* buff,  uint8_t dataSize, bool doOneCycle = false) {
    if(dataSize<1) dataSize = 1;
    while (isSetSlaveConnection(buff)) {
	if (isSlaveWrite()) {
	    WRITE_REG(i2cType->DR, *slaveBuffPointer);
	};
	if (isSlaveRead()) {
	    if(isSlaveWrongRegAddr){
		stop();
		return;
	    };
	    *slaveBuffPointer = READ_REG(i2cType->DR);
	};

	++slaveBuffCounter;
	if (slaveBuffCounter < dataSize) {
	    ++slaveBuffPointer;
	}
	else {
	    slaveBuffCounter = 0;
	};

	if (doOneCycle) return;
    };
};

void I2C::slaveReadWrite (uint8_t *buff, bool doOneCycle = false) {
    slaveReadWrite(buff, 1, doOneCycle);
};

void I2C::slaveReadWrite (std::unordered_map<uint8_t, uint8_t*>* buff, bool doOneCycle = false) {
    slaveReadWrite(buff, 1, doOneCycle);
};

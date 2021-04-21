#pragma once
#include "top.h"

class Hardware{
public:
	const uint32_t sys_freq = XTAL;
	mkpd_bc mkpd;
	uart uart2;
	Timer movTimer;
	Timer commTimer;
	
	Hardware();
	
private:
	inline void mem_ctrl_init();
	inline void init();
	inline void setupPin(GPIO_T* pPort, uint16_t pin);
	inline void setupPins(GPIO_T* pPort, uint16_t pins);
};


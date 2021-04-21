#pragma once
#include "top.h"

class Hardware{
public:
	const uint32_t sys_freq = XTAL;
	mkpd_ep mkpd;
	Debugger dbgUART;
	Timer cmdTimer1; // Command Handler Timer, Start in Algorithm, Off in Anlgorithm
	Timer cmdTimer2; // Command Handler Timer, Start in Algorithm, Off in Anlgorithm
	Timer ccTimer;  // Communication Control Timer, Start in ZoneController, Off - none
	Timer selfTimer;// Self Operation Timer, Start in Algorithm, Off in Anlgorithm
	
	Hardware();
	
private:
	inline void mem_ctrl_init();
	inline void init();
	inline void setupPin(GPIO_T* pPort, uint16_t pin);
	inline void setupPins(GPIO_T* pPort, uint16_t pins);
};
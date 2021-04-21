#pragma once
#include "top.h"

class Timer{
private:
	TIMER_T* 	name;
	IRQn_T 		irqNum;
	int 		irqVec;
public:
	Timer(TIMER_T* pTimer, IRQn_T num, int vec);
	
	void Start(uint32_t time);
	inline void Off(){ TIMER_Disable(name); }
	inline void Reload(uint32_t time){ TIMER_SetValue(name, XTAL/1000*time); }
private:
	inline void setup(uint32_t time);
	inline void start();
};

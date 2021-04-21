#include "top.h"

Timer::Timer(TIMER_T* pTimer, IRQn_T num, int vec){
	name = pTimer;
	irqNum = num;
	irqVec = vec;
} 

void Timer::Start(uint32_t time){
	setup(time);
	start();
}

inline void Timer::setup(uint32_t time){
	TIMER_SetValue(name, XTAL/1000*time);
	TIMER_IntEnable(name);
	NVIC_EnableIRQ(irqNum, irqVec);
}

inline void Timer::start(){
	TIMER_Enable(name);
}

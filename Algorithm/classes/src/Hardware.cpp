#include "top.h"

Hardware::Hardware(): 
	mkpd(sys_freq),
	dbgUART(UART2, sys_freq),
	cmdTimer1(TIMER1, Timer1, TIM1_INT_VEC),
	cmdTimer2(TIMER4, Timer4, TIM4_INT_VEC),
	ccTimer(TIMER2, Timer2, TIM2_INT_VEC),
	selfTimer(TIMER3, Timer3, TIM3_INT_VEC)
{
	init();
}

inline void Hardware::mem_ctrl_init(){  
	//config altfunc RAM_Cen1   
	CMN_REG->ALT_FUNCTION_CTRL[5] |= 1<<2*12;		//F12 - func 2
	GPIO_F->ALTFUNCSET = 1<<12;						//F12
}

inline void Hardware::init(){
	mem_ctrl_init();
	setupPins(BL_PORT, BL_PINS);
}

inline void Hardware::setupPin(GPIO_T* pPort, uint16_t pin){
	pPort->OUTENCLR = pin; 
	pPort->OUTENSET |= pin;
}

inline void Hardware::setupPins(GPIO_T* pPort, uint16_t pins){
	pPort->OUTENCLR = pins; 
	pPort->OUTENSET |= pins;
}

#include "top.h"

/*----------------------------------------------------------------------------*/
extern "C" void MKPD1_IRQ(void){
  	global.mkpdInterrupt = MKPD_Get_Interrupt(MKPD1);
	if( global.mkpdInterrupt ==  MKPD_INTERRUPT_BC_INT){
  		//обработка прерывания КШ по окончанию транзакции
		BL4_INV();
		global.IsMI = true;
	}
		
	MKPD1->INTERRUPT &= 0xFFFE; 
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
extern "C" void Timer_1_IRQ(void){
	global.movCnt++;
  	TIMER_IntClr(TIMER1);
	global.MovTI = true;
	global.IsTI = true;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
extern "C" void Timer_2_IRQ(void){
  	global.commCnt++;
	TIMER_IntClr(TIMER2);
	global.CommTI = true;
	global.IsTI = true;
}
/*----------------------------------------------------------------------------*/

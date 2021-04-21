#include "top.h"

/*----------------------------------------------------------------------------*/
extern "C" void MKPD1_IRQ(void){
  
  	global.mkpdInterrupt = MKPD_Get_Interrupt(MKPD1);
	if( global.mkpdInterrupt ==  MKPD_INTERRUPT_EP_INT0){
		//обработка прерывания ОУ по приему командного слова
		global.CommandWord = MKPD_Get_Endpoint_Command_Word(MKPD1);
		if( !(global.CommandWord & (1 << 10)) ){
		  	//команда на прием данных от КШ
			MKPD1->INTERRUPT &= 0xFFF0; 
			MKPD_Set_Endpoint_Attributes(MKPD1, 1 );
			while( !(MKPD_Get_Interrupt(MKPD1) & MKPD_INTERRUPT_EP_INT1) );
			//UART_SendByte(UART2, 0xDD);
			global.IsMI = true;
		}
	}
	//UART_SendByte(UART2, 0xCC);
	MKPD1->INTERRUPT &= 0xFFF0; 
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
extern "C" void Timer_1_IRQ(void)
{
    BL1_INV();
	TIMER_IntClr(TIMER1);
	global.CmdTI1 = true;
	global.IsTI = true;
}
/*----------------------------------------------------------------------------*/
extern "C" void Timer_4_IRQ(void)
{
    BL2_INV();
  	TIMER_IntClr(TIMER4);
	global.CmdTI2 = true;
	global.IsTI = true;
}
/*----------------------------------------------------------------------------*/
extern "C" void Timer_2_IRQ(void)
{
    BL3_INV();
  	TIMER_IntClr(TIMER2);
	global.CommTI = true;
	global.IsTI = true;
}
/*----------------------------------------------------------------------------*/
extern "C" void Timer_3_IRQ(void)
{
  	TIMER_IntClr(TIMER3);
	global.SelfTI = true;
	global.IsTI = true;
}
/*----------------------------------------------------------------------------*/

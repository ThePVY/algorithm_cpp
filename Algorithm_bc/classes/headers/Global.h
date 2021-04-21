#pragma once

#include "top.h"

class Global{
public:
	volatile uint8_t 		mkpdInterrupt;
	volatile bool			uart_ept_en;
	volatile bool			IsMI;		//Manchester Ivent
	volatile 				Command_Word_T	BCcommand;	
	volatile bool			IsTI;		//Timer Ivent
	volatile bool			MovTI;		//Movement TI
	volatile bool			CommTI;		//Communication TI
	
	volatile uint32_t		movCnt;
	volatile uint32_t		commCnt;
	
	Global();
	
	/*
	 * @brief Извлечение подадреса из КС (биты 6-10) 
	 */
	inline uint16_t GetSubaddr(){
		getBCcommand();
		return BCcommand.bit.Subaddr__Manage_mode;
	}
	
	inline bool Interrupt(TIMER_T* name){ return (name->INTCLEAR)? false : true; }
private:
	inline void getBCcommand(){
		BCcommand.all = MKPD_Get_Endpoint_Command_Word(MKPD1);
	}
	
};

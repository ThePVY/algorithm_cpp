#pragma once

#include "top.h"

class Global{
public:
	volatile uint8_t 		mkpdInterrupt;
	volatile uint32_t		CommandWord;
	volatile bool			uart_ept_en;
	volatile bool			IsMI; //Manchester Ivent
	volatile Command_Word_T	BCcommand;	
	volatile bool			IsTI; //Timer Ivent
	volatile bool			CmdTI1, CmdTI2;
	volatile bool			CommTI;
	volatile bool			SelfTI;
	
	Global();
	
	/*
	 * @brief Извлечение подадреса из КС (биты 6-10) 
	 */
	inline Subaddrs GetSubaddr(){
		getBCcommand();
		return (Subaddrs)BCcommand.bit.Subaddr__Manage_mode;
	}
	
	inline bool Interrupt(TIMER_T* name) volatile{ return (name->INTCLEAR)? false : true; }
private:
	inline void getBCcommand(){
		BCcommand.all = MKPD_Get_Endpoint_Command_Word(MKPD1);
	}
	
};

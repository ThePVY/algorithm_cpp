#pragma once
#include "top.h"

class mkpd_bc{
private:
	uint32_t sys_freq;
public:
	uint8_t BC_DMA_buff[SUBADDR_SHIFT];
	
	mkpd_bc(uint32_t freq);
	
private:
	inline void Init();	
	inline void MKPD_init(MKPD_T * mkpd , CTRL_T ctrl_num);	
	inline void Init_ports_Manchester();
	inline void MKPD_Clock_Init(CTRL_T ctrl_num);
};

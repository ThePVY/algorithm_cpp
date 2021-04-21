#pragma once
#include "top.h"

class mkpd_ep{
private:
	uint32_t sys_freq;
public:
	uint8_t EP_DMA_buff[SUBADDR_NUM*2*MAX_PACK_LENGTH + 2*MAX_PACK_LENGTH];
	
	mkpd_ep(uint32_t freq);
	
private:
	inline void Init();	
	inline void MKPD_init(MKPD_T * mkpd , CTRL_T ctrl_num);	
	inline void Init_ports_Manchester();
	inline void MKPD_Clock_Init(CTRL_T ctrl_num);
};

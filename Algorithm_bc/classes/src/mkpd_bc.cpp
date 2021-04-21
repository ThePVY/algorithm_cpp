#include "top.h"

mkpd_bc::mkpd_bc(uint32_t freq): sys_freq(freq){
	for(int i = 0; i < SUBADDR_SHIFT; i++){
		BC_DMA_buff[i] = 0;
	}
	Init();	
}	

inline void mkpd_bc::Init(){
	Init_ports_Manchester();
	MKPD_init(MKPD1, MKPD1_CTRL_NUM);
	MKPD_ConfigBusController(MKPD1, (uint32_t)BC_DMA_buff, (uint32_t)BC_DMA_buff,
							 MKPD_SETTING0_CHANNEL_A);
	//прерывани€
	//NVIC_EnableIRQ(MKPD1_NUM, MKPD1_INT_VECT);
}

inline void mkpd_bc::MKPD_init(MKPD_T * mkpd , CTRL_T ctrl_num)
{
	MKPD_Clock_Init(ctrl_num);								// ѕодача тактовых сигналов
  
	MKPD_Set_Interpacket_Time(mkpd, 0xF);
	MKPD_Set_Wait_Time(mkpd, 38);							// >= 21 mks
	MKPD_Set_Edge_Time(mkpd, SYS_FREQ/5);					// > 0.2 mks  
	MKPD_Set_System_Clock(mkpd, SYS_FREQ);
	MKPD_Set_InvTX(mkpd, 1);
	MKPD_Set_IncWith(mkpd, 0);
	MKPD_Set_DecoderDisable(mkpd, 0); 					//all enabled
	
	MKPD_Set_NoActivity_Time(mkpd, SYS_FREQ * 13 / 10);		// > 1.3 mks
	MKPD_Set_BCWaitReply_Time(mkpd, 36);					// > 35 mks
	MKPD_Set_Clk_500NS(mkpd, SYS_FREQ / 2);              
	MKPD_Set_Clk_1250NS(mkpd, SYS_FREQ * 125 / 100);
	MKPD_Set_Clk_1500NS(mkpd, SYS_FREQ * 150 / 100);
	MKPD_Set_Clk_1750NS(mkpd, SYS_FREQ * 175 / 100);
	MKPD_Set_Clk_2250NS(mkpd, SYS_FREQ * 225 / 100);          
	
}	
inline void mkpd_bc::Init_ports_Manchester()
{
	
	PWR_CLK_Disable(MKPD1_CTRL_NUM); 
	CLK_INIT_PAUSE;
	PWR_RST_Enable(MKPD1_CTRL_NUM);
   
	//config altfunc                
	CMN_REG->ALT_FUNCTION_CTRL[4] &= 0xFF0000FF;		//E4-E11 - func 1
  
	//enable altfunc in gpio       
	MKPD_PORT->ALTFUNCSET = 0x0FF0;						//E4-E11
}

inline void mkpd_bc::MKPD_Clock_Init(CTRL_T ctrl_num)
{
	PWR_CLK_Enable(ctrl_num); 
	CLK_INIT_PAUSE;
	PWR_RST_Disable(ctrl_num);	
}

#include "top.h"

uart::uart(UART_T* pUART, uint32_t freq){
	this->pUART = pUART;
	sys_freq = freq;
	init();
}

inline void uart::init(){
	//настроим UART
	gpioInit_UART2();											// Инициализация GPIO для UART2
	UART_Init(UART2);											// Инициализация UART
	UART_SetBaud(UART2, BAUDRATE_115200, sys_freq);				// Установка целой и дробной частей делителя для получения заданной скорости последовательного обмена
	UART_Config(UART2, (UART_LCR_H_PDIS |						// Установка длины слова данных, числа стоповых бит и контроля четности
						UART_LCR_H_EPS_ODD |
						UART_LCR_H_STP1 |
						UART_LCR_H_FEN | 
						UART_LCR_H_WLEN8 | 
						UART_LCR_H_SPS_DIS));    
	UART_Enable(UART2);                                     	// Разрешение работы UART
	UART_TXEnable(UART2); 										// Разрешение работы передатчика
	UART_RXEnable(UART2);						 				// Разрешение работы приемника
	UART_SetupFIFOS(UART2, UART_IFLS_1DIV2, UART_IFLS_1DIV2);	// Установка порогов прерываний по заполнению буфера приемника/передатчика  
	UART_IntEnable(UART2, UART_IMSC_OEIM);
}

/**
* @brief Инициализация GPIO для UART2
*/
inline void uart::gpioInit_UART2()
{
	PWR_CLK_Disable(UART_2_CTRL_NUM); 
	CLK_INIT_PAUSE;
	PWR_RST_Enable(UART_2_CTRL_NUM);
	//config altfunc                
	CMN_REG->ALT_FUNCTION_CTRL[4] &= 0xFFFFFFC3;	//E1-E2 - func 1	
	//enable altfunc in gpio       
	GPIO_E->ALTFUNCSET = 1<<1 | 1<<2;				//E1-E2                                   
}

/**
 * @brief Передача всего содержимого buff по pUART
*/
void uart::Flush(uint8_t *buff, uint32_t size){
	for(int i = 0; i < size; i++){
		SendByte(buff[i]);
	}
}

void uart::FlushWords(uint8_t *buff, uint32_t size){
	for(int i = 0; i < size/2; i++){
		SendByte(buff[2*i+1]);
		SendByte(buff[2*i]);
	}
}

/*-------------------------------------------------------------------*/
Debugger::Debugger(UART_T* pUART, uint32_t freq): uart(pUART, freq){
	JustOnce = false;
	empty();
}

void Debugger::Synchronize(uint8_t d){
	Push(d);
	Push(d);
	Push(d);
	Push(d);
}

void Debugger::Flush(){
	for(int i = 0; i < index; i++){
		SendByte(buffer[i]);
	}
	index = 0;
}

void Debugger::Push(uint8_t *buff, uint16_t start, uint16_t end){
	for(int i = start; i <= end; i++){
		Push(buff[i]);	
	}
}

void Debugger::Push(MovementParameters* movParam){
	Push(movParam->v);
	Push(movParam->h);
	Push(movParam->s);
	Push(movParam->t);
	Push(movParam->fm);
}

void Debugger::Push(FlightDutyTask* flightTask){
	Push(flightTask->Ndz);
	for(int i = 0; i < 10; i++){
		Push(flightTask->Sdz_s[i]);
	}
	for(int i = 0; i < 10; i++){
		Push(flightTask->Sdz_e[i]);
	}
	Push(flightTask->Nsd);
	for(int i = 0; i < 4; i++){
		Push(flightTask->Ssd_e[i]);
	}
}

void Debugger::Push(StartDutyTask* startTask){
	Push(startTask->Hmin);
	Push(startTask->Hmax);
	Push(startTask->Vmin);
	Push(startTask->Vxmax);
	Push(startTask->Vymax);
	Push(startTask->Vzmax);
	Push(startTask->Ntp);
	Push(startTask->Nsd);
	for(int i = 0; i < 4; i++){
		Push(startTask->Ssd_e[i]);
	}
}

inline void Debugger::empty(){
	index = 0;
}






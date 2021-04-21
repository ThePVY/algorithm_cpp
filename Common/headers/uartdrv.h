#pragma once
#include "top.h"

class uart{
public:
	uint32_t sys_freq;
	UART_T* pUART;
	
	uart(UART_T* pUART, uint32_t freq);
	
	void Flush(uint8_t *buff, uint32_t size);
	void FlushWords(uint8_t *buff, uint32_t size);
	inline void SendByte(uint8_t byte){ 
		UART_SendByte(pUART, byte);
		waite4ready();
	}
protected:
	inline void init();
	inline void gpioInit_UART2();
	void waite4ready(){ while(UART_GetStatus(pUART, UART_FR_BUSY)); }
};
/*-------------------------------------------------------------------*/
class Debugger : public uart{
private:
	uint16_t index;
	uint8_t buffer[96];
	uint8_t dataCnt;
public:
	bool JustOnce;
	
	Debugger(UART_T* pUART, uint32_t freq);
	
	void Synchronize(uint8_t d);
	
	void Flush();
	
	inline void Push(uint8_t data){ buffer[index++] = data; }
	inline void Push(uint16_t data){ Push((uint8_t)(data >> 8)); Push((uint8_t)data); }
	void Push(uint8_t *buff, uint16_t start, uint16_t end);
	void Push(MovementParameters* movParam);
	void Push(FlightDutyTask* flightTask);
	void Push(StartDutyTask* startTask);
	
	void PerformTestAction(){
		Synchronize(ACTION);
		Push((uint8_t)Actions::test);
		Flush();
	}
private:
	inline void empty();
	
};

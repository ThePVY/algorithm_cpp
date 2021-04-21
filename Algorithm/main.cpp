#include "top.h"

int main()
{
	Algorithm algorithm;
	
	UART_SendByte(UART2, 0xAA);
	while(true){
		algorithm.ProcessIvents();
	}
}

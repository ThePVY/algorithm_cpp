#include "top.h"

	
Global::Global(){
	mkpdInterrupt = 0;
	CommandWord = 0;
	uart_ept_en = false;
	IsMI = false;
	IsTI = false;
	CmdTI1 = false;
	CmdTI2 = false;
	CommTI = false;
	SelfTI = false;
	BCcommand.all = 0;
}




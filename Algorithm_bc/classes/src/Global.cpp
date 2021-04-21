#include "top.h"

	
Global::Global(): uart_ept_en(false), IsMI(false), IsTI(false), MovTI(false), CommTI(false)
{
	mkpdInterrupt = 0;
	BCcommand.all = 0;
	
	movCnt = 0;
	commCnt = 0;
}




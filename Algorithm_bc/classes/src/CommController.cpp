#include "top.h"

CommController::CommController(Timer* cT): commTimer(cT), IsActive(false), IsCommTime(false){}

void CommController::ProcessTI(){
	IsCommTime = true;
	commTimer->Reload(COMM_TIME_STEP);
}

#pragma once
#include "top.h"

class CommController{
private:
	Timer* commTimer;
public:
	bool IsActive;
	bool IsCommTime;
	
	CommController(Timer* cT);
	
	inline void StartCountdown(){ commTimer->Start(COMM_TIME_STEP); IsActive = true; }
	void ProcessTI();
private:
	
};


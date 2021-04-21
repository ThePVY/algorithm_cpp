#pragma once

#include "top.h"

class Algorithm{
public:
	Hardware MC;
	DataExtractor Extractor;
	ZoneController ZC;
	SelfOperation SOC;
	
	StartDutyTask StartTask;
	FlightDutyTask FlightTask;
	MovementParameters MovParam;
	
	Command1x Cmd1x;
	Handler1_12 H11;
	Handler1_12 H12;
	Handler1_34 H13;
	Handler1_34 H14;
	Command4x Cmd4x;
	Handler4x H4x;
	
	Algorithm();
	
	void ProcessIvents();
	
private:
	inline void processCommunication();
	inline void processSetup();
	
	void processPackage();
	void processCommand(Subaddrs subaddr);
	void processTimer();
};

	
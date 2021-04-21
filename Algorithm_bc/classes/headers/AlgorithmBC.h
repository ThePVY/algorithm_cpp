#pragma once
#include "top.h"

class AlgorithmBC{
public:
	Hardware			MC;
	MovementController 	MovCtrl;
	CommController		CommCtrl;
	PackageController 	PackCtrl;

	MovementParameters 	MovParam;
	FlightDutyTask		FlightTask;
	StartDutyTask		StartTask;
	
	AlgorithmBC();
	
	void StartMovement();
	void ProcessIvents();
	
	friend int main();
	friend class PackageController;
private:
	inline void processTI();
};

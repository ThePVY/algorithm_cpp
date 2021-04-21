#include "top.h"

MovementController::MovementController(AlgorithmBC* a): a(a){
	distance = SECTION_LENGTH;
	currentSection = TSections::TS0;
	IsActive = false;
	IsNextSection = true;
}

void MovementController::StartMovement(){
	a->MC.movTimer.Start(DIST_TIME_STEP); 
	IsActive = true; 
}

void MovementController::ProcessTI(){
	if(distance >= 0){
		distance -= DISTANCE_STEP;
	}
	else{
		distance = SECTION_LENGTH;
		currentSection = (TSections)((int)currentSection + 1);
		updateFDT();
		IsNextSection = true;
	}
	updateMP();
	a->MC.movTimer.Reload(DIST_TIME_STEP);
}

inline void MovementController::updateMP(){
	a->MovParam.v = 600;
	a->MovParam.h = 20000;
	a->MovParam.s = distance; //меняется
	a->MovParam.t = (uint16_t)(distance/a->MovParam.v); //меняется
	a->MovParam.fm = 1;
}

void MovementController::updateFDT(){
	if(currentSection <= TSections::TS4){
		a->FlightTask.Ndz = 1;
		a->FlightTask.Sdz_s[0] = DIST_DZ_START;
		nullify(a->FlightTask.Sdz_s, 1, 9);
		a->FlightTask.Sdz_e[0] = DIST_DZ_END;
		nullify(a->FlightTask.Sdz_e, 1, 9);
		a->FlightTask.Nsd = 2;
		a->FlightTask.Ssd_e[0] = DIST_SD_END;
		nullify(a->FlightTask.Ssd_e, 1, 3);
	}else if(currentSection != TSections::TS6){
		a->FlightTask.Ndz = 2;
		a->FlightTask.Sdz_s[0] = DISTANCE_STEP * 30;
		a->FlightTask.Sdz_s[1] = DISTANCE_STEP * 20;
		nullify(a->FlightTask.Sdz_s, 2, 8);
		a->FlightTask.Sdz_e[0] = DISTANCE_STEP * 25;
		a->FlightTask.Sdz_e[1] = DISTANCE_STEP * 15;
		nullify(a->FlightTask.Sdz_e, 2, 8);
		a->FlightTask.Nsd = 0;
		nullify(a->FlightTask.Ssd_e, 0, 4);
	}else{
		a->FlightTask.Ndz = 1;
		a->FlightTask.Sdz_s[0] = DISTANCE_STEP * 37;
		nullify(a->FlightTask.Sdz_s, 1, 9);
		a->FlightTask.Sdz_e[0] = DISTANCE_STEP * 3;
		nullify(a->FlightTask.Sdz_e, 1, 9);
		a->FlightTask.Nsd = 0;
		nullify(a->FlightTask.Ssd_e, 0, 4);
	}
}

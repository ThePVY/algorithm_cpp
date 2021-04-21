#pragma once
#include "top.h"

class Algorithm;

/*
Каждый Такт информационного взаимодействия (при получении ПД)
класс контролирует зону (enum class Zones), в которой находится устройство.
*/
class ZoneController{
private:
	Algorithm* a;
	uint8_t indexDZ;
	uint8_t indexSD_overall;
	uint8_t indexSD_inS;
public:
	Zones Zone;
	uint8_t SectionCounter;
	DZTypes DZType;
	
	ZoneController(Algorithm* a);
	
	void UpdateZone();
	inline void IndexDZ(uint8_t i) { indexDZ = i; }
	inline void IndexSD(uint8_t i) { indexSD_inS = i; }
	
private:
	inline void updateSD();
	inline void updateDZ();
	inline bool isInDZ();
	inline bool crossedSD();
	
};







#pragma once
#include "top.h"

class AlgorithmBC;
class PackageController;

class MovementController{
private:
	int distance;		//расстояние до ППМ
	AlgorithmBC* a;
	
	TSections currentSection;
public:
	bool IsActive; //Используется для обработки прерывания movTimer
	bool IsNextSection; //Флаг, сигнализирующий о переходе на новый УТ (надо передавать FDT)
	
	MovementController(AlgorithmBC* a);
	
	void StartMovement();
	inline int Distance(){ return distance; }
	inline TSections CurrentSection(){ return currentSection; }
	void ProcessTI();
	
	friend class PackageController;
private:
	inline void updateMP();
	void updateFDT();
};

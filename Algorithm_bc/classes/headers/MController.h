#pragma once
#include "top.h"

class AlgorithmBC;
class PackageController;

class MovementController{
private:
	int distance;		//���������� �� ���
	AlgorithmBC* a;
	
	TSections currentSection;
public:
	bool IsActive; //������������ ��� ��������� ���������� movTimer
	bool IsNextSection; //����, ��������������� � �������� �� ����� �� (���� ���������� FDT)
	
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

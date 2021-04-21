#pragma once

#include "top.h"

class Algorithm;

class DataExtractor{
private:
	Algorithm*			a;
  	StartDutyTask*		startTask;
	FlightDutyTask*		flightTask;
	MovementParameters*	movParam;
	Command1x*			command1x;
	Command4x*			command4x;
	
	uint8_t* dma_buff;
	uint16_t index;
	Packages updatedPackage;
	
public:
	DataExtractor(Algorithm* a);
	
	inline uint8_t* GetDMABuff(){ return dma_buff; }
	inline uint16_t GetIndex() { return index; }
	inline Packages GetUpdatedPackage(){ return updatedPackage; }
	
	void ExtractData(Subaddrs subaddr);
	
private:
	void setIndex(Subaddrs subaddr);
	inline void fillMovParam();
	void extractPackage1x(Subaddrs subaddr);
	void extractPackage4x(Subaddrs subaddr);
	void extractPackageMP(Subaddrs subaddr);
	void extractPackageFDT(Subaddrs subaddr);
	void extractPackageSDT(Subaddrs subaddr);
	inline uint16_t pop();
	inline void nullify(uint16_t* buff, int start, int end);
};

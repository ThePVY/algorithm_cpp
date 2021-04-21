#pragma once

#include "top.h"

class AlgorithmBC;

class PackageX{
protected:
	uint8_t* dma_buff;
	uint16_t dma_index;
	uart* dbgUART;
	MovementParameters* movParam;
public:
	PackageX(AlgorithmBC* a);
	
	void SendDI(Subaddrs saddr);
	
protected:
	inline void fillMP();
	inline void push(uint16_t data);
	inline void processTransaction(Subaddrs EP1_saddr, uint8_t dataLength);
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*-->������� + �� = 6 ��*/
class PackageNX : public PackageX{
public:
	PackageNX(AlgorithmBC* a);
	
	void Send(Subaddrs subaddr, uint16_t cmd);
	
private:
	inline void fillDMA(uint16_t cmd);
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*-->Flight Duty Task--> ��� + �� = 26 + 5 = 31 ��*/
class PackageFDT : public PackageX{
private:
	FlightDutyTask* flightTask;
public:	
	PackageFDT(AlgorithmBC* a);
	
	void Send(Subaddrs subaddr);

private:
	inline void fillDMA();
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*-->Start Duty Task--> ��� + �� = 8 ��*/
class PackageSDT : public PackageX{
private:
	StartDutyTask* startTask;
public:	
	PackageSDT(AlgorithmBC* a);
	
	void Send(Subaddrs subaddr);

private:
	inline void fillDMA();
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*-->Movement Parameters--> �� = 5 ��*/
class PackageMP : public PackageX{
public:
	PackageMP(AlgorithmBC* a);
	
	void Send(Subaddrs subaddr);

private:
	inline void fillDMA();
};

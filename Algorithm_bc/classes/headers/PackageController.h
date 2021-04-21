#pragma once
#include "top.h"

class AlgorithmBC;

class PackageController{
private:
	AlgorithmBC* a;
	
	PackageNX packNX;
	PackageFDT packFDT;
	PackageSDT packSDT;
	PackageMP packMP;
	uint16_t* dma_buff;
	uint8_t	package_length;
	
	bool cmd11_IsSent;
	bool cmd12_IsSent;
	bool cmd13_IsSent;
	bool cmd14_IsSent;
	bool cmd4x_IsSent;
	
	uint32_t packCounter;
public:
	PackageController(AlgorithmBC* a);
	
	void SendPackage(Subaddrs subaddr);
	void ProcessCommunication(int distance, TSections section);
	
private:
	void processTS0(int distance);
	void processTS1_3(int distance, Subaddrs c4x);
	void processTS4_5();
	void processTS6();
};


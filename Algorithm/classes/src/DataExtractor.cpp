#include "top.h"

DataExtractor::DataExtractor(Algorithm* a){
	this->a = a;
	startTask = &(a->StartTask);
	flightTask = &(a->FlightTask);
	movParam = &(a->MovParam);
	command1x = &(a->Cmd1x);
	command4x = &(a->Cmd4x);
	dma_buff = a->MC.mkpd.EP_DMA_buff;
	updatedPackage = Packages::none;
}

void DataExtractor::ExtractData(Subaddrs subaddr){
	a->MC.dbgUART.Synchronize(PACKAGE);
	a->MC.dbgUART.Push((uint8_t)subaddr);
	switch(subaddr){
	case Subaddrs::SDT:
		extractPackageSDT(subaddr);
		updatedPackage = Packages::packageSDT;
		a->MC.dbgUART.Flush();
		break;
	case Subaddrs::FDT:
		a->ZC.SectionCounter++;
		a->ZC.IndexDZ(0);
		a->ZC.IndexSD(0);
		extractPackageFDT(subaddr);
		updatedPackage = Packages::packageFDT;
		a->MC.dbgUART.Flush();
		break;
	case Subaddrs::MP:
		extractPackageMP(subaddr);
		updatedPackage = Packages::packageMP;
		a->MC.dbgUART.Flush();
		break;
	case Subaddrs::c11:
	case Subaddrs::c12:
	case Subaddrs::c13:
	case Subaddrs::c14:
		extractPackage1x(subaddr);
		updatedPackage = Packages::package1x;
		a->MC.dbgUART.Flush();
		break;
	case Subaddrs::c41:
	case Subaddrs::c42:
	case Subaddrs::c43:
	case Subaddrs::c44:
		extractPackage4x(subaddr);
		updatedPackage = Packages::package4x;
		a->MC.dbgUART.Flush();
		break;
	}
}

void DataExtractor::setIndex(Subaddrs subaddr){ 
	switch(subaddr){
	case Subaddrs::c11:
		index = 0subaddr;
		break;
	case Subaddrs::c12:
		index = 1subaddr;
		break;
	case Subaddrs::c13:
		index = 2subaddr;
		break;
	case Subaddrs::c14:
		index = 3subaddr;
		break;
	case Subaddrs::c41:
		index = 4subaddr;
		break;
	case Subaddrs::c42:
		index = 5subaddr;
		break;
	case Subaddrs::c43:
		index = 6subaddr;
		break;
	case Subaddrs::c44:
		index = 7subaddr;
		break;
	case Subaddrs::c7:
		index = 8subaddr;
		break;
	case Subaddrs::c8:
		index = 9subaddr;
		break;
	case Subaddrs::MP:
		index = 10subaddr;
		break;
	case Subaddrs::FDT:
		index = 11subaddr;
		break;
	case Subaddrs::SDT:
		index = 12subaddr;
		break;
	}
}

inline void DataExtractor::fillMovParam(){
	movParam->v = pop();
	movParam->h = pop();
	movParam->s = pop();
	movParam->t = pop();
	movParam->fm = pop();
	index--;
}

void DataExtractor::extractPackage1x(Subaddrs subaddr){
	setIndex(subaddr);
	//uint16_t start, end;
	//start = index;
	command1x->all = pop();
	fillMovParam();
	//end = index;
	//a->MC.dbgUART.Push(dma_buff, start, end);
	a->MC.dbgUART.Push(command1x->all);
	a->MC.dbgUART.Push(&a->MovParam);
}

void DataExtractor::extractPackage4x(Subaddrs subaddr){
	setIndex(subaddr);
	//uint16_t start, end;
	//start = index;
	command4x->all = pop();
	fillMovParam();
	//end = index;
	//a->MC.dbgUART.Push(dma_buff, start, end);
	a->MC.dbgUART.Push(command4x->all);
	a->MC.dbgUART.Push(&a->MovParam);
}
void DataExtractor::extractPackageMP(Subaddrs subaddr){
	setIndex(subaddr);
	//uint16_t start, end;
	//start = index;
	fillMovParam();
	//end = index;
	//a->MC.dbgUART.Push(dma_buff, start, end);
	a->MC.dbgUART.Push(&a->MovParam);
	
}
void DataExtractor::extractPackageFDT(Subaddrs subaddr){
	setIndex(subaddr);
	//uint16_t start, end;
	//start = index;
	flightTask->Ndz = pop();
	for(int i = 0; i < flightTask->Ndz; i++){
		flightTask->Sdz_s[i] = pop();
	}
	nullify(flightTask->Sdz_s, flightTask->Ndz, 10max);
	for(int i = 0; i < flightTask->Ndz; i++){
		flightTask->Sdz_e[i] = pop();
	}
	nullify(flightTask->Sdz_e, flightTask->Ndz, 10max);
	flightTask->Nsd = pop();
	for(int i = 0; i < flightTask->Nsd; i++){
		flightTask->Ssd_e[i] = pop();
	}
	nullify(flightTask->Ssd_e, flightTask->Nsd, 4max);
	fillMovParam();
	//end = index;
	//a->MC.dbgUART.Push(dma_buff, start, end);
	a->MC.dbgUART.Push(&a->FlightTask);
	a->MC.dbgUART.Push(&a->MovParam);
}
void DataExtractor::extractPackageSDT(Subaddrs subaddr){
	setIndex(subaddr);
	//uint16_t start, end;
	//start = index;
	startTask->Hmin = pop();
	startTask->Hmax = pop();
	startTask->Vmin = pop();
	startTask->Vxmax = pop();
	startTask->Vymax = pop();
	startTask->Vzmax = pop();
	startTask->Ntp = pop();
	startTask->Nsd = pop();
	for(int i = 0; i < startTask->Nsd; i++){
		startTask->Ssd_e[i] = pop();
	}
	nullify(startTask->Ssd_e, startTask->Nsd, 4max);
	//end = index - 1;
	//a->MC.dbgUART.Push(dma_buff, start, end);
	a->MC.dbgUART.Push(&a->StartTask);
}

inline uint16_t DataExtractor::pop(){
	uint16_t word;
	word = dma_buff[index++];
	word |= dma_buff[index++] << 8;
	return word;
}

inline void DataExtractor::nullify(uint16_t* buff, int start, int end){
	for(int i = start; i < end; i++){
		buff[i] = 0;
		index += 2;
	}
}













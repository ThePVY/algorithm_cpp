#include "top.h"

PackageX::PackageX(AlgorithmBC* a): dma_index(0){
	dma_buff = a->MC.mkpd.BC_DMA_buff;
	movParam = &a->MovParam;
	dbgUART = &a->MC.uart2;
}

void PackageX::SendDI(Subaddrs saddr){
	dbgUART->SendByte(0xAC);
	dbgUART->SendByte(0xAC);
	dbgUART->SendByte(0xAC);
	dbgUART->SendByte(0xAC);
	dbgUART->SendByte(static_cast<uint8_t>(saddr));
	dbgUART->FlushWords(dma_buff, dma_index);
}

inline void PackageX::fillMP(){
	push(movParam->v);
	push(movParam->h);
	push(movParam->s);
	push(movParam->t);
	push(movParam->fm);
}

inline void PackageX::push(uint16_t data){
	dma_buff[dma_index++]  = (uint8_t)data;
	dma_buff[dma_index++]  = (uint8_t)(data >> 8);
}

inline void PackageX::processTransaction(Subaddrs EP1_saddr, uint8_t dataLength){
	int volatile status;
	status = MKPD_StartMessage(MKPD1, TX_ONE, TT_WRITE,
						EP1_addr, (unsigned int)EP1_saddr,
						1, 0,
						dataLength,
						TRANSACTION_TIMEOUT,
						MANAGE_CODE);
	//dbgUART->SendByte((uint8_t)status);
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
PackageNX::PackageNX(AlgorithmBC* a): PackageX(a){}

void PackageNX::Send(Subaddrs subaddr, uint16_t cmd){
	fillDMA(cmd);
	processTransaction(subaddr, CMD_PACKAGE_LENGTH);
}

void PackageNX::fillDMA(uint16_t cmd){
	dma_index = 0;
	push(cmd);
	fillMP();
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
PackageFDT::PackageFDT(AlgorithmBC* a): PackageX(a), flightTask(&a->FlightTask){}

void PackageFDT::Send(Subaddrs subaddr){
	fillDMA();
	processTransaction(subaddr, FDT_PACKAGE_LENGTH);
}

inline void PackageFDT::fillDMA(){
	dma_index = 0;
	push(flightTask->Ndz);
	for(int i = 0; i < 10; i++)
		push(flightTask->Sdz_s[i]);
	for(int i = 0; i < 10; i++)
		push(flightTask->Sdz_e[i]);
	push(flightTask->Nsd);
	for(int i = 0; i < 4; i++)
		push(flightTask->Ssd_e[i]);
	fillMP();
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
PackageSDT::PackageSDT(AlgorithmBC* a): PackageX(a), startTask(&a->StartTask){}

void PackageSDT::Send(Subaddrs subaddr){
	fillDMA();
	processTransaction(subaddr, SDT_PACKAGE_LENGTH);
}

inline void PackageSDT::fillDMA(){
	dma_index = 0;
	push(startTask->Hmin);
	push(startTask->Hmax);
	push(startTask->Vmin);
	push(startTask->Vxmax);
	push(startTask->Vymax);
	push(startTask->Vzmax);
	push(startTask->Ntp);
	push(startTask->Nsd);
	for(int i = 0; i < 4; i++)
		push(startTask->Ssd_e[i]);
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
PackageMP::PackageMP(AlgorithmBC* a): PackageX(a){}

void PackageMP::Send(Subaddrs subaddr){
	fillDMA();
	processTransaction(subaddr, SDT_PACKAGE_LENGTH);
}

inline void PackageMP::fillDMA(){
	dma_index = 0;
	fillMP();
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/












#include "top.h"

Handler1_x::Handler1_x(Algorithm* a, Timer* cmdTimer){
	this->a = a;
	this->cmdTimer = cmdTimer;
	pin1 = Pins1x::none;
	pin2 = Pins1x::none;
	pauseBit = false;
	code = 0;
	codeIndex = 0;
	Time = 0;
	IsActive = false;
	subaddr = Subaddrs::none;
}

void Handler1_x::configureTime(){
	switch(a->Cmd1x.bits.time){
	case 0:
		Time = (uint32_t)Time1x::t0;
		break;
	case 1:
		Time = (uint32_t)Time1x::t1;
		break;
	case 2:
		Time = (uint32_t)Time1x::t2;
		break;
	case 3:
		Time = (uint32_t)Time1x::t3;
		break;
	default:
		Time = 0;
		break;
	}
}
void Handler1_x::configurePins(){
	switch(a->Cmd1x.bits.outs){
	case 0:
		pin1 = Pins1x::pin1;
		pin2 = Pins1x::pin2;
		break;
	case 1:
		pin1 = Pins1x::pin2;
		pin2 = Pins1x::pin3;
		break;
	case 2:
		pin1 = Pins1x::pin3;
		pin2 = Pins1x::pin4;
		break;
	case 3:
		pin1 = Pins1x::pin1;
		pin2 = Pins1x::pin4;
		break;	
	default:
		pin1 = Pins1x::none;
		pin2 = Pins1x::none;
		break;
	}
}

inline bool Handler1_x::pinsConflicting(){
	if(pin1 == otherHandler->Pin1() || pin2 == otherHandler->Pin2() ||
	   pin1 == otherHandler->Pin2() || pin2 == otherHandler->Pin1() ||
	   pin1 == Pins1x::none || pin2 == Pins1x::none){
		return true;
	}
	else{
		return false;
	}
}

void Handler1_x::ProcessCmd(){
	if(processStart()){
		processCS();
	}
}

void Handler1_x::ProcessTI(){
	processCS();
	processTimerOff();
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
Handler1_12::Handler1_12(Algorithm* a, Timer* ct): Handler1_x(a, ct){}

bool Handler1_12::processStart(){
	pauseBit = false;
	codeIndex = 0;
	configureTime();
	configurePins();	
	if(!pinsConflicting()){
		IsActive = true;
		code = a->Cmd1x.bits.code;
		cmdTimer->Start(Time);
		
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd1_12);
		a->MC.dbgUART.Push((uint8_t)pin1);
		a->MC.dbgUART.Push((uint8_t)pin2);
		a->MC.dbgUART.Push((uint8_t)(Time>>8));
		a->MC.dbgUART.Push((uint8_t)Time);
		return true;
	}
	else{
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::pins1xConflict);
		a->MC.dbgUART.Push((uint8_t)pin1);
		a->MC.dbgUART.Push((uint8_t)pin2);
		a->MC.dbgUART.Push((uint8_t)otherHandler->Pin1());
		a->MC.dbgUART.Push((uint8_t)otherHandler->Pin2());
		a->MC.dbgUART.Flush();
		return false;
	}
}

/*
Process Control Sequence
*/
void Handler1_12::processCS(){
	bool setPin1;
	if(!pauseBit){
		pauseBit = true;
		setPin1 = (bool)((code >> codeIndex) & 0x1);
		if(setPin1){
			setBit(V1x_PORT->DATAOUT, pin1);
			clearBit(V1x_PORT->DATAOUT, pin2);
			a->MC.dbgUART.Push((uint8_t)2);
		}else{
			clearBit(V1x_PORT->DATAOUT, pin1);
			setBit(V1x_PORT->DATAOUT, pin2);
			a->MC.dbgUART.Push((uint8_t)1);
		}
	}else{
		pauseBit = false;
		clearBit(V1x_PORT->DATAOUT, pin1);
		clearBit(V1x_PORT->DATAOUT, pin2);
		codeIndex++;
		a->MC.dbgUART.Push((uint8_t)0);
	}
}

void Handler1_12::processTimerOff(){
	if(isEndOfCS()){
		codeIndex = 0;
		IsActive = false;
		cmdTimer->Off();
		a->MC.dbgUART.Flush();
	}
	else{
		cmdTimer->Reload(Time);
	}
}
/*----------------------------------------------------------------------------*/
Handler1_34::Handler1_34(Algorithm* a, Timer* ct): Handler1_x(a, ct){

}

bool Handler1_34::processStart(){
	pauseBit = false;
	codeIndex = 0;
	configureTime();
	configurePins();
	if(!pinsConflicting()){
		IsActive = true;
		code = a->Cmd1x.bits.code;
		cmdTimer->Start(Time);
		
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd1_34_start);
		a->MC.dbgUART.Push((uint8_t)pin1);
		a->MC.dbgUART.Push((uint8_t)pin2);
		a->MC.dbgUART.Push((uint8_t)(Time>>8));
		a->MC.dbgUART.Push((uint8_t)Time);
		a->MC.dbgUART.Flush();
		return true;
	}
	else{
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::pins1xConflict);
		a->MC.dbgUART.Push((uint8_t)pin1);
		a->MC.dbgUART.Push((uint8_t)pin2);
		a->MC.dbgUART.Push((uint8_t)otherHandler->Pin1());
		a->MC.dbgUART.Push((uint8_t)otherHandler->Pin2());
		a->MC.dbgUART.Flush();
		return false;
	}
}

/*
Process Control Sequence
*/
void Handler1_34::processCS(){
	if(!pauseBit){
		pauseBit = true;
		bool setPin1 = (bool)((code >> codeIndex) & 0x1);
		if(setPin1){
			setBit(V1x_PORT->DATAOUT, pin1);
			clearBit(V1x_PORT->DATAOUT, pin2);
		}else{
			clearBit(V1x_PORT->DATAOUT, pin1);
			setBit(V1x_PORT->DATAOUT, pin2);
		}
	}else{
		pauseBit = false;
		clearBit(V1x_PORT->DATAOUT, pin1);
		clearBit(V1x_PORT->DATAOUT, pin2);
		codeIndex++;
	}
}

void Handler1_34::processTimerOff(){
	if(isEndOfCS()){
		codeIndex = 0;
	}
	if(a->ZC.Zone != Zones::SD0){
		IsActive = false;
		cmdTimer->Off();
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd1_34_end);
		a->MC.dbgUART.Flush();
	}
	else{
		cmdTimer->Reload(Time);
	}
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
Handler4x::Handler4x(Algorithm* a): a(a){
	lastSettedPin = Pins4x::none;
	pin1 = Pins4x::none;
	pin2 = Pins4x::none;
	pin3 = Pins4x::none;
	pin4 = Pins4x::none;
	pin1IsSet = false;
	pin2IsSet = false;
	pin3IsSet = false;
	pin4IsSet = false;
	delay12 = 0;
	delay23 = 0;
	delay34 = 0;
	sdNum = 0;
	cmdNum = 0;
}


Pins4x Handler4x::setPin(uint8_t pin){
	switch(pin){
	case 0: 
		return Pins4x::pin1;
	case 1: 
		return Pins4x::pin2;
	case 2: 
		return Pins4x::pin3;
	case 3: 
		return Pins4x::pin4;
	default:
		return Pins4x::none;
	}
}

void Handler4x::configurePins(){
	pin1 = setPin((uint8_t)a->Cmd4x.bits.out1);
	pin2 = setPin((uint8_t)a->Cmd4x.bits.out2);
	pin3 = setPin((uint8_t)a->Cmd4x.bits.out3);
	//присвоить оставшийся пин из четырех (три уже занято)
	pin4 = setPin((uint8_t)(a->Cmd4x.bits.out1 ^ a->Cmd4x.bits.out2 ^ a->Cmd4x.bits.out3));
}

/*--задать задержки в мс (на вход подается время, кратное 2,5 с)--*/
void Handler4x::configureTime(){
	delay12 = 2500*(uint32_t)(a->Cmd4x.bits.delay12);
	delay23 = 2500*(uint32_t)(a->Cmd4x.bits.delay23);
	delay34 = 2500*(uint32_t)(a->Cmd4x.bits.delay34);
}

/*Соотносит номер команды В41-В44 с subaddr. 4 в выражении - нормирование.
!!!Пока что используется универсальный подход в ущерб быстродействию!!!*/
void Handler4x::matchCmd(){
	//cmdNum = static_cast<uint8_t>(subaddr) - 4;
	switch(subaddr){
	case Subaddrs::c41:
		cmdNum = 1;
		break;
	case Subaddrs::c42:
		cmdNum = 2;
		break;
	case Subaddrs::c43:
		cmdNum = 3;
		break;
	case Subaddrs::c44:
		cmdNum = 4;
		break;
	default:
		cmdNum = 0xFF;
		break;
	}
}
/*ставит в соответствие с БД чило от 0 до 4. 1 в выражении - нормирование.
!!!Пока что используется универсальный подход в ущерб быстродействию!!!*/
void Handler4x::matchSD(){
	//sdNum = static_cast<uint8_t>(a->ZC.Zone) - 1;
	switch(a->ZC.Zone){
	case Zones::SD0:
		sdNum = 0;
		break;
	case Zones::SD1:
		sdNum = 1;
		break;
	case Zones::SD2:
		sdNum = 2;
		break;
	case Zones::SD3:
		sdNum = 3;
		break;
	case Zones::SD4:
		sdNum = 4;
		break;
	default:
		cmdNum = 0;
		break;
	}
}
/*
	Функция начинает набор мощности (последовательное включение пинов), контролируя,
были ли уже выставлены какие-нибудь пины и можно ли вообще набирать мощность в этой зоне.
	Перед выставлением каждого пина проверяем, можно ли его включать в этой зоне.
	Перед включением таймера также проверяем, можно ли будет включить следующий пин в этой зоне.
	При этом имеем ввиду, что ProcessCmd может быть вызван только при получении команд 4x,
что обусловлено классом Algorithm.
*/
void Handler4x::ProcessCmd(Subaddrs subaddr){
	IsActive = true;
	Handler4x::subaddr = subaddr;
	configurePins();
	configureTime();
	matchCmd();
	matchSD();
	if(lastSettedPin == Pins4x::none && a->ZC.Zone >= Zones::SD1 && subaddr >= Subaddrs::c41 && sdNum >= cmdNum){
		setBit(V4x_PORT->DATAOUT, (uint16_t)pin1);
		pin1IsSet = true;
		lastSettedPin = Pins4x::pin1;
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd4x);
		a->MC.dbgUART.Push((uint8_t)lastSettedPin);
		if(subaddr != Subaddrs::c41 && (a->ZC.Zone >= Zones::SD2)){
			a->MC.cmdTimer1.Start(delay12);
			a->MC.dbgUART.Push((uint8_t)1);
		}
		else{
			a->MC.dbgUART.Push((uint8_t)0);
		}
		a->MC.dbgUART.Push((uint8_t)pin4IsSet);
		a->MC.dbgUART.Push((uint8_t)pin3IsSet);
		a->MC.dbgUART.Push((uint8_t)pin2IsSet);
		a->MC.dbgUART.Push((uint8_t)pin1IsSet);
		a->MC.dbgUART.Flush();
	}
	else if(lastSettedPin == Pins4x::pin1 && a->ZC.Zone >= Zones::SD2 && subaddr >= Subaddrs::c42 && sdNum >= cmdNum){
		setBit(V4x_PORT->DATAOUT, (uint16_t)pin2);
		pin2IsSet = true;
		lastSettedPin = Pins4x::pin2;
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd4x);
		a->MC.dbgUART.Push((uint8_t)lastSettedPin);
		if(subaddr != Subaddrs::c42 && (a->ZC.Zone >= Zones::SD3)){
			a->MC.cmdTimer1.Start(delay23);
			a->MC.dbgUART.Push((uint8_t)1);
		}
		else{
			a->MC.dbgUART.Push((uint8_t)0);
		}
		a->MC.dbgUART.Push((uint8_t)pin4IsSet);
		a->MC.dbgUART.Push((uint8_t)pin3IsSet);
		a->MC.dbgUART.Push((uint8_t)pin2IsSet);
		a->MC.dbgUART.Push((uint8_t)pin1IsSet);
		a->MC.dbgUART.Flush();
	}
	else if(lastSettedPin == Pins4x::pin2 && a->ZC.Zone >= Zones::SD3 && subaddr >= Subaddrs::c43 && sdNum >= cmdNum){
		setBit(V4x_PORT->DATAOUT, (uint16_t)pin3);
		pin3IsSet = true;
		lastSettedPin = Pins4x::pin3;
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd4x);
		a->MC.dbgUART.Push((uint8_t)lastSettedPin);
		if(subaddr != Subaddrs::c43 && (a->ZC.Zone >= Zones::SD4)){
			a->MC.cmdTimer1.Start(delay34);
			a->MC.dbgUART.Push((uint8_t)1);
		}
		else{
			a->MC.dbgUART.Push((uint8_t)0);
		}
		a->MC.dbgUART.Push((uint8_t)pin4IsSet);
		a->MC.dbgUART.Push((uint8_t)pin3IsSet);
		a->MC.dbgUART.Push((uint8_t)pin2IsSet);
		a->MC.dbgUART.Push((uint8_t)pin1IsSet);
		a->MC.dbgUART.Flush();
	}
	else if(lastSettedPin == Pins4x::pin3 && a->ZC.Zone >= Zones::SD4 && subaddr == Subaddrs::c44 && sdNum >= cmdNum){
		setBit(V4x_PORT->DATAOUT, (uint16_t)pin4);
		pin4IsSet = true;
		lastSettedPin = Pins4x::pin4;
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd4x);
		a->MC.dbgUART.Push((uint8_t)lastSettedPin);
		a->MC.dbgUART.Push((uint8_t)0);
		a->MC.dbgUART.Push((uint8_t)pin4IsSet);
		a->MC.dbgUART.Push((uint8_t)pin3IsSet);
		a->MC.dbgUART.Push((uint8_t)pin2IsSet);
		a->MC.dbgUART.Push((uint8_t)pin1IsSet);
		a->MC.dbgUART.Flush();
	}
	else{
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd4x);
		a->MC.dbgUART.Push((uint8_t)Pins4x::none);
		a->MC.dbgUART.Push((uint8_t)0);
		a->MC.dbgUART.Push((uint8_t)pin4IsSet);
		a->MC.dbgUART.Push((uint8_t)pin3IsSet);
		a->MC.dbgUART.Push((uint8_t)pin2IsSet);
		a->MC.dbgUART.Push((uint8_t)pin1IsSet);
		a->MC.dbgUART.Flush();
	}
}

/*
	Process Timer Ivent
	Функция обрабатывает прерывания таймера, пока IsActive = true;
	Она, как и ProcessStart, контролирует, были ли уже включены какие-то
пины и если были, то включает следующий и, если требуется включить еще пины,
перезагружает таймер новым значением, если же переключать пины не требуется, 
то IsActive = false и таймер выключается.
*/
void Handler4x::ProcessTI(){
	if(lastSettedPin == Pins4x::pin1){
		setBit(V4x_PORT->DATAOUT, (uint16_t)pin2);
		pin2IsSet = true;
		lastSettedPin = Pins4x::pin2;
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd4x);
		a->MC.dbgUART.Push((uint8_t)lastSettedPin);
		if(subaddr != Subaddrs::c42 && (a->ZC.Zone >= Zones::SD3)){
			a->MC.cmdTimer1.Reload(delay23);
			a->MC.dbgUART.Push((uint8_t)1);
		}
		else{
			IsActive = false;
			a->MC.dbgUART.Push((uint8_t)0);
		}
		a->MC.dbgUART.Push((uint8_t)pin4IsSet);
		a->MC.dbgUART.Push((uint8_t)pin3IsSet);
		a->MC.dbgUART.Push((uint8_t)pin2IsSet);
		a->MC.dbgUART.Push((uint8_t)pin1IsSet);
		a->MC.dbgUART.Flush();
	}
	else if(lastSettedPin == Pins4x::pin2){
		setBit(V4x_PORT->DATAOUT, (uint16_t)pin3);
		pin3IsSet = true;
		lastSettedPin = Pins4x::pin3;
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd4x);
		a->MC.dbgUART.Push((uint8_t)lastSettedPin);
		if(subaddr != Subaddrs::c43  && (a->ZC.Zone >= Zones::SD4)){
			a->MC.cmdTimer1.Reload(delay34);
			a->MC.dbgUART.Push((uint8_t)1);
		}
		else{
			IsActive = false;
			a->MC.dbgUART.Push((uint8_t)0);
		}
		a->MC.dbgUART.Push((uint8_t)pin4IsSet);
		a->MC.dbgUART.Push((uint8_t)pin3IsSet);
		a->MC.dbgUART.Push((uint8_t)pin2IsSet);
		a->MC.dbgUART.Push((uint8_t)pin1IsSet);
		a->MC.dbgUART.Flush();
	}
	else if(lastSettedPin == Pins4x::pin3){
		setBit(V4x_PORT->DATAOUT, (uint16_t)pin4);
		pin4IsSet = true;
		lastSettedPin = Pins4x::pin4;
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd4x);
		a->MC.dbgUART.Push((uint8_t)lastSettedPin);
		IsActive = false;
		a->MC.dbgUART.Push((uint8_t)0);
		a->MC.dbgUART.Push((uint8_t)pin4IsSet);
		a->MC.dbgUART.Push((uint8_t)pin3IsSet);
		a->MC.dbgUART.Push((uint8_t)pin2IsSet);
		a->MC.dbgUART.Push((uint8_t)pin1IsSet);
		a->MC.dbgUART.Flush();
	}
	else{
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::handleCmd4x);
		a->MC.dbgUART.Push((uint8_t)Pins4x::none);
		a->MC.dbgUART.Push((uint8_t)0);
		a->MC.dbgUART.Push((uint8_t)pin4IsSet);
		a->MC.dbgUART.Push((uint8_t)pin3IsSet);
		a->MC.dbgUART.Push((uint8_t)pin2IsSet);
		a->MC.dbgUART.Push((uint8_t)pin1IsSet);
		a->MC.dbgUART.Flush();
	}
	if(!IsActive){
		a->MC.cmdTimer1.Off();
	}
}






















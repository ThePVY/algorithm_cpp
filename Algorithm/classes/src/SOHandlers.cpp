#include "top.h"

HandlerCCT::HandlerCCT(Algorithm* a): a(a){
	IsActive = false;
	ConnectionLost = false;
	IsHandled = false;
}

void HandlerCCT::ProcessStart(){
	a->MC.ccTimer.Start(COMMUNICATION_TIMEOUT);
	IsActive = true;
}

void HandlerCCT::ProcessTI(){
	failCnt++;
	if(failCnt >= 5){
		ConnectionLost = true;
	}
	a->MC.ccTimer.Reload(COMMUNICATION_TIMEOUT);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
SetupHandler::SetupHandler(Algorithm* a): a(a){
	IsActive = false;
	IsReady = false;
	IsCansel = false;
	settedPin = SetupPins::none;
}

void SetupHandler::ProcessStart(){
	IsActive = true;
	setBit(SETUP_PORT->DATAOUT, SetupPins::pin1);
	settedPin = SetupPins::pin1;
	a->MC.selfTimer.Start(SETUP_DELAY);
}

void SetupHandler::ProcessTI(){
	if(settedPin == SetupPins::pin1){
		clearBit(SETUP_PORT->DATAOUT, SetupPins::pin1);
		setBit(SETUP_PORT->DATAOUT, SetupPins::pin2);
		settedPin = SetupPins::pin2;
	}
	else if(settedPin == SetupPins::pin2){
		clearBit(SETUP_PORT->DATAOUT, SetupPins::pin2);
		setBit(SETUP_PORT->DATAOUT, SetupPins::pin3);
		settedPin = SetupPins::pin3;
	}
	else if(settedPin == SetupPins::pin3){
		clearBit(SETUP_PORT->DATAOUT, SetupPins::pin3);
		settedPin = SetupPins::none;
		IsReady = true;
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::setup);
		a->MC.dbgUART.Flush();
	}
	else if(settedPin == SetupPins::cancelPin){
		clearBit(SETUP_PORT->DATAOUT, SetupPins::cancelPin);
		settedPin = SetupPins::none;
		IsReady = false;
		IsActive = false;
		IsCansel = false;
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::canselSetup);
		a->MC.dbgUART.Flush();
	}
	if(IsReady || !IsActive){
		a->MC.selfTimer.Off(); //отключили таймер после взведения или после отмены взведения
	}
	else{
		a->MC.selfTimer.Reload(SETUP_DELAY);
	}
}

inline void SetupHandler::Cancel(){
	setBit(SETUP_PORT->DATAOUT, SetupPins::cancelPin);
	settedPin = SetupPins::cancelPin;
	IsCansel = true;
	a->MC.selfTimer.Start(SETUP_CANCEL_DELAY);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
PassifyHandler::PassifyHandler(Algorithm* a): a(a), IsActive(false){}

void PassifyHandler::ProcessStart(){
	setBit(PASSIFY_PORT->DATAOUT, PassifyPins::pin1);
	a->MC.selfTimer.Start(PASSIFY_DELAY);
	IsActive = true;
}

void PassifyHandler::ProcessTI(){
	clearBit(PASSIFY_PORT->DATAOUT, PassifyPins::pin1);
	a->MC.selfTimer.Off();
	IsActive = false;
	
	a->MC.dbgUART.Synchronize(ACTION);
	a->MC.dbgUART.Push((uint8_t)Actions::passify);
	a->MC.dbgUART.Flush();
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
TriggerHandler::TriggerHandler(Algorithm* a): a(a), IsActive(false){}

void TriggerHandler::ProcessStart(){
	if(a->SOC.Setup.IsReady){
		setBit(TRIGGER_PORT->DATAOUT, TriggerPins::pin1);
		a->MC.selfTimer.Start(TRIGGER_DELAY);
		IsActive = true;
	}
	else if(!a->SOC.Setup.IsActive){
		a->SOC.Setup.ProcessStart();
	}
}

void TriggerHandler::ProcessTI(){
	clearBit(TRIGGER_PORT->DATAOUT, TriggerPins::pin1);
	a->MC.selfTimer.Off();
	IsActive = false;
	
	a->MC.dbgUART.Synchronize(ACTION);
	a->MC.dbgUART.Push((uint8_t)Actions::trigger);
	a->MC.dbgUART.Flush();
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
SelfOperation::SelfOperation(Algorithm* a): a(a), Hcct(a), Setup(a), Trigger(a), Passify(a){}

void SelfOperation::TrySetupStart(){
	if(isInDZ() && !Setup.IsActive){
		Setup.ProcessStart();
	}
}

void SelfOperation::TrySetupCancel(){
	if( (!isInDZ()) && Setup.IsActive && !Setup.IsCansel && !Hcct.ConnectionLost ){
		Setup.Cancel();
		//Отмена только в этом случае, чтобы Setup.ProcessStart() не вызывался все время,
		//пока IsInDZ() == true
	}}

void SelfOperation::HandleConnectionLoss(){
	if(!a->MC.dbgUART.JustOnce){
		a->MC.dbgUART.JustOnce = true;
		a->MC.dbgUART.Synchronize(ACTION);
		a->MC.dbgUART.Push((uint8_t)Actions::connectionLost);
		a->MC.dbgUART.Flush();
	}
	if(isInSD() && !Passify.IsActive){
		Passify.ProcessStart();
	}
	else if(isInDZ() && !Trigger.IsActive){
		Trigger.ProcessStart();
	}
	if(Trigger.IsActive || Passify.IsActive){
		Hcct.IsHandled = true;
		a->MC.dbgUART.JustOnce = false;
	}
}

inline bool SelfOperation::isOnT(){
	return (a->ZC.Zone == Zones::T)? true : false;
}
inline bool SelfOperation::isInSD(){
	return (a->ZC.Zone <= Zones::SD4 && a->ZC.Zone >= Zones::SD0)? true : false;
}
inline bool SelfOperation::isInDZ(){
	return (a->ZC.Zone >= Zones::SD1_DZ && a->ZC.Zone <= Zones::DZ)? true : false;
}
inline bool SelfOperation::isInSD_DZ(){
	return (a->ZC.Zone >= Zones::SD1_DZ && a->ZC.Zone != Zones::DZ)? true : false;
}




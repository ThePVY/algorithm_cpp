#pragma once
#include "top.h"

class Algorithm;

/*
Communication Control Timer включается при выходе из БД=0 и работает до (?)
*/
class HandlerCCT{
private:
	Algorithm* a;
	uint8_t failCnt;
public:
	bool IsActive;
	bool ConnectionLost;
	bool IsHandled;
	
	HandlerCCT(Algorithm* a);
	
	void ProcessStart();
	void ProcessTI();
	
	inline void ResetFailCnt(){ failCnt = 0; }
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
class SetupHandler{
private:
	Algorithm* a;
	SetupPins settedPin;
public:
	bool IsActive;
	bool IsReady;
	bool IsCansel;
	
	SetupHandler(Algorithm* a);
	
	void ProcessStart();
	void ProcessTI();
	inline void Cancel();
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
class PassifyHandler{
private:
	Algorithm* a;
public:
	bool IsActive;
	
	PassifyHandler(Algorithm* a);
	
	void ProcessStart();
	void ProcessTI();
};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
class TriggerHandler{
private:
	Algorithm* a;
public:
	bool IsActive;
	
	TriggerHandler(Algorithm* a);
	
	void ProcessStart();
	void ProcessTI();

};
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
class SelfOperation{
private:
	Algorithm* a;
public:
	HandlerCCT Hcct;
	SetupHandler Setup;
	TriggerHandler Trigger;
	PassifyHandler Passify;
public:
	SelfOperation(Algorithm* a);
	
	void TrySetupStart();
	void TrySetupCancel();
	void HandleConnectionLoss();
	
private:
	inline bool isOnT();
	inline bool isInDZ();
	inline bool isInSD_DZ();
	inline bool isInSD();
};
	




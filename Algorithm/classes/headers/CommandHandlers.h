#pragma once
#include "top.h"

class Handler1_x{
protected:
	Algorithm* a;
	Timer* cmdTimer;
	Handler1_x* otherHandler;
	Pins1x pin1, pin2;
	bool pauseBit;
	uint16_t code;
	uint8_t codeIndex;
	Subaddrs subaddr;
public:
	uint32_t Time;
	bool IsActive;
	
	Handler1_x(Algorithm* a, Timer* cmdTimer);
	void ProcessCmd();
	void ProcessTI();
	
	inline Pins1x Pin1(){ return pin1; }
	inline Pins1x Pin2(){ return pin2; }
	
	inline void OtherHandler(Handler1_x* oh){ otherHandler = oh; }
	inline Handler1_x* OtherHandler(){ return otherHandler; }
	
protected:
	virtual bool processStart() = 0;
	virtual void processCS() = 0;
	virtual void processTimerOff() = 0;
	
	inline bool pinsConflicting();
	inline bool isEndOfCS(){ return (codeIndex == 12)? true : false; }
	void configureTime();
	void configurePins();
};
/*----------------------------------------------------------------------------*/
class Handler1_12 : public Handler1_x{
public:
	Handler1_12(Algorithm* a, Timer* ct);
	
private:
	virtual bool processStart();
	virtual void processCS();
	virtual void processTimerOff();
};
/*----------------------------------------------------------------------------*/
class Handler1_34 : public Handler1_x{
public:
	Handler1_34(Algorithm* a, Timer* ct);

private:
	virtual bool processStart();
	virtual void processCS();
	virtual void processTimerOff();
};

/*----------------------------------------------------------------------------*/
//Продумать, когда сбрасывать lastSettedPin до Pins4x::none !!!
class Handler4x{
private:
	Algorithm* a;
	Pins4x lastSettedPin;
	Pins4x pin1, pin2, pin3, pin4;
	bool pin1IsSet, pin2IsSet, pin3IsSet, pin4IsSet; 
	uint32_t delay12, delay23, delay34;
	Subaddrs subaddr;
	uint8_t sdNum, cmdNum;
public:
	uint32_t Time;
	bool IsActive;
	
	Handler4x(Algorithm* a);
	
	void ProcessCmd(Subaddrs subaddr);
	void ProcessTI();
private:
	Pins4x setPin(uint8_t pin);
	void configureTime();
	void configurePins();
	inline void matchCmd();
	inline void matchSD();
};










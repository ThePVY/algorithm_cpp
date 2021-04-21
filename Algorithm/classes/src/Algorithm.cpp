#include "top.h"

Algorithm::Algorithm(): 
Extractor(this), 
ZC(this), 
H11(this, &MC.cmdTimer1),
H12(this, &MC.cmdTimer1), 
H13(this, &MC.cmdTimer1),
H14(this, &MC.cmdTimer2),
H4x(this),
SOC(this){
	H11.OtherHandler(&H12);
	H12.OtherHandler(&H11);
	H13.OtherHandler(&H14);
	H14.OtherHandler(&H13); 
}

void Algorithm::ProcessIvents(){
	if(global.IsMI){
		processCommunication();
		processPackage();
		global.IsMI = false;
	}
	if(global.IsTI){
		processTimer();
		global.IsTI = false;
	}
	if(SOC.Hcct.ConnectionLost && !SOC.Hcct.IsHandled){
		SOC.HandleConnectionLoss();
	}
	processSetup();
}

inline void Algorithm::processCommunication(){
	if(SOC.Hcct.ConnectionLost){
		SOC.Hcct.ConnectionLost = false;
		SOC.Hcct.IsHandled = false;
		MC.dbgUART.Synchronize(ACTION);
		MC.dbgUART.Push((uint8_t)Actions::connectionRestored);
		MC.dbgUART.Flush();
	}
	SOC.Hcct.ResetFailCnt();
}

inline void Algorithm::processSetup(){
	SOC.TrySetupStart();
	SOC.TrySetupCancel();
}

void Algorithm::processPackage(){
	Subaddrs subaddr = global.GetSubaddr();
	Extractor.ExtractData(subaddr);
	ZC.UpdateZone();
	processCommand(subaddr);
}

void Algorithm::processCommand(Subaddrs subaddr){
	switch(subaddr){
	case Subaddrs::c11:
		H11.ProcessCmd();
		break;
	case Subaddrs::c12:
		H12.ProcessCmd();
		break;
	case Subaddrs::c13:
		H13.ProcessCmd();
		break;
	case Subaddrs::c14:
		H14.ProcessCmd();
		break;
	case Subaddrs::c41:
	case Subaddrs::c42:
	case Subaddrs::c43:
	case Subaddrs::c44:
		H4x.ProcessCmd(subaddr);
		break;
	case Subaddrs::c7:
		SOC.Trigger.ProcessStart();
		break;
	case Subaddrs::c8:
		SOC.Passify.ProcessStart();
		break;
	}
}

void Algorithm::processTimer(){
	if(SOC.Hcct.IsActive && global.CommTI){
		SOC.Hcct.ProcessTI();
		global.CommTI = false;
	}
	if(H11.IsActive && global.CmdTI1){
		H11.ProcessTI();
		global.CmdTI1 = false;
	}
	if(H12.IsActive && global.CmdTI1){
		H12.ProcessTI();
		global.CmdTI1 = false;
	}
	if(H13.IsActive && global.CmdTI1){
		H13.ProcessTI();
		global.CmdTI1 = false;
	}
	if(H14.IsActive && global.CmdTI2){
		H14.ProcessTI();
		global.CmdTI2 = false;
	}
	if(H4x.IsActive && global.CmdTI1){
		H4x.ProcessTI();
		global.CmdTI1 = false;
	}
	if((SOC.Setup.IsActive && !SOC.Setup.IsReady || SOC.Setup.IsCansel) && global.SelfTI){
		SOC.Setup.ProcessTI();
		global.SelfTI = false;
	}
	else if(SOC.Passify.IsActive && global.SelfTI){
		SOC.Passify.ProcessTI();
		global.SelfTI = false;
	}
	else if(SOC.Trigger.IsActive){
		SOC.Trigger.ProcessTI();
		global.SelfTI = false;
	}
}














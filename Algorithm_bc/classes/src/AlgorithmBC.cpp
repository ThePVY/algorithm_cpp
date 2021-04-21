#include "top.h"

AlgorithmBC::AlgorithmBC(): MovCtrl(this), PackCtrl(this), CommCtrl(&MC.commTimer)
{
	StartTask.Hmin = 50;
	StartTask.Hmax = 30000;
	StartTask.Vmin = 300;
	StartTask.Vxmax = 900;
	StartTask.Vymax = 900;
	StartTask.Vzmax = 300;
	StartTask.Ntp = 10;
	StartTask.Nsd = 2;
	StartTask.Ssd_e[0] = DIST_SD_END;
	nullify(StartTask.Ssd_e, 1, 3);
}

void AlgorithmBC::StartMovement(){ 
	MovCtrl.StartMovement();
	CommCtrl.StartCountdown();
}

void AlgorithmBC::ProcessIvents(){
	if(CommCtrl.IsCommTime){
		PackCtrl.ProcessCommunication(MovCtrl.Distance(), MovCtrl.CurrentSection());
		BL2_INV();
		CommCtrl.IsCommTime = false;
	}
	if(global.IsTI){
		processTI();
		global.IsTI = false;
	}
	if(global.IsMI){
		global.IsMI = false;
	}
}

inline void AlgorithmBC::processTI(){
	if(global.MovTI){
		BL1_INV();
		MovCtrl.ProcessTI();//имитация движения, смены УТ и обновление пакетов данных
		global.MovTI = false;
	}
	if(global.CommTI){
		CommCtrl.ProcessTI();//выставление флага о необходимости ИО IsCommTime
		global.CommTI = false;
	}
}

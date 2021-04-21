#include "top.h"

PackageController::PackageController(AlgorithmBC* a): a(a), 
packNX(a), packFDT(a), packSDT(a), packMP(a){
	cmd11_IsSent = false;
	cmd12_IsSent = false;
	cmd13_IsSent = false;
	cmd14_IsSent = false;
	cmd4x_IsSent = false;
	packCounter = 0;
}

void PackageController::SendPackage(Subaddrs subaddr){
	switch(subaddr){
	case Subaddrs::c11:
		packNX.Send(Subaddrs::c11, Command1x::Form(pins12, 0b00, 0b101010101010).all);
		packNX.SendDI(Subaddrs::c11);
		cmd11_IsSent = true;
		break;
	case Subaddrs::c12:
		packNX.Send(Subaddrs::c12, Command1x::Form(pins14, 0b00, 0b010101010101).all);
		packNX.SendDI(Subaddrs::c12);
		cmd12_IsSent = true;
		break;
	case Subaddrs::c13:
		packNX.Send(Subaddrs::c13, Command1x::Form(pins12, 0b00, 0b101010101010).all);
		packNX.SendDI(Subaddrs::c13);
		cmd13_IsSent = true;
		break;
	case Subaddrs::c14:
		packNX.Send(Subaddrs::c14, Command1x::Form(pins14, 0b00, 0b010101010101).all);
		packNX.SendDI(Subaddrs::c14);
		cmd14_IsSent = true;
		break;
	case Subaddrs::c41:
		packNX.Send(Subaddrs::c41, Command4x::Form(pin1, 0, 0, 0, 0, 0).all);
		packNX.SendDI(Subaddrs::c41);
		cmd4x_IsSent = true;
		break;
	case Subaddrs::c42:
		packNX.Send(Subaddrs::c42, Command4x::Form(pin1, pin2, 0, d12, 0, 0).all);
		packNX.SendDI(Subaddrs::c42);
		cmd4x_IsSent = true;
		break;
	case Subaddrs::c43:
		packNX.Send(Subaddrs::c43, Command4x::Form(pin1, pin2, pin3, d12, d23, 0).all);
		packNX.SendDI(Subaddrs::c43);
		cmd4x_IsSent = true;
		break;
	case Subaddrs::c44:
		packNX.Send(Subaddrs::c44, Command4x::Form(pin1, pin2, pin3, d12, d23, d34).all);
		packNX.SendDI(Subaddrs::c44);
		cmd4x_IsSent = true;
		break;
	case Subaddrs::MP:
		packMP.Send(Subaddrs::MP);
		packMP.SendDI(Subaddrs::MP);
		break;
	case Subaddrs::FDT:
		packFDT.Send(Subaddrs::FDT);
		packFDT.SendDI(Subaddrs::FDT);
		cmd4x_IsSent = false;
		a->MovCtrl.IsNextSection = false;
		packCounter = 0;
		break;
	case Subaddrs::SDT:
		packSDT.Send(Subaddrs::SDT);
		packSDT.SendDI(Subaddrs::SDT);
		break;
	case Subaddrs::c7:
		
		break;
	case Subaddrs::c8:
		
		break;
	}
	packCounter++;
}

void PackageController::ProcessCommunication(int distance, TSections section){
	switch(section){
	case TSections::TS0:
		processTS0(distance);
		break;
	case TSections::TS1:
		processTS1_3(distance, Subaddrs::c42);
		break;
	case TSections::TS2:
		processTS1_3(distance, Subaddrs::c43);
		break;
	case TSections::TS3:
		processTS1_3(distance, Subaddrs::c44);
		break;
	case TSections::TS4:
	case TSections::TS5:
		processTS4_5();
		break;
	case TSections::TS6:
		processTS6();
		break;
	case TSections::TS7:
		processTS4_5();
		break;
	}
}

void PackageController::processTS0(int distance){
	if(a->MovCtrl.IsNextSection){
		a->MovCtrl.updateFDT();
		SendPackage(Subaddrs::FDT);
	}
	//else if(packCounter == 4){
	//	SendPackage(Subaddrs::c41);
	//}
	else if(distance <= DIST_TO_V11 && !cmd11_IsSent){
		SendPackage(Subaddrs::c11);
	}
	else if(distance <= DIST_TO_V12 && !cmd12_IsSent){
		SendPackage(Subaddrs::c12);
	}
	else if(distance <= DIST_TO_V13 && !cmd13_IsSent){
		SendPackage(Subaddrs::c13);
	}
	else if(distance <= DIST_TO_V14 && !cmd14_IsSent){
		SendPackage(Subaddrs::c14);
	}
	else if(distance <= DIST_TO_V4X && !cmd4x_IsSent){
		SendPackage(Subaddrs::c41);
	}
	else{
		SendPackage(Subaddrs::MP);
	}
}

void PackageController::processTS1_3(int distance, Subaddrs c4x){
	
	if(a->MovCtrl.IsNextSection){
		SendPackage(Subaddrs::FDT);
	}
	else if(distance <= DIST_TO_V4X && !cmd4x_IsSent){
		SendPackage(c4x);
	}
	else if(packCounter <= 2 || packCounter >= 8){
		SendPackage(Subaddrs::MP);
	}
	else{
		packCounter++;
	}
	
	/*
	if(a->MovCtrl.IsNextSection){
		SendPackage(Subaddrs::FDT);
	}
	else if(packCounter == 4){
		SendPackage(Subaddrs::c42);
	}
	else if(packCounter == 8){
		SendPackage(Subaddrs::c43);
	}
	else if(packCounter == 12){
		SendPackage(Subaddrs::c44);
	}
	else{
		SendPackage(Subaddrs::MP);
	}
	*/
}

void PackageController::processTS4_5(){
	if(a->MovCtrl.IsNextSection){
		SendPackage(Subaddrs::FDT);
		a->MovCtrl.IsNextSection = false;
	}
	else{
		SendPackage(Subaddrs::MP);
	}
}

void PackageController::processTS6(){
	if(a->MovCtrl.IsNextSection){
		SendPackage(Subaddrs::FDT);
		a->MovCtrl.IsNextSection = false;
	}
	else if(packCounter < 6 || packCounter > 20){
		SendPackage(Subaddrs::MP);
	}
	else{
		packCounter++;
	}
}









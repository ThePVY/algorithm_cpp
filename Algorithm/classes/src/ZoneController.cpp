#include "top.h"

/*
	Зоны БД меняются последовательно и без промежутков между друг другом. Последней БД
является БД = 4. 
	indexSD_overall характеризует текущий номер БД, он увеличивается на 1 после прохождения
очередной зоны БД.
	indexSD_inS характеризует текущий номер БД на УТ, то есть может быть так, что indexSD_overall = 4,
а indexSD_inS = 0 -> это значит, что уже пройдены БД = 0, 1, 2, 3 и сейчас БД = 4, однако на текущем
УТ зона БД всего одна, что и дает ей номер 0
	Также indexSD_overall и indexDZ используются для извлечения данных из массивов структур InnerVariables. 
*/

ZoneController::ZoneController(Algorithm* a): a(a){
	Zone = Zones::SD0;
	DZType = DZTypes::type1;
	indexSD_overall = 0;
	indexSD_inS = 0;
	indexDZ = 0;
	SectionCounter = 0;
}

/*
	Если ты в БД, то ты можешь быть и в ОЗ,
	если не в БД, то ты можешь быть или в ОЗ или просто на траектории Т.
*/
void ZoneController::UpdateZone(){
	updateSD();
	updateDZ();
	if(indexSD_overall <= (uint8_t)SafeDistances::SD4){
		if(isInDZ()){
			switch(indexSD_overall){
			case 1:
				Zone = Zones::SD1_DZ;
				break;
			case 2:
				Zone = Zones::SD2_DZ;
				break;
			case 3:
				Zone = Zones::SD3_DZ;
				break;
			case 4:
				Zone = Zones::SD4_DZ;
				break;
			default:
				Zone = Zones::none;
				break;
			}
		}else{
			switch(indexSD_overall){
			case 0:
				Zone = Zones::SD0;
				break;
			case 1:
				Zone = Zones::SD1;
				a->SOC.Hcct.ProcessStart();//Как только вышел из SD0 - запустить таймер
				break;
			case 2:
				Zone = Zones::SD2;
				break;
			case 3:
				Zone = Zones::SD3;
				break;
			case 4:
				Zone = Zones::SD4;
				break;
			default:
				Zone = Zones::none;
				break;
			}
		}
	}else{
		if(isInDZ()){
			Zone = Zones::DZ;
		}else{
			Zone = Zones::T;
		}
	}
	a->MC.dbgUART.Synchronize(ACTION);
	a->MC.dbgUART.Push((uint8_t)Actions::updateZone);
	a->MC.dbgUART.Push((uint8_t)Zone);
	a->MC.dbgUART.Flush();
}

/*-->Если конец БД лежит на другом УТ, то a->FlightTask.Ssd_e[indexSD_overall] = 0,
и соответственно a->MovParam.s будет всегда больше 0, что означает что мы не 
перейдем на другой БД.*/
inline void ZoneController::updateSD(){
	if(crossedSD()){
		//Значит мы пересекли конец БД
		indexSD_overall++;
		indexSD_inS++;
	}
}

inline void ZoneController::updateDZ(){
	if(a->MovParam.s < a->FlightTask.Sdz_e[indexDZ]){
		//Значит мы пересекли конец ОЗ
		indexDZ++;
	}
}

inline bool ZoneController::isInDZ(){
	return (a->MovParam.s < a->FlightTask.Sdz_s[indexDZ] &&
			a->MovParam.s > a->FlightTask.Sdz_e[indexDZ])? true : false;
}

inline bool ZoneController::crossedSD(){
	return (a->MovParam.s < a->FlightTask.Ssd_e[indexSD_inS] ||
			(!SectionCounter && a->MovParam.s < a->StartTask.Ssd_e[indexSD_inS]))? true : false;
}



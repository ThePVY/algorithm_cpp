#include "top.h"

/*
	���� �� �������� ��������������� � ��� ����������� ����� ���� ������. ��������� ��
�������� �� = 4. 
	indexSD_overall ������������� ������� ����� ��, �� ������������� �� 1 ����� �����������
��������� ���� ��.
	indexSD_inS ������������� ������� ����� �� �� ��, �� ���� ����� ���� ���, ��� indexSD_overall = 4,
� indexSD_inS = 0 -> ��� ������, ��� ��� �������� �� = 0, 1, 2, 3 � ������ �� = 4, ������ �� �������
�� ���� �� ����� ����, ��� � ���� �� ����� 0
	����� indexSD_overall � indexDZ ������������ ��� ���������� ������ �� �������� �������� InnerVariables. 
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
	���� �� � ��, �� �� ������ ���� � � ��,
	���� �� � ��, �� �� ������ ���� ��� � �� ��� ������ �� ���������� �.
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
				a->SOC.Hcct.ProcessStart();//��� ������ ����� �� SD0 - ��������� ������
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

/*-->���� ����� �� ����� �� ������ ��, �� a->FlightTask.Ssd_e[indexSD_overall] = 0,
� �������������� a->MovParam.s ����� ������ ������ 0, ��� �������� ��� �� �� 
�������� �� ������ ��.*/
inline void ZoneController::updateSD(){
	if(crossedSD()){
		//������ �� ��������� ����� ��
		indexSD_overall++;
		indexSD_inS++;
	}
}

inline void ZoneController::updateDZ(){
	if(a->MovParam.s < a->FlightTask.Sdz_e[indexDZ]){
		//������ �� ��������� ����� ��
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



#pragma once

#define MAX_NUM_DZ 10;
#define MAX_NUM_SD 4;

constexpr unsigned long long operator "" max(unsigned long long max){ 
	return max; 
}

struct MovementParameters{
  	uint16_t v = 0xFFFF; //текущая скорость
	uint16_t h = 0xFFFF; //текущая высота
	uint16_t s = 0xFFFF; //текущая дальность до ППМ
	uint16_t t = 0xFFFF; //время до ППМ
	uint16_t fm = 0;//режим полета (flight mode)
};

struct StartDutyTask{
	uint16_t Hmin = 0; //минимальная высота полета
	uint16_t Hmax = 0; //максимальная высота полета
	uint16_t Vmin = 0; //минимальная скорость полета
	uint16_t Vxmax = 0; //максимальная продольная скорость полета
	uint16_t Vymax = 0; //максимальная горизонтальная скорость полета
	uint16_t Vzmax = 0; //максимальная вертикальная скорость полета
	uint16_t Ntp = 0; 	//количество ППМ(пункт поворота маршрута - turn point)
	uint16_t Nsd = 0;	//количество зон БД (безопасная дистанция - safe distance)
	uint16_t Ssd_e[4max] = { 0 }; //расстояние между концом БД и концом УТ
};

struct FlightDutyTask{
	uint16_t Ndz = 0;//количество особых зон (dangerous zone)
	//убрал вид особой зоны (dangerous zone type), так как эта инфа не нужна для логики
	uint16_t Sdz_s[10max] = {0}; //расстояние между началом особой зоны и концом участка траектории (УТ)
	uint16_t Sdz_e[10max] = {0}; //расстояние между концом особой зоны и концом участка траектории (УТ)
	
	uint16_t Nsd = 0;//количество БД
	uint16_t Ssd_e[4max] = {0}; //расстояние между концом БД и концом УТ
};


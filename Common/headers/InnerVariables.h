#pragma once

#define MAX_NUM_DZ 10;
#define MAX_NUM_SD 4;

constexpr unsigned long long operator "" max(unsigned long long max){ 
	return max; 
}

struct MovementParameters{
  	uint16_t v = 0xFFFF; //������� ��������
	uint16_t h = 0xFFFF; //������� ������
	uint16_t s = 0xFFFF; //������� ��������� �� ���
	uint16_t t = 0xFFFF; //����� �� ���
	uint16_t fm = 0;//����� ������ (flight mode)
};

struct StartDutyTask{
	uint16_t Hmin = 0; //����������� ������ ������
	uint16_t Hmax = 0; //������������ ������ ������
	uint16_t Vmin = 0; //����������� �������� ������
	uint16_t Vxmax = 0; //������������ ���������� �������� ������
	uint16_t Vymax = 0; //������������ �������������� �������� ������
	uint16_t Vzmax = 0; //������������ ������������ �������� ������
	uint16_t Ntp = 0; 	//���������� ���(����� �������� �������� - turn point)
	uint16_t Nsd = 0;	//���������� ��� �� (���������� ��������� - safe distance)
	uint16_t Ssd_e[4max] = { 0 }; //���������� ����� ������ �� � ������ ��
};

struct FlightDutyTask{
	uint16_t Ndz = 0;//���������� ������ ��� (dangerous zone)
	//����� ��� ������ ���� (dangerous zone type), ��� ��� ��� ���� �� ����� ��� ������
	uint16_t Sdz_s[10max] = {0}; //���������� ����� ������� ������ ���� � ������ ������� ���������� (��)
	uint16_t Sdz_e[10max] = {0}; //���������� ����� ������ ������ ���� � ������ ������� ���������� (��)
	
	uint16_t Nsd = 0;//���������� ��
	uint16_t Ssd_e[4max] = {0}; //���������� ����� ������ �� � ������ ��
};


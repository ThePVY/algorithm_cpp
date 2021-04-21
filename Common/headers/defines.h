#pragma once

#include "top.h"

// MKPD
#define MKPD				MKPD1
#define MKPD_PORT			GPIO_E
#define UART_PORT			GPIO_E
#define SYS_FREQ 			80			///< Системная частота для использования в библиотечных функциях для MKPD
#define XTAL				80000000
#define EP1_addr 			1
#define TT_WRITE			1
#define TT_SEND_DATA		2
#define TRANSACTION_TIMEOUT	1000
#define MANAGE_CODE			0
#define SUBADDR_SHIFT		64
#define MAX_PACK_LENGTH		32
#define SUBADDR_NUM			13
#define WORDS_NUM			32

#define COMMUNICATION_TIMEOUT 1000

#define PACKAGE		0xAC
#define ACTION		0xAD

/*-->Определение задержек*/
#define SETUP_DELAY 50
#define SETUP_CANCEL_DELAY 50
#define PASSIFY_DELAY 500
#define TRIGGER_DELAY 500


/*->Вектора прерываний<-*/
#define MKPD1_INT_VECT 20
#define MKPD2_INT_VECT 21
#define UART2_INT_VECT 3
#define TIM1_INT_VEC 0
#define TIM2_INT_VEC 4
#define TIM3_INT_VEC 5
#define TIM4_INT_VEC 6


//***************Command PINS****************
#define V1x_PORT	GPIO_G
#define V4x_PORT	GPIO_G
#define SETUP_PORT	GPIO_F
#define PASSIFY_PORT	GPIO_F
#define TRIGGER_PORT	GPIO_F

    //***********************************
    // BL
#define BL_PORT 		 	GPIO_H
#define BL1_PIN 			(1<<0)
#define BL2_PIN 			(1<<1)
#define BL3_PIN 			(1<<2)
#define BL4_PIN 			(1<<3)
#define BL_PINS			 	(BL1_PIN | BL2_PIN | BL3_PIN | BL4_PIN)

#define BL1_SET()			BL_PORT->DATAOUT |= BL1_PIN
#define BL2_SET()			BL_PORT->DATAOUT |= BL2_PIN
#define BL3_SET()			BL_PORT->DATAOUT |= BL3_PIN
#define BL4_SET()			BL_PORT->DATAOUT |= BL4_PIN
#define BL1_CLEAR()		 	BL_PORT->DATAOUT &= ~BL1_PIN
#define BL2_CLEAR()		 	BL_PORT->DATAOUT &= ~BL2_PIN
#define BL3_CLEAR()		 	BL_PORT->DATAOUT &= ~BL3_PIN
#define BL4_CLEAR()		 	BL_PORT->DATAOUT &= ~BL4_PIN
#define BL1_INV()			BL_PORT->DATAOUT ^= BL1_PIN
#define BL2_INV()			BL_PORT->DATAOUT ^= BL2_PIN
#define BL3_INV()			BL_PORT->DATAOUT ^= BL3_PIN
#define BL4_INV()			BL_PORT->DATAOUT ^= BL4_PIN

/*------------------------ALGORITHM BC-----------------------------*/
#define DISTANCE_STEP 	1000
#define SECTION_LENGTH 	DISTANCE_STEP * 40
#define DIST_TIME_STEP	1000

#define DIST_SD_END		DISTANCE_STEP * 15
#define DIST_DZ_START	DISTANCE_STEP * 10
#define DIST_DZ_END		DISTANCE_STEP * 4

/*----*/
#define DIST_TO_V11		DISTANCE_STEP * 34
#define DIST_TO_V12		(DIST_TO_V11 - DISTANCE_STEP * 4)
#define DIST_TO_V13		(DIST_TO_V12 - DISTANCE_STEP * 4)
#define DIST_TO_V14		(DIST_TO_V13 - DISTANCE_STEP * 4)

#define DIST_TO_V4X		(DIST_SD_END - DISTANCE_STEP * 3)

#define COMM_TIME_STEP	DIST_TIME_STEP

#define	MKPD_BUFF_LENGTH		64
#define CMD_LENGTH				1
#define MP_LENGTH				5
#define	FDT_LENGTH				26
#define SDT_LENGTH				12
#define CMD_PACKAGE_LENGTH 		(CMD_LENGTH + MP_LENGTH)
#define MP_PACKAGE_LENGTH 		MP_LENGTH
#define FDT_PACKAGE_LENGTH 		(FDT_LENGTH + MP_LENGTH)
#define SDT_PACKAGE_LENGTH 		SDT_LENGTH
/*-------------------------------------------------------------------*/


/*-->Введение пользовательского литерала subaddr*/
constexpr uint16_t operator "" subaddr(unsigned long long subaddr){ 
	return subaddr * 64; 
}

enum class Subaddrs{
	c11 = 1,
	c12 = 2,
	c13 = 3,
	c14 = 4,
	c41 = 5,
	c42 = 6,
	c43 = 7,
	c44 = 8,
	c7 = 9,
	c8 = 0xA,
	MP = 0xB,
	FDT = 0xC,
	SDT = 0xD,
	none = 0xFF
};

enum class Actions{
	none,
	test = 0xD0,
	updateZone = 0xB0,
	handleCmd1_12 = 0xB1,
	handleCmd1_34_start = 0xB2,
	handleCmd1_34_end = 0xB3,
	handleCmd4x = 0xB4,
	setup = 0xB5,
	canselSetup = 0xB6,
	connectionLost = 0xB7,
	connectionRestored = 0xB8,
	passify = 0xB9,
	trigger = 0xBA,
	pins1xConflict = 0xBB
};

enum class ADVolumes{
	none = 0xFF,
	test = 0,
	updateZone = 1,
	handleCmd1_12 = 28,
	handleCmd1_34_start = 4,
	handleCmd1_34_end = 0,
	handleCmd4x = 6,
	setup = 0,
	canselSetup = 0,
	connectionLost = 0,
	connectionRestored = 0,
	passify = 0,
	trigger = 0,
	pins1xConflict = 4
};

enum class Packages{
	none,
	package1x,
	package4x,
	packageMP,
	packageFDT,
	packageSDT
};

/*-->Отражает вложенность зон*/
enum class Zones{
	T = 0,
	SD0 = 1,
	SD1 = 2,
	SD2 = 3,
	SD3 = 4,
	SD4 = 5,
	SD1_DZ = 6,
	SD2_DZ = 7,
	SD3_DZ = 8,
	SD4_DZ = 9,
	DZ = 0xA,
	none = 0x66
};
enum class SafeDistances{
	SD0, SD1, SD2, SD3, SD4, OutOfSD
};

enum class DZTypes{
	type1 = 1, type2, type3
};

/*-->Определения задержек для формирования команд В4x*/
enum Delays{
	d12 = 2,
	d23 = 2,
	d34 = 2
};

/*-->Определения пинов для КШ (то есть для формирования команд)*/
enum Pins{
	pin1 = 0,
	pin2 = 1,
	pin3 = 2,
	pin4 = 3,
	pins12 = 0,
	pins23 = 1,
	pins34 = 2,
	pins14 = 3
};

enum class TSections{
	TS0, TS1, TS2, TS3, TS4, TS5, TS6, TS7, TS8, TS9,
};

enum class Pins1x{
	none = 0xFF,
	pin1 = 4,
	pin2 = 5,
	pin3 = 6,
	pin4 = 7
};

enum class Time1x{
	t0 = 50/2,
	t1 = 100/2,
	t2 = 250/2,
	t3 = 500/2
};

enum class Pins4x{
	none = 0xFF,
	pin1 = 4,
	pin2 = 5,
	pin3 = 6,
	pin4 = 7
};

enum class SetupPins{
	none = 0xFF,
	pin1 = 9,
	pin2 = 10,
	pin3 = 11,
	cancelPin = 12
};

enum class PassifyPins{
	pin1 = 14
};

enum class TriggerPins{
	pin1 = 13
};

enum class PinLevel{
	High = 1,
	Low = 0
};

enum class ErrorCode{
	none, error
};


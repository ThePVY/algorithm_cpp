#pragma once

#include "chip_5023BC016.h"
#include "system.h"
#include "types.h"
#include "gpio.h"
#include "uart.h"
#include "mkpd.h"
#include "timer.h"
#include "stdint.h"
#include <cassert>

#include "defines.h"
#include "Commands.h"
#include "InnerVariables.h"
#include "mkpd_ep.h"
#include "uartdrv.h"
#include "timerdrv.h"
#include "Global.h"
#include "Hardware.h"
#include "DataExtractor.h"
#include "ZoneController.h"
#include "CommandHandlers.h"
#include "SOHandlers.h"
#include "Algorithm.h"



/*----------------------------------GLOBAL------------------------------------*/
extern Global global;
/*----------------------------------------------------------------------------*/

template <typename T, typename T1>
inline void setBit(T &portDataRegister, T1 bit){
	portDataRegister |= static_cast<T>(static_cast<T>(1)<<static_cast<T>(bit));
}

template <typename T, typename T1>
inline void clearBit(T &portDataRegister, T1 bit){
	portDataRegister &= ~static_cast<T>(static_cast<T>(1)<<static_cast<T>(bit));
}

template <typename T, typename T1>
inline void toggleBit(T &portDataRegister, T1 bit){
	portDataRegister ^= static_cast<T>(static_cast<T>(1)<<static_cast<T>(bit));
}

template <typename T, typename T1>
inline void nullify(T& array, T1 ind, T1 num){
	for(int i = ind; i < ind + num; i++){
		array[i] = 0;
	}
}

































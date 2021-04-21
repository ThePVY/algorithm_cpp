/*!\file
 * \brief Этот файл содержит функции, необходимые для взаимодействия с аппаратным модулем UART.
 *
 * Copyright(C) НПП Цифровые решения, 2018
 * Copyright(C) Команда разработчиков НПП Цифровые решения
 * Все права защищены.
 *
 * Программное обеспечение, описанное в этом файле, предназначено только для 
 * демонстрационных целей, и предоставляет программистам информацию о продукции 
 * организации "Цифровые решения". Это программное обеспечение поставляется "КАК ЕСТЬ" 
 * без каких-либо гарантий, "Цифровые решения" отказываются от любых гарантий, 
 * фактических или подразумеваемых, включая все подразумеваемые гарантии товарной пригодности, 
 * пригодности для конкретной цели и сохранения прав интеллектуальной собственности. 
 * Органицация "Цифровые решения" не несет никакой ответственности за использование 
 * программного обеспечения, не предоставляет лицензий или прав на патент, авторское право, 
 * или любые другие права интеллектуальной собственности, на какие-либо продукты. 
 * Организация "Цифровые решения" оставляет за собой право вносить изменения в программное 
 * обеспечение без уведомления. Организация "Цифровые решения" также не дает никаких 
 * заверений или гарантий, что это программное приложение подойдет для использования 
 * без дальнейшего тестирования или модификаций.
 *
 * Разрешение на использование, копирование, изменение и распространение этого программного 
 * обеспечения и документации предоставляется согласно условиям "Цифровых решений" и 
 * соответствующих авторских прав своей лицензии без оплаты, при условии, 
 * что это программное обеспечение используется совместно с микроконтроллерами организации
 * "Цифровые решения". Эти права должны распространяться во всех копиях этого кода.
 */

#include <system.h>
#include "dma.h"
#include "chip_5023BC016.h"
#include "uart.h"


/*****************************************************************************
 * Частные функции
 ****************************************************************************/

/** Возвращает номер модуля для использования в функциях включения/выключения тактового сигнала и сгнала сброса */
static CTRL_T UART_GetCtrlNum(UART_T *pUART)
{
    CTRL_T CtrlUART;
    if (pUART == UART1) 
    {
        CtrlUART = UART_1_CTRL_NUM;
    }
    if (pUART == UART2) 
    {
        CtrlUART = UART_2_CTRL_NUM;
    }
     if (pUART == UART3) 
    {
        CtrlUART = UART_3_CTRL_NUM;
    }
     if (pUART == UART4) 
    {
        CtrlUART = UART_4_CTRL_NUM;
    }
     if (pUART == UART5) 
    {
        CtrlUART = UART_5_CTRL_NUM;
    }
     if (pUART == UART6) 
    {
        CtrlUART = UART_6_CTRL_NUM;
    }
    return CtrlUART;
}

/*****************************************************************************
 * Общие функции
 ****************************************************************************/

/**
 * @brief Сброс флагов прерываний
 * @param pUART: Указатель на структуру с регистрами UART
 * @param IntClear: Тип прерывания для сброса, принимает следующие значения:
 *						- UART_ICR_RXIC 
 *						- UART_ICR_TXIC
 *						- UART_ICR_RTIC
 *						- UART_ICR_FEIC
 *                                              - UART_ICR_PEIC  
 *                                              - UART_ICR_BEIC  
 *                                              - UART_ICR_OEIC  
 *                                              - UART_ICR_BITMASK        
*/
 void UART_ClearIntPending(UART_T *pUART, UART_INTCLEAR_T IntClear)
{
    pUART->ICR = IntClear;
}

/* Инициализация UART */
void UART_Init(UART_T *pUART)
{
    PWR_CLK_Enable(UART_GetCtrlNum(pUART)); 
    CLK_INIT_PAUSE;

    PWR_RST_Disable(UART_GetCtrlNum(pUART));    
    /* Выкючение передатчика */
    UART_Disable(pUART);
    UART_RXDisable(pUART);
    UART_TXDisable(pUART);
    /* Запрещение прерываний */
    UART_IntDisable(pUART, UART_IMSC_BITMASK);
}


/* Деициализация UART */
void UART_DeInit(UART_T *pUART)
{
    /* Запрещение прерываний */
    UART_IntDisable(pUART, UART_IMSC_BITMASK);
    /* Выключение UART */
    UART_RXDisable(pUART);
    UART_TXDisable(pUART);
    UART_Disable(pUART);
    PWR_CLK_Disable(UART_GetCtrlNum(pUART)); CLK_INIT_PAUSE;
    PWR_RST_Enable(UART_GetCtrlNum(pUART));
}

/**
 * @brief Установка порогов прерываний по заполнению буфера приемника/передатчика
 * @param pUART: Указатель на структуру с регистрами UART
 * @param rxfifolimit: Порог прерывания по заполнению буфера приемника
 * @param txfifolimit: Порог прерывания по заполнению буфера передатчика
 */
void UART_SetupFIFOS(UART_T *pUART, UART_IFLS rxfifolimit, UART_IFLS txfifolimit)
{
    pUART->IFLS = (rxfifolimit << 3) | txfifolimit;
}


/**
 * @brief Получение статуса маскированного прерывания
 * @param pUART: Указатель на структуру с регистрами UART
 * @param MaskInt: Тип прерывания, принимает следующие значения:
 *						- UART_MIS_RXMIS
 *						- UART_MIS_TXMIS
 *						- UART_MIS_RTMIS
 *						- UART_MIS_FEMIS
 *                                              - UART_MIS_PEMIS 
 *                                              - UART_MIS_BEMIS 
 *                                              - UART_MIS_OEMIS 
 * @return Статус прерывания, SET or RESET
 */
uint32_t UART_GetIntStatus(UART_T *pUART, UART_MASKINTSTATUS_T MaskInt)
{
	return (pUART->MIS & MaskInt) ? 1 : 0;
}


/**
 * @brief Установка делителя скорости передачи данных
 * @param pUART: Указатель на структуру с регистрами UART
 * @param IBRD: Целая часть делителя скорости передачи данных
 * @param FBRD: Дробная часть делителя скорости передачи данных
 */
 void UART_SetDivisor(UART_T *pUART, uint32_t IBRD, uint32_t FBRD)
{
    pUART->IBRD = UART_IBRD_BAUDDIV_INT(IBRD);
    pUART->FBRD = UART_FBRD_BAUDDIV_FRAC(FBRD);
}

/**
 * @brief Запрещение прерываний по UART'у
 * @param pUART: Указатель на структуру с регистрами UART
 * @param IntMask: Тип прерывания, принимает следующие значения:
                                                - UART_IMSC_RXIM 
                                                - UART_IMSC_TXIM 
                                                - UART_IMSC_RTIM 
                                                - UART_IMSC_FEIM 
                                                - UART_IMSC_PEIM 
                                                - UART_IMSC_BEIM 
                                                - UART_IMSC_OEIM 
                                                - UART_IMSC_BITMASK
 */
 void UART_IntDisable(UART_T *pUART, UART_INTMASK_T IntMask)
{
    pUART->IMSC &= (~IntMask) & UART_IMSC_BITMASK;
}

/**
 * @brief Прием одного байта по UART'у
 * @param pUART: Указатель на структуру с регистрами UART
 * @return Принятый байт
 */
 uint8_t UART_ReadByte(UART_T *pUART)
{
    return (uint8_t) (pUART->DR);
}

/**
 * @brief Разрешение прерываний по UART'у
 * @param pUART: Указатель на структуру с регистрами UART
 * @param IntMask: Тип прерывания, принимает следующие значения:
                                                - UART_IMSC_RXIM 
                                                - UART_IMSC_TXIM 
                                                - UART_IMSC_RTIM 
                                                - UART_IMSC_FEIM 
                                                - UART_IMSC_PEIM 
                                                - UART_IMSC_BEIM 
                                                - UART_IMSC_OEIM 
                                                - UART_IMSC_BITMASK 
 */
 void UART_IntEnable(UART_T *pUART, UART_INTMASK_T IntMask)
{
    pUART->IMSC |= IntMask;
}
     
/**
 * @brief Установка длины слова данных, числа стоповых бит и контроля четности
 * @param pUART: Указатель на структуру с регистрами UART
 * @param config: Установки UART, логическое сложение макросов, определенных для LCR_H, например: (UART_LCR_H_PEN | UART_LCR_H_EPS_EVEN | UART_LCR_H_STP1 | UART_LCR_H_FEN | UART_LCR_H_WLEN8 | UART_LCR_H_SPS_DIS)
 */
 void UART_Config(UART_T *pUART, uint32_t config)
{
    pUART->LCR_H = config;
}


/**
 * @brief Получение текущего статуса UART контроллера
 * @param pUART: Указатель на структуру с регистрами UART
 * @param Stat: Тип статуса, принимает следующие значения:
 *						- UART_FR_BUSY
 *						- UART_FR_RXFE
 *						- UART_FR_TXFF
 *						- UART_FR_RXFF
 *						- UART_FR_TXFE
                                                - UART_FR_RI   
 * @return Статус UART контроллера, SET or RESET

 */
FlagStatus UART_GetStatus(UART_T *pUART, UART_STATUS_T Stat)
{
//    return (pUART->FR & Stat) ? SET : RESET;
      if (pUART->FR & Stat)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
}

/* Передача массива байт по UART'у, без ожидания освобождения FIFO передатчика */
uint32_t UART_Send(UART_T *pUART, const void *data, uint32_t numBytes)
{
    int sent = 0; 
     
     
    uint8_t *p8 = (uint8_t *) data;
    /* Передаем данные пока FIFO передатчика не полон или не закончились данные */
    while ((sent < numBytes) && (!(UART_GetStatus(pUART, UART_FR_TXFF)))) 
    {
        UART_SendByte(pUART, *p8);
	p8++;
        sent++;
    }
    return sent;
}

/**
 * @brief запрещение работы UART
 * @param pUART: Указатель на структуру с регистрами UART
 */
 void UART_Disable(UART_T *pUART)
{
    pUART->CR &= (~UART_CR_UARTEN) & UART_CR_BITMASK;;
}

/**
 * @brief Разрешение работы передатчика
 * @param pUART: Указатель на структуру с регистрами UART
 */
 void UART_TXEnable(UART_T *pUART)
{
    pUART->CR |= UART_CR_TXE;
}

/**
 * @brief запрещение работы передатчика
 * @param pUART: Указатель на структуру с регистрами UART
 */
 void UART_TXDisable(UART_T *pUART)
{
    pUART->CR &= (~UART_CR_TXE) & UART_CR_BITMASK;
}

/**
 * @brief Разрешение работы UART
 * @param pUART: Указатель на структуру с регистрами UART
 */

void UART_Enable(UART_T *pUART)
{
    pUART->CR |= UART_CR_UARTEN;
}  

/**
 * @brief Разрешение работы приемника
 * @param pUART: Указатель на структуру с регистрами UART
 */
 void UART_RXEnable(UART_T *pUART)
{
    pUART->CR |= UART_CR_RXE;
}

/**
 * @brief запрещение работы приемника
 * @param pUART: Указатель на структуру с регистрами UART
 */
 void UART_RXDisable(UART_T *pUART)
{
    pUART->CR &= (~UART_CR_RXE) & UART_CR_BITMASK;;
}

/**
 * @brief Передача одного байта по UART'у
 * @param pUART: Указатель на структуру с регистрами UART
 * @param data: Байт для передачи
 */
 void UART_SendByte(UART_T *pUART, uint8_t data)
{
    pUART->DR = ((uint32_t) data) & UART_DR_MASK_DATA;
  //  pUART->DR = ((uint32_t) data);
}

/* Передача массива байт по UART'у, с ожиданием освобождения FIFO передатчика */
uint32_t UART_SendBlocking(UART_T *pUART, const void *data, uint32_t numBytes)
{
    int pass, sent = 0;
    uint8_t *p8 = (uint8_t *) data;
    while (numBytes > 0) 
    {
        pass = UART_Send(pUART, p8, numBytes);
	numBytes -= pass;
        sent += pass;
	p8 += pass;
    }
    return sent;
}

/* Прием массива байт по UART'у, без ожидания заполнения указанного массива полностью */
uint32_t UART_Read(UART_T *pUART, void *data, uint32_t numBytes)
{
    int readBytes = 0;
    uint8_t *p8 = (uint8_t *) data;
    /* Принимаем данные пока FIFO приемника не пуст или не принято необходимое число данных */
    while ((readBytes < numBytes) && (!(UART_GetStatus(pUART, UART_FR_RXFE)))) 
    {
	*p8 = UART_ReadByte(pUART);
	p8++;
	readBytes++;
    }
    return readBytes;
}

/* Прием массива байт по UART'у, с ожиданием заполнения указанного массива полностью */
uint32_t UART_ReadBlocking(UART_T *pUART, void *data, uint32_t numBytes)
{
    int pass, readBytes = 0;
    uint8_t *p8 = (uint8_t *) data;

    while (readBytes < numBytes) 
    {
	pass = UART_Read(pUART, p8, numBytes);
	numBytes -= pass;
	readBytes += pass;
	p8 += pass;
    }

    return readBytes;
}

/* Обработчик прерывания UART по приему данных для кольцевых буферов */
void UART_RXIntHandlerRB(UART_T *pUART, RINGBUFF_T *pRB)
{
    while (!(UART_GetStatus(pUART, UART_FR_RXFE))) 
    {
	uint8_t ch = UART_ReadByte(pUART);
	RingBuffer_Insert(pRB, &ch);
    }
}

/* Обработчик прерывания UART по передаче данных для кольцевых буферов */
void UART_TXIntHandlerRB(UART_T *pUART, RINGBUFF_T *pRB)
{
    uint8_t ch;
    while (!(UART_GetStatus(pUART, UART_FR_TXFF)) && RingBuffer_Pop(pRB, &ch))
    {
	UART_SendByte(pUART, ch);
    }

    /* Выключение прерывания, если кольцевой буфер пуст */
    if (RingBuffer_IsEmpty(pRB))
    {
	UART_IntDisable(pUART, UART_IMSC_TXIM);
    }
}

/* Запись данных в кольцевой буфер и начало передачи */
uint32_t UART_SendRB(UART_T *pUART, RINGBUFF_T *pRB, const void *data, uint32_t bytes)
{
    uint32_t ret;
    uint8_t ch;
    uint8_t *p8 = (uint8_t *) data;
    /* Отключение прерывания по передаче на время работы с кольцевым буфером */
    UART_IntDisable(pUART, UART_IMSC_TXIM);
    /* Заполнение кольцевого буфера данными */
    ret = RingBuffer_InsertMult(pRB, p8, bytes);
    while (!(UART_GetStatus(pUART, UART_FR_TXFF)) && RingBuffer_Pop(pRB, &ch)) 
    {
	UART_SendByte(pUART, ch);
    }
    /**Дозапись данных, если возможно */
    ret += RingBuffer_InsertMult(pRB, (p8 + ret), (bytes - ret));
    /* Включение прерывания по передаче */
    UART_IntEnable(pUART, UART_IMSC_TXIM);
    return ret;
}

/* Чтение данных из кольцевого буфера после приема */
uint32_t UART_ReadRB(UART_T *pUART, RINGBUFF_T *pRB, void *data, uint32_t bytes)
{
    (void) pUART;
    return RingBuffer_PopMult(pRB, (uint8_t *) data, bytes);
}

/* Обработчик прерывания UART по приему/передаче данных для кольцевых буферов */
void UART_IRQRBHandler(UART_T *pUART, RINGBUFF_T *pRXRB, RINGBUFF_T *pTXRB)
{
    /* Обработка прерывания по передаче */
    if (UART_GetIntStatus(pUART, UART_MIS_TXMIS)) 
    {
	UART_TXIntHandlerRB(pUART, pTXRB);
	/* Выключение прерывания, если кольцевой буфер пуст */
	if (RingBuffer_IsEmpty(pTXRB)) 
        {
            UART_IntDisable(pUART, UART_IMSC_TXIM);
	}
    }
    /* Обработка прерывания по приему */
    UART_RXIntHandlerRB(pUART, pRXRB);
}

/* Определение и установка оптимальных параметров делителя частоты */
uint32_t UART_SetBaud(UART_T *pUART, uint32_t baud,const uint32_t sys_freq)
{
    float div = (sys_freq/16.0)/baud;
    uint32_t ibrd = (uint32_t) div;
    uint32_t fbrd = (uint32_t)((div - ibrd)*64+0.5);
    UART_SetDivisor(pUART, ibrd, fbrd);
    /* Возврат установленного значения частоты */
    return (uint32_t)(sys_freq/(16*(ibrd + fbrd/64.0)));
}

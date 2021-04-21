/*!\file
 * \brief Этот файл содержит структуры, макросы и функции, необходимые для взаимодействия с аппаратным модулем UART.
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
 * Организация "Цифровые решения" не несет никакой ответственности за использование 
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

#ifndef UART_H_
#define UART_H_

#include "types.h"
#include "ringbuffer.h"
    
#define UART_DR_MASK_DATA                ((uint32_t)(0x00FF))                   /**< маскирование данных без статуса для регистра данных DR */

/** \brief  Структура для доступа к регистрам UART
 */
typedef struct
{
    __RW uint32_t DR;                                                           /**< Смещение: 0x000 Регистр данных. */
    __RW uint32_t RSR_ECR;                                                      /**< Смещение: 0x004 Регистр состояния приемника/сброса ошибки. */
    uint32_t RESERVED0[4];                                                      
    __RO  uint32_t FR;                                                          /**< Смещение: 0x018 Регистр флагов. */
    uint32_t RESERVED1[2];                                                
    __RW uint32_t IBRD;                                                         /**< Смещение: 0x024 Целая часть делителя скорости обмена данными. */
    __RW uint32_t FBRD;                                                         /**< Смещение: 0x028 Дробная часть делителя скорости обменаданными. */
    __RW uint32_t LCR_H;                                                        /**< Смещение: 0x02C Регистр управления линией LCR_H. */
    __RW uint32_t CR;                                                           /**< Смещение: 0x030 Регистр управления потоком CR. */
    __RW uint32_t IFLS;                                                         /**< Смещение: 0x034 Регистр порога прерывания по заполнению буфера FIFO. */
    __RW uint32_t IMSC;                                                         /**< Смещение: 0x038 Регистр маски прерывания. */
    __RO uint32_t RIS;                                                          /**< Смещение: 0x03C Регистр состояния прерываний. */
    __RO uint32_t MIS;                                                          /**< Смещение: 0x040 Регистр состояния прерываний с маскированием. */
    __WO uint32_t ICR;                                                          /**< Смещение: 0x044 Регистр сброса прерывания. */
    __RW uint32_t DMACR;                                                        /**< Смещение: 0x048 Регистр управления DMA. */
}UART_T;                                                                             
                                                                                     
/**                                                                                  
 * @brief Макросы для регистра DR                                                    
 */                                                                                  
#define UART_DR_DATA(x)                  ((uint32_t)((x) & 0xFF))               /**< принимаемые/передаваемые данные */     
#define UART_DR_FE                       ((uint32_t)(1 << 8))                   /**< ошибка в структуре кадра */
#define UART_DR_PE                       ((uint32_t)(1 << 9))                   /**< ошибка контроля четности */
#define UART_DR_BE                       ((uint32_t)(1 << 10))                  /**< разрыв линии */
#define UART_DR_OE                       ((uint32_t)(1 << 11))                  /**< переполнение буфера приемника */
//#define UART_DR_MASK_DATA                ((uint32_t)(0x00FF))                   /**< маскирование данных без статуса для регистра данных DR */

/**
 * @brief Макросы и типы для регистра RSR_ECR
 */
typedef enum  
{
    UART_RSR_FE = ((uint32_t)(1 << 0)),                                         /**< ошибка в структуре кадра */
    UART_RSR_PE = ((uint32_t)(1 << 1)),                                         /**< ошибка контроля четности */
    UART_RSR_BE = ((uint32_t)(1 << 2)),                                         /**< разрыв линии */
    UART_RSR_OE = ((uint32_t)(1 << 3)),                                         /**< переполнение буфера приемника */
}UART_REC_STATUS_T;

/**
 * @brief Макросы и типы для регистра FR
 */
typedef enum 
{
    UART_FR_BUSY = ((uint32_t)(1 << 3)),                                        /**< UART занят */
    UART_FR_RXFE = ((uint32_t)(1 << 4)),                                        /**< буфер FIFO приемника пуст. */
    UART_FR_TXFF = ((uint32_t)(1 << 5)),                                        /**< буфер FIFO передатчика заполнен.  */
    UART_FR_RXFF = ((uint32_t)(1 << 6)),                                        /**< буфер FIFO приемника заполнен */
    UART_FR_TXFE = ((uint32_t)(1 << 7)),                                        /**< буфер FIFO передатчика пуст */
    UART_FR_RI   = ((uint32_t)(1 << 8)),                                        /**< инверсия линии nUARTRI */
}UART_STATUS_T;

/**
 * @brief Макросы для регистра UARTBIRD 
 */
#define UART_IBRD_BAUDDIV_INT(x)         ((uint32_t)((x) & 0xFFFF))               /**< целая часть коэффициента деления  */

/**
 * @brief Макросы для регистра UARTx_FBRD 
 */
#define UART_FBRD_BAUDDIV_FRAC(x)        ((uint32_t)((x) & 0x1F))                 /**< дробная часть коэффициента деления  */

/**
 * @brief Макросы и типы для регистра UARTx_LCR_H 
*/
#define UART_LCR_H_BRK                   ((uint32_t)(1 << 0))                   /**< разрыв линии */
#define UART_LCR_H_PEN                   ((uint32_t)(1 << 1))                   /**< разрешение проверки четности */
#define UART_LCR_H_PDIS                  ((uint32_t)(0 << 1))                   /**< запрещение проверки четности */
#define UART_LCR_H_EPS_EVEN              ((uint32_t)(1 << 2))                   /**< дополнение до четного */
#define UART_LCR_H_EPS_ODD               ((uint32_t)(0 << 2))                   /**< дополнение до нечетного */
#define UART_LCR_H_STP2                  ((uint32_t)(1 << 3))                   /**< режим передачи двух стоповых бит */
#define UART_LCR_H_STP1                  ((uint32_t)(0 << 3))                   /**< режим передачи одного стопового бита */
#define UART_LCR_H_FEN                   ((uint32_t)(1 << 4))                   /**< разрешение работы буфера FIFO приемника и передатчика */
#define UART_LCR_H_FDIS                  ((uint32_t)(0 << 4))                   /**< запрещение работы буфера FIFO приемника и передатчика */

typedef enum 
{
    UART_LCR_H_WLEN5 = ((uint32_t)(0 << 5)),                                    /**< длина слова 5 бит */
    UART_LCR_H_WLEN6 = ((uint32_t)(1 << 5)),                                    /**< длина слова 6 бит */
    UART_LCR_H_WLEN7 = ((uint32_t)(2 << 5)),                                    /**< длина слова 7 бит */
    UART_LCR_H_WLEN8 = ((uint32_t)(3 << 5)),                                    /**< длина слова 8 бит */
}UART_WLEN;

#define UART_LCR_H_SPS_EN                ((uint32_t)(1 << 7))                   /**< разрешение передачи бита четности с фиксированным значением */
#define UART_LCR_H_SPS_DIS               ((uint32_t)(0 << 7))                   /**< запрещение передачи бита четности с фиксированным значением */

/*
 * @brief Макросы для регистра UARTx_CR 
 */
#define UART_CR_UARTEN                   ((uint32_t)(1 << 0))                   /**< разрешение работы приемопередатчика */
#define UART_CR_LBE                      ((uint32_t)(1 << 7))                   /**< разрешение работы в режиме loopback */
#define UART_CR_TXE                      ((uint32_t)(1 << 8))                   /**< разрешение работы передатчика */
#define UART_CR_RXE                      ((uint32_t)(1 << 9))                   /**< разрешение работы приемника */
#define UART_CR_BITMASK                  ((uint32_t)(0x381))

/**
 * @brief Тип UART_IFLS для регистра UARTx_IFLS 
*/
typedef enum 
{
    UART_IFLS_1DIV8 = ((uint32_t)(0 << 0)),                                     /**< буфер заполнен на 1/8  */
    UART_IFLS_1DIV4 = ((uint32_t)(1 << 0)),                                     /**< буфер заполнен на 1/4  */
    UART_IFLS_1DIV2 = ((uint32_t)(2 << 0)),                                     /**< буфер заполнен на 1/2  */
    UART_IFLS_3DIV4 = ((uint32_t)(3 << 0)),                                     /**< буфер заполнен на 3/4  */
    UART_IFLS_7DIV8 = ((uint32_t)(4 << 0)),                                     /**< буфер заполнен на 7/8  */
}UART_IFLS;   

/**
 * @brief Макросы и типы для регистра UARTx_IMSC 
*/
typedef enum 
{
    UART_IMSC_RXIM = ((uint32_t)(1 << 4)),                                      /**< маскирование прерывания прерывания от приемника UARTRXINTR*/
    UART_IMSC_TXIM = ((uint32_t)(1 << 5)),                                      /**< маскирование прерывания от передатчика UARTTXINTR */
    UART_IMSC_RTIM = ((uint32_t)(1 << 6)),                                      /**< маскирование прерывания по таймауту приема данных UARTRTINTR */
    UART_IMSC_FEIM = ((uint32_t)(1 << 7)),                                      /**< маскирование прерывания по ошибке в структуре кадра UARTFEINTR */
    UART_IMSC_PEIM = ((uint32_t)(1 << 8)),                                      /**< маскирование прерывания по ошибке контроля четности UARTPEINTR */
    UART_IMSC_BEIM = ((uint32_t)(1 << 9)),                                      /**< маскирование прерывания по разрыву линии UARTBEINTR */
    UART_IMSC_OEIM = ((uint32_t)(1 << 10)),                                     /**< маскирование прерывания по переполнению буфера UARTOEINTR */
    UART_IMSC_BITMASK = ((uint32_t)(0x7F << 4)),
}UART_INTMASK_T;

/**
 * @brief Макросы и типы для регистра UARTx_RIS  
*/
typedef enum 
{
    UART_RIS_RXRIS = ((uint32_t)(1 << 4)),                                      /**< состояние прерывания прерывания от приемника UARTRXINTR*/
    UART_RIS_TXRIS = ((uint32_t)(1 << 5)),                                      /**< состояние прерывания от передатчика UARTTXINTR */
    UART_RIS_RTRIS = ((uint32_t)(1 << 6)),                                      /**< состояние прерывания по таймауту приема данных UARTRTINTR */
    UART_RIS_FERIS = ((uint32_t)(1 << 7)),                                      /**< состояние прерывания по ошибке в структуре кадра UARTFEINTR */
    UART_RIS_PERIS = ((uint32_t)(1 << 8)),                                      /**< состояние прерывания по ошибке контроля четности UARTPEINTR */
    UART_RIS_BERIS = ((uint32_t)(1 << 9)),                                      /**< состояние прерывания по разрыву линии UARTBEINTR */
    UART_RIS_OERIS = ((uint32_t)(1 << 10)),                                     /**< состояние прерывания по переполнению буфера UARTOEINTR */
    UART_RIS_BITMASK = ((uint32_t)(0x7F << 4)),
}UART_INTSTATUS_T;

/**
 * @brief Макросы и типы для регистра UARTx_MIS  
*/
typedef enum 
{
    UART_MIS_RXMIS = ((uint32_t)(1 << 4)),                                      /**< маскированное состояние прерывания прерывания от приемника UARTRXINTR*/
    UART_MIS_TXMIS = ((uint32_t)(1 << 5)),                                      /**< маскированное состояние прерывания от передатчика UARTTXINTR */
    UART_MIS_RTMIS = ((uint32_t)(1 << 6)),                                      /**< маскированное состояние прерывания по таймауту приема данных UARTRTINTR */
    UART_MIS_FEMIS = ((uint32_t)(1 << 7)),                                      /**< маскированное состояние прерывания по ошибке в структуре кадра UARTFEINTR */
    UART_MIS_PEMIS = ((uint32_t)(1 << 8)),                                      /**< маскированное состояние прерывания по ошибке контроля четности UARTPEINTR */
    UART_MIS_BEMIS = ((uint32_t)(1 << 9)),                                      /**< маскированное состояние прерывания по разрыву линии UARTBEINTR */
    UART_MIS_OEMIS = ((uint32_t)(1 << 10)),                                     /**< маскированное состояние прерывания по переполнению буфера UARTOEINTR */
    UART_MIS_BITMASK = ((uint32_t)(0x7F << 4)),        
}UART_MASKINTSTATUS_T;

/**
 * @brief Макросы и типы для регистра UARTx_ICR  
*/
typedef enum 
{
    UART_ICR_RXIC = ((uint32_t)(1 << 4)),                                       /**< сброс прерывания прерывания от приемника UARTRXINTR*/
    UART_ICR_TXIC = ((uint32_t)(1 << 5)),                                       /**< сброс прерывания от передатчика UARTTXINTR */
    UART_ICR_RTIC = ((uint32_t)(1 << 6)),                                       /**< сброс прерывания по таймауту приема данных UARTRTINTR */
    UART_ICR_FEIC = ((uint32_t)(1 << 7)),                                       /**< сброс прерывания по ошибке в структуре кадра UARTFEINTR */
    UART_ICR_PEIC = ((uint32_t)(1 << 8)),                                       /**< сброс прерывания по ошибке контроля четности UARTPEINTR */
    UART_ICR_BEIC = ((uint32_t)(1 << 9)),                                       /**< сброс прерывания по разрыву линии UARTBEINTR */
    UART_ICR_OEIC = ((uint32_t)(1 << 10)),                                      /**< сброс прерывания по переполнению буфера UARTOEINTR */        
    UART_ICR_BITMASK = ((uint32_t)(0x7F << 4)),                                 /**< BITMASK*/
}UART_INTCLEAR_T;

/**
 * @brief Макросы и типы для регистра UARTx_DMACR 
*/
typedef enum 
{
    UART_DMACR_RXDMAE = ((uint32_t)(1 << 0)),                                   /**< разрешение использования DMA при приеме */	
    UART_DMACR_TXDMAE = ((uint32_t)(1 << 1)),	                                /**< разрешение использования DMA при передаче */
    UART_DMACR_DMAONERR = ((uint32_t)(1 << 2)),	                                /**< Если бит установлен в 1, то в случае возникновения прерывания по обнаружению ошибки блокируются запросы DMA от приемника UARTRXDMASREQ и UARTRXDMABREQ.*/
    UART_DMACR_BITMASK = ((uint32_t)(3 << 0)),                                  /**< разрешение использования DMA при приеме и передаче */
}UART_DMACR_T;

#define UART_DMACR_DMAONERR              ((uint32_t)(1 << 2))                   /**< разрешение блокировки запросов DMA от приемника UARTRXDMASREQ и UARTRXDMABREQ в случае возникновения прерывания по обнаружению ошибки */  
#define BAUDRATE_921600                  (921600)                               /**< 921600 (бит/с) */
#define BAUDRATE_460800                  (460800)                               /**< 460800 (бит/с) */
#define BAUDRATE_230400                  (230400)                               /**< 230400 (бит/с) */
#define BAUDRATE_115200                  (115200)                               /**< 115200 (бит/с) */
#define BAUDRATE_57600                   (57600)                                /**< 57600 (бит/с) */
#define BAUDRATE_38400                   (38400)                                /**< 38400 (бит/с) */   
#define BAUDRATE_19200                   (19200)                                /**< 19200 (бит/с) */
#define BAUDRATE_14400                   (14400)                                /**< 14400 (бит/с) */
#define BAUDRATE_9600                    (9600)                                 /**< 9600 (бит/с) */
#define BAUDRATE_2400                    (2400)                                 /**< 2400 (бит/с) */
#define BAUDRATE_1200                    (1200)                                 /**< 1200 (бит/с) */
#define BAUDRATE_110                     (110)                                  /**< 110 (бит/с) */ 


/**
 * @brief Разрешение работы передатчика
 * @param pUART: Указатель на структуру с регистрами UART
 */
 void UART_TXEnable(UART_T *pUART);

/**
 * @brief запрещение работы передатчика
 * @param pUART: Указатель на структуру с регистрами UART
 */
 void UART_TXDisable(UART_T *pUART);

/**
 * @brief Разрешение работы приемника
 * @param pUART: Указатель на структуру с регистрами UART
 */
 void UART_RXEnable(UART_T *pUART);
   
/**
 * @brief запрещение работы приемника
 * @param pUART: Указатель на структуру с регистрами UART
 */
 void UART_RXDisable(UART_T *pUART);

/**
 * @brief Разрешение работы UART
 * @param pUART: Указатель на структуру с регистрами UART
 */
 void UART_Enable(UART_T *pUART);

/**
 * @brief запрещение работы UART
 * @param pUART: Указатель на структуру с регистрами UART
 */
 void UART_Disable(UART_T *pUART);

/**
 * @brief Передача одного байта по UART'у
 * @param pUART: Указатель на структуру с регистрами UART
 * @param data: Байт для передачи
 */
 void UART_SendByte(UART_T *pUART, uint8_t data);


/**
 * @brief Прием одного байта по UART'у
 * @param pUART: Указатель на структуру с регистрами UART
 * @return Принятый байт
 */
 uint8_t UART_ReadByte(UART_T *pUART);

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
 void UART_IntEnable(UART_T *pUART, UART_INTMASK_T IntMask);

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
 void UART_IntDisable(UART_T *pUART, UART_INTMASK_T IntMask);


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
 uint32_t UART_GetIntStatus(UART_T *pUART, UART_MASKINTSTATUS_T MaskInt);

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
 void UART_ClearIntPending(UART_T *pUART, UART_INTCLEAR_T IntClear);

/**
 * @brief Установка порогов прерываний по заполнению буфера приемника/передатчика
 * @param pUART: Указатель на структуру с регистрами UART
 * @param rxfifolimit: Порог прерывания по заполнению буфера приемника
 * @param txfifolimit: Порог прерывания по заполнению буфера передатчика
 */
 void UART_SetupFIFOS(UART_T *pUART, UART_IFLS rxfifolimit, UART_IFLS txfifolimit);

/**
 * @brief Установка длины слова данных, числа стоповых бит и контроля четности
 * @param pUART: Указатель на структуру с регистрами UART
 * @param config: Установки UART, логическое сложение макросов, определенных для LCR_H, например: (UART_LCR_H_PEN | UART_LCR_H_EPS_EVEN | UART_LCR_H_STP1 | UART_LCR_H_FEN | UART_LCR_H_WLEN8 | UART_LCR_H_SPS_DIS)
 */
 void UART_Config(UART_T *pUART, uint32_t config);

/**
 * @brief Установка делителя скорости передачи данных
 * @param pUART: Указатель на структуру с регистрами UART
 * @param IBRD: Целая часть делителя скорости передачи данных
 * @param FBRD: Дробная часть делителя скорости передачи данных
 */
 void UART_SetDivisor(UART_T *pUART, uint32_t IBRD, uint32_t FBRD);

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
FlagStatus UART_GetStatus(UART_T *pUART, UART_STATUS_T Stat);

/**
 * @brief Инициализация UART
 * @param pUART: Указатель на структуру с регистрами UART
 */
void UART_Init(UART_T *pUART);


/**
 * @brief Деинициализация UART
 * @param pUART: Указатель на структуру с регистрами UART
 */
void UART_DeInit(UART_T *pUART);

/**
 * @brief Установка целой и дробной частей делителя для получения заданной скорости последовательного обмена
 * @param pUART: Указатель на структуру с регистрами UART
 * @param baud: Необходимая скорость последовательного обмена, например: BAUDRATE_921600..BAUDRATE_110
 * @return Полученная скорость с учетом ошибки или 0, если делитель вычислить не удалось
 */
uint32_t UART_SetBaud(UART_T *pUART, uint32_t baud,const uint32_t sys_freq);

/**
 * @brief Передача массива байт по UART'у, без ожидания освобождения FIFO передатчика
 * @param pUART: Указатель на структуру с регистрами UART
 * @param data: Указатель на данные для передачи
 * @param numBytes: Длина данных для передачи
 * @return Длина переданных данных
 */
uint32_t UART_Send(UART_T *pUART, const void *data, uint32_t numBytes);

/**
 * @brief Прием массива байт по UART'у, без ожидания заполнения указанного массива полностью
 * @param pUART: Указатель на структуру с регистрами UART
 * @param data: Указатель на массив для записи данных
 * @param numBytes: Длина данных для приема
 * @return Длина принятых данных
 */
uint32_t UART_Read(UART_T *pUART, void *data, uint32_t numBytes);

/**
 * @brief Передача массива байт по UART'у, с ожиданием освобождения FIFO передатчика
 * @param pUART: Указатель на структуру с регистрами UART
 * @param data: Указатель на данные для передачи
 * @param numBytes: Длина данных для передачи
 * @return Длина переданных данных
 */
uint32_t UART_SendBlocking(UART_T *pUART, const void *data, uint32_t numBytes);

/**
 * @brief Прием массива байт по UART'у, с ожиданием заполнения указанного массива полностью
 * @param pUART: Указатель на структуру с регистрами UART
 * @param data: Указатель на массив для записи данных
 * @param numBytes: Длина данных для приема
 * @return Длина принятых данных
 */
uint32_t UART_ReadBlocking(UART_T *pUART, void *data, uint32_t numBytes);

/**
 * @brief Обработчик прерывания UART по приему данных для кольцевых буферов
 * @param pUART: Указатель на структуру с регистрами UART
 * @param pRB: Указатель на структуру кольцевого буфера
 */
void UART_RXIntHandlerRB(UART_T *pUART, RINGBUFF_T *pRB);

/**
 * @brief Обработчик прерывания UART по передаче данных для кольцевых буферов
 * @param pUART: Указатель на структуру с регистрами UART
 * @param pRB: Указатель на структуру кольцевого буфера
 */
void UART_TXIntHandlerRB(UART_T *pUART, RINGBUFF_T *pRB);

/**
 * @brief Обработчик прерывания UART по приему/передаче данных для кольцевых буферов
 * @param pUART: Указатель на структуру с регистрами UART
 * @param pRXRB: Указатель на структуру кольцевого буфера для приема
 * @param pTXRB: Указатель на структуру кольцевого буфера для передачи
 */
void UART_IRQRBHandler(UART_T *pUART, RINGBUFF_T *pRXRB, RINGBUFF_T *pTXRB);

/**
 * @brief Запись данных в кольцевой буфер и начало передачи
 * @param pUART	: Указатель на структуру с регистрами UART
 * @param pRB: указатель на структуру кольцевого буфера
 * @param data: Данные для записи
 * @param bytes: Длина данных
 * @return Длина данных, записанных в буфер
 */
uint32_t UART_SendRB(UART_T *pUART, RINGBUFF_T *pRB, const void *data, uint32_t bytes);

/**
 * @brief Чтение данных из кольцевого буфера после приема
 * @param pUART	: Указатель на структуру с регистрами UART
 * @param pRB: Указатель на структуру кольцевого буфера
 * @param data: Указатель на массив для приема данных
 * @param bytes: Длина данных для приема
 * @return Длина принятых данных
 */
uint32_t UART_ReadRB(UART_T *pUART, RINGBUFF_T *pRB, void *data, uint32_t bytes);


#endif 
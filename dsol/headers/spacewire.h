/*!\file
 * \brief Этот файл содержит структуры, макросы и функции, необходимые для взаимодействия с аппаратным модулем SpaceWire.
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

#ifndef SPACEWIRE_H_
#define SPACEWIRE_H_

#include "types.h"



#define SPW_DSC_COUNT 32

/** \brief  Структура для доступа к регистрам Spacewire
 */
typedef struct
{
    __RW uint32_t CONTROL;                                                      /**< Смещение: 0x00 Регистр управления */
    __RW uint32_t STATUS;                                                       /**< Смещение: 0x04 Регистр статуса */
    __RW uint32_t TXSCALER;                                                     /**< Смещение: 0x08 Регистр делителя тактовых сигналов */
    __RW uint32_t TIMECODE;                                                     /**< Смещение: 0x0C Регистр временных меток */
    __RW uint32_t RXDESCPTR;                                                    /**< Смещение: 0x10 Регистр указателя на таблицу дескрипторов приема */
    __RW uint32_t TXDESCPTR;	                                                /**< Смещение: 0x14 Регистр указателя на таблицу дескрипторов передачи */
    __RW uint32_t TXSCALERLINK;                                                 /**< Смещение: 0x18 Регистр делителя тактовых сигналов  во время Link*/
    __RW uint32_t RESETTIME;                                                    /**< Смещение: 0x1C Регистр задания времени ожидания при Link (6,4 мкс) в тактах системной частоты */
    __RW uint32_t DISCONNECTTIME;                                               /**< Смещение: 0x20 Регистр задания времени таймаута приемника  (850 нс) (в тактах системной частоты) */
    __RW uint32_t ENDIANNES;                                                    /**< Смещение: 0x24 Регистр задания эндианности на приеме и на передаче */      
} SPW_T;

/**
 * @brief Макросы для CONTROL
 */
#define SW_CONTROL_RESET_AMBA               ((uint32_t)(1 << 0))                /**< Запись «1» сбрасывает контроллер */
#define SW_CONTROL_RESET_DMA                ((uint32_t)(1 << 1))                /**< Запись «1» сбрасывает контроллер DMA */
#define SW_CONTROL_LINK_START               ((uint32_t)(1 << 2))                /**< Linkstart; запись «1» разрешает установку соединения. */
#define SW_CONTROL_AUTOSTART                ((uint32_t)(1 << 3))                /**< Autostart; Запись «1» разрешает автоматическую установку соединения в случае потери.*/
#define SW_CONTROL_LINK_DISABLE             ((uint32_t)(1 << 4))                /**< Linkdisable; запись «1» запрещает работу Link контроллера. */
#define SW_CONTROL_ALLOW_TIMECODE_TX        ((uint32_t)(1 << 5))                /**< разрешение передачи временных меток */
#define SW_CONTROL_RESTART_RX_DMA           ((uint32_t)(1 << 6))                /**< запуск RXDMA */
#define SW_CONTROL_RESTART_TX_DMA           ((uint32_t)(1 << 7))                /**< запуск TXDMA */
#define SW_CONTROL_CANCEL_TX_DMA            ((uint32_t)(1 << 8))                /**< Запись «1» прерывает работу TXDMA и RXDMA */
#define SW_CONTROL_INT_EN_LINK_UP_DOWN      ((uint32_t)(1 << 9))                /**< Разрешение прерывания при установке соединения */
#define SW_CONTROL_INT_EN_TIME_CODE         ((uint32_t)(1 << 10))               /**< Разрешение прерывания при приеме временных меток*/
#define SW_CONTROL_INT_EN_RX_DSCR_COMPLETE  ((uint32_t)(1 << 11))               /**< Разрешение прерывания по завершению RX дескриптора при IE = «1» */
#define SW_CONTROL_INT_EN_TX_DSCR_COMPLETE  ((uint32_t)(1 << 12))               /**< Разрешение прерывания по завершению TX дескриптора при IE = «1» */
#define SW_CONTROL_INT_EN_RX_PACKET         ((uint32_t)(1 << 13))               /**< Разрешение прерывания при приеме пакета по завершению работы TX дескриптора */
#define SW_CONTROL_DESCTABLESIZE(x)         (__RO (uint32_t)((x) & 0xF << 24))    /**< Размер таблицы дескрипторов, доступен только на чтение */

/**
 * @brief Макросы для STATUS
 */
#define SW_STATUS_LINK_STATUS_DISABLED      ((uint32_t)(0x0 << 0))              /**< статус Link контроллера: выключен */
#define SW_STATUS_LINK_STATUS_START         ((uint32_t)(0x1 << 0))              /**< статус Link контроллера: старт */
#define SW_STATUS_LINK_STATUS_CONNECTED     ((uint32_t)(0x2 << 0))              /**< статус Link контроллера: соединение установлено */
#define SW_STATUS_LINK_STATUS_ENABLED       ((uint32_t)(0x3 << 0))              /**< статус Link контроллера: запущен */
#define SW_STATUS_DISCONNECT_ERR            ((uint32_t)(1 << 2))                /**< ошибка соединения */
#define SW_STATUS_PARITY_ERR                ((uint32_t)(1 << 3))                /**< ошибка четности */
#define SW_STATUS_ESCAPE_ERR                ((uint32_t)(1 << 4))                /**< ошибка escape */          
#define SW_STATUS_CREDIT_ERR                ((uint32_t)(1 << 5))                /**< ошибка credit */           
#define SW_STATUS_RX_DMA_RUNNING            ((uint32_t)(1 << 6))                /**< RXDMA запущен */   
#define SW_STATUS_TX_DMA_RUNNING            ((uint32_t)(1 << 7))                /**< TXDMA запущен */              
#define SW_STATUS_AHB_ERR                   ((uint32_t)(1 << 8))                /**< ошибка шины AHB */             
#define SW_STATUS_RECEIVED_TIMECODE         ((uint32_t)(1 << 10))               /**< Получен пакет с временной меткой. Для сброса бита необходимо записать «1»*/            
#define SW_STATUS_RX_COMPLETE               ((uint32_t)(1 << 11))               /**< RX дескриптор завершен при IE = «1». Для сброса бита необходимо записать «1» */             
#define SW_STATUS_TX_COMPLETE               ((uint32_t)(1 << 12))               /**< TX дескриптор завершен при IE = «1». Для сброса бита необходимо записать «1» */  
#define SW_STATUS_PACKET_RX                 ((uint32_t)(1 << 13))               /**< Получен пакет. Для сброса бита необходимо записать «1»*/            
#define SW_STATUS_RXFIFO_EMPTY              ((uint32_t)(1 << 14))               /**< (только чтение) - память RXFIFO не содержит данных, и последний пакет был отправлен по RXDMA */

           
/**
 * @brief Макросы для TXSCALER
 */
#define SW_TXSCALER_DIVISOR(x)               ((uint32_t)(((x) & 0xFF) << 0))        /**< делитель частоты тактового сигнала передатчика */

/**
 * @brief Макросы для RXDESCPTR
 */
#define SW_RXDESCPTR_DSCR_NUM(x)             ((uint32_t)(((x) & 0x1F) << 3))      /**< Номер дескриптора */
#define SW_RXDESCPTR_DSCR_ADDR(x)            ((uint32_t)(((x) & 0xFFFFFF) << 8)) /**< Адрес начала таблицы дескрипторов */

/**
 * @brief Макросы для TXDESCPTR
 */
#define SW_TXDESCPTR(x)                       ((uint32_t)(((x) & 0x1F) << 3))               /**< Номер дескриптора */
#define SW_TXDESCPTR_DSCR_ADDR(x)             ((uint32_t)(((x) & 0xFFFFFF) << 8)) /**< Адрес начала таблицы дескрипторов */

/**
 * @brief Макросы для TxScalerLink
 */
#define SW_TxScalerLink_DIVISOR(x)             ((uint32_t)(((x) & 0xFF) << 0))    /**< TxScalerLink*/

/**
 * @brief Макросы для ResetTime
 */
#define SW_ResetTime_RESET_TIME(x)             ((uint32_t)(((x) & 0x3FF) << 0))   /**< ResetTime*/

/**
 * @brief Макросы для DISCONNECTTIME
 */
#define SW_DISCONNECTTIME_DISCONNECT_TIME(x)   ((uint32_t)(((x) & 0xFF) << 0))  /**< DisconnectTime*/

/**
 * @brief Макросы для Endianness
 */
#define SW_Endianness_RX_ENDIAN(x)              ((uint32_t)((x) << 1))            /**< RxEndianness. Значение 0 - little endian, 1 - big endian*/
#define SW_Endianness_TX_ENDIAN(x)              ((uint32_t)((x) << 0))            /**< TxEndianness. Значение 0 - little endian, 1 - big endian*/

   
   
/** \brief  Структура для DMA дескриптора SpaceWire
 */
typedef struct
{
    volatile uint32_t HEADER;
    unsigned char*        DATA_PTR;	
} SPW_DMA_DSC_T;


/** \brief  Структура для таблицы DMA дескрипторов Spacewire
 */
typedef struct
{
    SPW_DMA_DSC_T TXDsc[SPW_DSC_COUNT];
    SPW_DMA_DSC_T RXDsc[SPW_DSC_COUNT];
} SPW_DMA_DSC_TBL_T;


/**
 * @brief Макросы для HEADER дескриптора
 */
#define SW_DMA_DSC_HEADER_NUM(x)            ((uint32_t)(((x) & 0xFFFF) << 0))     /**< количество байт */
#define SW_DMA_DSC_HEADER_EN                ((uint32_t)(1 << 16))               /**< разрешение пользоваться дескриптором */
#define SW_DMA_DSC_HEADER_WR                ((uint32_t)(1 << 17))               /**< прерывание списка дескрипторов */
#define SW_DMA_DSC_HEADER_IE                ((uint32_t)(1 << 18))               /**< разрешение прерывания и выставление статуса по завершении */
#define SW_DMA_DSC_HEADER_DONE              ((uint32_t)(1 << 19))               /**< статус завершения */
#define SW_DMA_DSC_HEADER_EOP               ((uint32_t)(1 << 20))               /**< признак EOP */
#define SW_DMA_DSC_HEADER_EEP               ((uint32_t)(1 << 21))               /**< признак EEP */   
   
/**
 * @brief Инициализация SpaceWire
 * @param pSPW : Указатель на структуру с регистрами SpaceWire
 */
void SPW_Init(SPW_T *pSPW);

/**
 * @brief Денициализация SpaceWire
 * @param pSPW : Указатель на структуру с регистрами SpaceWire
 */
void SPW_DeInit(SPW_T *pSPW);

/**
 * @brief Выбор тактовой частоты блоков Spacewire
 * @param pSPW : Указатель на структуру с регистрами SpaceWire
 */
void SPW_freq(uint8_t freq_num);





#endif
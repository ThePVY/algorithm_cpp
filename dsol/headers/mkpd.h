/*!\file
 * \brief Этот файл содержит структуры, макросы и функции, необходимые для взаимодействия с аппаратным модулем MKPD.
 * \note МКПД - Мультиплексный канал передачи данных, согласно ГОСТ Р 52070-2003
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

#ifndef MKPD_H_
#define MKPD_H_

#include "types.h"


/**
 * @brief Структура для доступа к регистрам МКПД.
 */
typedef struct
{
    __RW uint32_t BCONE0;                                                       /**< Смещение: 0x0000 1й регистр контроллера шины 0 */
    __RW uint32_t BCONE1;                                                       /**< Смещение: 0x0004 2й регистр контроллера шины 0 */
    __RW uint32_t BCONE2;                                                       /**< Смещение: 0x0008 3й регистр контроллера шины 0 */
    __RO uint32_t BCONE3;                                                       /**< Смещение: 0x000C 4й регистр контроллера шины 0 */
    __RO uint32_t BCONE4;                                                       /**< Смещение: 0x0010 5й регистр контроллера шины 0 */
    __RW uint32_t BCTWO0;                                                       /**< Смещение: 0x0014 1й регистр контроллера шины 1 */
    __RW uint32_t BCTWO1;                                                       /**< Смещение: 0x0018 2й регистр контроллера шины 1 */
    __RW uint32_t BCTWO2;                                                       /**< Смещение: 0x001C 3й регистр контроллера шины 1 */
    __RO uint32_t BCTWO3;                                                       /**< Смещение: 0x0020 4й регистр контроллера шины 1 */
    __RO uint32_t BCTWO4;                                                       /**< Смещение: 0x0024 5й регистр контроллера шины 1 */
    __RW uint32_t EP0;                                                          /**< Смещение: 0x0028 1й регистр оконечного устройства */
    __RW uint32_t EP1;                                                          /**< Смещение: 0x002C 2й регистр оконечного устройства */
    __RO uint32_t EP2;                                                          /**< Смещение: 0x0030 3й регистр оконечного устройства */
    __RO uint32_t EP3;                                                          /**< Смещение: 0x0034 4й регистр оконечного устройства */
    __RW uint32_t SETTING0;                                                     /**< Смещение: 0x0038 Регистр настроек 0 */
    __RW uint32_t SETTING1;                                                     /**< Смещение: 0x003С Регистр настроек 1 */
    __RW uint32_t SETTING2;                                                     /**< Смещение: 0x0040 Регистр настроек 2 */
    __RW uint32_t SETTING3;                                                     /**< Смещение: 0x0044 Регистр настроек 3 */
    __RW uint32_t MONITOR0;                                                     /**< Смещение: 0x0048 1й регистр монитора */
    __RW uint32_t MONITOR1;                                                     /**< Смещение: 0x004С 2й регистр монитора */
    __RW uint32_t MONITOR2;                                                     /**< Смещение: 0x0050 3й регистр монитора */
    __RO uint32_t MONITOR3;                                                     /**< Смещение: 0x0054 4й регистр монитора */
    __RW uint32_t INTERRUPT;                                                    /**< Смещение: 0x0058 Регистр прерываний */
}MKPD_T;
         
/**
 * @brief Макросы для регистра BCONE0
 */
#define MKPD_BCONE0_SUB_ADDR1(x)        ((uint32_t)(((x) & 0x1F) << 0))           /**< подадрес оконечного устройства для второго командного слова */
#define MKPD_BCONE0_EP_ADDR1(x)         ((uint32_t)(((x) & 0x1F) << 5))           /**< адрес оконечного устройства для второго командного слова */
#define MKPD_BCONE0_NUM(x)              ((uint32_t)(((x) & 0x1F) << 10))          /**< количество передаваемых или принимаемых слов данных */
#define MKPD_BCONE0_SUB_ADDR0(x)        ((uint32_t)(((x) & 0x1F) << 16))          /**< подадрес оконечного устройства, которому предназначается командное слово */
#define MKPD_BCONE0_EP_ADDR0(x)         ((uint32_t)(((x) & 0x1F) << 21))          /**< адрес оконечного устройства, которому предназначается командное слово */

/**
 * @brief Макросы для регистра BCONE2
 */
#define MKPD_BCONE2_TYPE_TRANS(x)       ((uint32_t)(((x) & 0x0F) << 0))           /**< код транзакции */
#define MKPD_BCONE2_MANAGE_CODE(x)         ((unsigned int)(((x) & 0x01) << 4))                /**< код транзакции */
#define MKPD_BCONE2_ENA                 ((uint32_t)(1 << 8))                    /**< запуск начала транзакции */
#define MKPD_BCONE2_COM_DATA(x)         ((uint32_t)(((x) & 0xFFFF) << 16))        /**< слово данных для передачи */

/**
 * @brief Макросы для регистра BCONE3
 */
#define MKPD_BCONE3_REPLY_WORD(x)       ((uint32_t)((x) & 0xFFFF))                /**< слово данных, которое передается с ответным словом  */
#define MKPD_BCONE3_REPLY(x)            ((uint32_t)(((x) >> 16) & 0xFFFF))        /**< ответное слово на командное слово транзакции */

/**
 * @brief Макросы для регистра BCONE4
 */
#define MKPD_BCONE4_STATUS              ((uint32_t)(1 << 0))                    /**< маска для бита статуса */
#define MKPD_BCONE4_ERROR               ((uint32_t)(1 << 8))                    /**< маска для бита ошибки */
#define MKPD_BCONE4_TIMEOUT             ((uint32_t)(1 << 16))                   /**< маска для бита тайм-аута */

/**
 * @brief Макросы для регистра BCTWO0
 */
#define MKPD_BCTWO0_SUB_ADDR1(x)        ((uint32_t)(((x) & 0x1F) << 0))           /**< подадрес оконечного устройства для второго командного слова */
#define MKPD_BCTWO0_EP_ADDR1(x)         ((uint32_t)(((x) & 0x1F) << 5))           /**< адрес оконечного устройства для второго командного слова */
#define MKPD_BCTWO0_NUM(x)              ((uint32_t)(((x) & 0x1F) << 10))          /**< количество передаваемых или принимаемых слов данных */
#define MKPD_BCTWO0_SUB_ADDR0(x)        ((uint32_t)(((x) & 0x1F) << 16))          /**< подадрес оконечного устройства, которому предназначается командное слово */
#define MKPD_BCTWO0_EP_ADDR0(x)         ((uint32_t)(((x) & 0x1F) << 21))          /**< адрес оконечного устройства, которому предназначается командное слово */

/**
 * @brief Макросы для регистра BCTWO2
 */
#define MKPD_BCTWO2_TYPE_TRANS(x)       ((uint32_t)(((x) & 0x0F) << 0))           /**< код транзакции */
#define MKPD_BCTWO2_MANAGE_CODE         ((uint32_t)(1 << 4))                    /**< формат признака режима управления в командном слове */
#define MKPD_BCTWO2_ENA                 ((uint32_t)(1 << 8))                    /**< запуск начала транзакции */
#define MKPD_BCTWO2_COM_DATA(x)         ((uint32_t)(((x) & 0xFFFF) << 16))        /**< содержит слово данных */

/**
 * @brief Макросы для регистра BCTWO3
 */
#define MKPD_BCTWO3_REPLY_WORD(x)       ((uint32_t)((x) & 0xFFFF))                /**< слово данных, которое передается с ответным словом */
#define MKPD_BCTWO3_REPLY(x)            ((uint32_t)(((x) >> 16) & 0xFFFF))        /**< ответное слово на командное слово транзакции */

/**
 * @brief Макросы для регистра BCTWO4
 */
#define MKPD_BCTWO4_STATUS              ((uint32_t)(1 << 0))                    /**< маска для бита статуса */
#define MKPD_BCTWO4_ERROR               ((uint32_t)(1 << 8))                    /**< маска для бита ошибки */
#define MKPD_BCTWO4_TIMEOUT             ((uint32_t)(1 << 16))                   /**< маска для бита тайм-аута */

/**
 * @brief Макросы для регистра EP1
 */
#define MKPD_EP1_FEP1                   ((uint32_t)(1 << 0))                    /**< признак «Неисправность оконечного устройства» в ОС оконечного устройства */
#define MKPD_EP1_MAN                    ((uint32_t)(1 << 1))                    /**< признак «Принято управление интерфейсом» в ОС оконечного устройства */
#define MKPD_EP1_FEP0                   ((uint32_t)(1 << 2))                    /**< признак «Неисправность абонента» в ОС оконечного устройства */
#define MKPD_EP1_BUSY                   ((uint32_t)(1 << 3))                    /**< признак «Абонент занят» в ОС оконечного устройства. При сбросе равен 1 */
#define MKPD_EP1_RXGROUP                ((uint32_t)(1 << 4))                    /**< признак «Принята групповая команда» */
#define MKPD_EP1_RESERV(x)              ((uint32_t)(((x) & 0x03) << 5))           /**< резерв в ОС оконечного устройства */
#define MKPD_EP1_SREQ                   ((uint32_t)(1 << 8))                    /**< признак «Запрос на обслуживание» в ОС оконечного устройства */
#define MKPD_EP1_ERROR                  ((uint32_t)(1 << 8))                    /**< признак «Ошибка в сообщении» */  
#define MKPD_EP1_RDATA(x)               ((uint32_t)(((x) & 0xFFFF) << 16))        /**< содержит слово данных */

/**
 * @brief Макросы для регистра EP2
 */
#define MKPD_EP2_EP_COM_ERR             ((uint32_t)(1 << 0))                    /**< маска для бита ошибки */
#define MKPD_EP2_EP_COM_TIMEOUT         ((uint32_t)(1 << 1))                    /**< маска для бита тайм-аута */
  
/**
 * @brief Макросы для регистра EP3
 */   
#define MKPD_EP3_EP_COM_DATA(x)         ((uint32_t)((x) & 0xFFFF))                /**< маска для принятого слова данных */
#define MKPD_EP3_EP_COM(x)              ((uint32_t)(((x) >> 16) & 0xFFFF))        /**< контрольное слово принятое оконченным устройством */

/**
 * @brief Макросы и типы для регистра SETTING0
 */
#define MKPD_SETTING0_EP_ADDR(x)        ((uint32_t)(((x) & 0x1F) << 0))           /**< задает адрес оконечного устройства */

typedef enum 
{
    MKPD_SETTING0_MODE_DISABLED  = ((uint32_t)(0 << 8)),                        /**< задаёт режим работы - блок отключен */
    MKPD_SETTING0_MODE_BC  = ((uint32_t)(1 << 8)),                              /**< задаёт режим работы - контроллер шины (КШ) */
    MKPD_SETTING0_MODE_EP  = ((uint32_t)(2 << 8)),                              /**< задаёт режим работы - оконечное устройство (ОУ) */
    MKPD_SETTING0_MODE_M  = ((uint32_t)(3 << 8)),                               /**< задаёт режим работы - монитор (М) */
}MKPD_SETTING0_MODE_T;

typedef enum 
{
    MKPD_SETTING0_CHANNEL_A  = ((uint32_t)(0 << 16)),                           /**< задаёт рабочий канал A */
    MKPD_SETTING0_CHANNEL_B  = ((uint32_t)(1 << 16)),                           /**< задаёт рабочий канал B */
}MKPD_SETTING0_CHANNEL_T;

#define MKPD_SETTING0_SYS_CLK(x)        ((uint32_t)(((x) & 0xFF) << 24))          /**< системная частота в МГц */

/**
 * @brief Макросы для регистра SETTING1
 */
#define MKPD_SETTING1_EDGE(x)           ((uint32_t)(((x) & 0xFF) << 8))           /**< задает время запрещенного состояния дифференциального сигнала в тактах системной частоты блока */
#define MKPD_SETTING1_RWAIT(x)          ((uint32_t)(((x) & 0xFF) << 16))          /**< задает время ожидания ответного слова или слова данных в режиме работы контроллера шины и оконечного устройства */
#define MKPD_SETTING1_TIME(x)           ((uint32_t)(((x) & 0x0F) << 24))          /**< задает время паузы между сообщениями в микросекундах */



/**
 * @brief Макросы и типы для регистра SETTING2
 */
#define MKPD_SETTING2_500NS(x)           ((unsigned int)(((x) & 0xFF) << 0))      /**< задает количество тактов системной частоты равное 0.5 мкс */
 
#define MKPD_SETTING2_INVTX(x)           ((unsigned int)(((x) & 0x01) << 8))      /**< бит инвертирования дифференциального сигнала при передаче */
   
#define MKPD_SETTING2_INCWITH(x)         ((unsigned int)(((x) & 0x01) << 9))      /**< задает режим появления сигнала разрешения передачи */
   
#define MKPD_SETTING2_DECDIS(x)          ((unsigned int)(((x) & 0x0F) << 10))     /**< отключает и включает декодеры */
 
#define MKPD_SETTING2_NOACTTIME(x)       ((uint32_t)(((x) & 0xFF) << 16))     /**< задает время, в течение которго декодер определяет, что на линии нет активности */
    
#define MKPD_SETTING2_BCWAITREPLY(x)     ((uint32_t)(((x) & 0xFF) << 24))     /**< задает время ожидания ОС в режиме работы КШ, должно быть не менее 35 мкс */

typedef enum 
{
    MKPD_SETTING2_DECDIS_A  = ((uint32_t)(1 << 10)),                            /**< отключает декодер А */
    MKPD_SETTING2_DECDIS_B  = ((uint32_t)(1 << 11)),                            /**< отключает декодер B */  
    MKPD_SETTING2_DECDIS_C  = ((uint32_t)(1 << 12)),                            /**< отключает декодер C */ 
    MKPD_SETTING2_DECDIS_D  = ((uint32_t)(1 << 13)),                            /**< отключает декодер D */   
}MKPD_DECDIS_MODE_T;
 
/**
 * @brief Макросы для регистра SETTING3
 */
#define MKPD_SETTING3_1250NS(x)         ((uint32_t)(((x) & 0xFF) << 0))           /**< количество тактов системной частоты, равное 1,25 мкс. */
#define MKPD_SETTING3_1500NS(x)         ((uint32_t)(((x) & 0xFF) << 8))           /**< количество тактов системной частоты, равное 1,5 мкс. */
#define MKPD_SETTING3_1750NS(x)         ((uint32_t)(((x) & 0xFF) << 16))          /**< количество тактов системной частоты, равное 1,75 мкс. */
#define MKPD_SETTING3_2250NS(x)         ((uint32_t)(((x) & 0xFF) << 24))          /**< количество тактов системной частоты, равное 2,25 мкс. */

/**
 * @brief Макросы для регистра INTERRUPT
 */
#define MKPD_INTERRUPT_BC_INT           ((uint32_t)(1 << 0))                    /**< прерывание контроллера шины - прерывание окончания транзакции в контроллере шины */
#define MKPD_INTERRUPT_EP_INT0          ((uint32_t)(1 << 1))                    /**< прерывание оконечного устройства - прерывание по приёму командного слова */
#define MKPD_INTERRUPT_EP_INT1          ((uint32_t)(1 << 2))                    /**< прерывание оконечного устройства - прерывание окончания транзакции в оконечном устройстве */
#define MKPD_INTERRUPT_MON_INT          ((uint32_t)(1 << 3))                    /**< прерывание монитора - прерывание срабатывает, когда указатель записи достигает адреса в памяти DMA_MONITOR_ADDR + THRESHOLD */

/**
 * @brief Макросы, относящиеся к логике работы контроллера
 */
#define MKPD_MAX_WORD_IN_PACKET         32                                      /**< максимальное допустимое количество слов данных в пакете */ 
#define MKPD_EP_SUBADDR_COUNT           32 //16                                 /**< количество подадресов в оконечном устройстве */                                  
#define MKPD_MANAGE_MODE_MASK           0xF                                     /**< Содержимое поля "Режим управления" в командном слове, в случае передачи команд управления */    
#define MKPD_EP_GROUP_ADDR              0x1F                                    /**< Значение группового адреса */                               
   
/**   
 * @brief Выбор интерфейса передачи для контроллера шины
 */   
typedef enum 
{
    TX_ONE,                                                                     /**< передача по первому интерфейсу контроллера шины */
    TX_TWO,                                                                     /**< передача по второму интерфейсу контроллера шины */
}MKPD_TX_T;

/**
 * @brief Структура командного слова (КС)
 */  
struct Command_Word_Bits
{
    volatile uint16_t  Data_size__Command_code:5;                               /**< число слов данных / код команды */
    volatile uint16_t  Subaddr__Manage_mode:4;                                  /**< подадрес / режим управления */
    volatile uint16_t  Command_word_mark:1;                                     /**< признак "передача командного слова" */
    volatile uint16_t  Tx_rx_mark:1;                                            /**< разряд "приём/передача" */
    volatile uint16_t  EP_addr:5;                                               /**< адрес оконечного устройства */
};

/**
 * @brief Структура для доступа к командному слову (КС)
 */  
typedef union Command_Word
{
    volatile uint16_t               all;                                        /**< обращение к с целому слову */
    struct Command_Word_Bits        bit;                                        /**< обращение к отдельным полям слова */
}Command_Word_T;

/**
 * @brief Содержимое ответного слова (ОС)
 */ 
struct Reply_Word_Bits
{
    volatile uint16_t  FEP1:1;                                                  /**< признак "неисправность ОУ" */
    volatile uint16_t  MAN:1;                                                   /**< признак "принято управление интерфейсом" */
    volatile uint16_t  FEP0:1;                                                  /**< признак "неисправность абонента" */
    volatile uint16_t  BUSY:1;                                                  /**< признак "абонент занят" */
    volatile uint16_t  Group_rx:1;                                              /**< признак "принята групповая команда" */
    volatile uint16_t  RES:3;                                                   /**< резервные биты */
    volatile uint16_t  SREQ:1;                                                  /**< признак "запрос на обслуживание" */
    volatile uint16_t  Reply_tx:1;                                              /**< признак "передача ответного слова" */
    volatile uint16_t  Data_err:1;                                              /**< признак "ошибка в сообщении" */
    volatile uint16_t  EP_addr:5;                                               /**< адрес оконечного устройства */
};

/**
 * @brief Установка значения системной частоты
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param sys_clk: частота (в МГц)
 * @retval None
 */   
void MKPD_Set_System_Clock(MKPD_T *pMKPD, uint32_t sys_clk);

/**
 * @brief Установка рабочего канала для контроллера шины. 
 * @note Имеет значение только в режиме работы КШ.
 * @param pMKPD: указатель на структуру с регистрами MKPD.
 * @param channel: номер рабочего канала.
 *         Параметр channel может принимать значения:
 *          @arg MKPD_SETTING0_CHANNEL_A: рабочий канал для КШ - А
 *          @arg MKPD_SETTING0_CHANNEL_B: рабочий канал для КШ - B
 * @retval None
 */   
void MKPD_Set_Channel(MKPD_T *pMKPD, uint32_t channel);

/**
 * @brief Установка режима работы блока.
 * @param pMKPD: указатель на структуру с регистрами MKPD.
 * @param channel: номер рабочего канала.
 *         Параметр channel может принимать значения:
 *          @arg MKPD_SETTING0_MODE_DISABLED: блок отключен
 *          @arg MKPD_SETTING0_MODE_BC: блок функционирует в режиме КШ
 *          @arg MKPD_SETTING0_MODE_EP: блок функционирует в режиме ОУ
 *          @arg MKPD_SETTING0_MODE_M: блок функционирует в режиме М
 * @retval None
 */   
void MKPD_Set_Mode(MKPD_T *pMKPD, uint32_t mode);

/**
 * @brief	Установка формата транзакции
 * @param	pMKPD           : Указатель на структуру с регистрами MKPD
 * @param       index           : Номер интерфейса для передачи. TX_ONE либо TX_TWO 
 * @param	type_trans      : Формат транзакции, доступны значения до 1 до 10 в соответствии с ГОСТ Р 52070-2003
 * @param       manage_code     : Формат признака режима управления в командном слове. 0 = 00000 либо 1 = 11111
 */   
void MKPD_Set_BC_Transaction_Format2(MKPD_T *pMKPD, MKPD_TX_T index, unsigned int type_trans, unsigned int manage_code);

/**
 * @brief Установка адреса оконечного устройства. 
 * @note Имеет значение только в режиме работы ОУ.
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param ep_addr: адрес ОУ (0..31)
 * @retval None
 */   
void MKPD_Set_EP_Address(MKPD_T *pMKPD, uint32_t ep_addr);
/**
 * @brief Установка временного интервала между передачей пакетов
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param time: время (в мкс). Допустимые значения от 4 до 15
 * @retval None
 */   
void MKPD_Set_Interpacket_Time(MKPD_T *pMKPD, uint32_t time);
   
/**
 * @brief Установка времени ожидания ОС или СД в режиме работы КШ и ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param rwait: время (в мкс). Допустимые значения от 34 до 255
 * @retval None
 */   
void MKPD_Set_Wait_Time(MKPD_T *pMKPD, uint32_t rwait);

/**
 * @brief Установка времени запрещенного состояния дифференциального сигнала
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param edge: время (в тактах системной частоты). Допустимые значения от 0 до 255
 * @retval None
 */   
void MKPD_Set_Edge_Time(MKPD_T *pMKPD, uint32_t edge);


/**
 * @brief	Настройка сигнала разрешения передачи
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	IncWith	: 1 - расширенная передача сигнала; 0 - одновременно с диф. сигналом
 */   
void MKPD_Set_IncWith(MKPD_T *pMKPD, unsigned int IncWith);

/**
 * @brief	Программное отключение декодеров
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Disable_mask	: 4 бита, по одному на декодер, запись 1 отключает 
 *              декодер, запись 0 включает: бит 0 - А, бит 1 - B, бит 2 - C, бит 3 - D
 */   
void MKPD_Set_DecoderDisable(MKPD_T *pMKPD, unsigned int Disable_mask);

/**
 * @brief	Настройка времени ожидания отсутствия активности на линии, не менее 1.3 мкс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Noacttime	: Время ожидания, в тактах системной частоты
 */   
void MKPD_Set_NoActivity_Time(MKPD_T *pMKPD, unsigned int Noacttime);

/**
 * @brief	Настройка времени ожидания ОС в режиме КШ
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Bcwaitreply	: Время ожидания ОС, в тактах системной частоты, в мкс
 */   
void MKPD_Set_BCWaitReply_Time(MKPD_T *pMKPD, unsigned int Bcwaitreply);

/**
 * @brief	Тонкая настройка количества тактов системной частоты в 500 нс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Clk	: Количество тактов системной частоты
 */   
void MKPD_Set_Clk_500NS(MKPD_T *pMKPD, unsigned int Clk);

/**
 * @brief	Тонкая настройка количества тактов системной частоты в 1250 нс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Clk	: Количество тактов системной частоты
 */   
void MKPD_Set_Clk_1250NS(MKPD_T *pMKPD, unsigned int Clk);
/**
 * @brief	Тонкая настройка количества тактов системной частоты в 1500 нс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Clk	: Количество тактов системной частоты
 */   
void MKPD_Set_Clk_1500NS(MKPD_T *pMKPD, unsigned int Clk);

/**
 * @brief	Тонкая настройка количества тактов системной частоты в 1750 нс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Clk	: Количество тактов системной частоты
 */   
void MKPD_Set_Clk_1750NS(MKPD_T *pMKPD, unsigned int Clk);

/**
 * @brief	Тонкая настройка количества тактов системной частоты в 2250 нс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Clk	: Количество тактов системной частоты
 */   
void MKPD_Set_Clk_2250NS(MKPD_T *pMKPD, unsigned int Clk);

/**
 * @brief Определяет готовность контроллера шины к новой транзакции
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO)  
 * @return SET or RESET - состояние готовности к передаче
 */   
int MKPD_BC_IsReady(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief Установка приёмной частоты сигнала
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param clkrx: частота (в МГц). 
 * @note Приёмная частота должна превышать частоту передатчика более чем в 5 раз
 * @retval None
 */ 
//void MKPD_Set_Clock_RX(MKPD_T *pMKPD, uint32_t clkrx);
 
/**
 * @brief Возвращает значение прерывания
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @return Считывает содержимое регистра прерываний. 
 *          Возможны возвращаемые значения:
 *           MKPD_INTERRUPT_BC_INT: прерывание окончания транзакции в КШ
 *           MKPD_INTERRUPT_EP_INT0: прерывание ОУ, по приёму КС
 *           MKPD_INTERRUPT_EP_INT1: прерывание ОУ, по окончанию транзакции
 *           MKPD_INTERRUPT_MON_INT: прерывание монитора, по достижению порога
 */   
uint32_t MKPD_Get_Interrupt(MKPD_T *pMKPD);

/**
 * @brief Настройка параметров инвертирования дифференциального сигнала
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param invert_params: параметры инвертирования.
 *         Параметр invert_params может принимать значения:
 *          @arg MKPD_LOOPBACK_INVTX: инвертирование диф. сигнала при передаче
 *          @arg MKPD_LOOPBACK_INVRX0: инвертирование диф. сигнала в приёмнике 0 канала
 *          @arg MKPD_LOOPBACK_INVRX1: инвертирование диф. сигнала в приёмнике 1 канала
 *          @arg MKPD_LOOPBACK_AUTO_ENA: включение автоопределения линии диф. сигнала в приёмнике
 * @retval None
 */   
void MKPD_Set_Inverting(MKPD_T *pMKPD, uint32_t invert_params);

/**
 * @brief Включение местного заворота линии
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @retval None
 */   
void MKPD_Loopback_Enable(MKPD_T *pMKPD);

/**
 * @brief Отключение местного заворота линии
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @retval None
 */   
void MKPD_Loopback_Disable(MKPD_T *pMKPD);

/**
 * @brief Установка параметров транзакции
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @param ep_addr0: адрес ОУ, которому предназначено КС
 * @param sub_addr0: подадрес ОУ (признак режима управления), которому предназначено КС
 * @param ep_addr1: адрес ОУ для второго КС
 * @param sub_addr1: подадрес ОУ для второго КС
 * @param num: количество передаваемых или принимаемых СД. В режиме управления также содержит код команды
 * @retval None
 */   
void MKPD_Set_BC_TX_Params(MKPD_T *pMKPD, MKPD_TX_T index, 
                                     uint32_t ep_addr0, uint32_t sub_addr0, 
                                     uint32_t ep_addr1, uint32_t sub_addr1, 
                                     uint32_t num);
/**
 * @brief Установка адреса DMA
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @param dma_addr: адрес первого байта в области памяти КШ
 * @retval None
 */   
void MKPD_Set_BC_DMA_Address(MKPD_T *pMKPD, MKPD_TX_T index, uint32_t dma_addr);

/**
 * @brief Настройка контроллера шины
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param address_one: начальный адрес в памяти для хранения слов данных интерфейса 1
 * @param address_two: начальный адрес в памяти для хранения слов данных интерфейса 2
 * @param channel: номер рабочего канала.
 *         Параметр channel может принимать значения:
 *          @arg MKPD_SETTING0_CHANNEL_A: рабочий канал для КШ - А
 *          @arg MKPD_SETTING0_CHANNEL_B: рабочий канал для КШ - B
 * @retval None
 */
void MKPD_ConfigBusController(MKPD_T *pMKPD, uint32_t address_one, uint32_t address_two, uint32_t channel);

/**
 * @brief Установка слова данных для передачи в транзакциях формата 6 или 10.
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO)  
 * @param com_data: содержимое слова данных, 16 бит
 * @retval None
 */   
void MKPD_Set_BC_COM_Data(MKPD_T *pMKPD, MKPD_TX_T index, uint32_t com_data);

/**
 * @brief Установка формата транзакции
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO)  
 * @param type_trans: формат транзакции (1..10)
 * @retval None
 */   
void MKPD_Set_BC_Transaction_Format(MKPD_T *pMKPD, MKPD_TX_T index, uint32_t type_trans);

/**
 * @brief Установка формата транзакции
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO)  
 * @retval None
 */   
void MKPD_BC_Start_Transaction(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief Определяет, находится ли транзакция в очереди на передачу
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return SET or RESET - состояние ожидания транзакции
 */   
FlagStatus MKPD_BC_IsWaiting(MKPD_T *pMKPD, MKPD_TX_T index);
/**
 * @brief Определяет, передается ли транзакция в настоящий момент
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return SET or RESET - состояние ожидания транзакции
 */  
FlagStatus MKPD_BC_IsSending(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief Возвращает значение флага ошибки транзации
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return SET or RESET - состояние ожидания транзакции
 */  
FlagStatus MKPD_BC_IsError(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief Возвращает значение флага таймаута транзации
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return SET or RESET - состояние ожидания транзакции
 */    
FlagStatus MKPD_BC_IsTimeout(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief Возвращает ответное слово, полученное от ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return Содержимое ответного слова, 16 бит
 */   
uint32_t MKPD_BC_Reply_Word(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief Возвращает ответные данные, полученные от ОУ (для транзакций формата 5)
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return Содержимое ответного слова, 16 бит
 */     
uint32_t MKPD_BC_Reply_Data(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief Передача сообщения от КШ 
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO)  
 * @param type_trans: формат транзакции, доступны значения (1..10)
 * @param ep_addr0: адрес ОУ, которому предназначено КС
 * @param sub_addr0: подадрес ОУ, которому предназначено КС
 * @param ep_addr1: адрес ОУ для второго КС
 * @param sub_addr1: подадрес ОУ для второго КС
 * @param num: количество передаваемых или принимаемых СД. В режиме управления содержит код команды
 * @param timeout: таймаут на передачу сообщения
 * @return Успешная передача сообщения - 0; Транзакция не начата - 1; Транзакция не завершилась - 2
 */

unsigned int MKPD_StartMessage(MKPD_T *pMKPD, MKPD_TX_T index, unsigned int type_trans,                                      
                       unsigned int ep_addr0, unsigned int sub_addr0, 
                       unsigned int ep_addr1, unsigned int sub_addr1, 
                       unsigned int num, 
                       unsigned int timeout,
                       unsigned int manage_code);
                       

/**
 * @brief Установка адреса первого байта области памяти ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param dma_ep: адрес. Для всех подадресов используется общая память
 * @retval None
 */   
void MKPD_Set_Endpoint_DMA_Address(MKPD_T *pMKPD, uint32_t dma_ep);
/**
 * @brief Настройка оконечного устройства
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param address: начальный адрес в памяти для хранения слов данных
 * @param ep_address: адрес оконечного устройства (0..31)
 * @retval None
 */
void MKPD_ConfigEndpoint(MKPD_T *pMKPD, uint32_t address, uint32_t ep_address);

/**
 * @brief Установка слова данных для передачи от ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param rdata: содержимое слова данных, 16 бит
 * @retval None
 */   
void MKPD_Set_Endpoint_RDATA(MKPD_T *pMKPD, uint32_t rdata);

/**
 * @brief Установка признаков в ОС ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param attributes: набор признаков. 
 *         Параметр attributes может принимать значения:
 *          @arg MKPD_EP1_FEP1: неисправность ОУ
 *          @arg MKPD_EP1_MAN: принято управление интерфейсом
 *          @arg MKPD_EP1_FEP0: неисправность абонента
 *          @arg MKPD_EP1_BUSY: абонент занят
 *          @arg MKPD_EP1_RES(x): задание значения резервного поля
 *          @arg MKPD_EP1_SREQ: запрос на обслуживание
 * @retval None
 */   
void MKPD_Set_Endpoint_Attributes(MKPD_T *pMKPD, uint32_t attributes);
/**
 * @brief	Установка инвертирования дифференциального сигнала на передаче
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	invTX	: 1 - инвертировать сигнал на передаче; 0 - не инвертировать
 */   
void MKPD_Set_InvTX(MKPD_T *pMKPD, unsigned int invTX);

/**
 * @brief Возвращает принятое от КШ слово данных 
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @return Содержимое ответного слова, 16 бит
 */   
uint32_t MKPD_Get_Endpoint_COM_Data(MKPD_T *pMKPD);

/**
 * @brief Возвращает значение флага таймаута
 * @param pMKPD: указатель на структуру с регистрами MKPD  
 * @return SET or RESET - состояние готовности к передаче
 */   
FlagStatus MKPD_Get_Endpoint_COM_Timeout(MKPD_T *pMKPD);

/**
 * @brief Возвращает значение флага ошибки в слове данных (используется в транзакциях №6, 10)
 * @param pMKPD: указатель на структуру с регистрами MKPD  
 * @return SET or RESET - состояние готовности к передаче
 */   
FlagStatus MKPD_Get_Endpoint_COM_Error(MKPD_T *pMKPD);

/**
 * @brief Возвращает командное слово, принятое ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD  
 * @return SET or RESET - состояние готовности к передаче
 */  
uint32_t MKPD_Get_Endpoint_Command_Word(MKPD_T *pMKPD);

/**
 * @brief Задание начального адреса DMA для монитора
 * @param pMKPD: указатель на структуру с регистрами MKPD  
 * @param dma_monitor_addr: начальный адрес в памяти для записи
 * @retval None
 */   
void MKPD_Set_Monitor_DMA_Address(MKPD_T *pMKPD, uint32_t dma_monitor_addr);

/**
 * @brief Задание размера буфера монитора
 * @param pMKPD: указатель на структуру с регистрами MKPD 
 * @param memory_size: количество 32-битных слов, выделенных для монитора
 * @retval None
 */   
void MKPD_Set_Monitor_Memory_Size(MKPD_T *pMKPD, uint32_t memory_size);

/**
 * @brief Задание порогового значения для монитора
 * @param pMKPD: указатель на структуру с регистрами MKPD 
 * @param threshold: количество записанных слов, при котором срабатывает прерывание монитора
 * @retval None
 */   
void MKPD_Set_Monitor_Threshold(MKPD_T *pMKPD, uint32_t threshold);

/**
 * @brief Настройка монитора
 * @param pMKPD: указатель на структуру с регистрами MKPD 
 * @param address: начальный адрес в памяти для хранения слов данных
 * @param size: количество 32-битных слов, выделенных для монитора
 * @param threshold: количество записанных слов, при котором срабатывает прерывание монитора
 * @retval None
 */
void MKPD_ConfigMonitor(MKPD_T *pMKPD, uint32_t address, uint32_t size, uint32_t threshold);


#endif /* MKPD_H_ */
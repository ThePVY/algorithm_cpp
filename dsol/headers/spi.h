/*!\file
 * \brief Этот файл содержит структуры, макросы и функции, необходимые для взаимодействия с интерфейсом SPI.
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

#ifndef SPI_H
#define SPI_H
#include "types.h"
#include "system.h"


/**
 * @brief Структура для доступа к регистрам SPI.
 */
typedef struct
{
    __RW uint32_t CR0;                                                          /**< Смещение: 0x0000 Регистр управления 0 */
    __RW uint32_t CR1;                                                          /**< Смещение: 0x0004 Регистр управления 1 */
    __RW uint32_t DR;                                                           /**< Смещение: 0x0008 Буфер FIFO приемопередатчика */
    __RO uint32_t SR;                                                           /**< Смещение: 0x000C Регистр состояния */
    __RW uint32_t CPSR;                                                         /**< Смещение: 0x0010 Регистр делителя тактовой частоты */
    __RW uint32_t IMSC;                                                         /**< Смещение: 0x0014 Регистр маски прерывания */
    __RO uint32_t RIS;                                                          /**< Смещение: 0x0018 Регистр состояния прерываний без учета маскирования */
    __RO uint32_t MIS;                                                          /**< Смещение: 0x001C Регистр состояния прерываний с учетом маскирования */
    __WO uint32_t ICR;                                                          /**< Смещение: 0x0020 Регистр сброса прерывания */
    __RW uint32_t DMACR;                                                        /**< Смещение: 0x0024 Регистр управления прямым доступом к памяти */
}SPI_T;                                                                             

/**
 * @brief Макросы и типы для регистра CR0
 */
#define SPI_CR0_DSS(x)  ((uint32_t)((x) & 0x0F))                                /**< размер слова данных 4-16 бита */
#define SPI_CR0_SCR(x)  ((uint32_t)(((x) & 0xFF) << 8))                           /**< cкорость последовательного обмена */

typedef enum 
{
    SPI_BITS_4 = ((uint32_t)(3 << 0)),		                                /**< размер слова данных 4 бита */
    SPI_BITS_5 = ((uint32_t)(4 << 0)),		                                /**< размер слова данных 5 бит */
    SPI_BITS_6 = ((uint32_t)(5 << 0)),		                                /**< размер слова данных 6 бит */
    SPI_BITS_7 = ((uint32_t)(6 << 0)),		                                /**< размер слова данных 7 бит */
    SPI_BITS_8 = ((uint32_t)(7 << 0)),		                                /**< размер слова данных 8 бит */
    SPI_BITS_9 = ((uint32_t)(8 << 0)),		                                /**< размер слова данных 9 бит */
    SPI_BITS_10 = ((uint32_t)(9 << 0)),	                                        /**< размер слова данных 10 бит */
    SPI_BITS_11 = ((uint32_t)(10 << 0)),	                                /**< размер слова данных 11 бит */
    SPI_BITS_12 = ((uint32_t)(11 << 0)),	                                /**< размер слова данных 12 бит */
    SPI_BITS_13 = ((uint32_t)(12 << 0)),	                                /**< размер слова данных 13 бит */
    SPI_BITS_14 = ((uint32_t)(13 << 0)),	                                /**< размер слова данных 14 бит */
    SPI_BITS_15 = ((uint32_t)(14 << 0)),	                                /**< размер слова данных 15 бит */
    SPI_BITS_16 = ((uint32_t)(15 << 0)),	                                /**< размер слова данных 16 бит */
}SPI_BITS_T;

typedef enum 
{
    SPI_FRF_SPI = ((uint32_t)(0 << 4)), 			                /**< протокол SPI фирмы Motorola */
    SPI_FRF_TI = ((uint32_t)(1 << 4)),     	                                /**< протокол SPI фирмы Texas Instruments */
    SPI_FRF_MICROWIRE = ((uint32_t)(2 << 4)),                                   /**< протокол Microwire фирмы National Semiconductor */
}SPI_FRAME_FORMAT_T;

typedef enum {
    SPI_CLOCK_SPH0_SPO0 = ((uint32_t)(0 << 6)),		                        
    SPI_CLOCK_SPH0_SPO1 = ((uint32_t)(1 << 6)),		                        
    SPI_CLOCK_SPH1_SPO0 = ((uint32_t)(2 << 6)),		                       
    SPI_CLOCK_SPH1_SPO1 = ((uint32_t)(3 << 6)),		                        
    SPI_CLOCK_MODE0 = SPI_CLOCK_SPH0_SPO0,                                      
    SPI_CLOCK_MODE1 = SPI_CLOCK_SPH0_SPO1,                                      
    SPI_CLOCK_MODE2 = SPI_CLOCK_SPH1_SPO0,                                      
    SPI_CLOCK_MODE3 = SPI_CLOCK_SPH1_SPO1,                                      
}SPI_CLOCK_MODE_T;

/**
 * @brief Макросы и типы для регистра CR1
 */
#define SPI_CR1_LBM_EN  ((uint32_t)(1 << 0))                                    /**< включение режима loopback */
#define SPI_CR1_SSE_EN  ((uint32_t)(1 << 1))                                    /**< разрешение работы приемопередатчика */
#define SPI_CR1_SOD_DIS ((uint32_t)(1 << 3))                                    /**< запрет выходных линий в режиме ведомого устройства */
#define SPI_CR1_BITMASK ((uint32_t)(0x0F))

typedef enum 
{
    SPI_MODE_MS_MASTER = ((uint32_t)(0 << 2)),	                                /**< режим работы - ведущий */
    SPI_MODE_MS_SLAVE = ((uint32_t)(1 << 2)),	                                /**< режим работы - ведомый */
}SPI_MODE_T;

/**
 * @brief Макросы для регистра DR
 */
#define SPI_DR_DATA(x)  ((uint32_t)((x) & 0xFFFF))                              /**< принимаемые/передаваемые данные */

/**
 * @brief Тип для регистра SR
 */
typedef enum 
{
    SPI_SR_TFE = ((uint32_t)(1 << 0)),                                          /**< маска для чтения состояния буфера FIFO передатчика (1 - пуст) */
    SPI_SR_TNF = ((uint32_t)(1 << 1)),                                          /**< маска для чтения состояния буфера FIFO передатчика (1 - не заполнен) */
    SPI_SR_RNE = ((uint32_t)(1 << 2)),                                          /**< маска для чтения состояния буфера FIFO приемника (1 - не пуст) */
    SPI_SR_RFF = ((uint32_t)(1 << 3)),                                          /**< маска для чтения состояния буфера FIFO приемника (1 - заполнен) */
    SPI_SR_BSY = ((uint32_t)(1 << 4)),                                          /**< маска для чтения состояния модуля SPI (1 - в настоящее время передает и/или принимает данные, либо буфер FIFO передатчика не пуст) */
}SPI_STATUS_T;

/**
 * @brief Макросы для регистра CPSR
 */
#define SPI_CPSR_CPSDVSR(x)     ((x) & 0xFF)                                      /**< коэффициент деления тактовой частоты */

/**
 * @brief Тип для регистра IMSC
 */
typedef enum 
{
    SPI_IMSC_RORIM = ((uint32_t)(1 << 0)),                                      /**< маскирование прерывания по переполнению буфера приемника */
    SPI_IMSC_RTIM = ((uint32_t)(1 << 1)),                                       /**< маскирование прерывания по таймауту приемника */
    SPI_IMSC_RXIM = ((uint32_t)(1 << 2)),                                       /**< маскирование прерывания по заполнению на 50% и более буфера FIFO приемника */
    SPI_IMSC_TXIM = ((uint32_t)(1 << 3)),                                       /**< маскирование прерывания по заполнению на 50% и менее буфера FIFO передатчика */
    SPI_IMSC_BITMASK = ((uint32_t)(0xF << 0)),
}SPI_INTMASK_T;

/**
 * @brief Тип для регистра RIS
 */
typedef enum 
{
    SPI_RIS_RORRIS = ((uint32_t)(1 << 0)),	                                /**< состояние прерывания по переполнению буфера приемника без маски */
    SPI_RIS_RTRIS = ((uint32_t)(1 << 1)),	                                /**< состояние прерывания по таймауту приемника без маски */
    SPI_RIS_RXRIS = ((uint32_t)(1 << 2)),	                                /**< состояние прерывания по заполнению на 50% и менее буфера FIFO приемника без маски */
    SPI_RIS_TXRIS = ((uint32_t)(1 << 3)),	                                /**< состояние прерывания по заполнению на 50% и менее буфера FIFO передатчика без маски */
}SPI_RAWINTSTATUS_T;

/**
 * @brief Тип для регистра MIS
 */
typedef enum 
{
    SPI_MIS_RORMIS = ((uint32_t)(1 << 0)),	                                /**< маскированное состояние прерывания по переполнению буфера приемника*/
    SPI_MIS_RTMIS = ((uint32_t)(1 << 1)),	                                /**< маскированное состояние прерывания по таймауту приемника */
    SPI_MIS_RXMIS = ((uint32_t)(1 << 2)),	                                /**< маскированное состояние прерывания по заполнению на 50% и менее буфера FIFO приемника */
    SPI_MIS_TXMIS = ((uint32_t)(1 << 3)),	                                /**< маскированное состояние прерывания по заполнению на 50% и менее буфера FIFO передатчика */
}SPI_MASKINTSTATUS_T;

/**
 * @brief Тип для регистра ICR
 */
typedef enum 
{
    SPI_ICR_RORIC = ((uint32_t)(1 << 0)),                                       /**< cброс прерывания по переполнению буфера приемника */
    SPI_ICR_RTIC = ((uint32_t)(1 << 1)),                                        /**< cброс прерывания по таймауту приемника */
    SPI_ICR_BITMASK = ((uint32_t)(3 << 0)),                                     /**< cброс всех прерываний */
}SPI_INTCLEAR_T;

/**
 * @brief Тип для регистра DMACR
 */
typedef enum 
{
    SPI_DMACR_RXDMAE = ((uint32_t)(1 << 0)),                                    /**< разрешение использования DMA при приеме */
    SPI_DMACR_TXDMAE = ((uint32_t)(1 << 1)),	                                /**< разрешение использования DMA при передаче */
    SPI_DMACR_BITMASK = ((uint32_t)(3 << 0)),                                   /**< разрешение использования DMA при приеме и передаче */
}SPI_DMACR_T;

/**
 * @brief Структура настройки SPI
 */
typedef struct 
{
    SPI_BITS_T bits;					                        /**< размер слова данных */
    SPI_CLOCK_MODE_T clockMode;	                                                /**< формата тактового сигнала */
    SPI_FRAME_FORMAT_T frameFormat;	                                        /**< формат слова данных */
}SPI_CONFIG_T;

/**
 * @brief Структура для работы с буфером SPI
 */
typedef struct 
{
    void      *tx_data;	                                                        /**< Указатель на передаваемые данные */
    uint32_t  tx_cnt;	                                                        /**< Счетчик переданных данных */
    void      *rx_data;	                                                        /**< Указатель на принятые данные */
    uint32_t  rx_cnt;	                                                        /**< Счетчик принятых данных */
    uint32_t  length;	                                                        /**< Длина передаваемых данных */
}SPI_DATA_SETUP_T;
  
/** Разрешение работы приемопередатчика */   
#define	SPI_Enable(gl_spi_t) (((SPI_T *)(gl_spi_t))->CR1 |= SPI_CR1_SSE_EN)
   
/** Запрещение работы приемопередатчика */
#define	SPI_Disable(gl_spi_t) (((SPI_T *)(gl_spi_t))->CR1 &= (~SPI_CR1_SSE_EN) & SPI_CR1_BITMASK)

/** Включение режима loopback */
#define	SPI_LoopBackEnable(gl_spi_t) (((SPI_T *)(gl_spi_t))->CR1 |= SPI_CR1_LBM_EN)

/** Включение DMA для SPI */
#define	SPI_DMA_Enable(gl_spi_t) (((SPI_T *)(gl_spi_t))->DMACR |= SPI_DMACR_BITMASK)

/** Выключение DMA для SPI */
#define	SPI_DMA_Disable(gl_spi_t) (((SPI_T *)(gl_spi_t))->DMACR &= ~SPI_DMACR_BITMASK)

/** Включение прерывания по заполнению на 50% и менее буфера FIFO передатчика */
#define	SPI_TXInt_Enable(gl_spi_t) (((SPI_T *)(gl_spi_t))->IMSC |= SPI_IMSC_TXIM)

/** Выключение прерывания по заполнению на 50% и менее буфера FIFO передатчика */
#define	SPI_TXInt_Disable(gl_spi_t) (((SPI_T *)(gl_spi_t))->IMSC &= (~SPI_IMSC_TXIM) & SPI_IMSC_BITMASK)

/** Включение прерывания по заполнению на 50% и более буфера FIFO приемника */
#define	SPI_RXInt_Enable(gl_spi_t) (((SPI_T *)(gl_spi_t))->IMSC |= SPI_IMSC_RXIM)

/** Выключение прерывания по заполнению на 50% и более буфера FIFO приемника */
#define	SPI_RXInt_Disable(gl_spi_t) (((SPI_T *)(gl_spi_t))->IMSC &= (~SPI_IMSC_RXIM) & SPI_IMSC_BITMASK)

/** Сброс флагов прерываний 
 *   Тип прерывания для сброса, принимает следующие значения:
 *    SPI_ICR_RORIC 
 *    SPI_ICR_RTIC 	
 */
#define	SPI_ClearIntPending(gl_spi_t,gl_spi_intclr) (((SPI_T *)(gl_spi_t))->ICR = (SPI_INTCLEAR_T)gl_spi_intclr)

/**
 * @brief Сброс SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval None.
 */
void SPI_DeInit(SPI_T *pSPI);

/**
 * @brief Инициализация SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval None.
 */
void SPI_Init(SPI_T *pSPI);

/**
 * @brief Возвращает номер модуля для использования в функциях включения/выключения SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval CtrlSPI: номер модуля.
 */
CTRL_T SPI_GetCtrlNum(SPI_T *pSPI);

/**
 * @brief Установка формата информационного кадра
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param pbits: размер слова данных, может быть SPI_BITS_4..SPI_BITS_16.
 * @param pframeFormat: формат информационного кадра.
 *         Параметр pframeFormat может принимать значения:
 *          @arg SPI_FRF_SPI: протокол SPI фирмы Motorola
 *          @arg SPI_FRF_TI: протокол SSI фирмы Texas Instruments
 *          @arg SPI_FRF_MICROWIRE: протокол Microwire фирмы National Semiconductor
 * @param pclockMode: полярность и фаза тактового сигнала. Используется только в режиме обмена SPI фирмы Motorola
 *         Параметр pclockMode может принимать значения:
 *	    @arg SPI_CLOCK_MODE0: сигнал синхронизации (CPOL) - низкий уровень, выборка данных (CPHA) - задний фронт сигнала синхронизации
 *	    @arg SPI_CLOCK_MODE1: сигнал синхронизации (CPOL) - высокий уровень, выборка данных (CPHA) - задний фронт сигнала синхронизации
 *	    @arg SPI_CLOCK_MODE2: сигнал синхронизации (CPOL) - низкий уровень, выборка данных (CPHA) - передний фронт сигнала синхронизации
 *	    @arg SPI_CLOCK_MODE3: сигнал синхронизации (CPOL) - высокий уровень, выборка данных (CPHA) - передний фронт сигнала синхронизации
 * @retval None.         
 */
void SPI_SetFormat(SPI_T *pSPI, uint32_t pbits, uint32_t pframeFormat, uint32_t pclockMode);

/**
 * @brief Установка режима работы (ведущий или ведомый).
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param pmode: режим работы, принимает следующие значения:
 *         Параметр pmode может принимать значения:
 *          @arg SPI_MODE_MASTER: режим работы - ведущий
 *          @arg SPI_MODE_SLAVE: режим работы - ведомый
 * @retval None.
 */
void SPI_Set_Mode(SPI_T *pSPI, uint32_t pmode);

/**
 * @brief Установка скорости последовательного обмена: FSSPCLKOUT=FSSPCLK/(CPSDVR*(1+SCR))
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param clk_rate: SCR - делитель частоты (1..256).
 * @param prescale: CPSDVR - четный коэффициент (2..254).
 * @retval None.
 */
void SPI_SetClockRate(SPI_T *pSPI, uint32_t clk_rate, uint32_t prescale);

/**
 * @brief Установка частоты тактового сигнала для интерфейса SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param bitRate: частота обмена.
 * @retval None.
 */
void SPI_SetBitRate(SPI_T *pSPI, uint32_t bitRate);

/**
 * @brief Получение числа бит в одном слове данных.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval Количество бит в одном слове данных минус один
 */
inline uint8_t SPI_GetDataSize(SPI_T *pSPI);

/**
 * @brief Отправка слова данных по интерфейсу SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param tx_data: данные для отправки
 * @retval None.
 */
void SPI_SendFrame(SPI_T *pSPI, uint16_t tx_data);

/**
 * @brief Прием слова данных по интерфейсу SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval Слово данных.
 */
uint16_t SPI_ReceiveFrame(SPI_T *pSPI);

/**
 * @brief Запись одного байта в буфер SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval None.
 */
void SPI_Write1BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);
/**
 * @brief Чтение одного байта из буфера SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval None.
 */
void SPI_Read1BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);

/**
 * @brief Запись двух байт в буфер SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval None.
 */
void SPI_Write2BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);
/**
 * @brief Чтение двух байт из буфера SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval None.
 */
void SPI_Read2BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);

/**
 * @brief Запись методом постоянного опроса.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param buffer: указатель на передаваемые данные.
 * @param buffer_len: размер передаваемых данных.
 * @retval tx_cnt - количество переданных данных.
 */
uint32_t SPI_WriteFrames_Blocking(SPI_T *pSPI, uint8_t *buffer, uint32_t buffer_len);

/**
 * @brief Чтение методом постоянного опроса.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param buffer: указатель на принимаемые данные.
 * @param buffer_len: размер принимаемых данных.
 * @retval rx_cnt - количество принятых данных.
 */
uint32_t SPI_ReadFrames_Blocking(SPI_T *pSPI, uint8_t *buffer, uint32_t buffer_len);

/**
 * @brief Чтение/запись 8 бит данных при помощи прерываний.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval Cтатус операции.
 */
Status SPI_Int_RWFrames8Bits(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);

/**
 * @brief Чтение/запись 16 бит данных при помощи прерываний.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval Cтатус операции.
 */
Status SPI_Int_RWFrames16Bits(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);

/**
 * @brief Очистка буфера приемника и сброс флагов прерываний.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval None.
 */
void SPI_Int_FlushData(SPI_T *pSPI);

/**
 * @brief Получение текущего статуса контроллера SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param pStat: тип статуса.
 *         Параметр pStat может принимать значения:
 *          @arg SPI_SR_TFE: буфер FIFO передатчика пуст
 *          @arg SPI_SR_TNF: буфер FIFO передатчика не заполнен
 *          @arg SPI_SR_RNE: буфер FIFO приемника не пуст
 *          @arg SPI_SR_RFF: буфер FIFO приемника заполнен
 *          @arg SPI_SR_BSY: флаг активности передачи или приема
 * @retval SET or RESET, cтатус контроллера SPI.
 */
FlagStatus SPI_GetStatus(SPI_T *pSPI, SPI_STATUS_T pStat);

/**
 * @brief Получение статуса маскированного прерывания. 
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param pMaskInt: тип маскированного прерывания. 
 *         Параметр pMaskInt может принимать значения:
 *          @arg SPI_MIS_RORMIS: состояние маскированного прерывания SSPRORINTR
 *	    @arg SPI_MIS_RTMIS: состояние маскированного прерывания SSPRTINTR
 *          @arg SPI_MIS_RXMIS: состояние маскированного прерывания SSPRXINTR
 *          @arg SPI_MIS_TXMIS: состояние маскированного прерывания SSPTXINTR
 * @retval SET or RESET, cтатус прерывания.
 */
IntStatus SPI_GetIntStatus(SPI_T *pSPI, SPI_MASKINTSTATUS_T pMaskInt);

/**
 * @brief Получение статуса прерывания. 
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param pRawInt: тип прерывания. 
 *         Параметр pMaskInt может принимать значения:
 *	    @arg SPI_MIS_RORRIS: состояние до маскирования прерывания SSPRORINTR
 *          @arg SPI_MIS_RTRIS: состояние до маскирования прерывания SSPRTINTR
 *          @arg SPI_MIS_RXRIS: состояние до маскирования прерывания SSPRXINTR
 *	    @arg SPI_MIS_TXRIS: состояние до маскирования прерывания SSPTXINTR
 * @retval SET or RESET, cтатус прерывания.
 */
IntStatus SPI_GetRawIntStatus(SPI_T *pSPI, SPI_RAWINTSTATUS_T pRawInt);


#endif /* SPI_H */

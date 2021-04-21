/*!\file
 * \brief Этот файл содержит функции, необходимые для взаимодействия с интерфейсом SPI.
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

#include "chip_5023BC016.h"
#include "system.h"
#include "spi.h"
#include "dma.h"



/**
 * @brief Сброс SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval None.
 */
void SPI_DeInit(SPI_T *pSPI) 
{
    SPI_Disable(pSPI);
    PWR_CLK_Disable(SPI_GetCtrlNum(pSPI));
    CLK_INIT_PAUSE;
    PWR_RST_Enable(SPI_GetCtrlNum(pSPI));
}

/**
 * @brief Инициализация SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval None.
 */
void SPI_Init(SPI_T *pSPI) 
{
    PWR_CLK_Enable(SPI_GetCtrlNum(pSPI));
    CLK_INIT_PAUSE;
    PWR_RST_Disable(SPI_GetCtrlNum(pSPI));
}

/**
 * @brief Возвращает номер модуля для использования в функциях включения/выключения SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval CtrlSPI: номер модуля.
 */
CTRL_T SPI_GetCtrlNum(SPI_T *pSPI)
{
    CTRL_T CtrlSPI;
    if (pSPI == SPI1)
    {
        CtrlSPI = SPI_1_CTRL_NUM;
    }
    else 
    {
        CtrlSPI = SPI_2_CTRL_NUM;
    }
    return CtrlSPI;
}

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
void SPI_SetFormat(SPI_T *pSPI, uint32_t pbits, uint32_t pframeFormat, uint32_t pclockMode)
{
	pSPI->CR0 = (pSPI->CR0 & ~0xFF) | pbits | pframeFormat | pclockMode;
}

/**
 * @brief Установка режима работы (ведущий или ведомый).
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param pmode: режим работы, принимает следующие значения:
 *         Параметр pmode может принимать значения:
 *          @arg SPI_MODE_MASTER: режим работы - ведущий
 *          @arg SPI_MODE_SLAVE: режим работы - ведомый
 * @retval None.
 */
void SPI_Set_Mode(SPI_T *pSPI, uint32_t pmode)
{
	pSPI->CR1 = (pSPI->CR1 & ~(1 << 2)) | pmode;
}

/**
 * @brief Установка скорости последовательного обмена: FSSPCLKOUT=FSSPCLK/(CPSDVR*(1+SCR))
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param clk_rate: SCR - делитель частоты (1..256).
 * @param prescale: CPSDVR - четный коэффициент (2..254).
 * @retval None.
 */
void SPI_SetClockRate(SPI_T *pSPI, uint32_t clk_rate, uint32_t prescale)
{
    uint32_t temp;
    temp = pSPI->CR0 & (~(SPI_CR0_SCR(0xFF)));
    pSPI->CR0 = temp | (SPI_CR0_SCR(clk_rate));
    pSPI->CPSR = prescale;
}

/**
 * @brief Установка частоты тактового сигнала для интерфейса SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param bitRate: частота обмена.
 * @retval None.
 */
void SPI_SetBitRate(SPI_T *pSPI, uint32_t bitRate)
{
    uint32_t SPI_clk, cr0_div, cmp_clk, prescale;
    SPI_clk = sys_freq;
    cr0_div = 0;
    cmp_clk = 0xFFFFFFFF;
    prescale = 2;
    while (cmp_clk > bitRate) 
    {
        cmp_clk = SPI_clk / ((cr0_div + 1) * prescale);
	if (cmp_clk >= bitRate) 
        {
            cr0_div++;
            if (cr0_div > 0xFF)
            {
                cr0_div = 0;
		prescale += 2;
            }
	}
    }
    SPI_SetClockRate(pSPI, cr0_div, prescale);
}

/**
 * @brief Получение числа бит в одном слове данных.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval Количество бит в одном слове данных минус один
 */
uint8_t SPI_GetDataSize(SPI_T *pSPI)
{
    return SPI_CR0_DSS(pSPI->CR0);
}

/**
 * @brief Отправка слова данных по интерфейсу SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param tx_data: данные для отправки
 * @retval None.
 */
void SPI_SendFrame(SPI_T *pSPI, uint16_t tx_data)
{
    pSPI->DR = SPI_DR_DATA(tx_data);
}

/**
 * @brief Прием слова данных по интерфейсу SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval Слово данных.
 */
uint16_t SPI_ReceiveFrame(SPI_T *pSPI)
{
    return (uint16_t)(SPI_DR_DATA(pSPI->DR));
}

/**
 * @brief Запись одного байта в буфер SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval None.
 */
void SPI_Write1BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup) 
{
    if (xf_setup->tx_data)
    {
        SPI_SendFrame(pSPI,
	(*(uint8_t *) ((uint32_t) xf_setup->tx_data + xf_setup->tx_cnt)));
    }
    else 
    {
	SPI_SendFrame(pSPI, 0xFF);
    }
    xf_setup->tx_cnt++;
}

/**
 * @brief Чтение одного байта из буфера SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval None.
 */
void SPI_Read1BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup)
{
    uint16_t rDat;
    while ((SPI_GetStatus(pSPI, SPI_SR_RNE) == SET) && (xf_setup->rx_cnt < xf_setup->length)) 
    {
        rDat = SPI_ReceiveFrame(pSPI);
	if (xf_setup->rx_data)
        {
            *(uint8_t *) ((uint32_t) xf_setup->rx_data + xf_setup->rx_cnt) = rDat;
        }
	xf_setup->rx_cnt++;
    }
}

/**
 * @brief Запись двух байт в буфер SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval None.
 */
void SPI_Write2BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup) 
{
    if (xf_setup->tx_data)
    {
        SPI_SendFrame(pSPI, (*(uint16_t *) ((uint32_t) xf_setup->tx_data + xf_setup->tx_cnt)));
    }
    else 
    {
        SPI_SendFrame(pSPI, 0xFFFF);
    }
    xf_setup->tx_cnt += 2;
}

/**
 * @brief Чтение двух байт из буфера SPI.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval None.
 */
void SPI_Read2BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup)
{
    uint16_t rDat;
    while ((SPI_GetStatus(pSPI, SPI_SR_RNE) == SET) && (xf_setup->rx_cnt < xf_setup->length))
    {
        rDat = SPI_ReceiveFrame(pSPI);
	if (xf_setup->rx_data) 
        {
            *(uint16_t *) ((uint32_t) xf_setup->rx_data + xf_setup->rx_cnt) = rDat;
        }
	xf_setup->rx_cnt += 2;
    }
}

/**
 * @brief Чтение/запись методом постоянного опроса.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval Указатель на принятые/записанные данные или статус операции.
 */
uint32_t SPI_RWFrames_Blocking(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup)
{
    /* Очистка FIFO приемника */
    while (SPI_GetStatus(pSPI, SPI_SR_RNE)) 
    {
        SPI_ReceiveFrame(pSPI);
    }
    /* Очистка статуса */
    SPI_ClearIntPending(pSPI, SPI_ICR_BITMASK);
    if (SPI_GetDataSize(pSPI) > SPI_BITS_8)
    {
        while (xf_setup->rx_cnt < xf_setup->length || xf_setup->tx_cnt < xf_setup->length) 
        {
            /* запись данных в буфер */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (xf_setup->tx_cnt < xf_setup->length)) 
            {
                SPI_Write2BFifo(pSPI, xf_setup);
            }
            /* проверка наличия ошибки по переполнению */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /* проверка наличия данных в FIFO приемника*/
            SPI_Read2BFifo(pSPI, xf_setup);
	}
    }
    else 
    {
        while (xf_setup->rx_cnt < xf_setup->length || xf_setup->tx_cnt < xf_setup->length) 
        {
            /* запись данных в буфер */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (xf_setup->tx_cnt < xf_setup->length)) 
            {
                SPI_Write1BFifo(pSPI, xf_setup);
            }
            /* проверка наличия ошибки по переполнению */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /* проверка наличия данных в FIFO приемника*/
            SPI_Read1BFifo(pSPI, xf_setup);
	}
    }
    if (xf_setup->tx_data)
    {
        return xf_setup->tx_cnt;
    }
    else if (xf_setup->rx_data) 
    {
	return xf_setup->rx_cnt;
    }
    return ERROR;
}

/**
 * @brief Запись методом постоянного опроса.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param buffer: указатель на передаваемые данные.
 * @param buffer_len: размер передаваемых данных.
 * @retval tx_cnt - количество переданных данных.
 */
uint32_t SPI_WriteFrames_Blocking(SPI_T *pSPI, uint8_t *buffer, uint32_t buffer_len) 
{
    uint32_t tx_cnt = 0, rx_cnt = 0;
    /* Очистка FIFO приемника*/
    while (SPI_GetStatus(pSPI, SPI_SR_RNE))
    {
        SPI_ReceiveFrame(pSPI);
    }
    /* Очистка статуса */
    SPI_ClearIntPending(pSPI, SPI_ICR_BITMASK);
    if (SPI_GetDataSize(pSPI) > SPI_BITS_8)
    {
        uint16_t *wdata16;
	wdata16 = (uint16_t *) buffer;
        while (tx_cnt < buffer_len || rx_cnt < buffer_len)
        {
            /* запись данных в буфер */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (tx_cnt < buffer_len)) 
            {
                SPI_SendFrame(pSPI, *wdata16);
                wdata16++;
		tx_cnt += 2;
            }
            /* проверка наличия ошибки по переполнению */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /* проверка наличия данных в FIFO приемника*/
            while (SPI_GetStatus(pSPI, SPI_SR_RNE) == SET)
            {
                SPI_ReceiveFrame(pSPI);
                rx_cnt += 2;
            }
        }
    }
    else 
    {
        uint8_t *wdata8;
	wdata8 = buffer;
	while (tx_cnt < buffer_len || rx_cnt < buffer_len)
        {
            /* запись данных в буфер */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (tx_cnt < buffer_len))
            {
                SPI_SendFrame(pSPI, *wdata8);
		wdata8++;
		tx_cnt++;
            }
            /* проверка наличия ошибки по переполнению */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET) 
            {
                return ERROR;
            }
            /* проверка наличия данных в FIFO приемника*/
            while (SPI_GetStatus(pSPI, SPI_SR_RNE) == SET && rx_cnt < buffer_len) 
            {
		SPI_ReceiveFrame(pSPI);
		rx_cnt++;
            }
	}
    }
    return tx_cnt;
}

/**
 * @brief Чтение методом постоянного опроса.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param buffer: указатель на принимаемые данные.
 * @param buffer_len: размер принимаемых данных.
 * @retval rx_cnt - количество принятых данных.
 */
uint32_t SPI_ReadFrames_Blocking(SPI_T *pSPI, uint8_t *buffer, uint32_t buffer_len) 
{
    uint32_t rx_cnt = 0, tx_cnt = 0;
    /* Очистка FIFO приемника*/
    while (SPI_GetStatus(pSPI, SPI_SR_RNE))
    {
	SPI_ReceiveFrame(pSPI);
    }
    /* Очистка статуса */
    SPI_ClearIntPending(pSPI, SPI_ICR_BITMASK);
    if (SPI_GetDataSize(pSPI) > SPI_BITS_8) 
    {
        uint16_t *rdata16;
	rdata16 = (uint16_t *) buffer;
	while (tx_cnt < buffer_len || rx_cnt < buffer_len) 
        {
            /* запись данных в буфер */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (tx_cnt < buffer_len)) 
            {
                SPI_SendFrame(pSPI, 0xFFFF);
		tx_cnt += 2;
            }
            /* проверка наличия ошибки по переполнению */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /* проверка наличия данных в FIFO приемника*/
            while (SPI_GetStatus(pSPI, SPI_SR_RNE) == SET && rx_cnt < buffer_len)
            {
                *rdata16 = SPI_ReceiveFrame(pSPI);
		rdata16++;
		rx_cnt += 2;
            }
	}
    }
    else 
    {
        uint8_t *rdata8;
	rdata8 = buffer;
	while (tx_cnt < buffer_len || rx_cnt < buffer_len)
        {
            /* запись данных в буфер */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (tx_cnt < buffer_len)) 
            {
                SPI_SendFrame(pSPI, 0xFF);
		tx_cnt++;
            }
            /* проверка наличия ошибки по переполнению */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /* проверка наличия данных в FIFO приемника*/
            while (SPI_GetStatus(pSPI, SPI_SR_RNE) == SET && rx_cnt < buffer_len) 
            {
                *rdata8 = SPI_ReceiveFrame(pSPI);
		rdata8++;
		rx_cnt++;
            }
        }
    }
    return rx_cnt;
}

/**
 * @brief Чтение/запись 8 бит данных при помощи прерываний.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval Cтатус операции.
 */
Status SPI_Int_RWFrames8Bits(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup)
{
    /* проверка наличия ошибки по переполнению в регистре RIS */
    if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET) 
    {
        return ERROR;
    }
    if ((xf_setup->tx_cnt != xf_setup->length) || (xf_setup->rx_cnt != xf_setup->length)) 
    {
        /* прооверка наличия данных в FIFO приемника */
        SPI_Read1BFifo(pSPI, xf_setup);
	if ((SPI_GetStatus(pSPI, SPI_SR_TNF)) && (xf_setup->tx_cnt != xf_setup->length)) 
        {
            /* запись данных в буфер */
            SPI_Write1BFifo(pSPI, xf_setup);
            /* проверка наличия ошибки по переполнению в регистре RIS */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /*  проверка наличия данных в FIFO приемника */
            SPI_Read1BFifo(pSPI, xf_setup);
	}
        return SUCCESS;
    }
    return ERROR;
}

/**
 * @brief Чтение/запись 16 бит данных при помощи прерываний.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @param xf_setup: указатель на структуру для работы с буфером SPI.
 * @retval Cтатус операции.
 */
Status SPI_Int_RWFrames16Bits(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup) 
{
    /* проверка наличия ошибки по переполнению в регистре RIS */
    if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
    {
        return ERROR;
    }
    if ((xf_setup->tx_cnt != xf_setup->length) || (xf_setup->rx_cnt != xf_setup->length)) 
    {
	/* проверка наличия данных в FIFO приемника */
	SPI_Read2BFifo(pSPI, xf_setup);
	if ((SPI_GetStatus(pSPI, SPI_SR_TNF)) && (xf_setup->tx_cnt != xf_setup->length)) 
        {
            /* запись данных в буфер */
            SPI_Write2BFifo(pSPI, xf_setup);
            /* проверка наличия ошибки по переполнению в регистре RIS */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /*  проверка наличия данных в FIFO приемника */
            SPI_Read2BFifo(pSPI, xf_setup);
	}
	return SUCCESS;
    }
    return ERROR;
}

/**
 * @brief Очистка буфера приемника и сброс флагов прерываний.
 * @param pSPI: указатель на структуру с регистрами SPI.
 * @retval None.
 */
void SPI_Int_FlushData(SPI_T *pSPI) 
{
    if (SPI_GetStatus(pSPI, SPI_SR_BSY)) 
    {
        while (SPI_GetStatus(pSPI, SPI_SR_BSY)) 
        {
	}
    }
    /* Очистка FIFO приемника*/
    while (SPI_GetStatus(pSPI, SPI_SR_RNE)) 
    {
        SPI_ReceiveFrame(pSPI);
    }
    /* Очистка статуса */
    SPI_ClearIntPending(pSPI, SPI_ICR_BITMASK);
}

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
FlagStatus SPI_GetStatus(SPI_T *pSPI, SPI_STATUS_T pStat)
{
//    return (pSPI->SR & pStat) ? SET : RESET;
      if (pSPI->SR & pStat)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
}

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
IntStatus SPI_GetIntStatus(SPI_T *pSPI, SPI_MASKINTSTATUS_T pMaskInt)
{
//    return (pSPI->MIS & pMaskInt) ? SET : RESET;
      if (pSPI->MIS & pMaskInt)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
        
}

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
IntStatus SPI_GetRawIntStatus(SPI_T *pSPI, SPI_RAWINTSTATUS_T pRawInt)
{
//    return (pSPI->RIS & pRawInt) ? SET : RESET;
      if (pSPI->RIS & pRawInt)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
}


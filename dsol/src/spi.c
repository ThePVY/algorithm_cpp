/*!\file
 * \brief ���� ���� �������� �������, ����������� ��� �������������� � ����������� SPI.
 *
 * Copyright(C) ��� �������� �������, 2018
 * Copyright(C) ������� ������������� ��� �������� �������
 * ��� ����� ��������.
 *
 * ����������� �����������, ��������� � ���� �����, ������������� ������ ��� 
 * ���������������� �����, � ������������� ������������� ���������� � ��������� 
 * ����������� "�������� �������". ��� ����������� ����������� ������������ "��� ����" 
 * ��� �����-���� ��������, "�������� �������" ������������ �� ����� ��������, 
 * ����������� ��� ���������������, ������� ��� ��������������� �������� �������� �����������, 
 * ����������� ��� ���������� ���� � ���������� ���� ���������������� �������������. 
 * ����������� "�������� �������" �� ����� ������� ��������������� �� ������������� 
 * ������������ �����������, �� ������������� �������� ��� ���� �� ������, ��������� �����, 
 * ��� ����� ������ ����� ���������������� �������������, �� �����-���� ��������. 
 * ����������� "�������� �������" ��������� �� ����� ����� ������� ��������� � ����������� 
 * ����������� ��� �����������. ����������� "�������� �������" ����� �� ���� ������� 
 * ��������� ��� ��������, ��� ��� ����������� ���������� �������� ��� ������������� 
 * ��� ����������� ������������ ��� �����������.
 *
 * ���������� �� �������������, �����������, ��������� � ��������������� ����� ������������ 
 * ����������� � ������������ ��������������� �������� �������� "�������� �������" � 
 * ��������������� ��������� ���� ����� �������� ��� ������, ��� �������, 
 * ��� ��� ����������� ����������� ������������ ��������� � ������������������ �����������
 * "�������� �������". ��� ����� ������ ���������������� �� ���� ������ ����� ����.
 */

#include "chip_5023BC016.h"
#include "system.h"
#include "spi.h"
#include "dma.h"



/**
 * @brief ����� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
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
 * @brief ������������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @retval None.
 */
void SPI_Init(SPI_T *pSPI) 
{
    PWR_CLK_Enable(SPI_GetCtrlNum(pSPI));
    CLK_INIT_PAUSE;
    PWR_RST_Disable(SPI_GetCtrlNum(pSPI));
}

/**
 * @brief ���������� ����� ������ ��� ������������� � �������� ���������/���������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @retval CtrlSPI: ����� ������.
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
 * @brief ��������� ������� ��������������� �����
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param pbits: ������ ����� ������, ����� ���� SPI_BITS_4..SPI_BITS_16.
 * @param pframeFormat: ������ ��������������� �����.
 *         �������� pframeFormat ����� ��������� ��������:
 *          @arg SPI_FRF_SPI: �������� SPI ����� Motorola
 *          @arg SPI_FRF_TI: �������� SSI ����� Texas Instruments
 *          @arg SPI_FRF_MICROWIRE: �������� Microwire ����� National Semiconductor
 * @param pclockMode: ���������� � ���� ��������� �������. ������������ ������ � ������ ������ SPI ����� Motorola
 *         �������� pclockMode ����� ��������� ��������:
 *	    @arg SPI_CLOCK_MODE0: ������ ������������� (CPOL) - ������ �������, ������� ������ (CPHA) - ������ ����� ������� �������������
 *	    @arg SPI_CLOCK_MODE1: ������ ������������� (CPOL) - ������� �������, ������� ������ (CPHA) - ������ ����� ������� �������������
 *	    @arg SPI_CLOCK_MODE2: ������ ������������� (CPOL) - ������ �������, ������� ������ (CPHA) - �������� ����� ������� �������������
 *	    @arg SPI_CLOCK_MODE3: ������ ������������� (CPOL) - ������� �������, ������� ������ (CPHA) - �������� ����� ������� �������������
 * @retval None.         
 */
void SPI_SetFormat(SPI_T *pSPI, uint32_t pbits, uint32_t pframeFormat, uint32_t pclockMode)
{
	pSPI->CR0 = (pSPI->CR0 & ~0xFF) | pbits | pframeFormat | pclockMode;
}

/**
 * @brief ��������� ������ ������ (������� ��� �������).
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param pmode: ����� ������, ��������� ��������� ��������:
 *         �������� pmode ����� ��������� ��������:
 *          @arg SPI_MODE_MASTER: ����� ������ - �������
 *          @arg SPI_MODE_SLAVE: ����� ������ - �������
 * @retval None.
 */
void SPI_Set_Mode(SPI_T *pSPI, uint32_t pmode)
{
	pSPI->CR1 = (pSPI->CR1 & ~(1 << 2)) | pmode;
}

/**
 * @brief ��������� �������� ����������������� ������: FSSPCLKOUT=FSSPCLK/(CPSDVR*(1+SCR))
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param clk_rate: SCR - �������� ������� (1..256).
 * @param prescale: CPSDVR - ������ ����������� (2..254).
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
 * @brief ��������� ������� ��������� ������� ��� ���������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param bitRate: ������� ������.
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
 * @brief ��������� ����� ��� � ����� ����� ������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @retval ���������� ��� � ����� ����� ������ ����� ����
 */
uint8_t SPI_GetDataSize(SPI_T *pSPI)
{
    return SPI_CR0_DSS(pSPI->CR0);
}

/**
 * @brief �������� ����� ������ �� ���������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param tx_data: ������ ��� ��������
 * @retval None.
 */
void SPI_SendFrame(SPI_T *pSPI, uint16_t tx_data)
{
    pSPI->DR = SPI_DR_DATA(tx_data);
}

/**
 * @brief ����� ����� ������ �� ���������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @retval ����� ������.
 */
uint16_t SPI_ReceiveFrame(SPI_T *pSPI)
{
    return (uint16_t)(SPI_DR_DATA(pSPI->DR));
}

/**
 * @brief ������ ������ ����� � ����� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
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
 * @brief ������ ������ ����� �� ������ SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
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
 * @brief ������ ���� ���� � ����� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
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
 * @brief ������ ���� ���� �� ������ SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
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
 * @brief ������/������ ������� ����������� ������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
 * @retval ��������� �� ��������/���������� ������ ��� ������ ��������.
 */
uint32_t SPI_RWFrames_Blocking(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup)
{
    /* ������� FIFO ��������� */
    while (SPI_GetStatus(pSPI, SPI_SR_RNE)) 
    {
        SPI_ReceiveFrame(pSPI);
    }
    /* ������� ������� */
    SPI_ClearIntPending(pSPI, SPI_ICR_BITMASK);
    if (SPI_GetDataSize(pSPI) > SPI_BITS_8)
    {
        while (xf_setup->rx_cnt < xf_setup->length || xf_setup->tx_cnt < xf_setup->length) 
        {
            /* ������ ������ � ����� */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (xf_setup->tx_cnt < xf_setup->length)) 
            {
                SPI_Write2BFifo(pSPI, xf_setup);
            }
            /* �������� ������� ������ �� ������������ */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /* �������� ������� ������ � FIFO ���������*/
            SPI_Read2BFifo(pSPI, xf_setup);
	}
    }
    else 
    {
        while (xf_setup->rx_cnt < xf_setup->length || xf_setup->tx_cnt < xf_setup->length) 
        {
            /* ������ ������ � ����� */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (xf_setup->tx_cnt < xf_setup->length)) 
            {
                SPI_Write1BFifo(pSPI, xf_setup);
            }
            /* �������� ������� ������ �� ������������ */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /* �������� ������� ������ � FIFO ���������*/
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
 * @brief ������ ������� ����������� ������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param buffer: ��������� �� ������������ ������.
 * @param buffer_len: ������ ������������ ������.
 * @retval tx_cnt - ���������� ���������� ������.
 */
uint32_t SPI_WriteFrames_Blocking(SPI_T *pSPI, uint8_t *buffer, uint32_t buffer_len) 
{
    uint32_t tx_cnt = 0, rx_cnt = 0;
    /* ������� FIFO ���������*/
    while (SPI_GetStatus(pSPI, SPI_SR_RNE))
    {
        SPI_ReceiveFrame(pSPI);
    }
    /* ������� ������� */
    SPI_ClearIntPending(pSPI, SPI_ICR_BITMASK);
    if (SPI_GetDataSize(pSPI) > SPI_BITS_8)
    {
        uint16_t *wdata16;
	wdata16 = (uint16_t *) buffer;
        while (tx_cnt < buffer_len || rx_cnt < buffer_len)
        {
            /* ������ ������ � ����� */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (tx_cnt < buffer_len)) 
            {
                SPI_SendFrame(pSPI, *wdata16);
                wdata16++;
		tx_cnt += 2;
            }
            /* �������� ������� ������ �� ������������ */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /* �������� ������� ������ � FIFO ���������*/
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
            /* ������ ������ � ����� */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (tx_cnt < buffer_len))
            {
                SPI_SendFrame(pSPI, *wdata8);
		wdata8++;
		tx_cnt++;
            }
            /* �������� ������� ������ �� ������������ */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET) 
            {
                return ERROR;
            }
            /* �������� ������� ������ � FIFO ���������*/
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
 * @brief ������ ������� ����������� ������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param buffer: ��������� �� ����������� ������.
 * @param buffer_len: ������ ����������� ������.
 * @retval rx_cnt - ���������� �������� ������.
 */
uint32_t SPI_ReadFrames_Blocking(SPI_T *pSPI, uint8_t *buffer, uint32_t buffer_len) 
{
    uint32_t rx_cnt = 0, tx_cnt = 0;
    /* ������� FIFO ���������*/
    while (SPI_GetStatus(pSPI, SPI_SR_RNE))
    {
	SPI_ReceiveFrame(pSPI);
    }
    /* ������� ������� */
    SPI_ClearIntPending(pSPI, SPI_ICR_BITMASK);
    if (SPI_GetDataSize(pSPI) > SPI_BITS_8) 
    {
        uint16_t *rdata16;
	rdata16 = (uint16_t *) buffer;
	while (tx_cnt < buffer_len || rx_cnt < buffer_len) 
        {
            /* ������ ������ � ����� */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (tx_cnt < buffer_len)) 
            {
                SPI_SendFrame(pSPI, 0xFFFF);
		tx_cnt += 2;
            }
            /* �������� ������� ������ �� ������������ */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /* �������� ������� ������ � FIFO ���������*/
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
            /* ������ ������ � ����� */
            if ((SPI_GetStatus(pSPI, SPI_SR_TNF) == SET) && (tx_cnt < buffer_len)) 
            {
                SPI_SendFrame(pSPI, 0xFF);
		tx_cnt++;
            }
            /* �������� ������� ������ �� ������������ */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /* �������� ������� ������ � FIFO ���������*/
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
 * @brief ������/������ 8 ��� ������ ��� ������ ����������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
 * @retval C����� ��������.
 */
Status SPI_Int_RWFrames8Bits(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup)
{
    /* �������� ������� ������ �� ������������ � �������� RIS */
    if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET) 
    {
        return ERROR;
    }
    if ((xf_setup->tx_cnt != xf_setup->length) || (xf_setup->rx_cnt != xf_setup->length)) 
    {
        /* ��������� ������� ������ � FIFO ��������� */
        SPI_Read1BFifo(pSPI, xf_setup);
	if ((SPI_GetStatus(pSPI, SPI_SR_TNF)) && (xf_setup->tx_cnt != xf_setup->length)) 
        {
            /* ������ ������ � ����� */
            SPI_Write1BFifo(pSPI, xf_setup);
            /* �������� ������� ������ �� ������������ � �������� RIS */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /*  �������� ������� ������ � FIFO ��������� */
            SPI_Read1BFifo(pSPI, xf_setup);
	}
        return SUCCESS;
    }
    return ERROR;
}

/**
 * @brief ������/������ 16 ��� ������ ��� ������ ����������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
 * @retval C����� ��������.
 */
Status SPI_Int_RWFrames16Bits(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup) 
{
    /* �������� ������� ������ �� ������������ � �������� RIS */
    if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
    {
        return ERROR;
    }
    if ((xf_setup->tx_cnt != xf_setup->length) || (xf_setup->rx_cnt != xf_setup->length)) 
    {
	/* �������� ������� ������ � FIFO ��������� */
	SPI_Read2BFifo(pSPI, xf_setup);
	if ((SPI_GetStatus(pSPI, SPI_SR_TNF)) && (xf_setup->tx_cnt != xf_setup->length)) 
        {
            /* ������ ������ � ����� */
            SPI_Write2BFifo(pSPI, xf_setup);
            /* �������� ������� ������ �� ������������ � �������� RIS */
            if (SPI_GetRawIntStatus(pSPI, SPI_RIS_RORRIS) == SET)
            {
                return ERROR;
            }
            /*  �������� ������� ������ � FIFO ��������� */
            SPI_Read2BFifo(pSPI, xf_setup);
	}
	return SUCCESS;
    }
    return ERROR;
}

/**
 * @brief ������� ������ ��������� � ����� ������ ����������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
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
    /* ������� FIFO ���������*/
    while (SPI_GetStatus(pSPI, SPI_SR_RNE)) 
    {
        SPI_ReceiveFrame(pSPI);
    }
    /* ������� ������� */
    SPI_ClearIntPending(pSPI, SPI_ICR_BITMASK);
}

/**
 * @brief ��������� �������� ������� ����������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param pStat: ��� �������.
 *         �������� pStat ����� ��������� ��������:
 *          @arg SPI_SR_TFE: ����� FIFO ����������� ����
 *          @arg SPI_SR_TNF: ����� FIFO ����������� �� ��������
 *          @arg SPI_SR_RNE: ����� FIFO ��������� �� ����
 *          @arg SPI_SR_RFF: ����� FIFO ��������� ��������
 *          @arg SPI_SR_BSY: ���� ���������� �������� ��� ������
 * @retval SET or RESET, c����� ����������� SPI.
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
 * @brief ��������� ������� �������������� ����������. 
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param pMaskInt: ��� �������������� ����������. 
 *         �������� pMaskInt ����� ��������� ��������:
 *          @arg SPI_MIS_RORMIS: ��������� �������������� ���������� SSPRORINTR
 *	    @arg SPI_MIS_RTMIS: ��������� �������������� ���������� SSPRTINTR
 *          @arg SPI_MIS_RXMIS: ��������� �������������� ���������� SSPRXINTR
 *          @arg SPI_MIS_TXMIS: ��������� �������������� ���������� SSPTXINTR
 * @retval SET or RESET, c����� ����������.
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
 * @brief ��������� ������� ����������. 
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param pRawInt: ��� ����������. 
 *         �������� pMaskInt ����� ��������� ��������:
 *	    @arg SPI_MIS_RORRIS: ��������� �� ������������ ���������� SSPRORINTR
 *          @arg SPI_MIS_RTRIS: ��������� �� ������������ ���������� SSPRTINTR
 *          @arg SPI_MIS_RXRIS: ��������� �� ������������ ���������� SSPRXINTR
 *	    @arg SPI_MIS_TXRIS: ��������� �� ������������ ���������� SSPTXINTR
 * @retval SET or RESET, c����� ����������.
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


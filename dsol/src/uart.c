/*!\file
 * \brief ���� ���� �������� �������, ����������� ��� �������������� � ���������� ������� UART.
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

#include <system.h>
#include "dma.h"
#include "chip_5023BC016.h"
#include "uart.h"


/*****************************************************************************
 * ������� �������
 ****************************************************************************/

/** ���������� ����� ������ ��� ������������� � �������� ���������/���������� ��������� ������� � ������ ������ */
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
 * ����� �������
 ****************************************************************************/

/**
 * @brief ����� ������ ����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param IntClear: ��� ���������� ��� ������, ��������� ��������� ��������:
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

/* ������������� UART */
void UART_Init(UART_T *pUART)
{
    PWR_CLK_Enable(UART_GetCtrlNum(pUART)); 
    CLK_INIT_PAUSE;

    PWR_RST_Disable(UART_GetCtrlNum(pUART));    
    /* ��������� ����������� */
    UART_Disable(pUART);
    UART_RXDisable(pUART);
    UART_TXDisable(pUART);
    /* ���������� ���������� */
    UART_IntDisable(pUART, UART_IMSC_BITMASK);
}


/* ������������� UART */
void UART_DeInit(UART_T *pUART)
{
    /* ���������� ���������� */
    UART_IntDisable(pUART, UART_IMSC_BITMASK);
    /* ���������� UART */
    UART_RXDisable(pUART);
    UART_TXDisable(pUART);
    UART_Disable(pUART);
    PWR_CLK_Disable(UART_GetCtrlNum(pUART)); CLK_INIT_PAUSE;
    PWR_RST_Enable(UART_GetCtrlNum(pUART));
}

/**
 * @brief ��������� ������� ���������� �� ���������� ������ ���������/�����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param rxfifolimit: ����� ���������� �� ���������� ������ ���������
 * @param txfifolimit: ����� ���������� �� ���������� ������ �����������
 */
void UART_SetupFIFOS(UART_T *pUART, UART_IFLS rxfifolimit, UART_IFLS txfifolimit)
{
    pUART->IFLS = (rxfifolimit << 3) | txfifolimit;
}


/**
 * @brief ��������� ������� �������������� ����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param MaskInt: ��� ����������, ��������� ��������� ��������:
 *						- UART_MIS_RXMIS
 *						- UART_MIS_TXMIS
 *						- UART_MIS_RTMIS
 *						- UART_MIS_FEMIS
 *                                              - UART_MIS_PEMIS 
 *                                              - UART_MIS_BEMIS 
 *                                              - UART_MIS_OEMIS 
 * @return ������ ����������, SET or RESET
 */
uint32_t UART_GetIntStatus(UART_T *pUART, UART_MASKINTSTATUS_T MaskInt)
{
	return (pUART->MIS & MaskInt) ? 1 : 0;
}


/**
 * @brief ��������� �������� �������� �������� ������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param IBRD: ����� ����� �������� �������� �������� ������
 * @param FBRD: ������� ����� �������� �������� �������� ������
 */
 void UART_SetDivisor(UART_T *pUART, uint32_t IBRD, uint32_t FBRD)
{
    pUART->IBRD = UART_IBRD_BAUDDIV_INT(IBRD);
    pUART->FBRD = UART_FBRD_BAUDDIV_FRAC(FBRD);
}

/**
 * @brief ���������� ���������� �� UART'�
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param IntMask: ��� ����������, ��������� ��������� ��������:
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
 * @brief ����� ������ ����� �� UART'�
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @return �������� ����
 */
 uint8_t UART_ReadByte(UART_T *pUART)
{
    return (uint8_t) (pUART->DR);
}

/**
 * @brief ���������� ���������� �� UART'�
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param IntMask: ��� ����������, ��������� ��������� ��������:
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
 * @brief ��������� ����� ����� ������, ����� �������� ��� � �������� ��������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param config: ��������� UART, ���������� �������� ��������, ������������ ��� LCR_H, ��������: (UART_LCR_H_PEN | UART_LCR_H_EPS_EVEN | UART_LCR_H_STP1 | UART_LCR_H_FEN | UART_LCR_H_WLEN8 | UART_LCR_H_SPS_DIS)
 */
 void UART_Config(UART_T *pUART, uint32_t config)
{
    pUART->LCR_H = config;
}


/**
 * @brief ��������� �������� ������� UART �����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param Stat: ��� �������, ��������� ��������� ��������:
 *						- UART_FR_BUSY
 *						- UART_FR_RXFE
 *						- UART_FR_TXFF
 *						- UART_FR_RXFF
 *						- UART_FR_TXFE
                                                - UART_FR_RI   
 * @return ������ UART �����������, SET or RESET

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

/* �������� ������� ���� �� UART'�, ��� �������� ������������ FIFO ����������� */
uint32_t UART_Send(UART_T *pUART, const void *data, uint32_t numBytes)
{
    int sent = 0; 
     
     
    uint8_t *p8 = (uint8_t *) data;
    /* �������� ������ ���� FIFO ����������� �� ����� ��� �� ����������� ������ */
    while ((sent < numBytes) && (!(UART_GetStatus(pUART, UART_FR_TXFF)))) 
    {
        UART_SendByte(pUART, *p8);
	p8++;
        sent++;
    }
    return sent;
}

/**
 * @brief ���������� ������ UART
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
 void UART_Disable(UART_T *pUART)
{
    pUART->CR &= (~UART_CR_UARTEN) & UART_CR_BITMASK;;
}

/**
 * @brief ���������� ������ �����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
 void UART_TXEnable(UART_T *pUART)
{
    pUART->CR |= UART_CR_TXE;
}

/**
 * @brief ���������� ������ �����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
 void UART_TXDisable(UART_T *pUART)
{
    pUART->CR &= (~UART_CR_TXE) & UART_CR_BITMASK;
}

/**
 * @brief ���������� ������ UART
 * @param pUART: ��������� �� ��������� � ���������� UART
 */

void UART_Enable(UART_T *pUART)
{
    pUART->CR |= UART_CR_UARTEN;
}  

/**
 * @brief ���������� ������ ���������
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
 void UART_RXEnable(UART_T *pUART)
{
    pUART->CR |= UART_CR_RXE;
}

/**
 * @brief ���������� ������ ���������
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
 void UART_RXDisable(UART_T *pUART)
{
    pUART->CR &= (~UART_CR_RXE) & UART_CR_BITMASK;;
}

/**
 * @brief �������� ������ ����� �� UART'�
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param data: ���� ��� ��������
 */
 void UART_SendByte(UART_T *pUART, uint8_t data)
{
    pUART->DR = ((uint32_t) data) & UART_DR_MASK_DATA;
  //  pUART->DR = ((uint32_t) data);
}

/* �������� ������� ���� �� UART'�, � ��������� ������������ FIFO ����������� */
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

/* ����� ������� ���� �� UART'�, ��� �������� ���������� ���������� ������� ��������� */
uint32_t UART_Read(UART_T *pUART, void *data, uint32_t numBytes)
{
    int readBytes = 0;
    uint8_t *p8 = (uint8_t *) data;
    /* ��������� ������ ���� FIFO ��������� �� ���� ��� �� ������� ����������� ����� ������ */
    while ((readBytes < numBytes) && (!(UART_GetStatus(pUART, UART_FR_RXFE)))) 
    {
	*p8 = UART_ReadByte(pUART);
	p8++;
	readBytes++;
    }
    return readBytes;
}

/* ����� ������� ���� �� UART'�, � ��������� ���������� ���������� ������� ��������� */
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

/* ���������� ���������� UART �� ������ ������ ��� ��������� ������� */
void UART_RXIntHandlerRB(UART_T *pUART, RINGBUFF_T *pRB)
{
    while (!(UART_GetStatus(pUART, UART_FR_RXFE))) 
    {
	uint8_t ch = UART_ReadByte(pUART);
	RingBuffer_Insert(pRB, &ch);
    }
}

/* ���������� ���������� UART �� �������� ������ ��� ��������� ������� */
void UART_TXIntHandlerRB(UART_T *pUART, RINGBUFF_T *pRB)
{
    uint8_t ch;
    while (!(UART_GetStatus(pUART, UART_FR_TXFF)) && RingBuffer_Pop(pRB, &ch))
    {
	UART_SendByte(pUART, ch);
    }

    /* ���������� ����������, ���� ��������� ����� ���� */
    if (RingBuffer_IsEmpty(pRB))
    {
	UART_IntDisable(pUART, UART_IMSC_TXIM);
    }
}

/* ������ ������ � ��������� ����� � ������ �������� */
uint32_t UART_SendRB(UART_T *pUART, RINGBUFF_T *pRB, const void *data, uint32_t bytes)
{
    uint32_t ret;
    uint8_t ch;
    uint8_t *p8 = (uint8_t *) data;
    /* ���������� ���������� �� �������� �� ����� ������ � ��������� ������� */
    UART_IntDisable(pUART, UART_IMSC_TXIM);
    /* ���������� ���������� ������ ������� */
    ret = RingBuffer_InsertMult(pRB, p8, bytes);
    while (!(UART_GetStatus(pUART, UART_FR_TXFF)) && RingBuffer_Pop(pRB, &ch)) 
    {
	UART_SendByte(pUART, ch);
    }
    /**�������� ������, ���� �������� */
    ret += RingBuffer_InsertMult(pRB, (p8 + ret), (bytes - ret));
    /* ��������� ���������� �� �������� */
    UART_IntEnable(pUART, UART_IMSC_TXIM);
    return ret;
}

/* ������ ������ �� ���������� ������ ����� ������ */
uint32_t UART_ReadRB(UART_T *pUART, RINGBUFF_T *pRB, void *data, uint32_t bytes)
{
    (void) pUART;
    return RingBuffer_PopMult(pRB, (uint8_t *) data, bytes);
}

/* ���������� ���������� UART �� ������/�������� ������ ��� ��������� ������� */
void UART_IRQRBHandler(UART_T *pUART, RINGBUFF_T *pRXRB, RINGBUFF_T *pTXRB)
{
    /* ��������� ���������� �� �������� */
    if (UART_GetIntStatus(pUART, UART_MIS_TXMIS)) 
    {
	UART_TXIntHandlerRB(pUART, pTXRB);
	/* ���������� ����������, ���� ��������� ����� ���� */
	if (RingBuffer_IsEmpty(pTXRB)) 
        {
            UART_IntDisable(pUART, UART_IMSC_TXIM);
	}
    }
    /* ��������� ���������� �� ������ */
    UART_RXIntHandlerRB(pUART, pRXRB);
}

/* ����������� � ��������� ����������� ���������� �������� ������� */
uint32_t UART_SetBaud(UART_T *pUART, uint32_t baud,const uint32_t sys_freq)
{
    float div = (sys_freq/16.0)/baud;
    uint32_t ibrd = (uint32_t) div;
    uint32_t fbrd = (uint32_t)((div - ibrd)*64+0.5);
    UART_SetDivisor(pUART, ibrd, fbrd);
    /* ������� �������������� �������� ������� */
    return (uint32_t)(sys_freq/(16*(ibrd + fbrd/64.0)));
}

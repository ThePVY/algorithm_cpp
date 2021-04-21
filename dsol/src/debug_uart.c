/*!\file
 * \brief ���� ���� �������� �������, ����������� ��� �������������� � ���������� �������.
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
#include "uart.h"
#include "debug_uart.h"
#include "ringbuffer.h"
#include "system.h"
#include "gpio.h"

RINGBUFF_T      dbg_uart_tx_rb;                                                 ///< ��������� ����� ����������� UART 
uint8_t         dbg_uart_tx_buf[DEBUG_UART_RB_SIZE];                            ///< ������, ������������ ��������� �������. 
UART_T * DEBUG_UART = UART1;                                        /**< ����� UART1 � �������� ����������� UART*/

/**
 * @brief	������������� ����������� UART'�
 */
void DBG_UART_Init(void)
{
#ifdef ENABLE_DEBUG_UART
    CMN_REG->PWR_CTRL_CLK |= (1<<2);                                              // ��������� �������� �������� ������
    CMN_REG->PWR_CTRL_RST |= (1<<2);                                              // ����� ���������������� ������
    UART_Init(UART1);                                                             // ������������� UART-�
    UART_SetBaud(UART1, BAUDRATE_921600, 80000000);                               // ��������� ����� ����� ������, ����� �������� ��� � �������� ��������//                              UART_LCR_H_FEN |                              //    UART_Config(UART_NUM[1], 112);
    UART_Config(UART1, 112);                                                      // ����������� � ��������� ����������� ���������� �������� �������                              //    UART_Config(UART_NUM[1], 112);
    UART_Enable(UART1);                                                           // ���������� ������ UART   
    UART_TXEnable(UART1);                                                         // ���������� ������ �����������
    UART_RXEnable(UART1);
    UART_SetupFIFOS(UART1, UART_IFLS_7DIV8, UART_IFLS_1DIV8);                     // ��������� ������� ���������� �� ���������� ������ ���������/�����������
    RingBuffer_Init(&dbg_uart_tx_rb, dbg_uart_tx_buf, 1, DEBUG_UART_RB_SIZE);     // ������������� ���������� ������
    //PRINT("__DEBUG_ENABLED");
#endif
}

void DBG_UART_Init_Args(UART_T *pUART,uint32_t baud)
{
     DEBUG_UART = pUART; 
#ifdef ENABLE_DEBUG_UART
    if (pUART==UART1)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<2);                                          // ��������� �������� �������� ������
        CMN_REG->PWR_CTRL_RST |= (1<<2);                                          // ����� ���������������� ������
    }
    if (pUART==UART2)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<3);                                          // ��������� �������� �������� ������
        CMN_REG->PWR_CTRL_RST |= (1<<3);                                          // ����� ���������������� ������
    }
    if (pUART==UART3)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<4);                                          // ��������� �������� �������� ������
        CMN_REG->PWR_CTRL_RST |= (1<<4);                                          // ����� ���������������� ������
    }
    if (pUART==UART4)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<5);                                          // ��������� �������� �������� ������
        CMN_REG->PWR_CTRL_RST |= (1<<5);                                          // ����� ���������������� ������
    }
    if (pUART==UART5)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<22);                                         // ��������� �������� �������� ������
        CMN_REG->PWR_CTRL_RST |= (1<<22);                                         // ����� ���������������� ������
    }
    if (pUART==UART6)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<23);                                         // ��������� �������� �������� ������
        CMN_REG->PWR_CTRL_RST |= (1<<23);                                         // ����� ���������������� ������
    }
    UART_Init(pUART);                                                             // ������������� UART-�
    UART_SetBaud(pUART, baud, 80000000);                                          // ��������� ����� ����� ������, ����� �������� ��� � �������� ��������//                              UART_LCR_H_FEN |                              //    UART_Config(UART_NUM[1], 112);
    UART_Config(pUART, 112);                                                      // ����������� � ��������� ����������� ���������� �������� �������                              //    UART_Config(UART_NUM[1], 112);
    UART_Enable(pUART);                                                           // ���������� ������ UART   
    UART_TXEnable(pUART);                                                         // ���������� ������ �����������
    UART_RXEnable(pUART);
    UART_SetupFIFOS(pUART, UART_IFLS_7DIV8, UART_IFLS_1DIV8);                     // ��������� ������� ���������� �� ���������� ������ ���������/�����������
    RingBuffer_Init(&dbg_uart_tx_rb, dbg_uart_tx_buf, 1, DEBUG_UART_RB_SIZE);     // ������������� ���������� ������
    //PRINT("__DEBUG_ENABLED");
#endif
}

/**
 * @brief	��������� ������, ����������� � ��������� ������, � ���������� UART
 */
void DBG_TX_Process(void)
{
#ifdef ENABLE_DEBUG_UART
    uint8_t ch;
    if (!(UART_GetStatus(DEBUG_UART, UART_FR_BUSY))) 
    {
        if(RingBuffer_Pop(&dbg_uart_tx_rb, &ch))
        {
            UART_SendByte(DEBUG_UART, ch);
        }
    }
#endif
}

/**
 * @brief	����� ���� ������, ����������� � ��������� ������, � ���������� UART
 */
void DBG_TX_Flush(void)
{
#ifdef ENABLE_DEBUG_UART
    uint8_t ch;
    while (!(RingBuffer_IsEmpty(&dbg_uart_tx_rb)))
    {
        if (!(UART_GetStatus(DEBUG_UART, UART_FR_BUSY))) 
        {
            if(RingBuffer_Pop(&dbg_uart_tx_rb, &ch))
            {
                UART_SendByte(DEBUG_UART, ch);
            }
        }
    }
#endif
}

/**
 * @brief	������ ������ ������ � ��������� �����
 * @param	buffer	: ��������� �� ������
 */
void DBG_WriteBuffer(char *buffer)
{
//#ifdef ENABLE_DEBUG_UART
    uint32_t length;
    length = strlen(buffer);
    RingBuffer_InsertMult(&dbg_uart_tx_rb, buffer, length);
//#endif  
}

/**
 * @brief	����� ����������� ������� � ���������� UART
 * @param	buffer	: ��������� �� ������
 * @param	length	: ����� ������ ��� ������
*/
void DBG_ShowBuffer(uint8_t *buffer, uint32_t length)
{
#ifdef ENABLE_DEBUG_UART
    uint32_t i;
    if (length) 
    {
        for(i=0; i<length; i++)
        {
            snprintf(dbg_buffer,256,"%02x ",buffer[i]);
            DBG_WriteBuffer(dbg_buffer);
        }
        DBG_WriteBuffer("\n");
    }
#endif
}

void gpioInit()
{
    GPIO_D->ALTFUNCSET |= (1 << 15); //uart1 tx
    GPIO_E->ALTFUNCSET |= (1 << 0);  //uart1 rx
    
   // GPIO_E->ALTFUNCSET |= (1 << 1);  //uart1 rx
   // GPIO_E->ALTFUNCSET |= (1 << 2);  //uart1 rx
}

//void clockInit()
//{
//    CMN_REG->PWR_CTRL_CLK |= (1<<2);
//    CMN_REG->PWR_CTRL_RST |= (1<<2);
//}

/**
 * @brief	��������� ������� �� ����������� UART'�
 * @return	���������� ������
*/
uint8_t DBG_GetChar(void)
{
#ifdef ENABLE_DEBUG_UART
    if (!(UART_GetStatus(DEBUG_UART, UART_FR_RXFE))) 
    {
	return (uint8_t) UART_ReadByte(DEBUG_UART);
    }
#endif
    return EOF;
}
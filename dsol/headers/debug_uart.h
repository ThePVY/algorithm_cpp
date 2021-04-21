/*!\file
 * \brief ���� ���� �������� ���������, ������� � �������, ����������� ��� �������������� � ���������� �������.
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

#ifndef DBG_H_
#define DBG_H_

#include <stdio.h>
#include <string.h>
#include "types.h"   
#include "gpio.h"
#include "uart.h"
#include "chip_5023BC016.h"

extern char dbg_buffer[256];

#define ENABLE_DEBUG_UART                                                       /**< ���������� ������������� ����������� UART*/
#define DEBUG_UART_RB_SIZE      1024                                            /**< ������ ���������� ������ ��� ����������� ������ */

/**
 * @brief ������� ��� ������������� ����������� ������
 */
#ifdef ENABLE_DEBUG_UART
#define PRINT(...)                   {snprintf(dbg_buffer,256,__VA_ARGS__); DBG_WriteBuffer(dbg_buffer);  DBG_WriteBuffer("\n");DBG_TX_Flush();}        ///< ������ � ��� ����
#define PRINTSTREAM(...)             {snprintf(dbg_buffer,256,__VA_ARGS__); DBG_WriteBuffer(dbg_buffer);}                                               ///< ������ � ��� ����
#define PRINTBUFFER(m,n)             DBG_ShowBuffer(m,n);                                                                                               ///< ������ � ��� ����
#define SCANCHAR()                   DBG_GetChar();                                                                                                     ///< ������ � ��� ���� �������
#else
#define PRINT(...) 
#define PRINTSTREAM(...)
#define PRINTBUFFER(m,n)             
#endif

/**
 * @brief	������������� ����������� UART'�
 */
void DBG_UART_Init(void);
void DBG_UART_Init_Args(UART_T *pUART,uint32_t baud);

/**
 * @brief	��������� ������, ����������� � ��������� ������, � ���������� UART
 */
void DBG_TX_Process(void);

/**
 * @brief	����� ���� ������, ����������� � ��������� ������, � ���������� UART
 */
void DBG_TX_Flush(void);

/**
 * @brief	������ ������ ������ � ��������� �����
 * @param	buffer	: ��������� �� ������
 */
void DBG_WriteBuffer(char *buffer);

/**
 * @brief	����� ����������� ������� � ���������� UART
 * @param	buffer	: ��������� �� ������
 * @param	length	: ����� ������ ��� ������
*/
void DBG_ShowBuffer(uint8_t *buffer, uint32_t length);

/**
 * @brief	��������� ������� �� ����������� UART'�
 * @return	���������� ������
*/
uint8_t DBG_GetChar(void);

/**
 * @brief	������������ gpio
*/
void gpioInit();

/**
 * @brief	������ clock ��� ����������� UART 
*/
void clockInit();



#endif
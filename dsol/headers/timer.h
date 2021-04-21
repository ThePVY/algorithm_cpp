/*!\file
 * \brief ���� ���� �������� ���������, ������� � �������, ����������� ��� �������������� � ���������� ������� �������.
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

#ifndef TIMER_H_
#define TIMER_H_

#include "types.h"


/** \brief  ��������� ��� ������� � ��������� �������
 */
typedef struct
{
    __RW uint32_t CTRL;                                                         /**< ��������: 0x000 ������� ���������� */
    __RW uint32_t VALUE;                                                        /**< ��������: 0x004 ������� ������� �������� */
    __RW uint32_t RELOAD;                                                       /**< ��������: 0x008 ������� ��� �������� �������� */
    __RW uint32_t INTCLEAR;                                                     /**< ��������: 0x00C ������� ����� ���������� */
}TIMER_T;                                                                           

/**
 * @brief ������� ��� �������� CTRL
 */
#define TIMER_CTRL_INT_EN              ((uint32_t)(1 << 3))                     /**< ���������� ���������� ������� */
#define TIMER_CTRL_ZERO2               ((uint32_t)(1 << 2))                     /**< [2] ������ �0� */
#define TIMER_CTRL_ZERO1               ((uint32_t)(1 << 1))                     /**< [1] ������ �0� */
#define TIMER_CTRL_OFF                 ((uint32_t)(0 << 0))                     /**< ���������� */


/**
 * @brief ��������� �������
 * @param pTIMER : ��������� �� ��������� � ���������� �������
 */
void TIMER_Enable(TIMER_T* pTIMER);

/**
 * @brief ���������� �������
 * @param pTIMER : ��������� �� ��������� � ���������� �������
 */
void TIMER_Disable(TIMER_T* pTIMER);

/**
 * @brief ���������� ������ ���������� �������
 * @param pTIMER : ��������� �� ��������� � ���������� �������
 */
void TIMER_IntEnable(TIMER_T* pTIMER);

/**
 * @brief ���������� ������ ���������� �������
 * @param pTIMER : ��������� �� ��������� � ���������� �������
 */
void TIMER_IntDisable(TIMER_T* pTIMER);

/**
 * @brief ��������� �������� �������� �������
 * @param pTIMER : ��������� �� ��������� � ���������� �������
 * @return ������� �������� �������
 */
uint32_t TIMER_GetValue(TIMER_T* pTIMER);

/**
 * @brief �������� �������� � ������
 * @param pTIMER : ��������� �� ��������� � ���������� �������
 * @param value : ��������, ����������� � ������
 */
void TIMER_SetValue(TIMER_T* pTIMER, uint32_t value);

/**
 * @brief ����� ����� ���������� �������
 * @param pTIMER : ��������� �� ��������� � ���������� �������
 */
void TIMER_IntClr(TIMER_T* pTIMER);





#endif                                                                         
                                                                               
                                                                               
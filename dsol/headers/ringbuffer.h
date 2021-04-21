/*!\file
 * \brief ���� ���� �������� ���������, ������� � �������, ����������� ��� �������������� � ���������� ��������.
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

#ifndef __RING_BUFFER_H_
#define __RING_BUFFER_H_

#include <string.h>   
#include "types.h"


/**
 * @brief ��������� ���������� ������
 */
typedef struct 
{
    void *data;                                                                 /**< ��������� �� ����� */ 
    int count;                                                                  /**< ������ ������ � ������ */
    int itemSz;                                                                 /**< ������ �������� ������ */
    uint32_t head;                                                              /**< ������ ��� ������ */
    uint32_t tail;                                                              /**< ������ ��� ������ */
}RINGBUFF_T;

/**
 * @brief ������� ��� ������ � ���������� ��������
 */
#define RB_INDH(gl_rb_t)     ((gl_rb_t)->head & ((gl_rb_t)->count - 1))
#define RB_INDT(gl_rb_t)     ((gl_rb_t)->tail & ((gl_rb_t)->count - 1))
#define RB_VHEAD(gl_rb_t)    (*(volatile uint32_t *) &(gl_rb_t)->head)          /**< �������������� �������, ������������ �� ����� ��� ������ � �����, ��� volatile */
#define RB_VTAIL(gl_rb_t)    (*(volatile uint32_t *) &(gl_rb_t)->tail)          /**< �������������� �������, ������������ �� ����� ��� ������ �� ������, ��� volatile */
#define	RB_FLUSH(gl_rb_t)    (((RINGBUFF_T *)gl_rb_t)->head = ((RINGBUFF_T *)gl_rb_t)->tail=0) /**< ����� ���������� ������ */  

/**
 * @brief ������������� ���������� ������.
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @param buffer: ��������� �� �����, ������� ����� �������������� � �������� ����������
 * @param itemSize: ������ �������� ������ 
 * @param count: ������ ������
 * @retval None
 */
void RingBuffer_Init(RINGBUFF_T *RingBuff, void *buffer, int itemSize, int count);

/**
 * @brief ������ ������ �������� � ��������� �����.
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @param data: ��������� �� �������
 * @retval ������ ��������
 */
Status RingBuffer_Insert(RINGBUFF_T *RingBuff, const void *data);

/**
 * @brief ������ ���������� ��������� � ��������� �����.
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @param data: ��������� �� ������ ������� ������� � ������� ��� ������
 * @param num: ������ �������
 * @retval (cnt1 + cnt2): ����� ������� ���������� ���������, 0 � ������ ������
 */
int RingBuffer_InsertMult(RINGBUFF_T *RingBuff, const void *data, int num);

/**
 * @brief ������ ������ �������� �� ���������� ������
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @param data: ��������� �� ������, ��� �������� ������������ ��������
 * @retval ������ ��������
 */
Status RingBuffer_Pop(RINGBUFF_T *RingBuff, void *data);

/**
 * @brief ������ ������� ��������� �� ���������� ������
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @param data: ��������� �� ������, ��� �������� ����������� ��������
 * @param num: ������������ ����� ���������, ������� ����� ��������� � �������
 * @retval (cnt1 + cnt2): ����� ������� ����������� ���������, 0 � ������ ������
 */
int RingBuffer_PopMult(RINGBUFF_T *RingBuff, void *data, int num);

/**
 * @brief ��������� ������� ���������� ������ � ������.
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @retval ������ ���������� ������ � ������
 */
 int RingBuffer_GetSize(RINGBUFF_T *RingBuff);

/**
 * @brief ��������� ���������� ���������, ���������� � ��������� �����.
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @retval ���������� ���������, ���������� � ��������� �����
 */
 int RingBuffer_GetCount(RINGBUFF_T *RingBuff);

/**
 * @brief ��������� ������� ���������� ����� � ��������� ������
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @retval ������ ���������� ����� � ��������� ������
 */
 int RingBuffer_GetFree(RINGBUFF_T *RingBuff);

/**
 * @brief �������� �� ������� ���������� ����� � ��������� ������
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @retval 1 ���� ��������� ����� ��������, ����� 0
 */
 int RingBuffer_IsFull(RINGBUFF_T *RingBuff);

/**
 * @brief �������� ���������� ������ �� ���������� ������
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @retval 1 ���� ��������� ����� ����, ����� 0
 */
 int RingBuffer_IsEmpty(RINGBUFF_T *RingBuff);


#endif /* __RING_BUFFER_H_ */

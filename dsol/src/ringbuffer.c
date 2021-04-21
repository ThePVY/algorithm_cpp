/*!\file
 * \brief ���� ���� �������� �������, ����������� ��� �������������� � ���������� ��������.
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

#include "ringbuffer.h"


/**
 * @brief ������������� ���������� ������.
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @param buffer: ��������� �� �����, ������� ����� �������������� � �������� ����������
 * @param itemSize: ������ �������� ������ 
 * @param count: ������ ������
 * @retval None
 */
void RingBuffer_Init(RINGBUFF_T *RingBuff, void *buffer, int itemSize, int count)
{
    RingBuff->data = buffer;
    RingBuff->count = count;
    RingBuff->itemSz = itemSize;
    RingBuff->head = RingBuff->tail = 0;
}


/**
 * @brief ������ ������ �������� � ��������� �����.
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @param data: ��������� �� �������
 * @retval ������ ��������
 */
Status RingBuffer_Insert(RINGBUFF_T *RingBuff, const void *data)
{
    uint8_t *ptr = RingBuff->data;
    /* �������� �� ������� ���������� ����� � ������ */
    if (RingBuffer_IsFull(RingBuff))
    {
        return ERROR;
    }
    ptr += RB_INDH(RingBuff) * RingBuff->itemSz;
    memcpy(ptr, data, RingBuff->itemSz);
    RingBuff->head++;
    
    return SUCCESS;
}

/**
 * @brief ������ ���������� ��������� � ��������� �����.
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @param data: ��������� �� ������ ������� ������� � ������� ��� ������
 * @param num: ������ �������
 * @retval (cnt1 + cnt2): ����� ������� ���������� ���������, 0 � ������ ������
 */
int RingBuffer_InsertMult(RINGBUFF_T *RingBuff, const void *data, int num)
{
    uint8_t *ptr = RingBuff->data;
    int cnt1, cnt2;
    
    /* �������� �� ������� ���������� ����� � ������ */
    if (RingBuffer_IsFull(RingBuff))
    {
        return (int)ERROR;
    }
    
    /* ���������� ����� ��������� */
    cnt1 = cnt2 = RingBuffer_GetFree(RingBuff);
    if (RB_INDH(RingBuff) + cnt1 >= RingBuff->count)
    {
        cnt1 = RingBuff->count - RB_INDH(RingBuff);
    }
    cnt2 -= cnt1;
    cnt1 = MIN(cnt1, num);
    num -= cnt1;
    cnt2 = MIN(cnt2, num);
    num -= cnt2;
    
    /* ������ �������� 1 */
    ptr += RB_INDH(RingBuff) * RingBuff->itemSz;
    memcpy(ptr, data, cnt1 * RingBuff->itemSz);
    RingBuff->head += cnt1;
    
    /* ������ �������� 2 */
    ptr = (uint8_t *) RingBuff->data + RB_INDH(RingBuff) * RingBuff->itemSz;
    data = (const uint8_t *) data + cnt1 * RingBuff->itemSz;
    memcpy(ptr, data, cnt2 * RingBuff->itemSz);
    RingBuff->head += cnt2;
    
    return cnt1 + cnt2;
}

/**
 * @brief ������ ������ �������� �� ���������� ������
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @param data: ��������� �� ������, ��� �������� ������������ ��������
 * @retval ������ ��������
 */
Status RingBuffer_Pop(RINGBUFF_T *RingBuff, void *data)
{
    uint8_t *ptr = RingBuff->data;
    /* �������� ���������� ������ �� ���������� ������ */
    if (RingBuffer_IsEmpty(RingBuff))
    {
        return ERROR;
    }
    ptr += RB_INDT(RingBuff) * RingBuff->itemSz;
    memcpy(data, ptr, RingBuff->itemSz);
    RingBuff->tail++;
    
    return SUCCESS;
}

/**
 * @brief ������ ������� ��������� �� ���������� ������
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @param data: ��������� �� ������, ��� �������� ����������� ��������
 * @param num: ������������ ����� ���������, ������� ����� ��������� � �������
 * @retval (cnt1 + cnt2): ����� ������� ����������� ���������, 0 � ������ ������
 */
int RingBuffer_PopMult(RINGBUFF_T *RingBuff, void *data, int num)
{
    uint8_t *ptr = RingBuff->data;
    int cnt1, cnt2;
	
    /* �������� ���������� ������ �� ���������� ������ */
    if (RingBuffer_IsEmpty(RingBuff))
    {
        return (int)ERROR;
    }

    /* ���������� ����� ��������� */
    cnt1 = cnt2 = RingBuffer_GetCount(RingBuff);
    if (RB_INDT(RingBuff) + cnt1 >= RingBuff->count)
    {
	cnt1 = RingBuff->count - RB_INDT(RingBuff);
    }
    cnt2 -= cnt1;
    cnt1 = MIN(cnt1, num);
    num -= cnt1;
    cnt2 = MIN(cnt2, num);
    num -= cnt2;
	
    /* ������ �������� 1 */
    ptr += RB_INDT(RingBuff) * RingBuff->itemSz;
    memcpy(data, ptr, cnt1 * RingBuff->itemSz);
    RingBuff->tail += cnt1;
    
    /* ������ �������� 2 */
    ptr = (uint8_t *) RingBuff->data + RB_INDT(RingBuff) * RingBuff->itemSz;
    data = (uint8_t *) data + cnt1 * RingBuff->itemSz;
    memcpy(data, ptr, cnt2 * RingBuff->itemSz);
    RingBuff->tail += cnt2;
        
    return cnt1 + cnt2;
}

/**
 * @brief ��������� ������� ���������� ������ � ������.
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @retval ������ ���������� ������ � ������
 */
 int RingBuffer_GetSize(RINGBUFF_T *RingBuff)
{
    return RingBuff->count;
}

/**
 * @brief ��������� ���������� ���������, ���������� � ��������� �����.
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @retval ���������� ���������, ���������� � ��������� �����
 */
 int RingBuffer_GetCount(RINGBUFF_T *RingBuff)
{
    uint32_t k1=RB_VTAIL(RingBuff);
    return RB_VHEAD(RingBuff)-k1;
    
    //return RB_VHEAD(RingBuff) - RB_VTAIL(RingBuff);
}

/**
 * @brief ��������� ������� ���������� ����� � ��������� ������
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @retval ������ ���������� ����� � ��������� ������
 */
 int RingBuffer_GetFree(RINGBUFF_T *RingBuff)
{
    return RingBuff->count - RingBuffer_GetCount(RingBuff);
}

/**
 * @brief �������� �� ������� ���������� ����� � ��������� ������
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @retval 1 ���� ��������� ����� ��������, ����� 0
 */
 int RingBuffer_IsFull(RINGBUFF_T *RingBuff)
{
    if (RingBuffer_GetCount(RingBuff) >= RingBuff->count)
    {
        return 1;
    }
    else
        return 0;   
}

/**
 * @brief �������� ���������� ������ �� ���������� ������
 * @param RingBuff: ��������� �� ��������� ���������� ������
 * @retval 1 ���� ��������� ����� ����, ����� 0
 */

 int RingBuffer_IsEmpty(RINGBUFF_T *RingBuff)
{   uint32_t k2=RB_VTAIL(RingBuff);                                                                         
    if (RB_VHEAD(RingBuff) == k2)                                               
    {
        return 1;
    }
    else
        return 0;
}


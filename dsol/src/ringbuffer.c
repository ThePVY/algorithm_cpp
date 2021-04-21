/*!\file
 * \brief Этот файл содержит функции, необходимые для взаимодействия с кольцевыми буферами.
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

#include "ringbuffer.h"


/**
 * @brief Инициализация кольцевого буфера.
 * @param RingBuff: указатель на структуру кольцевого буфера
 * @param buffer: указатель на буфер, который будет использоваться в качестве кольцевого
 * @param itemSize: размер элемента буфера 
 * @param count: размер буфера
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
 * @brief Запись одного элемента в кольцевой буфер.
 * @param RingBuff: указатель на структуру кольцевого буфера
 * @param data: указатель на элемент
 * @retval Статус операции
 */
Status RingBuffer_Insert(RINGBUFF_T *RingBuff, const void *data)
{
    uint8_t *ptr = RingBuff->data;
    /* Проверка на наличие свободного места в буфере */
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
 * @brief Запись нескольких элементов в кольцевой буфер.
 * @param RingBuff: указатель на структуру кольцевого буфера
 * @param data: указатель на первый элемент элемент в массиве для записи
 * @param num: размер массива
 * @retval (cnt1 + cnt2): число успешно записанных элементов, 0 в случае ошибки
 */
int RingBuffer_InsertMult(RINGBUFF_T *RingBuff, const void *data, int num)
{
    uint8_t *ptr = RingBuff->data;
    int cnt1, cnt2;
    
    /* Проверка на наличие свободного места в буфере */
    if (RingBuffer_IsFull(RingBuff))
    {
        return (int)ERROR;
    }
    
    /* Вычисление длины сегментов */
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
    
    /* Запись сегмента 1 */
    ptr += RB_INDH(RingBuff) * RingBuff->itemSz;
    memcpy(ptr, data, cnt1 * RingBuff->itemSz);
    RingBuff->head += cnt1;
    
    /* Запись сегмента 2 */
    ptr = (uint8_t *) RingBuff->data + RB_INDH(RingBuff) * RingBuff->itemSz;
    data = (const uint8_t *) data + cnt1 * RingBuff->itemSz;
    memcpy(ptr, data, cnt2 * RingBuff->itemSz);
    RingBuff->head += cnt2;
    
    return cnt1 + cnt2;
}

/**
 * @brief Чтение одного элемента из кольцевого буфера
 * @param RingBuff: указатель на структуру кольцевого буфера
 * @param data: указатель на массив, для хранения прочитанного элемента
 * @retval Статус операции
 */
Status RingBuffer_Pop(RINGBUFF_T *RingBuff, void *data)
{
    uint8_t *ptr = RingBuff->data;
    /* Проверка кольцевого буфера на отсутствие данных */
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
 * @brief Чтение массива элементов из кольцевого буфера
 * @param RingBuff: указатель на структуру кольцевого буфера
 * @param data: указатель на массив, для хранения прочитанных элемента
 * @param num: максимальное число элементов, которое можно сохранить в массиве
 * @retval (cnt1 + cnt2): число успешно прочитанных элементов, 0 в случае ошибки
 */
int RingBuffer_PopMult(RINGBUFF_T *RingBuff, void *data, int num)
{
    uint8_t *ptr = RingBuff->data;
    int cnt1, cnt2;
	
    /* Проверка кольцевого буфера на отсутствие данных */
    if (RingBuffer_IsEmpty(RingBuff))
    {
        return (int)ERROR;
    }

    /* Вычисление длины сегментов */
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
	
    /* Чтение сегмента 1 */
    ptr += RB_INDT(RingBuff) * RingBuff->itemSz;
    memcpy(data, ptr, cnt1 * RingBuff->itemSz);
    RingBuff->tail += cnt1;
    
    /* Чтение сегмента 2 */
    ptr = (uint8_t *) RingBuff->data + RB_INDT(RingBuff) * RingBuff->itemSz;
    data = (uint8_t *) data + cnt1 * RingBuff->itemSz;
    memcpy(data, ptr, cnt2 * RingBuff->itemSz);
    RingBuff->tail += cnt2;
        
    return cnt1 + cnt2;
}

/**
 * @brief Получение размера кольцевого буфера в байтах.
 * @param RingBuff: указатель на структуру кольцевого буфера
 * @retval Размер кольцевого буфера в байтах
 */
 int RingBuffer_GetSize(RINGBUFF_T *RingBuff)
{
    return RingBuff->count;
}

/**
 * @brief Получения количества элементов, записанных в кольцевой буфер.
 * @param RingBuff: указатель на структуру кольцевого буфера
 * @retval Количество элементов, записанных в кольцевой буфер
 */
 int RingBuffer_GetCount(RINGBUFF_T *RingBuff)
{
    uint32_t k1=RB_VTAIL(RingBuff);
    return RB_VHEAD(RingBuff)-k1;
    
    //return RB_VHEAD(RingBuff) - RB_VTAIL(RingBuff);
}

/**
 * @brief Получение размера свободного места в кольцевом буфере
 * @param RingBuff: указатель на структуру кольцевого буфера
 * @retval Размер свободного места в кольцевом буфере
 */
 int RingBuffer_GetFree(RINGBUFF_T *RingBuff)
{
    return RingBuff->count - RingBuffer_GetCount(RingBuff);
}

/**
 * @brief Проверка на наличие свободного места в кольцевом буфере
 * @param RingBuff: указатель на структуру кольцевого буфера
 * @retval 1 если кольцевой буфер заполнен, иначе 0
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
 * @brief Проверка кольцевого буфера на отсутствие данных
 * @param RingBuff: указатель на структуру кольцевого буфера
 * @retval 1 если кольцевой буфер пуст, иначе 0
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


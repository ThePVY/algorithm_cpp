/*!\file
 * \brief Этот файл содержит функции, необходимые для работы с памятью.
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

#include "memory.h"
#include "chip_5023BC016.h"
#include "string.h"
#include "types.h"



/**
 * @brief Чтение блок данных транзакциями по четыре байта
 * @param Addr : Адрес
 * @param *pBlock : Указатель на буфер для приема данных
 * @param Size : Размер блока данных
 */
void MEM_ReadBlock32(uint32_t Addr, uint32_t *pBlock, uint32_t Size)
{
    for(uint32_t OffSet = 0; OffSet < Size; OffSet++)
    {
        *pBlock = MEM_Read32(Addr+OffSet);
        pBlock++;
    }
}

typedef enum
{
    a,
    b,
}TYPE_T;

/**
 * @brief Запись блок данных транзакциями по четыре байта
 * @param Addr : Адрес
 * @param *pBlock : Указатель на буфер для передачи данных
 * @param Size : Размер блока данных
 */
void MEM_WriteBlock32(uint32_t Addr, uint32_t *pBlock, uint32_t Size)
{  
    //TYPE_T a; 
    for(uint32_t OffSet = 0; OffSet < Size; OffSet++)
    {
        MEM_Write32( Addr+OffSet, *pBlock);
        pBlock++;
    }
}

/**
 * @brief Чтение блок данных транзакциями по два байта
 * @param Addr : Адрес
 * @param *pBlock : Указатель на буфер для приема данных
 * @param Size : Размер блока данных
 */
void MEM_ReadBlock16(uint32_t Addr, uint16_t *pBlock, uint32_t Size)
{
    for(uint32_t OffSet = 0; OffSet < Size; OffSet++)
    {
        *pBlock = MEM_Read16(Addr+OffSet);
        pBlock++;
    }
}

/**
 * @brief  Запись блок данных транзакциями по два байта
 * @param  Addr : Адрес
 * @param  *pBlock : Указатель на буфер для передачи данных
 * @param  Size : Размер блока данных
 */
void MEM_WriteBlock16(uint32_t Addr, uint16_t *pBlock, uint32_t Size)
{  
    for(uint32_t OffSet = 0; OffSet < Size; OffSet++)
    {
        MEM_Write16( Addr+OffSet, *pBlock);
        pBlock++;
    }
}

/**
 * @brief Чтение блок данных транзакциями по одному байту
 * @param Addr : Адрес
 * @param *pBlock : Указатель на буфер для приема данных
 * @param Size : Размер блока данных
 */
void MEM_ReadBlock8(uint32_t Addr, uint8_t *pBlock, uint32_t Size)
{
    for(uint32_t OffSet = 0; OffSet < Size; OffSet++)
    {
        *pBlock = MEM_Read8(Addr+OffSet);
        pBlock++;
    }
}

/**
 * @brief Запись блок данных транзакциями по одному байту
 * @param Addr : Адрес
 * @param *pBlock : Указатель на буфер для передачи данных
 * @param Size : Размер блока данных
 */
void MEM_WriteBlock8(uint32_t Addr, uint8_t *pBlock, uint32_t Size)
{  
    for(uint32_t OffSet = 0; OffSet < Size; OffSet++)
    {
        MEM_Write8( Addr+OffSet, *pBlock);
        pBlock++;
    }
}

/**
 * @brief Выбор микросхемы памяти
 * @param MemChip : Тип микросхемы памяти 	
 */
void MEM_SetChip(MEMORY_CHIP MemChip)
{  
    MEMORY_CONTROL_REGISTER->CE = MemChip;
}

/**
 * @brief Взять выбранную микросхему
 * @return Тип микросхемы памяти
 */
uint8_t MEM_GetChip()
{  
    return (uint8_t)(MEMORY_CONTROL_REGISTER->CE);     
}

/**
 * @brief функция включения КЭШа
 */
void Func_Cache_Enable()
{
    CMN_REG->CACHE_HIGH_ADDR =  0x4ffff;
    CMN_REG->CACHE_MAIN |= CACHE_ENABLE(1)|CACHE_READY(1); 
    for (int i = 0;i<4096;i++);                                                 // 4096 тактов - время включения
}

/**
 * @brief Функция выключения КЭШа
 */
void Func_Cache_Disable()
{
    CMN_REG->CACHE_MAIN = CACHE_ENABLE(0)|CACHE_READY(0); 
}

/**
 * @brief       Функция установки скраберов
 * @param      	rng_addr - верхняя граница диапазона
 * @param      	prd_stop - период прерывания скрабером обращ контроллера вн памяти
 * @param      	prd_scan - период сканирования
 */
void Func_Scraber_Set(uint32_t  rng_addr,
                      uint32_t  prd_stop,
                      uint32_t  prd_scan,
                      BLOCK_NUMBER number)
{
    switch (number)
    {
        case BLOCK1:
            CMN_REG->INTMEM_SCR_RNG_ADDR = rng_addr;                                    
            CMN_REG->INTMEM_SCR_PRD_STOP = prd_stop;
            CMN_REG->INTMEM_SCR_PRD_SCAN = prd_scan;
   
            CMN_REG->INTMEMS_SCR_MAIN |= (1<<0);
            break;
        case BLOCK2:
            CMN_REG->INTMEM2_SCR_RNG_ADDR = rng_addr;                                    
            CMN_REG->INTMEM2_SCR_PRD_STOP = prd_stop;
            CMN_REG->INTMEM2_SCR_PRD_SCAN = prd_scan;
   
            CMN_REG->INTMEMS_SCR_MAIN |= (1<<1);
            break;
        default:
            break;
    }
}

/**
 * @brief Взять установленную страницу памяти
 * @return Установленная страница памяти
 */
uint8_t MEM_GetPage()
{  
    return (uint8_t)(MEMORY_CONTROL_REGISTER->MEMADD);
}

/**
 * @brief Установка страницы памяти
 * @param NumPage : Номер страницы памяти
 */
void MEM_SetPage(uint8_t NumPage)
{  
    MEMORY_CONTROL_REGISTER->MEMADD = (uint16_t)(NumPage);  
}

/**
 * @brief Запись байтного слова
 * @param Addr : Адрес
 * @param Data : Байтное слово
 */
void MEM_Write8(uint32_t Addr, uint8_t Data)
{
    *(uint8_t*)(MEMORY_DATA_ADDRESS_8 + Addr) = Data;
}

/**
 * @brief Запись двух байтного слова
 * @param Addr : Адрес
 * @param Data : Двух байтное слово
 */
void MEM_Write16(uint32_t Addr, uint16_t Data)
{  
    *(uint16_t*)(MEMORY_DATA_ADDRESS_16 + Addr) = Data; 
}

/**
 * @brief Запись четырех байтного слова
 * @param Addr : Адрес
 * @param Data : Четырех байтное слово
 */
void MEM_Write32(uint32_t Addr, uint32_t Data)
{  
    *(uint32_t*)(MEMORY_DATA_ADDRESS_32 + Addr) = Data; 
}

/**
 * @brief Чтение байтного слова
 * @param Addr : Адрес
 * @return Значение байтного слова
 */
uint8_t MEM_Read8(uint32_t Addr)
{
    return *(uint8_t*)(MEMORY_DATA_ADDRESS_8 + Addr);
}

/**
 * @brief Чтение двух байтного слова
 * @param Addr : Адрес
 * @return Значение двух байтного слова
 */
uint16_t MEM_Read16(uint32_t Addr)
{
    return *(uint16_t*)(MEMORY_DATA_ADDRESS_16 + Addr);
}

/**
 * @brief Чтение четырех байтного слова
 * @param Addr :Адрес
 * @return Значение четырех байтного слова
 */
uint32_t MEM_Read32(uint32_t Addr)
{
    return *(uint32_t*)(MEMORY_DATA_ADDRESS_32 + Addr);
}


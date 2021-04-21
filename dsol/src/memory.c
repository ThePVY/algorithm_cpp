/*!\file
 * \brief ���� ���� �������� �������, ����������� ��� ������ � �������.
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

#include "memory.h"
#include "chip_5023BC016.h"
#include "string.h"
#include "types.h"



/**
 * @brief ������ ���� ������ ������������ �� ������ �����
 * @param Addr : �����
 * @param *pBlock : ��������� �� ����� ��� ������ ������
 * @param Size : ������ ����� ������
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
 * @brief ������ ���� ������ ������������ �� ������ �����
 * @param Addr : �����
 * @param *pBlock : ��������� �� ����� ��� �������� ������
 * @param Size : ������ ����� ������
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
 * @brief ������ ���� ������ ������������ �� ��� �����
 * @param Addr : �����
 * @param *pBlock : ��������� �� ����� ��� ������ ������
 * @param Size : ������ ����� ������
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
 * @brief  ������ ���� ������ ������������ �� ��� �����
 * @param  Addr : �����
 * @param  *pBlock : ��������� �� ����� ��� �������� ������
 * @param  Size : ������ ����� ������
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
 * @brief ������ ���� ������ ������������ �� ������ �����
 * @param Addr : �����
 * @param *pBlock : ��������� �� ����� ��� ������ ������
 * @param Size : ������ ����� ������
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
 * @brief ������ ���� ������ ������������ �� ������ �����
 * @param Addr : �����
 * @param *pBlock : ��������� �� ����� ��� �������� ������
 * @param Size : ������ ����� ������
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
 * @brief ����� ���������� ������
 * @param MemChip : ��� ���������� ������ 	
 */
void MEM_SetChip(MEMORY_CHIP MemChip)
{  
    MEMORY_CONTROL_REGISTER->CE = MemChip;
}

/**
 * @brief ����� ��������� ����������
 * @return ��� ���������� ������
 */
uint8_t MEM_GetChip()
{  
    return (uint8_t)(MEMORY_CONTROL_REGISTER->CE);     
}

/**
 * @brief ������� ��������� ����
 */
void Func_Cache_Enable()
{
    CMN_REG->CACHE_HIGH_ADDR =  0x4ffff;
    CMN_REG->CACHE_MAIN |= CACHE_ENABLE(1)|CACHE_READY(1); 
    for (int i = 0;i<4096;i++);                                                 // 4096 ������ - ����� ���������
}

/**
 * @brief ������� ���������� ����
 */
void Func_Cache_Disable()
{
    CMN_REG->CACHE_MAIN = CACHE_ENABLE(0)|CACHE_READY(0); 
}

/**
 * @brief       ������� ��������� ���������
 * @param      	rng_addr - ������� ������� ���������
 * @param      	prd_stop - ������ ���������� ��������� ����� ����������� �� ������
 * @param      	prd_scan - ������ ������������
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
 * @brief ����� ������������� �������� ������
 * @return ������������� �������� ������
 */
uint8_t MEM_GetPage()
{  
    return (uint8_t)(MEMORY_CONTROL_REGISTER->MEMADD);
}

/**
 * @brief ��������� �������� ������
 * @param NumPage : ����� �������� ������
 */
void MEM_SetPage(uint8_t NumPage)
{  
    MEMORY_CONTROL_REGISTER->MEMADD = (uint16_t)(NumPage);  
}

/**
 * @brief ������ �������� �����
 * @param Addr : �����
 * @param Data : ������� �����
 */
void MEM_Write8(uint32_t Addr, uint8_t Data)
{
    *(uint8_t*)(MEMORY_DATA_ADDRESS_8 + Addr) = Data;
}

/**
 * @brief ������ ���� �������� �����
 * @param Addr : �����
 * @param Data : ���� ������� �����
 */
void MEM_Write16(uint32_t Addr, uint16_t Data)
{  
    *(uint16_t*)(MEMORY_DATA_ADDRESS_16 + Addr) = Data; 
}

/**
 * @brief ������ ������� �������� �����
 * @param Addr : �����
 * @param Data : ������� ������� �����
 */
void MEM_Write32(uint32_t Addr, uint32_t Data)
{  
    *(uint32_t*)(MEMORY_DATA_ADDRESS_32 + Addr) = Data; 
}

/**
 * @brief ������ �������� �����
 * @param Addr : �����
 * @return �������� �������� �����
 */
uint8_t MEM_Read8(uint32_t Addr)
{
    return *(uint8_t*)(MEMORY_DATA_ADDRESS_8 + Addr);
}

/**
 * @brief ������ ���� �������� �����
 * @param Addr : �����
 * @return �������� ���� �������� �����
 */
uint16_t MEM_Read16(uint32_t Addr)
{
    return *(uint16_t*)(MEMORY_DATA_ADDRESS_16 + Addr);
}

/**
 * @brief ������ ������� �������� �����
 * @param Addr :�����
 * @return �������� ������� �������� �����
 */
uint32_t MEM_Read32(uint32_t Addr)
{
    return *(uint32_t*)(MEMORY_DATA_ADDRESS_32 + Addr);
}


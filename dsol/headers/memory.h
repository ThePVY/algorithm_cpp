/*!\file
 * \brief ���� ���� �������� ���������, ������� � �������, ����������� ��� ������ � �������.
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

#ifndef MEMORY_H_
#define MEMORY_H_


#define MEMORY_CONTROL_REG_BASE_ADDRESS       (0x20002)                                                 ///< ����� �������� ��� ������������ ������� MRAM
#define MEMORY_EXPOSURE_TIME                  (1000000)                                                 ///< ����� EXPOSURE_TIME
#define MEMORY_DATA_REG_BASE_ADDRESS          (0x10000)                                                 ///< ����� ������
#define MEMORY_CONTROL_REGISTER               ((PMEMORY_CONTROL_MAP)MEMORY_CONTROL_REG_BASE_ADDRESS)    ///< ��������� ��������� ��� ������������ ������� MRAM
#define MEMORY_DATA_ADDRESS_32                ((uint32_t*)MEMORY_DATA_REG_BASE_ADDRESS)                 ///< uint32_t*
#define MEMORY_DATA_ADDRESS_16                ((uint16_t*)MEMORY_DATA_REG_BASE_ADDRESS)                 ///< uint16_t*
#define MEMORY_DATA_ADDRESS_8                 ((uint8_t*) MEMORY_DATA_REG_BASE_ADDRESS)                 ///< uint8_t*        

#include "types.h"

/**
 * @brief ��� ���������� ������.
 */
typedef enum MEMORY_CHIP_
{
    MEM_GPIO =0,
    MEM_SRAM = 4,                                                               /**< MEM_SRAM:  ���������� SRAM */
    MEM_MRAM = 1,                                                               /**< MEM_MRAM:  ���������� MRAM */
    MEM_ROM  = 2                                                                /**< MEM_ROM:   ���������� FLASH*/
}MEMORY_CHIP;

/**
 * @brief ���� ������.
 */
typedef enum
{
    BLOCK1 = 1,
    BLOCK2 = 2
}BLOCK_NUMBER;

/**
 * @brief  ��������� ��� ������� � ��������� ���������� �������
 */
typedef struct _MEMORY_CONTROL_MAP_
{
    __RW uint16_t CE;                                                           /**< ��������: 0x0000 ������� ��� ������ ���������� ������:  SRAM = 1, MRAM = 2, ROM  = 4*/ 
    __RW uint16_t MEMADD;                                                       /**< ��������: 0x0002 ������� ��� ��������� ������ �������� ������ �� 0 �� 15*/ 
}MEMORY_CONTROL_MAP, *PMEMORY_CONTROL_MAP;

/**
 * @brief ������� ���������� ����
 */
void Func_Cache_Disable();

/**
 * @brief ������� ��������� ����
 */
void Func_Cache_Enable();
    
/**
 * @brief       ������� ��������� ���������
 * @param      	rng_addr - ������� ������� ���������
 * @param      	prd_stop - ������ ���������� ��������� ����� ����������� �� ������
 * @param      	prd_scan - ������ ������������
 */
void Func_Scraber_Set(uint32_t  rng_addr,
                      uint32_t  prd_stop,
                      uint32_t  prd_scan,
                      BLOCK_NUMBER number);

/**
 * @brief       ����� ���������� ������
 * @param       MemChip     :��� ���������� ������ 	
 */
void MEM_SetChip(MEMORY_CHIP MemChip);

/**
 * @brief       ����� ��������� ����������
 * @return	��� ���������� ������
 */
uint8_t MEM_GetChip();

/**
 * @brief       ����� ������������� �������� ������
 * @return	������������� �������� ������
 */
uint8_t MEM_GetPage();

/**
 * @brief       ��������� �������� ������
 * @param       NumPage     :����� �������� ������
 */
void MEM_SetPage(uint8_t NumPage);

/**
 * @brief       ������ �������� �����
 * @param       Addr     :�����
 * @param       Data     :������� �����
 */
void MEM_Write8(uint32_t Addr, uint8_t Data);

/**
 * @brief       ������ ���� �������� �����
 * @param       Addr     :�����
 * @param       Data     :���� ������� �����
 */
void MEM_Write16(uint32_t Addr, uint16_t Data);

/**
 * @brief       ������ ������� �������� �����
 * @param       Addr     :�����
 * @param       Data     :������� ������� �����
 */
void MEM_Write32(uint32_t Addr, uint32_t Data);

/**
 * @brief       ������ �������� �����
 * @param       Addr     :�����
 * @return	�������� �������� �����
 */
uint8_t MEM_Read8(uint32_t Addr);

/**
 * @brief       ������ ���� �������� �����
 * @param       Addr     :�����
 * @return	�������� ���� �������� �����
 */
uint16_t MEM_Read16(uint32_t Addr);

/**
 * @brief       ������ ������� �������� �����
 * @param       Addr     :�����
 * @return	�������� ������� �������� �����
 */
uint32_t MEM_Read32(uint32_t Addr);


#endif


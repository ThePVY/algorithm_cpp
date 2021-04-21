/*!\file
 * \brief ���� ���� �������� ���������, ������� � �������, ����������� ��� �������������� � ���������� ������� ����������� �������.
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

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include "types.h"



/**
 * @brief ��������� ��� ������� � ��������� WATCHDOG.
 */
typedef struct
{
    __RW uint32_t WDOGLOAD;                                                     /**< ��������: 0x000 ������� ��� �������� �������� */
    __RO uint32_t WDOGVALUE;                                                    /**< ��������: 0x004 ������� ������� �������� */
    __RW uint32_t WDOGCONTROL;                                                  /**< ��������: 0x008 ������� ���������� */
    __WO uint32_t WDOGINTCLR;                                                   /**< ��������: 0x00C ������� ������ ���������� */
    __RO uint32_t WDOGRIS;                                                      /**< ��������: 0x010 ������� ������� ���������������� ���������� */
    __RO uint32_t WDOGMIS;                                                      /**< ��������: 0x014 ������� ������� �������������� ���������� */
         uint32_t RESERVED_0[762];   
    __RW uint32_t WDOGLOCK;                                                     /**< ��������: 0xC00 ������� ���������� ������ �� ��� ��������� �������� ����������� ������� */
         uint32_t RESERVED_1[191];
    __RW uint32_t WDOGITCR;                                                     /**< ��������: 0xF00 ������� ��������� ������ ��������������� ������������ */
    __WO uint32_t WDOGITOP;                                                     /**< ��������: 0xF04 ������� ���������� ������� ������ � ���������� � ������ ������������ */
}WDT_T;  

/**
 * @brief ������� ��� �������� WDOGCONTROL
 */
#define WDT_WDOGCONTROL_INTEN                  ((uint32_t)(1 << 0))             /**< ��������� ���������� */
#define WDT_WDOGCONTROL_RESEN                  ((uint32_t)(1 << 1))             /**< ��������� ��������� ������ */
#define WDT_WDOGCONTROL_BITMASK                ((uint32_t)(3 << 0))             

/**
 * @brief ������� ��� �������� WDOGINTCLR
 */
#define WDT_WDOGINTCLR_CLR                     ((uint32_t)(1 << 0))             /**< ����� ���������� ����������� ������� */

/**
 * @brief ������� ��� �������� WDOGRIS
 */
#define WDT_WDOGRIS_INT_RAW                    ((uint32_t)(1 << 0))             /**< ������ ���������������� ���������� */

/**
 * @brief ������� ��� �������� WDOGMIS
 */
#define WDT_WDOGMIS_INT                        ((uint32_t)(1 << 0))             /**< ������ �������������� ���������� */

/**
 * @brief ������� ��� �������� WDOGLOCK
 */
#define WDT_WDOGLOCK_WEN_UNLOCK                ((uint32_t)(0 << 0))             /**< ������ �� ��� �������� ��������� */
#define WDT_WDOGLOCK_WEN_LOCK                  ((uint32_t)(1 << 0))             /**< ������ �� ��� �������� ��������� */

/**
 * @brief ������� ��� �������� WDOGITCR
 */
#define WDT_WDOGITCR_TEST_MODULE_EN            ((uint32_t)(1 << 0))             /**< ��������� ������ ��������������� ������������ */
#define WDT_WDOGITCR_TEST_MODULE_DIS           ((uint32_t)(0 << 0))             /**< ���������� ������ ��������������� ������������ */

/**
 * @brief ������� ��� �������� WDOGITOP
 */
#define WDT_WDOGITOP_WDOGRES                   ((uint32_t)(1 << 0))             /**< �������� ������ � ������ ������������ */
#define WDT_WDOGITOP_WDOGINT                   ((uint32_t)(1 << 1))             /**< �������� ���������� � ������ ������������ */

/**
 * @brief ���������� ����������� ������ 
 * @param pWTD: ��������� �� ��������� � ���������� WATCHDOG
 * @retval None
 */
void WDT_HWResetDisable(WDT_T *pWTD);

/**
 * @brief ��������� ����������� ������
 * @param pWTD: ��������� �� ��������� � ���������� WATCHDOG
 * @retval None
 */
void WDT_HWResetEnable(WDT_T *pWTD);

/**
 * @brief ��������� ���������� �������� �������� ����������� ������� 
 * @param pWTD: ��������� �� ��������� � ���������� WATCHDOG
 * @param Value: ��������� �������� ��������
 * @retval None
 */
void WDT_SetValue(WDT_T *pWTD, uint32_t value);

/**
 * @brief ����� ������� �������� �������� ����������� ������� 
 * @param pWTD: ��������� �� ��������� � ���������� WATCHDOG
 * @retval ������� �������� ��������
 */
uint32_t WDT_GetValue(WDT_T *pWTD);

/**
 * @brief ���������� ���������� ����������� �������
 * @param pWTD: ��������� �� ��������� � ���������� WATCHDOG
 * @retval None
 */
void WDT_IntDisable(WDT_T *pWTD);
/**
 * @brief ��������� ���������� ����������� ������� 
 * @param pWTD: ��������� �� ��������� � ���������� WATCHDOG
 * @retval None
 */
void WDT_IntEnable(WDT_T *pWTD);
/**
 * @brief ����� ����� ���������� ����������� ������� � ��� ��������� � �������� �� �������� WDOGLOAD
 * @param pWTD: ��������� �� ��������� � ���������� WATCHDOG
 * @retval None
 */
void WDT_IntClr(WDT_T *pWTD);



#endif /* WATCHDOG_H_ */
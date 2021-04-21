/*!\file
 * \brief ���� ���� �������� �������� ��������� ������������ ���������������� 5023��016.
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

#ifndef CHIP_5023BC016_H_
#define CHIP_5023BC016_H_
#include "system.h"


/**
 * @brief ������������� ��������� ������������
 */
#define GPIO_A_BASE         (0x80000000)                                        /**<    ������� ����� ����� GPIO A */
#define GPIO_B_BASE         (0x80010000)                                        /**<    ������� ����� ����� GPIO B */
#define GPIO_C_BASE         (0x80020000)                                        /**<    ������� ����� ����� GPIO C */
#define GPIO_D_BASE         (0x80030000)                                        /**<    ������� ����� ����� GPIO D */
#define GPIO_E_BASE         (0x80040000)                                        /**<    ������� ����� ����� GPIO E */
#define GPIO_F_BASE         (0x80050000)                                        /**<    ������� ����� ����� GPIO F */
#define GPIO_G_BASE         (0x80060000)                                        /**<    ������� ����� ����� GPIO G */
#define GPIO_H_BASE         (0x80070000)                                        /**<    ������� ����� ����� GPIO H */
#define GPIO_I_BASE         (0x80080000)                                        /**<    ������� ����� ����� GPIO I */
#define CMN_REG_BASE        (0xA0000000)                                        /**<    ������� ����� ��������� ������ ���������� */
#define DMA_BASE            (0xA0010000)                                        /**<    ������� ����� ����������� DMA */
#define SPI1_BASE           (0xA0020000)                                        /**<    ������� ����� ���������� SPI 1 */
#define SPI2_BASE           (0xA0030000)                                        /**<    ������� ����� ���������� SPI 2 */
#define UART1_BASE          (0xA0040000)                                        /**<    ������� ����� ���������� UART 1 */
#define UART2_BASE          (0xA0050000)                                        /**<    ������� ����� ���������� UART 2 */
#define UART3_BASE          (0xA0060000)                                        /**<    ������� ����� ���������� UART 3 */
#define UART4_BASE          (0xA0070000)                                        /**<    ������� ����� ���������� UART 4 */
#define WDT_BASE            (0xA0080000)                                        /**<    ������� ����� ����������� ������� Watchdog */  
#define TIMER1_BASE         (0xA0090000)                                        /**<    ������� ����� ������� ������ ���������� Timer 1 */
#define SPW1_BASE           (0xA00A0000)                                        /**<    ������� ����� ���������� SpaceWire 1 */
#define SPW2_BASE           (0xA00B0000)                                        /**<    ������� ����� ���������� SpaceWire 2 */
#define MKPD1_BASE          (0xA00C0000)                                        /**<    ������� ����� ���������� ���� 1 */
#define MKPD2_BASE          (0xA00D0000)                                        /**<    ������� ����� ���������� ���� 2 */
#define MKPD3_BASE          (0xA00E0000)                                        /**<    ������� ����� ���������� ���� 3 */
#define MKPD4_BASE          (0xA00F0000)                                        /**<    ������� ����� ���������� ���� 4 */
#define TMTX_BASE           (0xA0100000)                                        /**<    ������� ����� ������ TMTX */ 
#define TCRX_BASE           (0xA0110000)                                        /**<    ������� ����� ������ TCRX */
#define FPU_BASE            (0xA0120000)                                        /**<    ������� ����� ����� FPU */ 
#define TIMER2_BASE         (0xA0130000)                                        /**<    ������� ����� ������� ������ ���������� Timer 2 */ 
#define TIMER3_BASE         (0xA0140000)                                        /**<    ������� ����� ������� ������ ���������� Timer 3 */ 
#define TIMER4_BASE         (0xA0150000)                                        /**<    ������� ����� ������� ������ ���������� Timer 4 */ 
#define RESERVE_P1_BASE     (0xA0160000)                                        /**<    ������ */ 
#define RESERVE_P2_BASE     (0xA0170000)                                        /**<    ������ */ 
#define RESERVE_P3_BASE     (0xA0180000)                                        /**<    ������ */ 
#define RESERVE_P4_BASE     (0xA0190000)                                        /**<    ������ */
#define RESERVE_Q_B         (0xA01A0000)                                        /**<    ������ */
#define CAN1_BASE           (0xA01B0000)                                        /**<    ������� ����� ���������� CAN 1 */
#define CAN2_BASE           (0xA01C0000)                                        /**<    ������� ����� ���������� CAN 1 */
#define NVIC_MUX_BASE       (0xA01D0000)                                        /**<    ������� ����� �������������� ���������� */
#define UART5_BASE          (0xA01E0000)                                        /**<    ������� ����� ���������� UART 5 */
#define UART6_BASE          (0xA01F0000)                                        /**<    ������� ����� ���������� UART 6 */
#define I2C_BASE            (0xA0200000)                                        /**<    ������� ����� ���������� I2C */
                                                                          
/**
 * @brief ������������� ��������� ������������ - �������� ������ � ������ 
 */
#define INT_MEM1_DATA_BASE  (0x60000000)                                        /**<    ������� ����� ������� � ������ ����� 1, ������ */
#define INT_MEM1_ECC_BASE   (0x60100000)                                        /**<    ������� ����� ������� � ������ ����� 1, ���� ECC */
#define INT_WAY_DATA_BASE   (0x61000000)                                        /**<    ������� ����� ������� � ������ ����, ������ */
#define INT_WAY_CRC_BASE    (0x61100000)                                        /**<    ������� ����� ������� � ������ ����, CRC */
#define INT_MEM2_DATA_BASE  (0x62000000)                                        /**<    ������� ����� ������� � ������ ����� 2, ������ */
#define INT_MEM2_ECC_BASE   (0x62100000)                                        /**<    ������� ����� ������� � ������ ����� 2, ���� ECC */


/**
 * @brief ��������� �� ���������
 */
#define GPIO_A              ((GPIO_T            *)(GPIO_A_BASE))                ///< ��������� �� ��������� GPIO_A
#define GPIO_B              ((GPIO_T            *)(GPIO_B_BASE))                ///< ��������� �� ��������� GPIO_B
#define GPIO_C              ((GPIO_T            *)(GPIO_C_BASE))                ///< ��������� �� ��������� GPIO_�
#define GPIO_D              ((GPIO_T            *)(GPIO_D_BASE))                ///< ��������� �� ��������� GPIO_D
#define GPIO_E              ((GPIO_T            *)(GPIO_E_BASE))                ///< ��������� �� ��������� GPIO_E
#define GPIO_F              ((GPIO_T            *)(GPIO_F_BASE))                ///< ��������� �� ��������� GPIO_F
#define GPIO_G              ((GPIO_T            *)(GPIO_G_BASE))                ///< ��������� �� ��������� GPIO_G
#define GPIO_H              ((GPIO_T            *)(GPIO_H_BASE))                ///< ��������� �� ��������� GPIO_H
#define GPIO_I              ((GPIO_T            *)(GPIO_I_BASE))                ///< ��������� �� ��������� GPIO_T
#define CMN_REG             ((CMN_REG_T         *)(CMN_REG_BASE))               ///< ��������� �� ��������� CMN_REG
#define DMA                 ((DMA_T             *)(DMA_BASE))                   ///< ��������� �� ��������� DMA
#define SPI1                ((SPI_T             *)(SPI1_BASE))                  ///< ��������� �� ��������� SPI1
#define SPI2                ((SPI_T             *)(SPI2_BASE))                  ///< ��������� �� ��������� SPI2
#define UART1               ((UART_T            *)(UART1_BASE))                 ///< ��������� �� ��������� UART1
#define UART2               ((UART_T            *)(UART2_BASE))                 ///< ��������� �� ��������� UART2
#define UART3               ((UART_T            *)(UART3_BASE))                 ///< ��������� �� ��������� UART3
#define UART4               ((UART_T            *)(UART4_BASE))                 ///< ��������� �� ��������� UART4
#define UART5               ((UART_T            *)(UART5_BASE))                 ///< ��������� �� ��������� UART5
#define UART6               ((UART_T            *)(UART6_BASE))                 ///< ��������� �� ��������� UART6
#define WDT                 ((WDT_T             *)(WDT_BASE))                   ///< ��������� �� ��������� WDT
#define TIMER1              ((TIMER_T           *)(TIMER1_BASE))                ///< ��������� �� ��������� TIMER1
#define TIMER2              ((TIMER_T           *)(TIMER2_BASE))                ///< ��������� �� ��������� TIMER2
#define TIMER3              ((TIMER_T           *)(TIMER3_BASE))                ///< ��������� �� ��������� TIMER3
#define TIMER4              ((TIMER_T           *)(TIMER4_BASE))                ///< ��������� �� ��������� TIMER4
#define RESERVE_P1          ((RES_P1            *)(RESERVE_P1_BASE))            ///< ������
#define RESERVE_P2          ((RES_P2            *)(RESERVE_P2_BASE))            ///< ������
#define RESERVE_P3          ((RES_P3            *)(RESERVE_P3_BASE))            ///< ������
#define RESERVE_P4          ((RES_P4            *)(RESERVE_P4_BASE))            ///< ������
#define CAN1                ((CAN_T             *)(CAN1_BASE))                  ///< ��������� �� ��������� CAN1
#define CAN2                ((CAN_T             *)(CAN2_BASE))                  ///< ��������� �� ��������� CAN2
#define CAN1_EXTANDED       ((CAN_EXTANDED_T    *)(CAN1_BASE))                  ///< ��������� �� ��������� CAN1_EXTANDED
#define CAN2_EXTANDED       ((CAN_EXTANDED_T    *)(CAN2_BASE))                  ///< ��������� �� ��������� CAN2_EXTANDED        
#define I2C                 ((I2C_T             *)(I2C_BASE))                   ///< ��������� �� ��������� I2C
#define SPW1                ((SPW_T             *)(SPW1_BASE))                  ///< ��������� �� ��������� SPW1
#define SPW2                ((SPW_T             *)(SPW2_BASE))                  ///< ��������� �� ��������� SPW2
#define MKPD1               ((MKPD_T            *)(MKPD1_BASE))                 ///< ��������� �� ��������� MKPD1
#define MKPD2               ((MKPD_T            *)(MKPD2_BASE))                 ///< ��������� �� ��������� MKPD2
#define MKPD3               ((MKPD_T            *)(MKPD3_BASE))                 ///< ��������� �� ��������� MKPD3
#define MKPD4               ((MKPD_T            *)(MKPD4_BASE))                 ///< ��������� �� ��������� MKPD4
#define TMTX                ((TMTX_T            *)(TMTX_BASE))                  ///< ��������� �� ��������� TMTX
#define TCRX                ((TCRX_T            *)(TCRX_BASE))                  ///< ��������� �� ��������� TCRX
#define FPU                 ((FPU_T             *)(FPU_BASE))                   ///< ��������� �� ��������� FPU
#define RESERVE_Q           ((RES_Q             *)(RESERVE_Q_B))                ///< ������
#define NVIC_MUX            ((volatile CONTROL_MUX_REGISTER  *)(NVIC_MUX_BASE)) ///< ��������� �� ��������� NVIC_MUX
                                                                                          

// ������������� �� ������ ���
#define SYSTICK_BASE        (0xE000E010)                                        /**<    ������� ����� ��������� ���������� �������� */
#define NVIC_BASE           (0xE000E100)                                        /**<    ������� ����� ��������� ���������� ������������ */
#define SYSCTRL_BASE        (0xE000ED00)                                        /**<    ������� ����� ��������� ���������� */ 
#define SYSTICK             ((SYSTICK_T         *)(SYSTICK_BASE))               /**<    ��������� �� ��������� � ���������� ���������� �������� */   
#define NVIC                ((NVIC_T            *)(NVIC_BASE))                  /**<    ��������� �� ��������� � ���������� ���������� ������������ */ 
#define SCB                 ((SCB_T             *)(SYSCTRL_BASE))               /**<    ��������� �� ��������� � ���������� ���������� */

#endif /* CHIP_5023BC016_H_ */

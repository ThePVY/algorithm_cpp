/*!\file
 * \brief Этот файл содержит описание адресного пространства микроконтроллера 5023ВС016.
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

#ifndef CHIP_5023BC016_H_
#define CHIP_5023BC016_H_
#include "system.h"


/**
 * @brief Распределение адресного пространства
 */
#define GPIO_A_BASE         (0x80000000)                                        /**<    Базовый адрес порта GPIO A */
#define GPIO_B_BASE         (0x80010000)                                        /**<    Базовый адрес порта GPIO B */
#define GPIO_C_BASE         (0x80020000)                                        /**<    Базовый адрес порта GPIO C */
#define GPIO_D_BASE         (0x80030000)                                        /**<    Базовый адрес порта GPIO D */
#define GPIO_E_BASE         (0x80040000)                                        /**<    Базовый адрес порта GPIO E */
#define GPIO_F_BASE         (0x80050000)                                        /**<    Базовый адрес порта GPIO F */
#define GPIO_G_BASE         (0x80060000)                                        /**<    Базовый адрес порта GPIO G */
#define GPIO_H_BASE         (0x80070000)                                        /**<    Базовый адрес порта GPIO H */
#define GPIO_I_BASE         (0x80080000)                                        /**<    Базовый адрес порта GPIO I */
#define CMN_REG_BASE        (0xA0000000)                                        /**<    Базовый адрес регистров общего назначения */
#define DMA_BASE            (0xA0010000)                                        /**<    Базовый адрес контроллера DMA */
#define SPI1_BASE           (0xA0020000)                                        /**<    Базовый адрес интерфейса SPI 1 */
#define SPI2_BASE           (0xA0030000)                                        /**<    Базовый адрес интерфейса SPI 2 */
#define UART1_BASE          (0xA0040000)                                        /**<    Базовый адрес интерфейса UART 1 */
#define UART2_BASE          (0xA0050000)                                        /**<    Базовый адрес интерфейса UART 2 */
#define UART3_BASE          (0xA0060000)                                        /**<    Базовый адрес интерфейса UART 3 */
#define UART4_BASE          (0xA0070000)                                        /**<    Базовый адрес интерфейса UART 4 */
#define WDT_BASE            (0xA0080000)                                        /**<    Базовый адрес сторожевого таймера Watchdog */  
#define TIMER1_BASE         (0xA0090000)                                        /**<    Базовый адрес таймера общего назначения Timer 1 */
#define SPW1_BASE           (0xA00A0000)                                        /**<    Базовый адрес интерфейса SpaceWire 1 */
#define SPW2_BASE           (0xA00B0000)                                        /**<    Базовый адрес интерфейса SpaceWire 2 */
#define MKPD1_BASE          (0xA00C0000)                                        /**<    Базовый адрес интерфейса МКПД 1 */
#define MKPD2_BASE          (0xA00D0000)                                        /**<    Базовый адрес интерфейса МКПД 2 */
#define MKPD3_BASE          (0xA00E0000)                                        /**<    Базовый адрес интерфейса МКПД 3 */
#define MKPD4_BASE          (0xA00F0000)                                        /**<    Базовый адрес интерфейса МКПД 4 */
#define TMTX_BASE           (0xA0100000)                                        /**<    Базовый адрес модуля TMTX */ 
#define TCRX_BASE           (0xA0110000)                                        /**<    Базовый адрес модуля TCRX */
#define FPU_BASE            (0xA0120000)                                        /**<    Базовый адрес блока FPU */ 
#define TIMER2_BASE         (0xA0130000)                                        /**<    Базовый адрес таймера общего назначения Timer 2 */ 
#define TIMER3_BASE         (0xA0140000)                                        /**<    Базовый адрес таймера общего назначения Timer 3 */ 
#define TIMER4_BASE         (0xA0150000)                                        /**<    Базовый адрес таймера общего назначения Timer 4 */ 
#define RESERVE_P1_BASE     (0xA0160000)                                        /**<    Резерв */ 
#define RESERVE_P2_BASE     (0xA0170000)                                        /**<    Резерв */ 
#define RESERVE_P3_BASE     (0xA0180000)                                        /**<    Резерв */ 
#define RESERVE_P4_BASE     (0xA0190000)                                        /**<    Резерв */
#define RESERVE_Q_B         (0xA01A0000)                                        /**<    Резерв */
#define CAN1_BASE           (0xA01B0000)                                        /**<    Базовый адрес интерфейса CAN 1 */
#define CAN2_BASE           (0xA01C0000)                                        /**<    Базовый адрес интерфейса CAN 1 */
#define NVIC_MUX_BASE       (0xA01D0000)                                        /**<    Базовый адрес мультиплексора прерываний */
#define UART5_BASE          (0xA01E0000)                                        /**<    Базовый адрес интерфейса UART 5 */
#define UART6_BASE          (0xA01F0000)                                        /**<    Базовый адрес интерфейса UART 6 */
#define I2C_BASE            (0xA0200000)                                        /**<    Базовый адрес интерфейса I2C */
                                                                          
/**
 * @brief Распределение адресного пространства - тестовый доступ к памяти 
 */
#define INT_MEM1_DATA_BASE  (0x60000000)                                        /**<    Базовый адрес доступа к памяти блока 1, данные */
#define INT_MEM1_ECC_BASE   (0x60100000)                                        /**<    Базовый адрес доступа к памяти блока 1, биты ECC */
#define INT_WAY_DATA_BASE   (0x61000000)                                        /**<    Базовый адрес доступа к памяти кэша, данные */
#define INT_WAY_CRC_BASE    (0x61100000)                                        /**<    Базовый адрес доступа к памяти кэша, CRC */
#define INT_MEM2_DATA_BASE  (0x62000000)                                        /**<    Базовый адрес доступа к памяти блока 2, данные */
#define INT_MEM2_ECC_BASE   (0x62100000)                                        /**<    Базовый адрес доступа к памяти блока 2, биты ECC */


/**
 * @brief Указатели на структуры
 */
#define GPIO_A              ((GPIO_T            *)(GPIO_A_BASE))                ///< Указатель на структуру GPIO_A
#define GPIO_B              ((GPIO_T            *)(GPIO_B_BASE))                ///< Указатель на структуру GPIO_B
#define GPIO_C              ((GPIO_T            *)(GPIO_C_BASE))                ///< Указатель на структуру GPIO_С
#define GPIO_D              ((GPIO_T            *)(GPIO_D_BASE))                ///< Указатель на структуру GPIO_D
#define GPIO_E              ((GPIO_T            *)(GPIO_E_BASE))                ///< Указатель на структуру GPIO_E
#define GPIO_F              ((GPIO_T            *)(GPIO_F_BASE))                ///< Указатель на структуру GPIO_F
#define GPIO_G              ((GPIO_T            *)(GPIO_G_BASE))                ///< Указатель на структуру GPIO_G
#define GPIO_H              ((GPIO_T            *)(GPIO_H_BASE))                ///< Указатель на структуру GPIO_H
#define GPIO_I              ((GPIO_T            *)(GPIO_I_BASE))                ///< Указатель на структуру GPIO_T
#define CMN_REG             ((CMN_REG_T         *)(CMN_REG_BASE))               ///< Указатель на структуру CMN_REG
#define DMA                 ((DMA_T             *)(DMA_BASE))                   ///< Указатель на структуру DMA
#define SPI1                ((SPI_T             *)(SPI1_BASE))                  ///< Указатель на структуру SPI1
#define SPI2                ((SPI_T             *)(SPI2_BASE))                  ///< Указатель на структуру SPI2
#define UART1               ((UART_T            *)(UART1_BASE))                 ///< Указатель на структуру UART1
#define UART2               ((UART_T            *)(UART2_BASE))                 ///< Указатель на структуру UART2
#define UART3               ((UART_T            *)(UART3_BASE))                 ///< Указатель на структуру UART3
#define UART4               ((UART_T            *)(UART4_BASE))                 ///< Указатель на структуру UART4
#define UART5               ((UART_T            *)(UART5_BASE))                 ///< Указатель на структуру UART5
#define UART6               ((UART_T            *)(UART6_BASE))                 ///< Указатель на структуру UART6
#define WDT                 ((WDT_T             *)(WDT_BASE))                   ///< Указатель на структуру WDT
#define TIMER1              ((TIMER_T           *)(TIMER1_BASE))                ///< Указатель на структуру TIMER1
#define TIMER2              ((TIMER_T           *)(TIMER2_BASE))                ///< Указатель на структуру TIMER2
#define TIMER3              ((TIMER_T           *)(TIMER3_BASE))                ///< Указатель на структуру TIMER3
#define TIMER4              ((TIMER_T           *)(TIMER4_BASE))                ///< Указатель на структуру TIMER4
#define RESERVE_P1          ((RES_P1            *)(RESERVE_P1_BASE))            ///< Резерв
#define RESERVE_P2          ((RES_P2            *)(RESERVE_P2_BASE))            ///< Резерв
#define RESERVE_P3          ((RES_P3            *)(RESERVE_P3_BASE))            ///< Резерв
#define RESERVE_P4          ((RES_P4            *)(RESERVE_P4_BASE))            ///< Резерв
#define CAN1                ((CAN_T             *)(CAN1_BASE))                  ///< Указатель на структуру CAN1
#define CAN2                ((CAN_T             *)(CAN2_BASE))                  ///< Указатель на структуру CAN2
#define CAN1_EXTANDED       ((CAN_EXTANDED_T    *)(CAN1_BASE))                  ///< Указатель на структуру CAN1_EXTANDED
#define CAN2_EXTANDED       ((CAN_EXTANDED_T    *)(CAN2_BASE))                  ///< Указатель на структуру CAN2_EXTANDED        
#define I2C                 ((I2C_T             *)(I2C_BASE))                   ///< Указатель на структуру I2C
#define SPW1                ((SPW_T             *)(SPW1_BASE))                  ///< Указатель на структуру SPW1
#define SPW2                ((SPW_T             *)(SPW2_BASE))                  ///< Указатель на структуру SPW2
#define MKPD1               ((MKPD_T            *)(MKPD1_BASE))                 ///< Указатель на структуру MKPD1
#define MKPD2               ((MKPD_T            *)(MKPD2_BASE))                 ///< Указатель на структуру MKPD2
#define MKPD3               ((MKPD_T            *)(MKPD3_BASE))                 ///< Указатель на структуру MKPD3
#define MKPD4               ((MKPD_T            *)(MKPD4_BASE))                 ///< Указатель на структуру MKPD4
#define TMTX                ((TMTX_T            *)(TMTX_BASE))                  ///< Указатель на структуру TMTX
#define TCRX                ((TCRX_T            *)(TCRX_BASE))                  ///< Указатель на структуру TCRX
#define FPU                 ((FPU_T             *)(FPU_BASE))                   ///< Указатель на структуру FPU
#define RESERVE_Q           ((RES_Q             *)(RESERVE_Q_B))                ///< Резерв
#define NVIC_MUX            ((volatile CONTROL_MUX_REGISTER  *)(NVIC_MUX_BASE)) ///< Указатель на структуру NVIC_MUX
                                                                                          

// СОВМЕСТИМОСТЬ СО СТАРОЙ ВЕР
#define SYSTICK_BASE        (0xE000E010)                                        /**<    Базовый адрес регистров системного счетчика */
#define NVIC_BASE           (0xE000E100)                                        /**<    Базовый адрес регистров управления прерываниями */
#define SYSCTRL_BASE        (0xE000ED00)                                        /**<    Базовый адрес регистров управления */ 
#define SYSTICK             ((SYSTICK_T         *)(SYSTICK_BASE))               /**<    Указатель на структуру с регистрами системного счетчика */   
#define NVIC                ((NVIC_T            *)(NVIC_BASE))                  /**<    Указатель на структуру с регистрами управления прерываниями */ 
#define SCB                 ((SCB_T             *)(SYSCTRL_BASE))               /**<    Указатель на структуру с регистрами управления */

#endif /* CHIP_5023BC016_H_ */

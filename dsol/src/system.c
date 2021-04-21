/*!\mainpage
 *      Настоящее описание распространяется на библиотеку для интегральной микросхемы 5023ВС016 (далее — микросхема СБИС CPU), 
 * предназначенной для применения в качестве специализированной схемы обработки информации в радиоэлектронной аппаратуре специального назначения.
 * Радиационно-стойкая специализированная микросхема 5023ВС016 предназначена для построения аппаратуры контрольно-измерительных систем (КИС), 
 * телеметрии служебных систем космических аппаратов с учетом эксплуатации их в жестких условиях специальных видов воздействующих факторов.
 *      Микросхема может использоваться для организации каналов связи по интерфейсам магистральной последовательной шины по ГОСТ Р 52070 с резервированием.
 * При этом микросхема может использоваться в качестве контроллера шины (КШ), оконечного устройства (ОУ), а также монитора.
 *      Наличие двух контроллеров интерфейсов SpaceWire со скоростью передачи данных до 100 Мбит/с позволяет использовать микросхему в каналах передачи данных данного типа.
 *      Микросхема имеет блоки передатчика телеметрической информации и приёмника телекомандной информации, позволяющие использовать различные виды кодирования (LDPC, Турбо, Рида-Соломона).
 *      Применение микросхемы позволяет создавать системы управления космическими аппаратами совместимыми с международными стандартами CCSDS,
 * уменьшить массогабаритные характеристики и потребляемую мощность аппаратуры КИС, телеметрии служебных систем космических аппаратов в 4 – 5 раз и 
 * обеспечить требования Федерального космического агентства по дозовой стойкости и воздействию тяжелых заряженных частиц.
 * 
 * Структура описания состоит из описания библиотеки (папка sputnik_lib) и описания примеров использования библиотеки (папка sputnik_demo).
 * Папка sputnik_lib включает в себя:
 *   
 *  - include - здесь находятся описания всех заголовочных файлов библиотеки
 *  - source - здесь находятся описания всех файлов реализации библиотеки
 *
 * Папка sputnik_demo включает в себя:
 *   - periph_alise - пример настройки алиасинга
 *   - periph_can - пример использования can
 *   - periph_cache - пример использования cache
 *   - periph_diod - пример использования диода
 *   - periph_i2c - пример использования I2C 
 *   - periph_fpu - пример использования FPU
 *   - periph_gpio - пример использования gpio
 *   - periph_mem_test- пример использования памяти
 *   - periph_MKPD - пример использования manchester
 *   - periph_spacewire - пример использования spacewire
 *   - periph_spi - пример использования SPI
 *   - periph_timer - пример использования timer
 *   - periph_TCRX - пример использования TCRX
 *   - periph_tmtx - пример использования tmtx
 *   - periph_uart - пример использования uart
 *   - periph_watchdog - пример использования watchdog
 *   - spw_rmap_test-KIT_V2 - пример использования RMAP
 *   - test_dma - пример использования dma
 * 
 *   В библиотеку входят заголовки и файлы исходного кода для работы со всеми модулями микросхемы, см.
 *  <a href="files.html"><span>список файлов</span></a>

 * \file
 * \brief Этот файл содержит функции, необходимые для взаимодействия с регистрами общего назначения.
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
 * что это программное обеспечнение используется совместно с микроконтроллерами организации
 * "Цифровые решения". Эти права должны распространяться во всех копиях этого кода.
 */

#include "system.h"

/**
 * @brief	Разрешение прерывания
 * @param	IRQn	: Номер прерывания
 */
void NVIC_EnableIRQ(IRQn_T IRQn, uint32_t vec)
{
    switch (IRQn)
    {
         case Watchdog:
            NVIC_MUX->INTR_MUX_CTRL_Watchdog = NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_Watchdog |=(uint32_t)(1<<31);  
            break;
         case Timer1:            
            NVIC_MUX->INTR_MUX_CTRL_Timer1 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_Timer1 |=(uint32_t)(1<<31);     
            break;
         case Timer2:
            NVIC_MUX->INTR_MUX_CTRL_Timer2 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_Timer2 |=(uint32_t)(1<<31); 
            break;
        case Timer3:
            NVIC_MUX->INTR_MUX_CTRL_Timer3 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_Timer3 |=(uint32_t)(1<<31); 
            break;
        case Timer4:
            NVIC_MUX->INTR_MUX_CTRL_Timer4 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_Timer4 |=(uint32_t)(1<<31); 
            break;
        case GPIOA:
            NVIC_MUX->INTR_MUX_CTRL_GPIOA =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_GPIOA |=(uint32_t)(1<<31); 
            break;
        case GPIOB:
            NVIC_MUX->INTR_MUX_CTRL_GPIOB =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_GPIOB |=(uint32_t)(1<<31); 
            break;
        case GPIOC:
            NVIC_MUX->INTR_MUX_CTRL_GPIOC =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_GPIOC |=(uint32_t)(1<<31); 
            break;
        case GPIOD:
            NVIC_MUX->INTR_MUX_CTRL_GPIOD =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_GPIOD |=(uint32_t)(1<<31); 
            break;
        case GPIOE:
            NVIC_MUX->INTR_MUX_CTRL_GPIOE =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_GPIOE |=(uint32_t)(1<<31); 
            break;
        case GPIOF:
            NVIC_MUX->INTR_MUX_CTRL_GPIOF =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_GPIOF |=(uint32_t)(1<<31); 
            break;
        case GPIOG:
            NVIC_MUX->INTR_MUX_CTRL_GPIOG =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_GPIOG |=(uint32_t)(1<<31); 
            break;
        case GPIOH:
            NVIC_MUX->INTR_MUX_CTRL_GPIOH =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_GPIOH |=(uint32_t)(1<<31); 
            break;
        case GPIOI:
            NVIC_MUX->INTR_MUX_CTRL_GPIOI =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_GPIOI |=(uint32_t)(1<<31); 
            break; 
        case UART_1:
            NVIC_MUX->INTR_MUX_CTRL_UART1 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_UART1 |=(uint32_t)(1<<31); 
            break;
        case UART_2:
            NVIC_MUX->INTR_MUX_CTRL_UART2 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_UART2 |=(uint32_t)(1<<31); 
            break;
        case UART_3:
            NVIC_MUX->INTR_MUX_CTRL_UART3 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_UART3 |=(uint32_t)(1<<31); 
            break;
        case UART_4:
            NVIC_MUX->INTR_MUX_CTRL_UART4 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_UART4 |=(uint32_t)(1<<31); 
            break;
        case UART_5:
            NVIC_MUX->INTR_MUX_CTRL_UART5 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_UART5 |=(uint32_t)(1<<31); 
            break;
        case UART_6:
            NVIC_MUX->INTR_MUX_CTRL_UART6 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_UART6 |=(uint32_t)(1<<31); 
            break;
        case SPI_1:
            NVIC_MUX->INTR_MUX_CTRL_SPI1 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_SPI1 |=(uint32_t)(1<<31); 
            break;
        case SPI_2:
            NVIC_MUX->INTR_MUX_CTRL_SPI2 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_SPI2 |=(uint32_t)(1<<31); 
            break;
        case Spacewire1:
            NVIC_MUX->INTR_MUX_CTRL_SPACEWIRE1 &=~NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_SPACEWIRE1 |=NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_SPACEWIRE1 &=~INTR_SRC_ENABLE; 
            NVIC_MUX->INTR_MUX_CTRL_SPACEWIRE1 |=INTR_SRC_ENABLE; 
            break;
        case Spacewire2:
            NVIC_MUX->INTR_MUX_CTRL_SPACEWIRE2 &=~NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_SPACEWIRE2 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_SPACEWIRE2 &=~INTR_SRC_ENABLE; 
            NVIC_MUX->INTR_MUX_CTRL_SPACEWIRE2 |=INTR_SRC_ENABLE; 
            break;
        case MKPD1_NUM:
            NVIC_MUX->INTR_MUX_CTRL_MKPD1 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_MKPD1 |=(uint32_t)(1<<31); 
            break;
        case MKPD2_NUM:
            NVIC_MUX->INTR_MUX_CTRL_MKPD2 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_MKPD2|=(uint32_t)(1<<31); 
            break;
        case MKPD3_NUM:
            NVIC_MUX->INTR_MUX_CTRL_MKPD3 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_MKPD3|=(uint32_t)(1<<31); 
            break;
        case MKPD4_NUM:
            NVIC_MUX->INTR_MUX_CTRL_MKPD4 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_MKPD4|=(uint32_t)(1<<31); 
            break;
        case TMTX_NUM:
            NVIC_MUX->INTR_MUX_CTRL_TMTX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_TMTX|=(uint32_t)(1<<31); 
            break;
        case TCRX_NUM:
            NVIC_MUX->INTR_MUX_CTRL_TCRX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_TCRX|=(uint32_t)(1<<31); 
            break;
        case I2C_NUM:
            NVIC_MUX->INTR_MUX_CTRL_I2C =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_I2C|=(uint32_t)(1<<31); 
            break;
        case CAN1_NUM:
            NVIC_MUX->INTR_MUX_CTRL_CAN1 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_CAN1|=(uint32_t)(1<<31); 
            break;
        case CAN2_NUM:
            NVIC_MUX->INTR_MUX_CTRL_CAN2 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_CAN2|=(uint32_t)(1<<31); 
            break;
        case EDAC:
            NVIC_MUX->INTR_MUX_CTRL_EDAC =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_EDAC|=(uint32_t)(1<<31); 
            break;
        case RES_Q_NUM:
            NVIC_MUX->INTR_MUX_CTRL_RES_Q =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_RES_Q|=(uint32_t)(1<<31); 
            break;
        case RESERVE_P1_NUM:
            NVIC_MUX->INTR_MUX_CTRL_RES_P1 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_RES_P1|=(uint32_t)(1<<31); 
            break;
        case RESERVE_P2_NUM:
            NVIC_MUX->INTR_MUX_CTRL_RES_P2 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_RES_P2|=(uint32_t)(1<<31); 
            break;
        case RESERVE_P3_NUM:
            NVIC_MUX->INTR_MUX_CTRL_RES_P3 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_RES_P3|=(uint32_t)(1<<31); 
            break;
        case RESERVE_P4_NUM:
            NVIC_MUX->INTR_MUX_CTRL_RES_P4 =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_RES_P4|=(uint32_t)(1<<31); 
            break;
        case DMA_SPI_1_TX:
            NVIC_MUX->INTR_MUX_CTRL_DMASPI1_TX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMASPI1_TX|=(uint32_t)(1<<31); 
            break;
        case DMA_SPI_1_RX:
            NVIC_MUX->INTR_MUX_CTRL_DMASPI1_RX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMASPI1_RX|=(uint32_t)(1<<31); 
            break;
        case DMA_SPI_2_TX:
            NVIC_MUX->INTR_MUX_CTRL_DMASPI2_TX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMASPI2_TX|=(uint32_t)(1<<31); 
            break;
        case DMA_SPI_2_RX:
            NVIC_MUX->INTR_MUX_CTRL_DMASPI2_RX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMASPI2_RX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_1_TX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART1_TX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART1_TX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_1_RX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART1_RX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART1_RX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_2_TX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART2_TX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART2_TX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_2_RX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART2_RX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART2_RX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_3_TX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART3_TX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART3_TX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_3_RX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART3_RX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART3_RX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_4_TX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART4_TX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART4_TX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_4_RX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART4_RX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART4_RX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_5_TX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART5_TX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART5_TX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_5_RX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART5_RX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART5_RX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_6_TX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART6_TX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART6_TX|=(uint32_t)(1<<31); 
            break;
        case DMA_UART_6_RX:
            NVIC_MUX->INTR_MUX_CTRL_DMAUART6_RX =NUM_INTR_VECTOR(vec); 
            NVIC_MUX->INTR_MUX_CTRL_DMAUART6_RX|=(uint32_t)(1<<31); 
            break;
        case DMA_CHAN16:
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN16 = NUM_INTR_VECTOR(vec);
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN16 |= (uint32_t)(1<<31);
            break;
        case DMA_CHAN17:
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN17 = NUM_INTR_VECTOR(vec);
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN17 |= (uint32_t)(1<<31);
            break;
        case DMA_CHAN18:
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN18 = NUM_INTR_VECTOR(vec);
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN18 |= (uint32_t)(1<<31);
            break;            
        case DMA_CHAN19:
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN19 = NUM_INTR_VECTOR(vec);
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN19 |= (uint32_t)(1<<31);
            break;            
        case DMA_CHAN20:
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN20 = NUM_INTR_VECTOR(vec);
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN20 |= (uint32_t)(1<<31);
            break;            
        case DMA_CHAN21:
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN21 = NUM_INTR_VECTOR(vec);
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN21 |= (uint32_t)(1<<31);
            break;            
        case DMA_CHAN22:
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN22 = NUM_INTR_VECTOR(vec);
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN22 |= (uint32_t)(1<<31);
            break;            
        case DMA_CHAN23:
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN23 = NUM_INTR_VECTOR(vec);
            NVIC_MUX->INTR_MUX_CTRL_DMA_CHAN23 |= (uint32_t)(1<<31);
            break;                        
    }    
    NVIC_En_IRQ(vec);                                                           /*< Разрешение прерываний*/
}
/**
 * @brief	Ввод модуля в асинхронный сброс
 * @param	CTRLn	: Номер модуля
 */
void PWR_RST_Enable(CTRL_T CTRLn)
{
    CMN_REG->PWR_CTRL_RST &= ~((uint32_t)(1 << CTRLn)); 
}

/**
 * @brief	Вывод модуля из асинхронного сброса 
 * @param	CTRLn	: Номер модуля
 */
void PWR_RST_Disable(CTRL_T CTRLn)
{
    CMN_REG->PWR_CTRL_RST &= ~((uint32_t)(1 << CTRLn)); 
    CMN_REG->PWR_CTRL_RST |= (uint32_t)(1 << CTRLn); 
}

/**
 * @brief	Отключение тактового сигнала от модуля
 * @param	CTRLn	: Номер модуля
 */
void PWR_CLK_Disable(CTRL_T CTRLn)
{
    CMN_REG->PWR_CTRL_CLK &= ~((uint32_t)(1 << CTRLn)); 
}

/**
 * @brief	Подача тактового сигнала на модуль
 * @param	CTRLn	: Номер модуля
 */
void PWR_CLK_Enable(CTRL_T CTRLn)
{
    CMN_REG->PWR_CTRL_CLK &= ~((uint32_t)(1 << CTRLn)); 
    CMN_REG->PWR_CTRL_CLK |= (uint32_t)(1 << CTRLn); 
}

/**
 * @brief	Запрещение прерывания
 * @param	IRQn	: Номер прерывания
 */
void NVIC_DisableIRQ(uint32_t vec)
{
    NVIC_Dis_IRQ(vec);
}

void SystemInit (void)
{  
    CMN_REG->EXTMEM_CTRL = EXT_MEM_TURN_CYCLES(7) | EXT_MEM_WRITE_CYCLES(7) | EXT_MEM_READ_CYCLES(7);
	CMN_REG->EXTMEM2_CTRL = EXT_MEM_TURN_CYCLES_2_4(7) | EXT_MEM_WRITE_CYCLES_2_4(7) | EXT_MEM_READ_CYCLES_2_4(7) | EXT_MEM_SIZE_2_4;  
   // CMN_REG->EDAC_CTRL  |= EDAC_En_1 ;
   // CMN_REG->EDAC_CTRL  |= EDAC_En_2 ;
}


/*!\file
 * \brief Этот файл содержит функции, необходимые для взаимодействия с отладочным выводом.
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

#include "chip_5023BC016.h"
#include "uart.h"
#include "debug_uart.h"
#include "ringbuffer.h"
#include "system.h"
#include "gpio.h"

RINGBUFF_T      dbg_uart_tx_rb;                                                 ///< Кольцевой буфер отладочного UART 
uint8_t         dbg_uart_tx_buf[DEBUG_UART_RB_SIZE];                            ///< Массив, используемый коьлцевым буфером. 
UART_T * DEBUG_UART = UART1;                                        /**< Выбор UART1 в качестве отладочного UART*/

/**
 * @brief	Инициализация отладочного UART'а
 */
void DBG_UART_Init(void)
{
#ifdef ENABLE_DEBUG_UART
    CMN_REG->PWR_CTRL_CLK |= (1<<2);                                              // Включение тактовых сигналов модуля
    CMN_REG->PWR_CTRL_RST |= (1<<2);                                              // Сброс соответствующего модуля
    UART_Init(UART1);                                                             // Инициализация UART-а
    UART_SetBaud(UART1, BAUDRATE_921600, 80000000);                               // Установка длины слова данных, числа стоповых бит и контроля четности//                              UART_LCR_H_FEN |                              //    UART_Config(UART_NUM[1], 112);
    UART_Config(UART1, 112);                                                      // Определение и установка оптимальных параметров делителя частоты                              //    UART_Config(UART_NUM[1], 112);
    UART_Enable(UART1);                                                           // Разрешение работы UART   
    UART_TXEnable(UART1);                                                         // Разрешение работы передатчика
    UART_RXEnable(UART1);
    UART_SetupFIFOS(UART1, UART_IFLS_7DIV8, UART_IFLS_1DIV8);                     // Установка порогов прерываний по заполнению буфера приемника/передатчика
    RingBuffer_Init(&dbg_uart_tx_rb, dbg_uart_tx_buf, 1, DEBUG_UART_RB_SIZE);     // Инициализация кольцевого буфера
    //PRINT("__DEBUG_ENABLED");
#endif
}

void DBG_UART_Init_Args(UART_T *pUART,uint32_t baud)
{
     DEBUG_UART = pUART; 
#ifdef ENABLE_DEBUG_UART
    if (pUART==UART1)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<2);                                          // Включение тактовых сигналов модуля
        CMN_REG->PWR_CTRL_RST |= (1<<2);                                          // Сброс соответствующего модуля
    }
    if (pUART==UART2)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<3);                                          // Включение тактовых сигналов модуля
        CMN_REG->PWR_CTRL_RST |= (1<<3);                                          // Сброс соответствующего модуля
    }
    if (pUART==UART3)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<4);                                          // Включение тактовых сигналов модуля
        CMN_REG->PWR_CTRL_RST |= (1<<4);                                          // Сброс соответствующего модуля
    }
    if (pUART==UART4)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<5);                                          // Включение тактовых сигналов модуля
        CMN_REG->PWR_CTRL_RST |= (1<<5);                                          // Сброс соответствующего модуля
    }
    if (pUART==UART5)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<22);                                         // Включение тактовых сигналов модуля
        CMN_REG->PWR_CTRL_RST |= (1<<22);                                         // Сброс соответствующего модуля
    }
    if (pUART==UART6)
    {
        CMN_REG->PWR_CTRL_CLK |= (1<<23);                                         // Включение тактовых сигналов модуля
        CMN_REG->PWR_CTRL_RST |= (1<<23);                                         // Сброс соответствующего модуля
    }
    UART_Init(pUART);                                                             // Инициализация UART-а
    UART_SetBaud(pUART, baud, 80000000);                                          // Установка длины слова данных, числа стоповых бит и контроля четности//                              UART_LCR_H_FEN |                              //    UART_Config(UART_NUM[1], 112);
    UART_Config(pUART, 112);                                                      // Определение и установка оптимальных параметров делителя частоты                              //    UART_Config(UART_NUM[1], 112);
    UART_Enable(pUART);                                                           // Разрешение работы UART   
    UART_TXEnable(pUART);                                                         // Разрешение работы передатчика
    UART_RXEnable(pUART);
    UART_SetupFIFOS(pUART, UART_IFLS_7DIV8, UART_IFLS_1DIV8);                     // Установка порогов прерываний по заполнению буфера приемника/передатчика
    RingBuffer_Init(&dbg_uart_tx_rb, dbg_uart_tx_buf, 1, DEBUG_UART_RB_SIZE);     // Инициализация кольцевого буфера
    //PRINT("__DEBUG_ENABLED");
#endif
}

/**
 * @brief	Пересылка данных, накопленных в кольцевом буфере, в отладочный UART
 */
void DBG_TX_Process(void)
{
#ifdef ENABLE_DEBUG_UART
    uint8_t ch;
    if (!(UART_GetStatus(DEBUG_UART, UART_FR_BUSY))) 
    {
        if(RingBuffer_Pop(&dbg_uart_tx_rb, &ch))
        {
            UART_SendByte(DEBUG_UART, ch);
        }
    }
#endif
}

/**
 * @brief	Вывод всех данных, накопленных в кольцевом буфере, в отладочный UART
 */
void DBG_TX_Flush(void)
{
#ifdef ENABLE_DEBUG_UART
    uint8_t ch;
    while (!(RingBuffer_IsEmpty(&dbg_uart_tx_rb)))
    {
        if (!(UART_GetStatus(DEBUG_UART, UART_FR_BUSY))) 
        {
            if(RingBuffer_Pop(&dbg_uart_tx_rb, &ch))
            {
                UART_SendByte(DEBUG_UART, ch);
            }
        }
    }
#endif
}

/**
 * @brief	Запись строки данных в кольцевой буфер
 * @param	buffer	: Указатель на строку
 */
void DBG_WriteBuffer(char *buffer)
{
//#ifdef ENABLE_DEBUG_UART
    uint32_t length;
    length = strlen(buffer);
    RingBuffer_InsertMult(&dbg_uart_tx_rb, buffer, length);
//#endif  
}

/**
 * @brief	Вывод содержимого массива в отладочный UART
 * @param	buffer	: Указатель на массив
 * @param	length	: Длина данных для вывода
*/
void DBG_ShowBuffer(uint8_t *buffer, uint32_t length)
{
#ifdef ENABLE_DEBUG_UART
    uint32_t i;
    if (length) 
    {
        for(i=0; i<length; i++)
        {
            snprintf(dbg_buffer,256,"%02x ",buffer[i]);
            DBG_WriteBuffer(dbg_buffer);
        }
        DBG_WriteBuffer("\n");
    }
#endif
}

void gpioInit()
{
    GPIO_D->ALTFUNCSET |= (1 << 15); //uart1 tx
    GPIO_E->ALTFUNCSET |= (1 << 0);  //uart1 rx
    
   // GPIO_E->ALTFUNCSET |= (1 << 1);  //uart1 rx
   // GPIO_E->ALTFUNCSET |= (1 << 2);  //uart1 rx
}

//void clockInit()
//{
//    CMN_REG->PWR_CTRL_CLK |= (1<<2);
//    CMN_REG->PWR_CTRL_RST |= (1<<2);
//}

/**
 * @brief	Получение символа из отладочного UART'а
 * @return	Полученный символ
*/
uint8_t DBG_GetChar(void)
{
#ifdef ENABLE_DEBUG_UART
    if (!(UART_GetStatus(DEBUG_UART, UART_FR_RXFE))) 
    {
	return (uint8_t) UART_ReadByte(DEBUG_UART);
    }
#endif
    return EOF;
}
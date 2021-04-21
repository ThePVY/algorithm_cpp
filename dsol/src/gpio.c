/*!\file
 * \brief Этот файл содержит функции, необходимые для взаимодействия с аппаратным модулем GPIO.
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

// gf_ver 2.2.0

#include "gpio.h"

/**
 * @brief Сконфигурировать вывод порта GPIO
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @param Pin_number: номер вывода (0..15).
 * @param Dir: тип конфигурации   
 *         Параметр Dir может принимать значения:
 *          @arg true: сконфигурировать на выход 
 *          @arg false: сконфигурировать на вход
 * @retval None.
 */
void GPIO_WriteDirBit(GPIO_T *pGPIO, uint8_t Pin_number, bool Dir)
{
    if (Dir) 
    {
        pGPIO->OUTENSET = (1UL << Pin_number);
    }
    else 
    {
	pGPIO->OUTENCLR = (1UL << Pin_number);
    }
}

 /**
 * @brief Установить режим GPIO или режим альтернативной функции.
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @param Pin_number: номер вывода (0..15).
 * @param AltSet: установка режима. 
 *         Параметр AltSet может принимать значения:
 *          @arg true: режим альтернативной функции, 
 *          @arg false: режим GPIO
 * @retval None.
 */
void GPIO_SetAltFunc(GPIO_T *pGPIO, uint16_t Pin_number, bool AltSet)
{
    if(AltSet)
    {
        pGPIO->ALTFUNCSET = (1UL << Pin_number);
    } 
    else 
    {
        pGPIO->ALTFUNCCLR = (1UL << Pin_number);
    }
}

 /**
 * @brief Запись данных в порт GPIO.
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @param mask: Маска соответствует выводам на порте, если бит в маске равен 1, 
 *              то состояние соответствующего вывода на порте будет обновлено.
 * @param val: значение записываемое в порт. 
 * @retval None.
 */
void GPIO_WritePort(GPIO_T *pGPIO, uint16_t mask, uint16_t val)
{
    if(mask & 0x00FF)
    {
        pGPIO->MASKLOWBYTE[mask & 0x00FF] = val;
    }
    if((mask & 0xFF00)>>8)
    {
        pGPIO->MASKHIGHBYTE[(mask & 0xFF00)>>8] = val;
    }
}

 /**
 * @brief Установка состояния на выводе порта GPIO.
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @param pin: номер вывода (0..15).
 * @param val: значение состояния. 
 *         Параметр val может принимать значения:
 *          @arg true: высокое состояние, 
 *          @arg false: низкое состояние
 * @retval None.
 */
void GPIO_WritePortBit(GPIO_T *pGPIO, uint8_t pin, bool val)
{
    if(pin<8)
    {
        pGPIO->MASKLOWBYTE[1 << pin] = val << pin;
    }
    else
    {
        pGPIO->MASKHIGHBYTE[(1 << pin)>>8] = (val << pin);
    }
}

/**
 * @brief Считать состояние выводов сконфигурированных на выход	
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @retval Текущее состояние выводов
 */
uint32_t GPIOOUT_ReadPort(GPIO_T *pGPIO)
{
    return (uint32_t)(pGPIO->DATAOUT);
}

/**
 * @brief Считать состояние выводов сконфигурированных на вход	
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @retval Текущее состояние выводов
 */
uint32_t GPIOIN_ReadPort(GPIO_T *pGPIO)
{
    return (uint32_t)(pGPIO->DATA);
}

/**
 * @brief Считать состояние вывода сконфигурированого на выход
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @param pin: номер вывода (0..15).
 * @retval Текущее состояние вывода: true - высокое, false - низкое
 */
bool GPIOOUT_ReadPortBit(GPIO_T *pGPIO, uint8_t pin)
{
    return (bool)(((pGPIO->DATAOUT) >> pin) & 1);
}

/**
 * @brief Считать состояние вывода сконфигурированного на вход 
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @param pin: номер вывода (0..15).
 * @retval Текущее состояние вывода: true - высокое, false - низкое
 */
bool GPIOIN_ReadPortBit(GPIO_T *pGPIO, uint8_t pin)
{
   return (bool)(((pGPIO->DATA) >> pin) & 1);
}

/**
 * @brief Считать конфигурацию вывода GPIO
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @param pin: номер вывода (0..15).
 * @retval Текущая конфигурация вывода: true - на выход, false - на вход
 */
bool GPIO_ReadDirBit(GPIO_T *pGPIO, uint8_t pin)
{
    return (bool)(((pGPIO->OUTENSET) >> pin) & 1);
}

/**
 * @brief Считать конфигурацию выводов GPIO
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @retval Текущее значение регистра OUTENSET
 */
uint32_t GPIO_GetDir(GPIO_T *pGPIO)
{
    return (uint32_t)(pGPIO->OUTENSET);
}

/**
 * @brief Считать установленный режим
 * @note  Выбран режим GPIO или режим альтернативной функции
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @retval Текущее значение регистра ALTFUNCSET
 */
uint32_t GPIO_GetAltFunc(GPIO_T *pGPIO)
{
    return (uint32_t)(pGPIO->ALTFUNCSET);
}

/**
 * @brief Настроить профиль прерывания.
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @param Pin_number: номер вывода (0..15).
 * @param IntMode: профиль настройки прерывания.
 *         Параметр GPIOPINT_MODE_T может принимать значения:
 *          @arg GPIOPINT_FRONT_HIGHT: работа по уровню, высокий логический уровень
 *          @arg GPIOPINT_FRONT_LOW: работа по уровню, низкий логический уровень
 *          @arg GPIOPINT_RISING_EDGE: работа по фронту, высокий логический уровень
 *          @arg GPIOPINT_FALLING_EDGE: работа по фронту, низкий логический уровень
 * @retval None.
 */
void GPIO_IntConfig(GPIO_T *pGPIO, uint32_t Pin_number, GPIOPINT_MODE_T IntMode)
{
    switch(IntMode)
    {
        case GPIOPINT_FRONT_HIGHT:
            pGPIO->INTTYPESET = (1 << Pin_number);
            pGPIO->INTPOLSET =  (1 << Pin_number);
            break;
        case GPIOPINT_FRONT_LOW:
            pGPIO->INTTYPESET = (1 << Pin_number);
            pGPIO->INTPOLCLR =  (1 << Pin_number);
            break;
        case GPIOPINT_RISING_EDGE:
            pGPIO->INTTYPECLR = (1 << Pin_number);
            pGPIO->INTPOLSET =  (1 << Pin_number);
            break;
        case GPIOPINT_FALLING_EDGE:
            pGPIO->INTTYPECLR = (1 << Pin_number);
            pGPIO->INTPOLCLR =  (1 << Pin_number);
            break;
        default:
            break;
  }
}

/**
 * @brief Взять текущий статус прерываня для каждого вывода
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @retval Текущий статус прерываний
 */
uint32_t GPIO_IntGetStatus(GPIO_T *pGPIO)
{
    return (uint32_t)(pGPIO->INTSTATUS);
}

/**
 * @brief Взять текущий профиль прерывания для вывода
 * @param pGPIO: указатель на структуру с регистрами GPIO.
 * @param pin: номер вывода (0..15).
 * @retval Текущий профиль прерывания
 */ 
GPIOPINT_MODE_T GPIO_GetIntConfigPin(GPIO_T *pGPIO, uint8_t pin)
{
    uint32_t p1=((pGPIO->INTTYPESET)&(1<<pin));  
    uint32_t p2=(pGPIO->INTPOLSET&(1<<pin));
    return (GPIOPINT_MODE_T)(((p1>>pin)<<1) | (p2>>pin));                             
}        



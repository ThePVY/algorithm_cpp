/*!\file
 * \brief ���� ���� �������� �������, ����������� ��� �������������� � ���������� ������� GPIO.
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

// gf_ver 2.2.0

#include "gpio.h"

/**
 * @brief ���������������� ����� ����� GPIO
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @param Pin_number: ����� ������ (0..15).
 * @param Dir: ��� ������������   
 *         �������� Dir ����� ��������� ��������:
 *          @arg true: ���������������� �� ����� 
 *          @arg false: ���������������� �� ����
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
 * @brief ���������� ����� GPIO ��� ����� �������������� �������.
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @param Pin_number: ����� ������ (0..15).
 * @param AltSet: ��������� ������. 
 *         �������� AltSet ����� ��������� ��������:
 *          @arg true: ����� �������������� �������, 
 *          @arg false: ����� GPIO
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
 * @brief ������ ������ � ���� GPIO.
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @param mask: ����� ������������� ������� �� �����, ���� ��� � ����� ����� 1, 
 *              �� ��������� ���������������� ������ �� ����� ����� ���������.
 * @param val: �������� ������������ � ����. 
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
 * @brief ��������� ��������� �� ������ ����� GPIO.
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @param pin: ����� ������ (0..15).
 * @param val: �������� ���������. 
 *         �������� val ����� ��������� ��������:
 *          @arg true: ������� ���������, 
 *          @arg false: ������ ���������
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
 * @brief ������� ��������� ������� ������������������ �� �����	
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @retval ������� ��������� �������
 */
uint32_t GPIOOUT_ReadPort(GPIO_T *pGPIO)
{
    return (uint32_t)(pGPIO->DATAOUT);
}

/**
 * @brief ������� ��������� ������� ������������������ �� ����	
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @retval ������� ��������� �������
 */
uint32_t GPIOIN_ReadPort(GPIO_T *pGPIO)
{
    return (uint32_t)(pGPIO->DATA);
}

/**
 * @brief ������� ��������� ������ ������������������ �� �����
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @param pin: ����� ������ (0..15).
 * @retval ������� ��������� ������: true - �������, false - ������
 */
bool GPIOOUT_ReadPortBit(GPIO_T *pGPIO, uint8_t pin)
{
    return (bool)(((pGPIO->DATAOUT) >> pin) & 1);
}

/**
 * @brief ������� ��������� ������ ������������������� �� ���� 
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @param pin: ����� ������ (0..15).
 * @retval ������� ��������� ������: true - �������, false - ������
 */
bool GPIOIN_ReadPortBit(GPIO_T *pGPIO, uint8_t pin)
{
   return (bool)(((pGPIO->DATA) >> pin) & 1);
}

/**
 * @brief ������� ������������ ������ GPIO
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @param pin: ����� ������ (0..15).
 * @retval ������� ������������ ������: true - �� �����, false - �� ����
 */
bool GPIO_ReadDirBit(GPIO_T *pGPIO, uint8_t pin)
{
    return (bool)(((pGPIO->OUTENSET) >> pin) & 1);
}

/**
 * @brief ������� ������������ ������� GPIO
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @retval ������� �������� �������� OUTENSET
 */
uint32_t GPIO_GetDir(GPIO_T *pGPIO)
{
    return (uint32_t)(pGPIO->OUTENSET);
}

/**
 * @brief ������� ������������� �����
 * @note  ������ ����� GPIO ��� ����� �������������� �������
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @retval ������� �������� �������� ALTFUNCSET
 */
uint32_t GPIO_GetAltFunc(GPIO_T *pGPIO)
{
    return (uint32_t)(pGPIO->ALTFUNCSET);
}

/**
 * @brief ��������� ������� ����������.
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @param Pin_number: ����� ������ (0..15).
 * @param IntMode: ������� ��������� ����������.
 *         �������� GPIOPINT_MODE_T ����� ��������� ��������:
 *          @arg GPIOPINT_FRONT_HIGHT: ������ �� ������, ������� ���������� �������
 *          @arg GPIOPINT_FRONT_LOW: ������ �� ������, ������ ���������� �������
 *          @arg GPIOPINT_RISING_EDGE: ������ �� ������, ������� ���������� �������
 *          @arg GPIOPINT_FALLING_EDGE: ������ �� ������, ������ ���������� �������
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
 * @brief ����� ������� ������ ��������� ��� ������� ������
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @retval ������� ������ ����������
 */
uint32_t GPIO_IntGetStatus(GPIO_T *pGPIO)
{
    return (uint32_t)(pGPIO->INTSTATUS);
}

/**
 * @brief ����� ������� ������� ���������� ��� ������
 * @param pGPIO: ��������� �� ��������� � ���������� GPIO.
 * @param pin: ����� ������ (0..15).
 * @retval ������� ������� ����������
 */ 
GPIOPINT_MODE_T GPIO_GetIntConfigPin(GPIO_T *pGPIO, uint8_t pin)
{
    uint32_t p1=((pGPIO->INTTYPESET)&(1<<pin));  
    uint32_t p2=(pGPIO->INTPOLSET&(1<<pin));
    return (GPIOPINT_MODE_T)(((p1>>pin)<<1) | (p2>>pin));                             
}        



/*!\file
 * \brief Этот файл содержит функции, необходимые для взаимодействия интерфейсом I2C.
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

#include "i2c.h"

/**
 * @brief Инициализация I2C.
 * @param pI2C: указатель на структуру с регистрами I2C.
 * @param clt_prsc: делитель частоты I2C.
 * @retval None.
 */
void I2C_Init(I2C_T *pI2C, uint32_t clt_prsc)
{
   I2C_GPIO_Init();
   PWR_CLK_Enable(I2C_CTRL_NUM);
   PWR_RST_Disable(I2C_CTRL_NUM);
   I2C->Clock_prescale = clt_prsc;  
   I2C->Control = I2C_ENABLE;
}

/**
 * @brief Инициализация портов в режиме альтернативной функции для работы I2C.
 * @param pI2C: None.
 * @retval None.
 */
void I2C_GPIO_Init()
{
   SET_ALTFUNC(PORT_E_ALTFUNC, 12, 2);
   SET_ALTFUNC(PORT_E_ALTFUNC, 13, 2);
   GPIO_SetAltFunc(GPIO_E, 12, true);
   GPIO_SetAltFunc(GPIO_E, 13, true);  
}

/**
 * @brief Отправка байта по интерфейсу I2C.
 * @param addr: адрес устройства I2C.
 * @param data: байт для передачи.
 * @retval Zero or error.
 */
unsigned int I2C_Write_Byte(unsigned char addr, unsigned char data)
{
    unsigned int timeout = 10000000;
    I2C->Tx_Rx = TDATA(addr)|RW(0);                                                          
    I2C->Com_Stat =  STA_RxACK(1)|STO_BUSY(0)|RD_AL(0)|WR(1)|ACK(0)|IACK_IF(0);
    while ((I2C->Com_Stat & TIP(1)) && --timeout > 0);                          
    if (!timeout)
    {
      return 1;
    }                                
    if (I2C->Com_Stat & STA_RxACK(1))                                               
    {
      return 2;
    }        
    I2C->Tx_Rx = data;
    I2C->Com_Stat = STA_RxACK(0)|STO_BUSY(1)|RD_AL(0)|WR(1)|ACK(0)|IACK_IF(0);               
    timeout = 10000000;
    while ((I2C->Com_Stat & TIP(1)) && --timeout > 0); 
    if (!timeout)
    {
      return 3;
    }
    if (I2C->Com_Stat & STA_RxACK(1))
    {
      return 4;
    }
    return 0;
}

/**
 * @brief Чтение байта по интерфейсу I2C.
 * @param addr: адрес устройства I2C.
 * @param data: принятый байт.
 * @retval Zero or error.
 */
unsigned int I2C_Read_Byte(unsigned char addr, unsigned char *data)
{
    unsigned int timeout = 10000000;
    I2C->Tx_Rx = TDATA(addr)|RW(1); 
    I2C->Com_Stat =  STA_RxACK(1)|STO_BUSY(0)|RD_AL(0)|WR(1)|ACK(0)|IACK_IF(0);
    while ((I2C->Com_Stat & TIP(1)) && --timeout > 0); 
    if (!timeout)
    {
      return 1;
    }                                
    if (I2C->Com_Stat & STA_RxACK(1))    
    {
      return 2;
    } 
    I2C->Com_Stat =  STA_RxACK(0)|STO_BUSY(1)|RD_AL(1)|WR(0)|ACK(1)|IACK_IF(0);                           
    timeout = 10000000;
    while ((I2C->Com_Stat & TIP(1)) && --timeout > 0); 
    if (!timeout)
    {
      return 3;
    }   
    *data = I2C->Tx_Rx;      
    return 0;
}

/**
 * @brief Запись данных по интерфейсу I2C.
 * @param ch_dev: адрес устройства I2C.
 * @param data: указатель на отправляемые данные
 * @param len: количество данных
 * @retval None.
 */
void I2C_WriteData(unsigned char ch_dev, unsigned char* data, unsigned int len)
{
    // Условие START на шине
    I2C->Tx_Rx = ch_dev;                                                          
    I2C->Com_Stat =  STA_RxACK(1)|WR(1);
    while (I2C->Com_Stat & TIP(1));                          
    
    // Запись данных
    for(int i=0; i<len; i++)
    {
      I2C->Tx_Rx = data[i]; 
      I2C->Com_Stat = WR(1) | (i == (len-1) ? STO_BUSY(1) : 0);
      while (I2C->Com_Stat & TIP(1)); 
    }
}

/**
 * @brief Чтение данных по интерфейсу I2C.
 * @param ch_dev: адрес устройства I2C.
 * @param data: указатель - расположение принятых данных
 * @param len: количество данных
 * @retval None.
 */
void I2C_ReadData(unsigned char ch_dev, unsigned char* data, unsigned int len)
{
    // Условие START на шине
    I2C->Tx_Rx = ch_dev; 
    I2C->Com_Stat =  STA_RxACK(1)|WR(1);
    while (I2C->Com_Stat & TIP(1));  
    
    // Чтение данных
    for (int i = 0; i < len; i++)
    {       
      I2C->Com_Stat = (RD_AL(1) | (i == (len-1) ? STO_BUSY(1) | ACK(1) : 0));
      while (I2C->Com_Stat & TIP(1)); 
      data[i] = I2C->Tx_Rx;      
    }
}

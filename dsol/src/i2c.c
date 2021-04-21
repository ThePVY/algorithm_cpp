/*!\file
 * \brief ���� ���� �������� �������, ����������� ��� �������������� ����������� I2C.
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

#include "i2c.h"

/**
 * @brief ������������� I2C.
 * @param pI2C: ��������� �� ��������� � ���������� I2C.
 * @param clt_prsc: �������� ������� I2C.
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
 * @brief ������������� ������ � ������ �������������� ������� ��� ������ I2C.
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
 * @brief �������� ����� �� ���������� I2C.
 * @param addr: ����� ���������� I2C.
 * @param data: ���� ��� ��������.
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
 * @brief ������ ����� �� ���������� I2C.
 * @param addr: ����� ���������� I2C.
 * @param data: �������� ����.
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
 * @brief ������ ������ �� ���������� I2C.
 * @param ch_dev: ����� ���������� I2C.
 * @param data: ��������� �� ������������ ������
 * @param len: ���������� ������
 * @retval None.
 */
void I2C_WriteData(unsigned char ch_dev, unsigned char* data, unsigned int len)
{
    // ������� START �� ����
    I2C->Tx_Rx = ch_dev;                                                          
    I2C->Com_Stat =  STA_RxACK(1)|WR(1);
    while (I2C->Com_Stat & TIP(1));                          
    
    // ������ ������
    for(int i=0; i<len; i++)
    {
      I2C->Tx_Rx = data[i]; 
      I2C->Com_Stat = WR(1) | (i == (len-1) ? STO_BUSY(1) : 0);
      while (I2C->Com_Stat & TIP(1)); 
    }
}

/**
 * @brief ������ ������ �� ���������� I2C.
 * @param ch_dev: ����� ���������� I2C.
 * @param data: ��������� - ������������ �������� ������
 * @param len: ���������� ������
 * @retval None.
 */
void I2C_ReadData(unsigned char ch_dev, unsigned char* data, unsigned int len)
{
    // ������� START �� ����
    I2C->Tx_Rx = ch_dev; 
    I2C->Com_Stat =  STA_RxACK(1)|WR(1);
    while (I2C->Com_Stat & TIP(1));  
    
    // ������ ������
    for (int i = 0; i < len; i++)
    {       
      I2C->Com_Stat = (RD_AL(1) | (i == (len-1) ? STO_BUSY(1) | ACK(1) : 0));
      while (I2C->Com_Stat & TIP(1)); 
      data[i] = I2C->Tx_Rx;      
    }
}

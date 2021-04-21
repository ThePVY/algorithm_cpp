/*!\file
 * \brief ���� ���� �������� �������, ����������� ��� �������������� � ���������� ������� MKPD.
 * \note ���� - �������������� ����� �������� ������, �������� ���� � 52070-2003
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

#include "chip_5023BC016.h"
#include "system.h"
#include "mkpd.h"


/**
 * @brief	��������� �������������� ����������������� ������� �� ��������
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	invTX	: 1 - ������������� ������ �� ��������; 0 - �� �������������
 */   
void MKPD_Set_InvTX(MKPD_T *pMKPD, unsigned int invTX)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0x1 << 8)) | MKPD_SETTING2_INVTX(invTX);
}
/**
 * @brief ��������� �������� ��������� �������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param sys_clk: ������� (� ���)
 * @retval None
 */   
void MKPD_Set_System_Clock(MKPD_T *pMKPD, uint32_t sys_clk)
{
    pMKPD->SETTING0 = (pMKPD->SETTING0 & ~(0xFF << 24)) | MKPD_SETTING0_SYS_CLK(sys_clk-1);
}
/**
 * @brief	��������� ������� ���������� ��������
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	IncWith	: 1 - ����������� �������� �������; 0 - ������������ � ���. ��������
 */   
void MKPD_Set_IncWith(MKPD_T *pMKPD, unsigned int IncWith)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0x1 << 9)) | MKPD_SETTING2_INCWITH(IncWith);
}

/**
 * @brief	����������� ���������� ���������
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Disable_mask	: 4 ����, �� ������ �� �������, ������ 1 ��������� 
 *              �������, ������ 0 ��������: ��� 0 - �, ��� 1 - B, ��� 2 - C, ��� 3 - D
 */   
void MKPD_Set_DecoderDisable(MKPD_T *pMKPD, unsigned int Disable_mask)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0xF << 10)) | MKPD_SETTING2_DECDIS(Disable_mask);
}

/**
 * @brief	��������� ������� �������� ���������� ���������� �� �����, �� ����� 1.3 ���
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Noacttime	: ����� ��������, � ������ ��������� �������
 */   
void MKPD_Set_NoActivity_Time(MKPD_T *pMKPD, unsigned int Noacttime)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0xFF << 16)) | MKPD_SETTING2_NOACTTIME(Noacttime);
}

/**
 * @brief	��������� ������� �������� �� � ������ ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Bcwaitreply	: ����� �������� ��, � ������ ��������� �������, � ���
 */   
void MKPD_Set_BCWaitReply_Time(MKPD_T *pMKPD, unsigned int Bcwaitreply)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0xFF << 24)) | MKPD_SETTING2_BCWAITREPLY(Bcwaitreply);
}

/**
 * @brief	������ ��������� ���������� ������ ��������� ������� � 500 ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Clk	: ���������� ������ ��������� �������
 */   
void MKPD_Set_Clk_500NS(MKPD_T *pMKPD, unsigned int Clk)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0xFF << 0)) | MKPD_SETTING2_500NS(Clk);
}

/**
 * @brief	������ ��������� ���������� ������ ��������� ������� � 1250 ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Clk	: ���������� ������ ��������� �������
 */   
void MKPD_Set_Clk_1250NS(MKPD_T *pMKPD, unsigned int Clk)
{
        pMKPD->SETTING3 = (pMKPD->SETTING3 & ~(0xFF << 0)) | MKPD_SETTING3_1250NS(Clk);
}

/**
 * @brief ���������� ���������� ����������� ���� � ����� ����������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO)  
 * @return SET or RESET - ��������� ���������� � ��������
 */  
int MKPD_BC_IsReady(MKPD_T *pMKPD, MKPD_TX_T index)

{
    if (index == TX_ONE)
                return ((pMKPD->BCONE2 & MKPD_BCONE2_ENA) || (pMKPD->BCONE4 & MKPD_BCONE4_STATUS)) ? 0 : 1;
        else
                return ((pMKPD->BCTWO2 & MKPD_BCONE2_ENA) || (pMKPD->BCTWO4 & MKPD_BCONE4_STATUS)) ? 0 : 1;
}
/**
 * @brief	������ ��������� ���������� ������ ��������� ������� � 2250 ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Clk	: ���������� ������ ��������� �������
 */   
void MKPD_Set_Clk_2250NS(MKPD_T *pMKPD, unsigned int Clk)
{
        pMKPD->SETTING3 = (pMKPD->SETTING3 & ~(0xFF << 24)) | MKPD_SETTING3_2250NS(Clk);
}
/**
 * @brief	������ ��������� ���������� ������ ��������� ������� � 1750 ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Clk	: ���������� ������ ��������� �������
 */   
void MKPD_Set_Clk_1750NS(MKPD_T *pMKPD, unsigned int Clk)
{
        pMKPD->SETTING3 = (pMKPD->SETTING3 & ~(0xFF << 16)) | MKPD_SETTING3_1750NS(Clk);
}
/**
 * @brief	������ ��������� ���������� ������ ��������� ������� � 1500 ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Clk	: ���������� ������ ��������� �������
 */  
void MKPD_Set_Clk_1500NS(MKPD_T *pMKPD, unsigned int Clk)
{
        pMKPD->SETTING3 = (pMKPD->SETTING3 & ~(0xFF << 8)) | MKPD_SETTING3_1500NS(Clk);
}

/**
 * @brief ��������� ���������� ��������� ����� ��������� �������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param time: ����� (� ���). ���������� �������� �� 4 �� 15
 * @retval None
 */   
void MKPD_Set_Interpacket_Time(MKPD_T *pMKPD, uint32_t time)
{
    if (time < 4)                                                               
    {
        time = 4;
    }
    pMKPD->SETTING1 = (pMKPD->SETTING1 & ~(0xF << 24)) | MKPD_SETTING1_TIME(time);
}
   
/**
 * @brief ��������� ������� �������� �� ��� �� � ������ ������ �� � ��
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param rwait: ����� (� ���). ���������� �������� �� 34 �� 255
 * @retval None
 */   
void MKPD_Set_Wait_Time(MKPD_T *pMKPD, uint32_t rwait)
{
    if (rwait < 21)
    {
        rwait = 21;
    }
    pMKPD->SETTING1 = (pMKPD->SETTING1 & ~(0xFF << 16)) | MKPD_SETTING1_RWAIT(rwait);
}

/**
 * @brief ��������� ������� ������������ ��������� ����������������� �������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param edge: ����� (� ������ ��������� �������). ���������� �������� �� 0 �� 255
 * @retval None
 */   
void MKPD_Set_Edge_Time(MKPD_T *pMKPD, uint32_t edge)
{
    pMKPD->SETTING1 = (pMKPD->SETTING1 & ~(0xFF << 8)) | MKPD_SETTING1_EDGE(edge);
}


/**
 * @brief ���������� �������� ����������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @return ��������� ���������� �������� ����������. 
 *          �������� ������������ ��������:
 *           MKPD_INTERRUPT_BC_INT: ���������� ��������� ���������� � ��
 *           MKPD_INTERRUPT_EP_INT0: ���������� ��, �� ����� ��
 *           MKPD_INTERRUPT_EP_INT1: ���������� ��, �� ��������� ����������
 *           MKPD_INTERRUPT_MON_INT: ���������� ��������, �� ���������� ������
 */   
uint32_t MKPD_Get_Interrupt(MKPD_T *pMKPD)
{
    return pMKPD->INTERRUPT;
}


/**
 * @brief ��������� ����� ������ ��� �������� � ����������� ������� 6 ��� 10.
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO)  
 * @param com_data: ���������� ����� ������, 16 ���
 * @retval None
 */   
void MKPD_Set_BC_COM_Data(MKPD_T *pMKPD, MKPD_TX_T index, uint32_t com_data)
{
    if (index == TX_ONE)
    {
        pMKPD->BCONE2 = (pMKPD->BCONE2 & ~(0xFFFF << 16)) | MKPD_BCONE2_COM_DATA(com_data);
    }
    else
    {
        pMKPD->BCTWO2 = (pMKPD->BCTWO2 & ~(0xFFFF << 16)) | MKPD_BCTWO2_COM_DATA(com_data);
    }
}

/**
 * @brief ��������� ������� ����������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO)  
 * @param type_trans: ������ ���������� (1..10)
 * @retval None
 */   
void MKPD_Set_BC_Transaction_Format(MKPD_T *pMKPD, MKPD_TX_T index, uint32_t type_trans)
{
    if (index == TX_ONE)
    {
        pMKPD->BCONE2 = (pMKPD->BCONE2 & ~(0xF << 0)) | MKPD_BCONE2_TYPE_TRANS((type_trans-1)%10);
    }
    else
    {
        pMKPD->BCTWO2 = (pMKPD->BCTWO2 & ~(0xF << 0)) | MKPD_BCONE2_TYPE_TRANS((type_trans-1)%10);
    }
}





/**
 * @brief ����������, ��������� �� ���������� � ������� �� ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return SET or RESET - ��������� �������� ����������
 */   
FlagStatus MKPD_BC_IsWaiting(MKPD_T *pMKPD, MKPD_TX_T index)
{
    if (index == TX_ONE)
    {

          if (pMKPD->BCONE2 & MKPD_BCONE2_ENA)
          {
                return SET;        
          
          }
          else
          {
                return RESET;
          }
          
    }
    else
    {

          if (pMKPD->BCTWO2 & MKPD_BCTWO2_ENA)
          {
                return SET;
          
          }
          else
          {
                return RESET;
          }
    }
}

/**
 * @brief ����������, ���������� �� ���������� � ��������� ������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return SET or RESET - ��������� �������� ����������
 */  
FlagStatus MKPD_BC_IsSending(MKPD_T *pMKPD, MKPD_TX_T index)
{
    if (index == TX_ONE)
    {

          if (pMKPD->BCONE4 & MKPD_BCONE4_STATUS)
          {
                return SET;
          }
          else
          {
                return RESET;
          }
    }
    else
    {

          if (pMKPD->BCTWO4 & MKPD_BCTWO4_STATUS)
          {
                return SET;
          }
          else
          {
                return RESET;
          }
    }
}

/**
 * @brief ���������� �������� ����� ������ ���������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return SET or RESET - ��������� �������� ����������
 */  
FlagStatus MKPD_BC_IsError(MKPD_T *pMKPD, MKPD_TX_T index)
{
    if (index == TX_ONE)
    {

          if (pMKPD->BCONE4 & MKPD_BCONE4_ERROR)
          {
                return SET;
          }
          else
          {
                return RESET;
          }
    }
    else
    {

          if (pMKPD->BCTWO4 & MKPD_BCTWO4_ERROR)
          {
                return SET;
          }
          else
          {
                return RESET;
          }
    }
}

/**
 * @brief ���������� �������� ����� �������� ���������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return SET or RESET - ��������� �������� ����������
 */    
FlagStatus MKPD_BC_IsTimeout(MKPD_T *pMKPD, MKPD_TX_T index)
{
    if (index == TX_ONE)
    {

          if (pMKPD->BCONE4 & MKPD_BCONE4_TIMEOUT)
          {
                return SET;
          }
          else
          {
                return RESET;
          }
    }
    else
    {
       if (pMKPD->BCTWO4 & MKPD_BCTWO4_TIMEOUT)
       {
            
                return SET;
       }
       else
                return RESET;

    }
}

/**
 * @brief ���������� �������� �����, ���������� �� ��
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return ���������� ��������� �����, 16 ���
 */   
uint32_t MKPD_BC_Reply_Word(MKPD_T *pMKPD, MKPD_TX_T index)
{
    if (index == TX_ONE)
    {
            return MKPD_BCONE3_REPLY(pMKPD->BCONE3);
    }
    else
    {
            return MKPD_BCTWO3_REPLY(pMKPD->BCTWO3);
    }
}

/**
 * @brief ���������� �������� ������, ���������� �� �� (��� ���������� ������� 5)
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return ���������� ��������� �����, 16 ���
 */     
uint32_t MKPD_BC_Reply_Data(MKPD_T *pMKPD, MKPD_TX_T index)
{
    if (index == TX_ONE)
    {
            return MKPD_BCONE3_REPLY_WORD(pMKPD->BCONE3);
    }
    else
    {
            return MKPD_BCTWO3_REPLY_WORD(pMKPD->BCTWO3);
    }
}





/**
 * @brief ��������� ����� ������ ��� �������� �� ��
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param rdata: ���������� ����� ������, 16 ���
 * @retval None
 */   
void MKPD_Set_Endpoint_RDATA(MKPD_T *pMKPD, uint32_t rdata)
{
    pMKPD->EP1 = (pMKPD->EP1 & ~(0xFFFF << 16)) | MKPD_EP1_RDATA(rdata);
}



/**
 * @brief ���������� �������� �� �� ����� ������ 
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @return ���������� ��������� �����, 16 ���
 */   
uint32_t MKPD_Get_Endpoint_COM_Data(MKPD_T *pMKPD)
{
        return MKPD_EP3_EP_COM_DATA(pMKPD->EP2);
}

/**
 * @brief ���������� �������� ����� ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD  
 * @return SET or RESET - ��������� ���������� � ��������
 */   
FlagStatus MKPD_Get_Endpoint_COM_Timeout(MKPD_T *pMKPD)
{

      if (pMKPD->EP2 & MKPD_EP2_EP_COM_TIMEOUT)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
}

/**
 * @brief ���������� �������� ����� ������ � ����� ������ (������������ � ����������� �6, 10)
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD  
 * @return SET or RESET - ��������� ���������� � ��������
 */   
FlagStatus MKPD_Get_Endpoint_COM_Error(MKPD_T *pMKPD)
{

      if (pMKPD->EP2 & MKPD_EP2_EP_COM_ERR)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
}

/**
 * @brief ���������� ��������� �����, �������� ��
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD  
 * @return SET or RESET - ��������� ���������� � ��������
 */  
uint32_t MKPD_Get_Endpoint_Command_Word(MKPD_T *pMKPD)
{
    return MKPD_EP3_EP_COM(pMKPD->EP3);
}

/**
 * @brief ������� ���������� ������ DMA ��� ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD  
 * @param dma_monitor_addr: ��������� ����� � ������ ��� ������
 * @retval None
 */   
void MKPD_Set_Monitor_DMA_Address(MKPD_T *pMKPD, uint32_t dma_monitor_addr)
{
        pMKPD->MONITOR0 = dma_monitor_addr;
}

/**
 * @brief ��������� ������ ���������� ����������. 
 * @note ����� �������� ������ � ������ ������ ��.
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param ep_addr: ����� �� (0..31)
 * @retval None
 */   
void MKPD_Set_EP_Address(MKPD_T *pMKPD, uint32_t ep_addr)
{
    pMKPD->SETTING0 = (pMKPD->SETTING0 & ~(0x1F << 0)) | MKPD_SETTING0_EP_ADDR(ep_addr);
}

/**
 * @brief ��������� �������� ������ ��� ����������� ����. 
 * @note ����� �������� ������ � ������ ������ ��.
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD.
 * @param channel: ����� �������� ������.
 *         �������� channel ����� ��������� ��������:
 *          @arg MKPD_SETTING0_CHANNEL_A: ������� ����� ��� �� - �
 *          @arg MKPD_SETTING0_CHANNEL_B: ������� ����� ��� �� - B
 * @retval None
 */   
void MKPD_Set_Channel(MKPD_T *pMKPD, uint32_t channel)
{
    pMKPD->SETTING0 = (pMKPD->SETTING0 & ~(0x1 << 16)) | channel;
}

/**
 * @brief ��������� ������ ������ �����.
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD.
 * @param channel: ����� �������� ������.
 *         �������� channel ����� ��������� ��������:
 *          @arg MKPD_SETTING0_MODE_DISABLED: ���� ��������
 *          @arg MKPD_SETTING0_MODE_BC: ���� ������������� � ������ ��
 *          @arg MKPD_SETTING0_MODE_EP: ���� ������������� � ������ ��
 *          @arg MKPD_SETTING0_MODE_M: ���� ������������� � ������ �
 * @retval None
 */   
void MKPD_Set_Mode(MKPD_T *pMKPD, uint32_t mode)
{
    pMKPD->SETTING0 = (pMKPD->SETTING0 & ~(0x3 << 8)) | mode;
}

/**
 * @brief ��������� ���������� ����������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @param ep_addr0: ����� ��, �������� ������������� ��
 * @param sub_addr0: �������� �� (������� ������ ����������), �������� ������������� ��
 * @param ep_addr1: ����� �� ��� ������� ��
 * @param sub_addr1: �������� �� ��� ������� ��
 * @param num: ���������� ������������ ��� ����������� ��. � ������ ���������� ����� �������� ��� �������
 * @retval None
 */   
void MKPD_Set_BC_TX_Params(MKPD_T *pMKPD, MKPD_TX_T index, 
                                     uint32_t ep_addr0, uint32_t sub_addr0, 
                                     uint32_t ep_addr1, uint32_t sub_addr1, 
                                     uint32_t num)
{
    if (index == TX_ONE)
    {
        pMKPD->BCONE0 = MKPD_BCONE0_EP_ADDR0(ep_addr0) |
                          MKPD_BCONE0_SUB_ADDR0(sub_addr0) |
                          MKPD_BCONE0_EP_ADDR1(ep_addr1) |
                          MKPD_BCONE0_SUB_ADDR1(sub_addr1) |
                          MKPD_BCONE0_NUM(num);
    }
    else
    {
        pMKPD->BCTWO0 = MKPD_BCTWO0_EP_ADDR0(ep_addr0) |
                          MKPD_BCTWO0_SUB_ADDR0(sub_addr0) |
                          MKPD_BCTWO0_EP_ADDR1(ep_addr1) |
                          MKPD_BCTWO0_SUB_ADDR1(sub_addr1) |
                          MKPD_BCTWO0_NUM(num);
    }
}

/**
 * @brief ��������� ������ DMA
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @param dma_addr: ����� ������� ����� � ������� ������ ��
 * @retval None
 */ 
void MKPD_Set_BC_DMA_Address(MKPD_T *pMKPD, MKPD_TX_T index, uint32_t dma_addr)
{
    if (index == TX_ONE)
    {
        pMKPD->BCONE1 = dma_addr;
    }
    else
    {
        pMKPD->BCTWO1 = dma_addr;
    }
}
/**
 * @brief ��������� ����������� ����
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param address_one: ��������� ����� � ������ ��� �������� ���� ������ ���������� 1
 * @param address_two: ��������� ����� � ������ ��� �������� ���� ������ ���������� 2
 * @param channel: ����� �������� ������.
 *         �������� channel ����� ��������� ��������:
 *          @arg MKPD_SETTING0_CHANNEL_A: ������� ����� ��� �� - �
 *          @arg MKPD_SETTING0_CHANNEL_B: ������� ����� ��� �� - B
 * @retval None
 */    
void MKPD_ConfigBusController(MKPD_T *pMKPD, uint32_t address_one, uint32_t address_two, uint32_t channel)
{        
    MKPD_Set_Channel(pMKPD, channel);
    MKPD_Set_BC_DMA_Address(pMKPD, TX_ONE, address_one);
    MKPD_Set_BC_DMA_Address(pMKPD, TX_TWO, address_two);
    MKPD_Set_Mode(pMKPD, MKPD_SETTING0_MODE_BC);
   
} 

/**
 * @brief ��������� ������� ����������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO)  
 * @retval None
 */   
void MKPD_BC_Start_Transaction(MKPD_T *pMKPD, MKPD_TX_T index)
{
    if (index == TX_ONE)
    {
        pMKPD->BCONE2 |=MKPD_BCONE2_ENA;
    }
    else
    {
        pMKPD->BCTWO2 |= MKPD_BCTWO2_ENA;
    }
}

/**
 * @brief �������� ��������� �� �� 
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO)  
 * @param type_trans: ������ ����������, �������� �������� (1..10)
 * @param ep_addr0: ����� ��, �������� ������������� ��
 * @param sub_addr0: �������� ��, �������� ������������� ��
 * @param ep_addr1: ����� �� ��� ������� ��
 * @param sub_addr1: �������� �� ��� ������� ��
 * @param num: ���������� ������������ ��� ����������� ��. � ������ ���������� �������� ��� �������
 * @param timeout: ������� �� �������� ���������
 * @return �������� �������� ��������� - 0; ���������� �� ������ - 1; ���������� �� ����������� - 2
 */
unsigned int MKPD_StartMessage(MKPD_T *pMKPD, MKPD_TX_T index, unsigned int type_trans,                                      
                       unsigned int ep_addr0, unsigned int sub_addr0, 
                       unsigned int ep_addr1, unsigned int sub_addr1, 
                       unsigned int num, 
                       unsigned int timeout,
                       unsigned int manage_code)
{  
              if (timeout == 0)
                return 1;  
        
        while(!MKPD_BC_IsReady(pMKPD, index) && (--timeout));                   //�������� ���������� � ��������       
        if (!timeout)
                return 1;                                                       //������: ���������� �� ���� ������ (����� �������)      
   

        
        MKPD_Set_BC_TX_Params(pMKPD, index, ep_addr0, 
                              sub_addr0, ep_addr1, sub_addr1, num);             //��������� ����������
        MKPD_Set_BC_Transaction_Format2(pMKPD, index, type_trans, manage_code); //������� ������� ����������
        MKPD_BC_Start_Transaction(pMKPD, index); 
        
        while(!MKPD_BC_IsReady(pMKPD, index) && (--timeout));
        
        if (!timeout)
                return 2;                                                       //������: ���������� �� ����������� (����� �������)
        return 0;
}

/**
 * @brief ��������� ������ ������� ����� ������� ������ ��
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param dma_ep: �����. ��� ���� ���������� ������������ ����� ������
 * @retval None
 */   
void MKPD_Set_Endpoint_DMA_Address(MKPD_T *pMKPD, uint32_t dma_ep)
{
    pMKPD->EP0 = dma_ep;
}

/**
 * @brief ��������� ���������� ����������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param address: ��������� ����� � ������ ��� �������� ���� ������
 * @param ep_address: ����� ���������� ���������� (0..31)
 * @retval None
 */
void MKPD_ConfigEndpoint(MKPD_T *pMKPD, uint32_t address, uint32_t ep_address)
{        
    MKPD_Set_Endpoint_DMA_Address(pMKPD, address);  
    MKPD_Set_EP_Address(pMKPD, ep_address); 
    MKPD_Set_Mode(pMKPD, MKPD_SETTING0_MODE_EP);
}

/**
 * @brief ��������� ��������� � �� ��
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param attributes: ����� ���������. 
 *         �������� attributes ����� ��������� ��������:
 *          @arg MKPD_EP1_FEP1: ������������� ��
 *          @arg MKPD_EP1_MAN: ������� ���������� �����������
 *          @arg MKPD_EP1_FEP0: ������������� ��������
 *          @arg MKPD_EP1_BUSY: ������� �����
 *          @arg MKPD_EP1_RES(x): ������� �������� ���������� ����
 *          @arg MKPD_EP1_SREQ: ������ �� ������������
 * @retval None
 */   
void MKPD_Set_Endpoint_Attributes(MKPD_T *pMKPD, uint32_t attributes)
{
    pMKPD->EP1 = (pMKPD->EP1 & ~0xFF) | attributes;
}

/**
 * @brief	��������� ������� ����������
 * @param	pMKPD           : ��������� �� ��������� � ���������� MKPD
 * @param       index           : ����� ���������� ��� ��������. TX_ONE ���� TX_TWO 
 * @param	type_trans      : ������ ����������, �������� �������� �� 1 �� 10 � ������������ � ���� � 52070-2003
 * @param       manage_code     : ������ �������� ������ ���������� � ��������� �����. 0 = 00000 ���� 1 = 11111
 */   
void MKPD_Set_BC_Transaction_Format2(MKPD_T *pMKPD, MKPD_TX_T index, unsigned int type_trans, unsigned int manage_code)
{
        if (index == TX_ONE)
                pMKPD->BCONE2 = (pMKPD->BCONE2 & ~(0x1F << 0)) | MKPD_BCONE2_TYPE_TRANS((type_trans-1)%10) | MKPD_BCONE2_MANAGE_CODE(manage_code);
        else
                pMKPD->BCTWO2 = (pMKPD->BCTWO2 & ~(0x1F << 0)) | MKPD_BCONE2_TYPE_TRANS((type_trans-1)%10) | MKPD_BCONE2_MANAGE_CODE(manage_code);
}

/**
 * @brief ������� ������� ������ ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD 
 * @param memory_size: ���������� 32-������ ����, ���������� ��� ��������
 * @retval None
 */   
void MKPD_Set_Monitor_Memory_Size(MKPD_T *pMKPD, uint32_t memory_size)
{
    pMKPD->MONITOR1 = memory_size;
}

/**
 * @brief ������� ���������� �������� ��� ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD 
 * @param threshold: ���������� ���������� ����, ��� ������� ����������� ���������� ��������
 * @retval None
 */   
void MKPD_Set_Monitor_Threshold(MKPD_T *pMKPD, uint32_t threshold)
{
    pMKPD->MONITOR2 = threshold;
}

/**
 * @brief ��������� ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD 
 * @param address: ��������� ����� � ������ ��� �������� ���� ������
 * @param size: ���������� 32-������ ����, ���������� ��� ��������
 * @param threshold: ���������� ���������� ����, ��� ������� ����������� ���������� ��������
 * @retval None
 */
void MKPD_ConfigMonitor(MKPD_T *pMKPD, uint32_t address, uint32_t size, uint32_t threshold)
{        
    MKPD_Set_Monitor_Memory_Size(pMKPD, size);
    MKPD_Set_Monitor_Threshold(pMKPD, threshold);
    MKPD_Set_Monitor_DMA_Address(pMKPD, address);
    MKPD_Set_Mode(pMKPD, MKPD_SETTING0_MODE_M);
}

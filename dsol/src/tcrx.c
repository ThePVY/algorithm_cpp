/*!\file
 * \brief ���� ���� �������� �������, ����������� ��� �������������� � ���������� ������� ��������� ������������� ����������.
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

#include "chip_5023BC016.h"
#include "system.h"
#include "tcrx.h"


/*****************************************************************************
 * ������� �������
 ****************************************************************************/
    
/*****************************************************************************
 * ����� �������
 ****************************************************************************/

/** �������� ����������� �� ���� */   
void TCRX_OpenDescriptor(uint32_t index, uint32_t pointer, uint32_t size)
{
    TCRX->DSCR_TBL[index].DSCR_PTR = pointer;        
    TCRX->DSCR_TBL[index].DSCR_FLAG_SIZE = TCRX_DSC_DSCR_FLAG_SIZE_READY | 
                                       TCRX_DSC_DSCR_FLAG_SIZE_SIZE( ((size == TCRX_DSCR_MAX_SIZE) ? 0 : size) ); 
}

/**
 * @brief ���������� �������� ����� DSCR_READY, ������������, ������ �� ����������
 * @param index : ����� �����������
 * @return �������� �����, SET or RESET
 */
FlagStatus TCRX_Dscr_Ready(uint32_t index)
{
//    return (TCRX->DSCR_TBL[index].DSCR_FLAG_SIZE & TCRX_DSC_DSCR_FLAG_SIZE_READY) ? SET : RESET;
      if (TCRX->DSCR_TBL[index].DSCR_FLAG_SIZE & TCRX_DSC_DSCR_FLAG_SIZE_READY)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
}

/**
 * @brief ���������� ���������� ������, �������� ������������
 * @param index	: ����� �����������
 * @return ���������� �������� ������, � ������
 */
uint32_t TCRX_Get_Data_Size(uint32_t index)
{
    uint32_t data_size = TCRX->DSCR_TBL[index].DSCR_FLAG_SIZE & 0x3FF;
    if (data_size == 0)
    {
        return TCRX_DSCR_MAX_SIZE;
    }
    else
    {
        return data_size;   
    }
}

/**
 * @brief ���������� �������� ����� SOF
 * @param index	: ����� �����������
 * @return �������� �����, SET or RESET
 */
FlagStatus TCRX_SOF_Flag(uint32_t index)
{
//    return (TCRX->DSCR_TBL[index].DSCR_FLAG_SIZE & TCRX_DSC_DSCR_FLAG_SIZE_SOF) ? SET : RESET;
      if (TCRX->DSCR_TBL[index].DSCR_FLAG_SIZE & TCRX_DSC_DSCR_FLAG_SIZE_SOF)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
}

/**
 * @brief ���������� �������� ����� EOF
 * @param index	: ����� �����������
 * @return �������� �����, SET or RESET
 */
FlagStatus TCRX_EOF_Flag(uint32_t index)
{
//    return (TCRX->DSCR_TBL[index].DSCR_FLAG_SIZE & TCRX_DSC_DSCR_FLAG_SIZE_EOF) ? SET : RESET;
      if (TCRX->DSCR_TBL[index].DSCR_FLAG_SIZE & TCRX_DSC_DSCR_FLAG_SIZE_EOF)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
}

/**
 * @brief ���������� �������� ����� ERROR
 * @param index	: ����� �����������
 * @return �������� �����, SET or RESET
 */
FlagStatus TCRX_ERROR_Flag(uint32_t index)
{
//    return (TCRX->DSCR_TBL[index].DSCR_FLAG_SIZE & TCRX_DSC_DSCR_FLAG_SIZE_ERROR) ? SET : RESET;
      if (TCRX->DSCR_TBL[index].DSCR_FLAG_SIZE & TCRX_DSC_DSCR_FLAG_SIZE_ERROR)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
}

/**
 * @brief ����� �������� ����������� ��� �����
 * @param index	: ����� �����������
 */
void TCRX_Set_Current_Descriptor(uint32_t index)
{
    TCRX->DSCR_CURRENT = index;
}

/**
 * @brief ��������� ������ ��������� �����������
 * @return ����� �����������
 */
uint32_t TCRX_Get_Current_Descriptor()
{
    return TCRX->DSCR_CURRENT & 0xF;
}


/**
 * @brief ��������� ����� ������
 */
void TCRX_Enable()
{
    TCRX->GLOBAL_ENABLE = TCRX_GLOBAL_ENABLE_EN;
}

/**
 * @brief ���������� ����� ������
 */
void TCRX_Disable()
{
    TCRX->GLOBAL_ENABLE &= ~TCRX_GLOBAL_ENABLE_EN;
}

/**
 * @brief ��������� ���������� ��������
 * @param randomizer: ��������� �������������, ��������� ��������� ��������:
 *                                              - TCRX_CODER_SEL_RAND
 *                                              - TCRX_CODER_SEL_RAND_OFF    
 * @param bch : ��������� �������� ���, ��������� ��������� ��������:
 *                                              - TCRX_CODER_SEL_BCH
 *                                              - TCRX_CODER_SEL_BCH_OFF
 * @param viterbi : ��������� ����������� �������� �������, ��������� ��������� ��������:
 *                                              - TCRX_CODER_SEL_VIT_HARD
 *                                              - TCRX_CODER_SEL_VIT_SOFT
 *                                              - TCRX_CODER_SEL_VIT_OFF
 */
void TCRX_Set_Decoder(uint32_t randomizer, uint32_t bch, uint32_t viterbi)
{
    TCRX->CODER_SEL = randomizer | bch | viterbi;
}

/**
 * @brief ���������� �������� ����� ������������ FIFO
 * @return �������� �����, SET or RESET
 */
FlagStatus TCRX_FIFO_Overflow()
{
//    return (TCRX->PHY_FIFO_OVERFLOW & TCRX_PHY_FIFO_OVERFLOW)? SET : RESET;
      if (TCRX->PHY_FIFO_OVERFLOW & TCRX_PHY_FIFO_OVERFLOW)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
}

/**
 * @brief ��������� �������� ������� ������ ������ � ���������� ��������� ������ � �������
 * @param start_seq : �������� ������� ������ ������. ����� 16 ���. ������ �������� ��� ������������ �� ������� �����
 * @param allow_1_err : ���������� ��� ���������� ��������� ������ � ������� ������ ������, ��������� ��������� ��������:
 *                                              - TCRX_START_SEQ_ALLOW_1_ERR
 *                                              - TCRX_START_SEQ_DENY_1_ERR
 */
void TCRX_Set_Start_Sequence(uint32_t start_seq, uint32_t allow_1_err)
{
    TCRX->START_SEQ = start_seq | allow_1_err;
}

/**
 * @brief ��������� �������� ������� ����� ������
 * @param tail_first : �������� ������� ����� ������, ������ �����. ����� 32 ���. ������ �������� ��� ������������ �� ������� �����
 * @param tail_second : �������� ������� ����� ������, ������ �����. ����� 32 ���. ��������� �������� ��� ������������ � ������� �����
 */
void TCRX_Set_Tail_Sequence(uint32_t tail_first, uint32_t tail_second)
{
    TCRX->TAIL_SEQ1 = tail_first;	
    TCRX->TAIL_SEQ2 = tail_second;
}    

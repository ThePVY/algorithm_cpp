/*!\file
 * \brief ���� ���� �������� �������, ����������� ��� �������������� � ���������� ������� ����������� ��������������� ����������.
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
#include "tmtx.h"


/*****************************************************************************
 * ������� �������
 ****************************************************************************/
 
/** �������, ������������ ������ ������ ����� ����������� ��������� ���������, � ����� */   
static uint32_t TMTX_BitFrameSizeOut()
{
    switch (TMTX_Get_Coder())          
    {
        case TMTX_CODER_SEL_NONE:
            return TMTX_BIT_OUT_SIZE_MAX;  
        case TMTX_CODER_SEL_LDPC:
            switch (TMTX_Get_LDPC_Type())
            {
                case TMTX_CC_LDPC_TYPE_7136:
                    return TMTX_BIT_OUT_SIZE_LDPC_7136;
            }                 
        case TMTX_CODER_SEL_TURBO:
            switch (TMTX_Get_Turbo_Type())
            {
                case TMTX_CC_TURBO_1DIV2:
                    return TMTX_BIT_OUT_SIZE_TURBO_1DIV2;
                case TMTX_CC_TURBO_1DIV3:
                    return TMTX_BIT_OUT_SIZE_TURBO_1DIV3;
                case TMTX_CC_TURBO_1DIV4:
                    return TMTX_BIT_OUT_SIZE_TURBO_1DIV4;
                case TMTX_CC_TURBO_1DIV6: 
                    return TMTX_BIT_OUT_SIZE_TURBO_1DIV6;
            }
        case TMTX_CODER_SEL_RS:
            return TMTX_BIT_OUT_SIZE_RS;
    }
    return 0;
}
   
/*****************************************************************************
 * ����� �������
 ****************************************************************************/

/** �������, ������������ ������ ������, ��������������� ������������ ��������, � ������ */   
uint32_t TMTX_GetFrameSize()
{
    switch (TMTX_Get_Coder())          
    {
    case TMTX_CODER_SEL_NONE:
        return TMTX_FRAME_SIZE_MAX;
    case TMTX_CODER_SEL_LDPC:
        return TMTX_FRAME_SIZE_LDPC;
    case TMTX_CODER_SEL_TURBO:
        return TMTX_FRAME_SIZE_TURBO;
    case TMTX_CODER_SEL_RS:
        switch (TMTX_Get_RS_Type())                 
        {
            case TMTX_CC_RS_TYPE_239:
            case TMTX_CC_RS_TYPE_239_CONV:
                return TMTX_FRAME_SIZE_RS_239;
            case TMTX_CC_RS_TYPE_223:
            case TMTX_CC_RS_TYPE_223_CONV:
                return TMTX_FRAME_SIZE_RS_223;       
        }
    }
    return 0;
}  

/** ��������� ���������� �������������. ������ ����� ������������ ������� ��� marker1, ��������� - ������� ��� marker6 (���� marker_size = MAX_MARKER_SIZE)*/
void TMTX_SetSyncMarker(uint8_t marker_size, 
                        uint32_t marker1, 
                        uint32_t marker2, 
                        uint32_t marker3, 
                        uint32_t marker4, 
                        uint32_t marker5, 
                        uint32_t marker6)
{
    TMTX_Set_Marker_And_Frame_Size(marker_size,
                                       TMTX_BitFrameSizeOut());
    TMTX->MARKER1 = marker1;
    TMTX->MARKER2 = marker2;
    TMTX->MARKER3 = marker3;
    TMTX->MARKER4 = marker4;
    TMTX->MARKER5 = marker5;
    TMTX->MARKER6 = marker6;
}

/** ��������� ������������� ������ � ��������� ������ ��� ������, ��������� ������������� � ����������� ������ */
void TMTX_SetEncoder(uint32_t coder_sel, 
                     uint32_t coder_config, 
                     uint32_t rand_state, 
                     uint32_t conv_state, 
                     uint32_t conv_speed)
{  
    TMTX->CODER_SEL = coder_sel | rand_state | conv_state;
    TMTX->CODERS_CONFIG = coder_config | conv_speed;        
}

/**
 * @brief ��������� ��������� �� ����� ������ ��� ����������� 1
 * @param addr: �������� ������, � �������� ���������� ����� ���������� ������
 */
void TMTX_Set_DSCR1_Pointer(uint32_t addr)
{
    TMTX->DSCR1_PTR = addr;
}

/**
 * @brief ��������� ��������� �� ����� ������ ��� ����������� 2
 * @param addr: �������� ������, � �������� ���������� ����� ���������� ������
 */
void TMTX_Set_DSCR2_Pointer(uint32_t addr)
{
    TMTX->DSCR2_PTR = addr;
}

/**
 * @brief ��������� ������� ����������� 1
 * @param size: ������ ����������� � ������
 */
void TMTX_Set_DSCR1_Size(uint32_t size)
{
    if (size > TMTX_MAX_DSCR_SIZE)
    {
         TMTX->DSCR1_FLAG_SIZE = TMTX_MAX_DSCR_SIZE - 1;
    }
    else
    {
        TMTX->DSCR1_FLAG_SIZE = size - 1;
    }
}

/**
 * @brief ��������� ������� ����������� 2
 * @param size: ������ ����������� � ������
 */
void TMTX_Set_DSCR2_Size(uint32_t size)
{
    if (size > TMTX_MAX_DSCR_SIZE)
    {
        TMTX->DSCR2_FLAG_SIZE = TMTX_MAX_DSCR_SIZE - 1;
    }
    else
    {
        TMTX->DSCR2_FLAG_SIZE = size - 1;
    }
}

/**
 * @brief ���������� �������� ������� ����� ����, ��� ������ ��� ����������� 1 ������������ ��� ��������
 */
void TMTX_DSCR1_Data_Ready()
{
    TMTX->DSCR1_FLAG_SIZE |= TMTX_DSCR1_SIZE_FLAG_DATA_PRES;
}

/**
 * @brief ���������� �������� ������� ����� ����, ��� ������ ��� ����������� 2 ������������ ��� ��������
 */
void TMTX_DSCR2_Data_Ready()
{
    TMTX->DSCR2_FLAG_SIZE |= TMTX_DSCR1_SIZE_FLAG_DATA_PRES;
}

/**
 * @brief ������� ���������� Global Enable �����������: ��������� ���� �������, ������������� �� �������� ������
 */
void TMTX_Global_Enable()
{
    TMTX->GLOBAL_ENABLE = TMTX_GLOBAL_ENABLE;  
}

/**
 * @brief ������� ��������� Global Enable �����������: ��� ������, fifo, ahb ���������� ����� ���������� � ����������� ������
 */
void TMTX_Global_Disable()
{
    TMTX->GLOBAL_ENABLE &= ~TMTX_GLOBAL_ENABLE;  
}

/**
 * @brief ���������� ��� ������������� ������
 * @return ��� ������������� ������, ����� ��������� ��������:
 *                                              - TMTX_CODER_SEL_LDPC
 *                                              - TMTX_CODER_SEL_TURBO 
 *                                              - TMTX_CODER_SEL_RS 
 *                                              - TMTX_CODER_SEL_NONE 
 */
uint32_t TMTX_Get_Coder()
{
    return TMTX->CODER_SEL & 0x3;
}

/**
 * @brief ������� ���������� �������� ����� ����������� ������������ FIFO
 * @return �������� �����, SET or RESET
 */
FlagStatus TMTX_FIFO_Underrun()
{
//    return (TMTX->PHY_FIFO_UNDERRUN) ? SET : RESET; 
      if (TMTX->PHY_FIFO_UNDERRUN)
      {
            return SET;
      }
      else
      {
            return RESET;
      }
}

/**
 * @brief ����� ����� ����������� ������������ FIFO
 */
void TMTX_FIFO_Underrun_Clear_Flag()
{
    TMTX->PHY_FIFO_UNDERRUN = TMTX_PHY_FIFO_UNDERRUN; 
}

/**
 * @brief ��������� ������� ������������� � ������� ������� �������������
 * @param marker_size: ������ ������������� (� �����)
 * @param frame_size: ������ ������� ������������� (� �����)
 */
void TMTX_Set_Marker_And_Frame_Size(uint8_t marker_size, uint32_t frame_size)
{
    if (marker_size > TMTX_MAX_MARKER_SIZE)
    {
        TMTX->MARKER_AND_FRAME_SIZE = TMTX_MARKER_AND_FRAME_MARKER_SIZE(TMTX_MAX_MARKER_SIZE) | 
                                              TMTX_MARKER_AND_FRAME_FRAME_SIZE(frame_size);
    }
    else
    {
        TMTX->MARKER_AND_FRAME_SIZE = TMTX_MARKER_AND_FRAME_MARKER_SIZE(marker_size) | 
                                              TMTX_MARKER_AND_FRAME_FRAME_SIZE(frame_size); 
    }
}

/**
 * @brief ���������� ��� ������������� ����������� ������
 * @return ��� ������������� ���������� ������, ����� ��������� ��������:
 *                                              - TMTX_CC_CONV_1DIV2
 *                                              - TMTX_CC_CONV_2DIV3
 *                                              - TMTX_CC_CONV_3DIV4 
 *                                              - TMTX_CC_CONV_5DIV6
 *                                              - TMTX_CC_CONV_7DIV8
 */
uint32_t TMTX_Get_Conv_Type()
{
    return (TMTX->CODERS_CONFIG & (3 << 0));
}

/**
 * @brief ���������� ��� ������������� ����� ������
 * @return ��� ������������� ���������� ������, ����� ��������� ��������:
 *                                              - TMTX_CC_TURBO_1DIV2
 *                                              - TMTX_CC_TURBO_1DIV3
 *                                              - TMTX_CC_TURBO_1DIV4 
 *                                              - TMTX_CC_TURBO_1DIV6
 */
uint32_t TMTX_Get_Turbo_Type()
{
    return (TMTX->CODERS_CONFIG & (3 << 8));
}
	
/**
 * @brief ���������� ��� ������������� ������ ����-��������
 * @return ��� ������������� ������ ����-��������, ����� ��������� ��������:
 *                                              - TMTX_CC_RS_TYPE_239
 *                                              - TMTX_CC_RS_TYPE_223
 *                                              - TMTX_CC_RS_TYPE_239_CONV 
 *                                              - TMTX_CC_RS_TYPE_223_CONV
 */
uint32_t TMTX_Get_RS_Type()
{
    return (TMTX->CODERS_CONFIG & (3 << 16));
}

/**
 * @brief ���������� ���, ��������������� ���������� ���� ������ LDPC
 * @return ��� ������������� ������ LDPC, ����� ��������� ��������:
 *                                              - TMTX_CC_LDPC_TYPE_7136
 *                                              - TMTX_CC_LDPC_TYPE_7156
 */
uint32_t TMTX_Get_LDPC_Type()
{
     return (TMTX->CODERS_CONFIG & (1 << 24));
}


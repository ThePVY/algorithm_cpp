/*!\file
 * \brief Этот файл содержит функции, необходимые для взаимодействия с аппаратным модулем передатчика телеметрической информации.
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
 * Органицация "Цифровые решения" не несет никакой ответственности за использование 
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
#include "system.h"
#include "tmtx.h"


/*****************************************************************************
 * Частные функции
 ****************************************************************************/
 
/** Функция, возвращающая размер фрейма после кодирования выбранным энкодером, в битах */   
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
 * Общие функции
 ****************************************************************************/

/** Функция, возвращающая размер фрейма, соответствующий настроенному энкодеру, в байтах */   
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

/** Настройка параметров синхромаркера. Первым будет передаваться младший бит marker1, последним - старший бит marker6 (если marker_size = MAX_MARKER_SIZE)*/
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

/** Установка используемого кодера и настройка режима его работы, настройка рандомизатора и сверточного кодера */
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
 * @brief Установка указателя на адрес памяти для дескриптора 1
 * @param addr: Значение адреса, с которого дескриптор начнёт считывание данных
 */
void TMTX_Set_DSCR1_Pointer(uint32_t addr)
{
    TMTX->DSCR1_PTR = addr;
}

/**
 * @brief Установка указателя на адрес памяти для дескриптора 2
 * @param addr: Значение адреса, с которого дескриптор начнёт считывание данных
 */
void TMTX_Set_DSCR2_Pointer(uint32_t addr)
{
    TMTX->DSCR2_PTR = addr;
}

/**
 * @brief Установка размера дескриптора 1
 * @param size: размер дескриптора в байтах
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
 * @brief Установка размера дескриптора 2
 * @param size: размер дескриптора в байтах
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
 * @brief Необходимо вызывать функцию после того, как данные для дескриптора 1 подготовлены для передачи
 */
void TMTX_DSCR1_Data_Ready()
{
    TMTX->DSCR1_FLAG_SIZE |= TMTX_DSCR1_SIZE_FLAG_DATA_PRES;
}

/**
 * @brief Необходимо вызывать функцию после того, как данные для дескриптора 2 подготовлены для передачи
 */
void TMTX_DSCR2_Data_Ready()
{
    TMTX->DSCR2_FLAG_SIZE |= TMTX_DSCR1_SIZE_FLAG_DATA_PRES;
}

/**
 * @brief Функция активирует Global Enable контроллера: включение всех модулей, ответственных за передачу данных
 */
void TMTX_Global_Enable()
{
    TMTX->GLOBAL_ENABLE = TMTX_GLOBAL_ENABLE;  
}

/**
 * @brief Функция отключает Global Enable контроллера: все кодеры, fifo, ahb контроллер будут находиться в асинхронном сбросе
 */
void TMTX_Global_Disable()
{
    TMTX->GLOBAL_ENABLE &= ~TMTX_GLOBAL_ENABLE;  
}

/**
 * @brief Возвращает тип используемого кодера
 * @return Тип используемого кодера, может принимать значения:
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
 * @brief Функция возвращает значение флага опустошения асинхронного FIFO
 * @return Значение флага, SET or RESET
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
 * @brief Сброс флага опустошения асинхронного FIFO
 */
void TMTX_FIFO_Underrun_Clear_Flag()
{
    TMTX->PHY_FIFO_UNDERRUN = TMTX_PHY_FIFO_UNDERRUN; 
}

/**
 * @brief Установка размера синхромаркера и периода вставки синхромаркера
 * @param marker_size: Размер синхромаркера (в битах)
 * @param frame_size: Период вставки синхромаркера (в битах)
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
 * @brief Возвращает тип используемого сверточного кодера
 * @return Тип используемого свёрточного кодера, может принимать значения:
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
 * @brief Возвращает тип используемого турбо кодера
 * @return Тип используемого свёрточного кодера, может принимать значения:
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
 * @brief Возвращает тип используемого кодера Рида-Соломона
 * @return Тип используемого кодера Рида-Соломона, может принимать значения:
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
 * @brief Возвращает код, соответствующий выбранному типу кодера LDPC
 * @return Тип используемого кодера LDPC, может принимать значения:
 *                                              - TMTX_CC_LDPC_TYPE_7136
 *                                              - TMTX_CC_LDPC_TYPE_7156
 */
uint32_t TMTX_Get_LDPC_Type()
{
     return (TMTX->CODERS_CONFIG & (1 << 24));
}


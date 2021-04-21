/*!\file
 * \brief Этот файл содержит функции, необходимые для взаимодействия с аппаратным модулем приемника телекомандной информации.
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
#include "tcrx.h"


/*****************************************************************************
 * Частные функции
 ****************************************************************************/
    
/*****************************************************************************
 * Общие функции
 ****************************************************************************/

/** Открытие дескриптора на приём */   
void TCRX_OpenDescriptor(uint32_t index, uint32_t pointer, uint32_t size)
{
    TCRX->DSCR_TBL[index].DSCR_PTR = pointer;        
    TCRX->DSCR_TBL[index].DSCR_FLAG_SIZE = TCRX_DSC_DSCR_FLAG_SIZE_READY | 
                                       TCRX_DSC_DSCR_FLAG_SIZE_SIZE( ((size == TCRX_DSCR_MAX_SIZE) ? 0 : size) ); 
}

/**
 * @brief Возвращает значение флага DSCR_READY, показывающее, открыт ли дескриптор
 * @param index : Номер дескриптора
 * @return Значение флага, SET or RESET
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
 * @brief Возвращает количество данных, принятых дескриптором
 * @param index	: Номер дескриптора
 * @return Количество принятых данных, в байтах
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
 * @brief Возвращает значение флага SOF
 * @param index	: Номер дескриптора
 * @return Значение флага, SET or RESET
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
 * @brief Возвращает значение флага EOF
 * @param index	: Номер дескриптора
 * @return Значение флага, SET or RESET
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
 * @brief Возвращает значение флага ERROR
 * @param index	: Номер дескриптора
 * @return Значение флага, SET or RESET
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
 * @brief Выбор текущего дескриптора для приёма
 * @param index	: Номер дескриптора
 */
void TCRX_Set_Current_Descriptor(uint32_t index)
{
    TCRX->DSCR_CURRENT = index;
}

/**
 * @brief Получение номера активного дескриптора
 * @return Номер дескриптора
 */
uint32_t TCRX_Get_Current_Descriptor()
{
    return TCRX->DSCR_CURRENT & 0xF;
}


/**
 * @brief Активация приёма данных
 */
void TCRX_Enable()
{
    TCRX->GLOBAL_ENABLE = TCRX_GLOBAL_ENABLE_EN;
}

/**
 * @brief Отключение приёма данных
 */
void TCRX_Disable()
{
    TCRX->GLOBAL_ENABLE &= ~TCRX_GLOBAL_ENABLE_EN;
}

/**
 * @brief Настройка параметров декодера
 * @param randomizer: Включение рандомизатора, принимает следующие значения:
 *                                              - TCRX_CODER_SEL_RAND
 *                                              - TCRX_CODER_SEL_RAND_OFF    
 * @param bch : Включение декодера БЧХ, принимает следующие значения:
 *                                              - TCRX_CODER_SEL_BCH
 *                                              - TCRX_CODER_SEL_BCH_OFF
 * @param viterbi : Включение сверточного декодера витерби, принимает следующие значения:
 *                                              - TCRX_CODER_SEL_VIT_HARD
 *                                              - TCRX_CODER_SEL_VIT_SOFT
 *                                              - TCRX_CODER_SEL_VIT_OFF
 */
void TCRX_Set_Decoder(uint32_t randomizer, uint32_t bch, uint32_t viterbi)
{
    TCRX->CODER_SEL = randomizer | bch | viterbi;
}

/**
 * @brief Возвращает значение флага переполнения FIFO
 * @return Значение флага, SET or RESET
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
 * @brief Установка значения маркера начала фрейма и разрешения единичной ошибки в маркере
 * @param start_seq : Значение маркера начала фрейма. Длина 16 бит. Первый принятый бит сравнивается со старшим битом
 * @param allow_1_err : Разрешение или запрещение единичной ошибки в маркере начала фрейма, принимает следующие значения:
 *                                              - TCRX_START_SEQ_ALLOW_1_ERR
 *                                              - TCRX_START_SEQ_DENY_1_ERR
 */
void TCRX_Set_Start_Sequence(uint32_t start_seq, uint32_t allow_1_err)
{
    TCRX->START_SEQ = start_seq | allow_1_err;
}

/**
 * @brief Установка значения маркера конца фрейма
 * @param tail_first : Значение маркера конца фрейма, первая часть. Длина 32 бит. Первый принятый бит сравнивается со старшим битом
 * @param tail_second : Значение маркера конца фрейма, вторая часть. Длина 32 бит. Последний принятый бит сравнивается с младшим битом
 */
void TCRX_Set_Tail_Sequence(uint32_t tail_first, uint32_t tail_second)
{
    TCRX->TAIL_SEQ1 = tail_first;	
    TCRX->TAIL_SEQ2 = tail_second;
}    

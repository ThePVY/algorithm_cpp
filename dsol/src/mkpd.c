/*!\file
 * \brief Этот файл содержит функции, необходимые для взаимодействия с аппаратным модулем MKPD.
 * \note МКПД - Мультиплексный канал передачи данных, согласно ГОСТ Р 52070-2003
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
#include "system.h"
#include "mkpd.h"


/**
 * @brief	Установка инвертирования дифференциального сигнала на передаче
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	invTX	: 1 - инвертировать сигнал на передаче; 0 - не инвертировать
 */   
void MKPD_Set_InvTX(MKPD_T *pMKPD, unsigned int invTX)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0x1 << 8)) | MKPD_SETTING2_INVTX(invTX);
}
/**
 * @brief Установка значения системной частоты
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param sys_clk: частота (в МГц)
 * @retval None
 */   
void MKPD_Set_System_Clock(MKPD_T *pMKPD, uint32_t sys_clk)
{
    pMKPD->SETTING0 = (pMKPD->SETTING0 & ~(0xFF << 24)) | MKPD_SETTING0_SYS_CLK(sys_clk-1);
}
/**
 * @brief	Настройка сигнала разрешения передачи
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	IncWith	: 1 - расширенная передача сигнала; 0 - одновременно с диф. сигналом
 */   
void MKPD_Set_IncWith(MKPD_T *pMKPD, unsigned int IncWith)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0x1 << 9)) | MKPD_SETTING2_INCWITH(IncWith);
}

/**
 * @brief	Программное отключение декодеров
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Disable_mask	: 4 бита, по одному на декодер, запись 1 отключает 
 *              декодер, запись 0 включает: бит 0 - А, бит 1 - B, бит 2 - C, бит 3 - D
 */   
void MKPD_Set_DecoderDisable(MKPD_T *pMKPD, unsigned int Disable_mask)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0xF << 10)) | MKPD_SETTING2_DECDIS(Disable_mask);
}

/**
 * @brief	Настройка времени ожидания отсутствия активности на линии, не менее 1.3 мкс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Noacttime	: Время ожидания, в тактах системной частоты
 */   
void MKPD_Set_NoActivity_Time(MKPD_T *pMKPD, unsigned int Noacttime)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0xFF << 16)) | MKPD_SETTING2_NOACTTIME(Noacttime);
}

/**
 * @brief	Настройка времени ожидания ОС в режиме КШ
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Bcwaitreply	: Время ожидания ОС, в тактах системной частоты, в мкс
 */   
void MKPD_Set_BCWaitReply_Time(MKPD_T *pMKPD, unsigned int Bcwaitreply)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0xFF << 24)) | MKPD_SETTING2_BCWAITREPLY(Bcwaitreply);
}

/**
 * @brief	Тонкая настройка количества тактов системной частоты в 500 нс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Clk	: Количество тактов системной частоты
 */   
void MKPD_Set_Clk_500NS(MKPD_T *pMKPD, unsigned int Clk)
{
        pMKPD->SETTING2 = (pMKPD->SETTING2 & ~(0xFF << 0)) | MKPD_SETTING2_500NS(Clk);
}

/**
 * @brief	Тонкая настройка количества тактов системной частоты в 1250 нс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Clk	: Количество тактов системной частоты
 */   
void MKPD_Set_Clk_1250NS(MKPD_T *pMKPD, unsigned int Clk)
{
        pMKPD->SETTING3 = (pMKPD->SETTING3 & ~(0xFF << 0)) | MKPD_SETTING3_1250NS(Clk);
}

/**
 * @brief Определяет готовность контроллера шины к новой транзакции
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO)  
 * @return SET or RESET - состояние готовности к передаче
 */  
int MKPD_BC_IsReady(MKPD_T *pMKPD, MKPD_TX_T index)

{
    if (index == TX_ONE)
                return ((pMKPD->BCONE2 & MKPD_BCONE2_ENA) || (pMKPD->BCONE4 & MKPD_BCONE4_STATUS)) ? 0 : 1;
        else
                return ((pMKPD->BCTWO2 & MKPD_BCONE2_ENA) || (pMKPD->BCTWO4 & MKPD_BCONE4_STATUS)) ? 0 : 1;
}
/**
 * @brief	Тонкая настройка количества тактов системной частоты в 2250 нс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Clk	: Количество тактов системной частоты
 */   
void MKPD_Set_Clk_2250NS(MKPD_T *pMKPD, unsigned int Clk)
{
        pMKPD->SETTING3 = (pMKPD->SETTING3 & ~(0xFF << 24)) | MKPD_SETTING3_2250NS(Clk);
}
/**
 * @brief	Тонкая настройка количества тактов системной частоты в 1750 нс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Clk	: Количество тактов системной частоты
 */   
void MKPD_Set_Clk_1750NS(MKPD_T *pMKPD, unsigned int Clk)
{
        pMKPD->SETTING3 = (pMKPD->SETTING3 & ~(0xFF << 16)) | MKPD_SETTING3_1750NS(Clk);
}
/**
 * @brief	Тонкая настройка количества тактов системной частоты в 1500 нс
 * @param	pMKPD	: Указатель на структуру с регистрами MKPD
 * @param	Clk	: Количество тактов системной частоты
 */  
void MKPD_Set_Clk_1500NS(MKPD_T *pMKPD, unsigned int Clk)
{
        pMKPD->SETTING3 = (pMKPD->SETTING3 & ~(0xFF << 8)) | MKPD_SETTING3_1500NS(Clk);
}

/**
 * @brief Установка временного интервала между передачей пакетов
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param time: время (в мкс). Допустимые значения от 4 до 15
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
 * @brief Установка времени ожидания ОС или СД в режиме работы КШ и ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param rwait: время (в мкс). Допустимые значения от 34 до 255
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
 * @brief Установка времени запрещенного состояния дифференциального сигнала
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param edge: время (в тактах системной частоты). Допустимые значения от 0 до 255
 * @retval None
 */   
void MKPD_Set_Edge_Time(MKPD_T *pMKPD, uint32_t edge)
{
    pMKPD->SETTING1 = (pMKPD->SETTING1 & ~(0xFF << 8)) | MKPD_SETTING1_EDGE(edge);
}


/**
 * @brief Возвращает значение прерывания
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @return Считывает содержимое регистра прерываний. 
 *          Возможны возвращаемые значения:
 *           MKPD_INTERRUPT_BC_INT: прерывание окончания транзакции в КШ
 *           MKPD_INTERRUPT_EP_INT0: прерывание ОУ, по приёму КС
 *           MKPD_INTERRUPT_EP_INT1: прерывание ОУ, по окончанию транзакции
 *           MKPD_INTERRUPT_MON_INT: прерывание монитора, по достижению порога
 */   
uint32_t MKPD_Get_Interrupt(MKPD_T *pMKPD)
{
    return pMKPD->INTERRUPT;
}


/**
 * @brief Установка слова данных для передачи в транзакциях формата 6 или 10.
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO)  
 * @param com_data: содержимое слова данных, 16 бит
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
 * @brief Установка формата транзакции
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO)  
 * @param type_trans: формат транзакции (1..10)
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
 * @brief Определяет, находится ли транзакция в очереди на передачу
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return SET or RESET - состояние ожидания транзакции
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
 * @brief Определяет, передается ли транзакция в настоящий момент
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return SET or RESET - состояние ожидания транзакции
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
 * @brief Возвращает значение флага ошибки транзации
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return SET or RESET - состояние ожидания транзакции
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
 * @brief Возвращает значение флага таймаута транзации
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return SET or RESET - состояние ожидания транзакции
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
 * @brief Возвращает ответное слово, полученное от ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return Содержимое ответного слова, 16 бит
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
 * @brief Возвращает ответные данные, полученные от ОУ (для транзакций формата 5)
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @return Содержимое ответного слова, 16 бит
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
 * @brief Установка слова данных для передачи от ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param rdata: содержимое слова данных, 16 бит
 * @retval None
 */   
void MKPD_Set_Endpoint_RDATA(MKPD_T *pMKPD, uint32_t rdata)
{
    pMKPD->EP1 = (pMKPD->EP1 & ~(0xFFFF << 16)) | MKPD_EP1_RDATA(rdata);
}



/**
 * @brief Возвращает принятое от КШ слово данных 
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @return Содержимое ответного слова, 16 бит
 */   
uint32_t MKPD_Get_Endpoint_COM_Data(MKPD_T *pMKPD)
{
        return MKPD_EP3_EP_COM_DATA(pMKPD->EP2);
}

/**
 * @brief Возвращает значение флага таймаута
 * @param pMKPD: указатель на структуру с регистрами MKPD  
 * @return SET or RESET - состояние готовности к передаче
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
 * @brief Возвращает значение флага ошибки в слове данных (используется в транзакциях №6, 10)
 * @param pMKPD: указатель на структуру с регистрами MKPD  
 * @return SET or RESET - состояние готовности к передаче
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
 * @brief Возвращает командное слово, принятое ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD  
 * @return SET or RESET - состояние готовности к передаче
 */  
uint32_t MKPD_Get_Endpoint_Command_Word(MKPD_T *pMKPD)
{
    return MKPD_EP3_EP_COM(pMKPD->EP3);
}

/**
 * @brief Задание начального адреса DMA для монитора
 * @param pMKPD: указатель на структуру с регистрами MKPD  
 * @param dma_monitor_addr: начальный адрес в памяти для записи
 * @retval None
 */   
void MKPD_Set_Monitor_DMA_Address(MKPD_T *pMKPD, uint32_t dma_monitor_addr)
{
        pMKPD->MONITOR0 = dma_monitor_addr;
}

/**
 * @brief Установка адреса оконечного устройства. 
 * @note Имеет значение только в режиме работы ОУ.
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param ep_addr: адрес ОУ (0..31)
 * @retval None
 */   
void MKPD_Set_EP_Address(MKPD_T *pMKPD, uint32_t ep_addr)
{
    pMKPD->SETTING0 = (pMKPD->SETTING0 & ~(0x1F << 0)) | MKPD_SETTING0_EP_ADDR(ep_addr);
}

/**
 * @brief Установка рабочего канала для контроллера шины. 
 * @note Имеет значение только в режиме работы КШ.
 * @param pMKPD: указатель на структуру с регистрами MKPD.
 * @param channel: номер рабочего канала.
 *         Параметр channel может принимать значения:
 *          @arg MKPD_SETTING0_CHANNEL_A: рабочий канал для КШ - А
 *          @arg MKPD_SETTING0_CHANNEL_B: рабочий канал для КШ - B
 * @retval None
 */   
void MKPD_Set_Channel(MKPD_T *pMKPD, uint32_t channel)
{
    pMKPD->SETTING0 = (pMKPD->SETTING0 & ~(0x1 << 16)) | channel;
}

/**
 * @brief Установка режима работы блока.
 * @param pMKPD: указатель на структуру с регистрами MKPD.
 * @param channel: номер рабочего канала.
 *         Параметр channel может принимать значения:
 *          @arg MKPD_SETTING0_MODE_DISABLED: блок отключен
 *          @arg MKPD_SETTING0_MODE_BC: блок функционирует в режиме КШ
 *          @arg MKPD_SETTING0_MODE_EP: блок функционирует в режиме ОУ
 *          @arg MKPD_SETTING0_MODE_M: блок функционирует в режиме М
 * @retval None
 */   
void MKPD_Set_Mode(MKPD_T *pMKPD, uint32_t mode)
{
    pMKPD->SETTING0 = (pMKPD->SETTING0 & ~(0x3 << 8)) | mode;
}

/**
 * @brief Установка параметров транзакции
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @param ep_addr0: адрес ОУ, которому предназначено КС
 * @param sub_addr0: подадрес ОУ (признак режима управления), которому предназначено КС
 * @param ep_addr1: адрес ОУ для второго КС
 * @param sub_addr1: подадрес ОУ для второго КС
 * @param num: количество передаваемых или принимаемых СД. В режиме управления также содержит код команды
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
 * @brief Установка адреса DMA
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO) 
 * @param dma_addr: адрес первого байта в области памяти КШ
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
 * @brief Настройка контроллера шины
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param address_one: начальный адрес в памяти для хранения слов данных интерфейса 1
 * @param address_two: начальный адрес в памяти для хранения слов данных интерфейса 2
 * @param channel: номер рабочего канала.
 *         Параметр channel может принимать значения:
 *          @arg MKPD_SETTING0_CHANNEL_A: рабочий канал для КШ - А
 *          @arg MKPD_SETTING0_CHANNEL_B: рабочий канал для КШ - B
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
 * @brief Установка формата транзакции
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO)  
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
 * @brief Передача сообщения от КШ 
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param index: номер интерфейса для передачи (TX_ONE/TX_TWO)  
 * @param type_trans: формат транзакции, доступны значения (1..10)
 * @param ep_addr0: адрес ОУ, которому предназначено КС
 * @param sub_addr0: подадрес ОУ, которому предназначено КС
 * @param ep_addr1: адрес ОУ для второго КС
 * @param sub_addr1: подадрес ОУ для второго КС
 * @param num: количество передаваемых или принимаемых СД. В режиме управления содержит код команды
 * @param timeout: таймаут на передачу сообщения
 * @return Успешная передача сообщения - 0; Транзакция не начата - 1; Транзакция не завершилась - 2
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
        
        while(!MKPD_BC_IsReady(pMKPD, index) && (--timeout));                   //ожидание готовности к передаче       
        if (!timeout)
                return 1;                                                       //Ошибка: транзакция не была начата (истек таймаут)      
   

        
        MKPD_Set_BC_TX_Params(pMKPD, index, ep_addr0, 
                              sub_addr0, ep_addr1, sub_addr1, num);             //установка параметров
        MKPD_Set_BC_Transaction_Format2(pMKPD, index, type_trans, manage_code); //задание формата транзакции
        MKPD_BC_Start_Transaction(pMKPD, index); 
        
        while(!MKPD_BC_IsReady(pMKPD, index) && (--timeout));
        
        if (!timeout)
                return 2;                                                       //Ошибка: транзакция не завершилась (истек таймаут)
        return 0;
}

/**
 * @brief Установка адреса первого байта области памяти ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param dma_ep: адрес. Для всех подадресов используется общая память
 * @retval None
 */   
void MKPD_Set_Endpoint_DMA_Address(MKPD_T *pMKPD, uint32_t dma_ep)
{
    pMKPD->EP0 = dma_ep;
}

/**
 * @brief Настройка оконечного устройства
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param address: начальный адрес в памяти для хранения слов данных
 * @param ep_address: адрес оконечного устройства (0..31)
 * @retval None
 */
void MKPD_ConfigEndpoint(MKPD_T *pMKPD, uint32_t address, uint32_t ep_address)
{        
    MKPD_Set_Endpoint_DMA_Address(pMKPD, address);  
    MKPD_Set_EP_Address(pMKPD, ep_address); 
    MKPD_Set_Mode(pMKPD, MKPD_SETTING0_MODE_EP);
}

/**
 * @brief Установка признаков в ОС ОУ
 * @param pMKPD: указатель на структуру с регистрами MKPD
 * @param attributes: набор признаков. 
 *         Параметр attributes может принимать значения:
 *          @arg MKPD_EP1_FEP1: неисправность ОУ
 *          @arg MKPD_EP1_MAN: принято управление интерфейсом
 *          @arg MKPD_EP1_FEP0: неисправность абонента
 *          @arg MKPD_EP1_BUSY: абонент занят
 *          @arg MKPD_EP1_RES(x): задание значения резервного поля
 *          @arg MKPD_EP1_SREQ: запрос на обслуживание
 * @retval None
 */   
void MKPD_Set_Endpoint_Attributes(MKPD_T *pMKPD, uint32_t attributes)
{
    pMKPD->EP1 = (pMKPD->EP1 & ~0xFF) | attributes;
}

/**
 * @brief	Установка формата транзакции
 * @param	pMKPD           : Указатель на структуру с регистрами MKPD
 * @param       index           : Номер интерфейса для передачи. TX_ONE либо TX_TWO 
 * @param	type_trans      : Формат транзакции, доступны значения до 1 до 10 в соответствии с ГОСТ Р 52070-2003
 * @param       manage_code     : Формат признака режима управления в командном слове. 0 = 00000 либо 1 = 11111
 */   
void MKPD_Set_BC_Transaction_Format2(MKPD_T *pMKPD, MKPD_TX_T index, unsigned int type_trans, unsigned int manage_code)
{
        if (index == TX_ONE)
                pMKPD->BCONE2 = (pMKPD->BCONE2 & ~(0x1F << 0)) | MKPD_BCONE2_TYPE_TRANS((type_trans-1)%10) | MKPD_BCONE2_MANAGE_CODE(manage_code);
        else
                pMKPD->BCTWO2 = (pMKPD->BCTWO2 & ~(0x1F << 0)) | MKPD_BCONE2_TYPE_TRANS((type_trans-1)%10) | MKPD_BCONE2_MANAGE_CODE(manage_code);
}

/**
 * @brief Задание размера буфера монитора
 * @param pMKPD: указатель на структуру с регистрами MKPD 
 * @param memory_size: количество 32-битных слов, выделенных для монитора
 * @retval None
 */   
void MKPD_Set_Monitor_Memory_Size(MKPD_T *pMKPD, uint32_t memory_size)
{
    pMKPD->MONITOR1 = memory_size;
}

/**
 * @brief Задание порогового значения для монитора
 * @param pMKPD: указатель на структуру с регистрами MKPD 
 * @param threshold: количество записанных слов, при котором срабатывает прерывание монитора
 * @retval None
 */   
void MKPD_Set_Monitor_Threshold(MKPD_T *pMKPD, uint32_t threshold)
{
    pMKPD->MONITOR2 = threshold;
}

/**
 * @brief Настройка монитора
 * @param pMKPD: указатель на структуру с регистрами MKPD 
 * @param address: начальный адрес в памяти для хранения слов данных
 * @param size: количество 32-битных слов, выделенных для монитора
 * @param threshold: количество записанных слов, при котором срабатывает прерывание монитора
 * @retval None
 */
void MKPD_ConfigMonitor(MKPD_T *pMKPD, uint32_t address, uint32_t size, uint32_t threshold)
{        
    MKPD_Set_Monitor_Memory_Size(pMKPD, size);
    MKPD_Set_Monitor_Threshold(pMKPD, threshold);
    MKPD_Set_Monitor_DMA_Address(pMKPD, address);
    MKPD_Set_Mode(pMKPD, MKPD_SETTING0_MODE_M);
}

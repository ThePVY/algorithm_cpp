/*!\file
 * \brief ���� ���� �������� ���������, ������� � �������, ����������� ��� �������������� � ���������� ������� MKPD.
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

#ifndef MKPD_H_
#define MKPD_H_

#include "types.h"


/**
 * @brief ��������� ��� ������� � ��������� ����.
 */
typedef struct
{
    __RW uint32_t BCONE0;                                                       /**< ��������: 0x0000 1� ������� ����������� ���� 0 */
    __RW uint32_t BCONE1;                                                       /**< ��������: 0x0004 2� ������� ����������� ���� 0 */
    __RW uint32_t BCONE2;                                                       /**< ��������: 0x0008 3� ������� ����������� ���� 0 */
    __RO uint32_t BCONE3;                                                       /**< ��������: 0x000C 4� ������� ����������� ���� 0 */
    __RO uint32_t BCONE4;                                                       /**< ��������: 0x0010 5� ������� ����������� ���� 0 */
    __RW uint32_t BCTWO0;                                                       /**< ��������: 0x0014 1� ������� ����������� ���� 1 */
    __RW uint32_t BCTWO1;                                                       /**< ��������: 0x0018 2� ������� ����������� ���� 1 */
    __RW uint32_t BCTWO2;                                                       /**< ��������: 0x001C 3� ������� ����������� ���� 1 */
    __RO uint32_t BCTWO3;                                                       /**< ��������: 0x0020 4� ������� ����������� ���� 1 */
    __RO uint32_t BCTWO4;                                                       /**< ��������: 0x0024 5� ������� ����������� ���� 1 */
    __RW uint32_t EP0;                                                          /**< ��������: 0x0028 1� ������� ���������� ���������� */
    __RW uint32_t EP1;                                                          /**< ��������: 0x002C 2� ������� ���������� ���������� */
    __RO uint32_t EP2;                                                          /**< ��������: 0x0030 3� ������� ���������� ���������� */
    __RO uint32_t EP3;                                                          /**< ��������: 0x0034 4� ������� ���������� ���������� */
    __RW uint32_t SETTING0;                                                     /**< ��������: 0x0038 ������� �������� 0 */
    __RW uint32_t SETTING1;                                                     /**< ��������: 0x003� ������� �������� 1 */
    __RW uint32_t SETTING2;                                                     /**< ��������: 0x0040 ������� �������� 2 */
    __RW uint32_t SETTING3;                                                     /**< ��������: 0x0044 ������� �������� 3 */
    __RW uint32_t MONITOR0;                                                     /**< ��������: 0x0048 1� ������� �������� */
    __RW uint32_t MONITOR1;                                                     /**< ��������: 0x004� 2� ������� �������� */
    __RW uint32_t MONITOR2;                                                     /**< ��������: 0x0050 3� ������� �������� */
    __RO uint32_t MONITOR3;                                                     /**< ��������: 0x0054 4� ������� �������� */
    __RW uint32_t INTERRUPT;                                                    /**< ��������: 0x0058 ������� ���������� */
}MKPD_T;
         
/**
 * @brief ������� ��� �������� BCONE0
 */
#define MKPD_BCONE0_SUB_ADDR1(x)        ((uint32_t)(((x) & 0x1F) << 0))           /**< �������� ���������� ���������� ��� ������� ���������� ����� */
#define MKPD_BCONE0_EP_ADDR1(x)         ((uint32_t)(((x) & 0x1F) << 5))           /**< ����� ���������� ���������� ��� ������� ���������� ����� */
#define MKPD_BCONE0_NUM(x)              ((uint32_t)(((x) & 0x1F) << 10))          /**< ���������� ������������ ��� ����������� ���� ������ */
#define MKPD_BCONE0_SUB_ADDR0(x)        ((uint32_t)(((x) & 0x1F) << 16))          /**< �������� ���������� ����������, �������� ��������������� ��������� ����� */
#define MKPD_BCONE0_EP_ADDR0(x)         ((uint32_t)(((x) & 0x1F) << 21))          /**< ����� ���������� ����������, �������� ��������������� ��������� ����� */

/**
 * @brief ������� ��� �������� BCONE2
 */
#define MKPD_BCONE2_TYPE_TRANS(x)       ((uint32_t)(((x) & 0x0F) << 0))           /**< ��� ���������� */
#define MKPD_BCONE2_MANAGE_CODE(x)         ((unsigned int)(((x) & 0x01) << 4))                /**< ��� ���������� */
#define MKPD_BCONE2_ENA                 ((uint32_t)(1 << 8))                    /**< ������ ������ ���������� */
#define MKPD_BCONE2_COM_DATA(x)         ((uint32_t)(((x) & 0xFFFF) << 16))        /**< ����� ������ ��� �������� */

/**
 * @brief ������� ��� �������� BCONE3
 */
#define MKPD_BCONE3_REPLY_WORD(x)       ((uint32_t)((x) & 0xFFFF))                /**< ����� ������, ������� ���������� � �������� ������  */
#define MKPD_BCONE3_REPLY(x)            ((uint32_t)(((x) >> 16) & 0xFFFF))        /**< �������� ����� �� ��������� ����� ���������� */

/**
 * @brief ������� ��� �������� BCONE4
 */
#define MKPD_BCONE4_STATUS              ((uint32_t)(1 << 0))                    /**< ����� ��� ���� ������� */
#define MKPD_BCONE4_ERROR               ((uint32_t)(1 << 8))                    /**< ����� ��� ���� ������ */
#define MKPD_BCONE4_TIMEOUT             ((uint32_t)(1 << 16))                   /**< ����� ��� ���� ����-���� */

/**
 * @brief ������� ��� �������� BCTWO0
 */
#define MKPD_BCTWO0_SUB_ADDR1(x)        ((uint32_t)(((x) & 0x1F) << 0))           /**< �������� ���������� ���������� ��� ������� ���������� ����� */
#define MKPD_BCTWO0_EP_ADDR1(x)         ((uint32_t)(((x) & 0x1F) << 5))           /**< ����� ���������� ���������� ��� ������� ���������� ����� */
#define MKPD_BCTWO0_NUM(x)              ((uint32_t)(((x) & 0x1F) << 10))          /**< ���������� ������������ ��� ����������� ���� ������ */
#define MKPD_BCTWO0_SUB_ADDR0(x)        ((uint32_t)(((x) & 0x1F) << 16))          /**< �������� ���������� ����������, �������� ��������������� ��������� ����� */
#define MKPD_BCTWO0_EP_ADDR0(x)         ((uint32_t)(((x) & 0x1F) << 21))          /**< ����� ���������� ����������, �������� ��������������� ��������� ����� */

/**
 * @brief ������� ��� �������� BCTWO2
 */
#define MKPD_BCTWO2_TYPE_TRANS(x)       ((uint32_t)(((x) & 0x0F) << 0))           /**< ��� ���������� */
#define MKPD_BCTWO2_MANAGE_CODE         ((uint32_t)(1 << 4))                    /**< ������ �������� ������ ���������� � ��������� ����� */
#define MKPD_BCTWO2_ENA                 ((uint32_t)(1 << 8))                    /**< ������ ������ ���������� */
#define MKPD_BCTWO2_COM_DATA(x)         ((uint32_t)(((x) & 0xFFFF) << 16))        /**< �������� ����� ������ */

/**
 * @brief ������� ��� �������� BCTWO3
 */
#define MKPD_BCTWO3_REPLY_WORD(x)       ((uint32_t)((x) & 0xFFFF))                /**< ����� ������, ������� ���������� � �������� ������ */
#define MKPD_BCTWO3_REPLY(x)            ((uint32_t)(((x) >> 16) & 0xFFFF))        /**< �������� ����� �� ��������� ����� ���������� */

/**
 * @brief ������� ��� �������� BCTWO4
 */
#define MKPD_BCTWO4_STATUS              ((uint32_t)(1 << 0))                    /**< ����� ��� ���� ������� */
#define MKPD_BCTWO4_ERROR               ((uint32_t)(1 << 8))                    /**< ����� ��� ���� ������ */
#define MKPD_BCTWO4_TIMEOUT             ((uint32_t)(1 << 16))                   /**< ����� ��� ���� ����-���� */

/**
 * @brief ������� ��� �������� EP1
 */
#define MKPD_EP1_FEP1                   ((uint32_t)(1 << 0))                    /**< ������� �������������� ���������� ���������� � �� ���������� ���������� */
#define MKPD_EP1_MAN                    ((uint32_t)(1 << 1))                    /**< ������� �������� ���������� ����������� � �� ���������� ���������� */
#define MKPD_EP1_FEP0                   ((uint32_t)(1 << 2))                    /**< ������� �������������� �������� � �� ���������� ���������� */
#define MKPD_EP1_BUSY                   ((uint32_t)(1 << 3))                    /**< ������� �������� ����� � �� ���������� ����������. ��� ������ ����� 1 */
#define MKPD_EP1_RXGROUP                ((uint32_t)(1 << 4))                    /**< ������� �������� ��������� ������� */
#define MKPD_EP1_RESERV(x)              ((uint32_t)(((x) & 0x03) << 5))           /**< ������ � �� ���������� ���������� */
#define MKPD_EP1_SREQ                   ((uint32_t)(1 << 8))                    /**< ������� ������� �� ������������ � �� ���������� ���������� */
#define MKPD_EP1_ERROR                  ((uint32_t)(1 << 8))                    /**< ������� ������� � ��������� */  
#define MKPD_EP1_RDATA(x)               ((uint32_t)(((x) & 0xFFFF) << 16))        /**< �������� ����� ������ */

/**
 * @brief ������� ��� �������� EP2
 */
#define MKPD_EP2_EP_COM_ERR             ((uint32_t)(1 << 0))                    /**< ����� ��� ���� ������ */
#define MKPD_EP2_EP_COM_TIMEOUT         ((uint32_t)(1 << 1))                    /**< ����� ��� ���� ����-���� */
  
/**
 * @brief ������� ��� �������� EP3
 */   
#define MKPD_EP3_EP_COM_DATA(x)         ((uint32_t)((x) & 0xFFFF))                /**< ����� ��� ��������� ����� ������ */
#define MKPD_EP3_EP_COM(x)              ((uint32_t)(((x) >> 16) & 0xFFFF))        /**< ����������� ����� �������� ���������� ����������� */

/**
 * @brief ������� � ���� ��� �������� SETTING0
 */
#define MKPD_SETTING0_EP_ADDR(x)        ((uint32_t)(((x) & 0x1F) << 0))           /**< ������ ����� ���������� ���������� */

typedef enum 
{
    MKPD_SETTING0_MODE_DISABLED  = ((uint32_t)(0 << 8)),                        /**< ����� ����� ������ - ���� �������� */
    MKPD_SETTING0_MODE_BC  = ((uint32_t)(1 << 8)),                              /**< ����� ����� ������ - ���������� ���� (��) */
    MKPD_SETTING0_MODE_EP  = ((uint32_t)(2 << 8)),                              /**< ����� ����� ������ - ��������� ���������� (��) */
    MKPD_SETTING0_MODE_M  = ((uint32_t)(3 << 8)),                               /**< ����� ����� ������ - ������� (�) */
}MKPD_SETTING0_MODE_T;

typedef enum 
{
    MKPD_SETTING0_CHANNEL_A  = ((uint32_t)(0 << 16)),                           /**< ����� ������� ����� A */
    MKPD_SETTING0_CHANNEL_B  = ((uint32_t)(1 << 16)),                           /**< ����� ������� ����� B */
}MKPD_SETTING0_CHANNEL_T;

#define MKPD_SETTING0_SYS_CLK(x)        ((uint32_t)(((x) & 0xFF) << 24))          /**< ��������� ������� � ��� */

/**
 * @brief ������� ��� �������� SETTING1
 */
#define MKPD_SETTING1_EDGE(x)           ((uint32_t)(((x) & 0xFF) << 8))           /**< ������ ����� ������������ ��������� ����������������� ������� � ������ ��������� ������� ����� */
#define MKPD_SETTING1_RWAIT(x)          ((uint32_t)(((x) & 0xFF) << 16))          /**< ������ ����� �������� ��������� ����� ��� ����� ������ � ������ ������ ����������� ���� � ���������� ���������� */
#define MKPD_SETTING1_TIME(x)           ((uint32_t)(((x) & 0x0F) << 24))          /**< ������ ����� ����� ����� ����������� � ������������� */



/**
 * @brief ������� � ���� ��� �������� SETTING2
 */
#define MKPD_SETTING2_500NS(x)           ((unsigned int)(((x) & 0xFF) << 0))      /**< ������ ���������� ������ ��������� ������� ������ 0.5 ��� */
 
#define MKPD_SETTING2_INVTX(x)           ((unsigned int)(((x) & 0x01) << 8))      /**< ��� �������������� ����������������� ������� ��� �������� */
   
#define MKPD_SETTING2_INCWITH(x)         ((unsigned int)(((x) & 0x01) << 9))      /**< ������ ����� ��������� ������� ���������� �������� */
   
#define MKPD_SETTING2_DECDIS(x)          ((unsigned int)(((x) & 0x0F) << 10))     /**< ��������� � �������� �������� */
 
#define MKPD_SETTING2_NOACTTIME(x)       ((uint32_t)(((x) & 0xFF) << 16))     /**< ������ �����, � ������� ������� ������� ����������, ��� �� ����� ��� ���������� */
    
#define MKPD_SETTING2_BCWAITREPLY(x)     ((uint32_t)(((x) & 0xFF) << 24))     /**< ������ ����� �������� �� � ������ ������ ��, ������ ���� �� ����� 35 ��� */

typedef enum 
{
    MKPD_SETTING2_DECDIS_A  = ((uint32_t)(1 << 10)),                            /**< ��������� ������� � */
    MKPD_SETTING2_DECDIS_B  = ((uint32_t)(1 << 11)),                            /**< ��������� ������� B */  
    MKPD_SETTING2_DECDIS_C  = ((uint32_t)(1 << 12)),                            /**< ��������� ������� C */ 
    MKPD_SETTING2_DECDIS_D  = ((uint32_t)(1 << 13)),                            /**< ��������� ������� D */   
}MKPD_DECDIS_MODE_T;
 
/**
 * @brief ������� ��� �������� SETTING3
 */
#define MKPD_SETTING3_1250NS(x)         ((uint32_t)(((x) & 0xFF) << 0))           /**< ���������� ������ ��������� �������, ������ 1,25 ���. */
#define MKPD_SETTING3_1500NS(x)         ((uint32_t)(((x) & 0xFF) << 8))           /**< ���������� ������ ��������� �������, ������ 1,5 ���. */
#define MKPD_SETTING3_1750NS(x)         ((uint32_t)(((x) & 0xFF) << 16))          /**< ���������� ������ ��������� �������, ������ 1,75 ���. */
#define MKPD_SETTING3_2250NS(x)         ((uint32_t)(((x) & 0xFF) << 24))          /**< ���������� ������ ��������� �������, ������ 2,25 ���. */

/**
 * @brief ������� ��� �������� INTERRUPT
 */
#define MKPD_INTERRUPT_BC_INT           ((uint32_t)(1 << 0))                    /**< ���������� ����������� ���� - ���������� ��������� ���������� � ����������� ���� */
#define MKPD_INTERRUPT_EP_INT0          ((uint32_t)(1 << 1))                    /**< ���������� ���������� ���������� - ���������� �� ����� ���������� ����� */
#define MKPD_INTERRUPT_EP_INT1          ((uint32_t)(1 << 2))                    /**< ���������� ���������� ���������� - ���������� ��������� ���������� � ��������� ���������� */
#define MKPD_INTERRUPT_MON_INT          ((uint32_t)(1 << 3))                    /**< ���������� �������� - ���������� �����������, ����� ��������� ������ ��������� ������ � ������ DMA_MONITOR_ADDR + THRESHOLD */

/**
 * @brief �������, ����������� � ������ ������ �����������
 */
#define MKPD_MAX_WORD_IN_PACKET         32                                      /**< ������������ ���������� ���������� ���� ������ � ������ */ 
#define MKPD_EP_SUBADDR_COUNT           32 //16                                 /**< ���������� ���������� � ��������� ���������� */                                  
#define MKPD_MANAGE_MODE_MASK           0xF                                     /**< ���������� ���� "����� ����������" � ��������� �����, � ������ �������� ������ ���������� */    
#define MKPD_EP_GROUP_ADDR              0x1F                                    /**< �������� ���������� ������ */                               
   
/**   
 * @brief ����� ���������� �������� ��� ����������� ����
 */   
typedef enum 
{
    TX_ONE,                                                                     /**< �������� �� ������� ���������� ����������� ���� */
    TX_TWO,                                                                     /**< �������� �� ������� ���������� ����������� ���� */
}MKPD_TX_T;

/**
 * @brief ��������� ���������� ����� (��)
 */  
struct Command_Word_Bits
{
    volatile uint16_t  Data_size__Command_code:5;                               /**< ����� ���� ������ / ��� ������� */
    volatile uint16_t  Subaddr__Manage_mode:4;                                  /**< �������� / ����� ���������� */
    volatile uint16_t  Command_word_mark:1;                                     /**< ������� "�������� ���������� �����" */
    volatile uint16_t  Tx_rx_mark:1;                                            /**< ������ "����/��������" */
    volatile uint16_t  EP_addr:5;                                               /**< ����� ���������� ���������� */
};

/**
 * @brief ��������� ��� ������� � ���������� ����� (��)
 */  
typedef union Command_Word
{
    volatile uint16_t               all;                                        /**< ��������� � � ������ ����� */
    struct Command_Word_Bits        bit;                                        /**< ��������� � ��������� ����� ����� */
}Command_Word_T;

/**
 * @brief ���������� ��������� ����� (��)
 */ 
struct Reply_Word_Bits
{
    volatile uint16_t  FEP1:1;                                                  /**< ������� "������������� ��" */
    volatile uint16_t  MAN:1;                                                   /**< ������� "������� ���������� �����������" */
    volatile uint16_t  FEP0:1;                                                  /**< ������� "������������� ��������" */
    volatile uint16_t  BUSY:1;                                                  /**< ������� "������� �����" */
    volatile uint16_t  Group_rx:1;                                              /**< ������� "������� ��������� �������" */
    volatile uint16_t  RES:3;                                                   /**< ��������� ���� */
    volatile uint16_t  SREQ:1;                                                  /**< ������� "������ �� ������������" */
    volatile uint16_t  Reply_tx:1;                                              /**< ������� "�������� ��������� �����" */
    volatile uint16_t  Data_err:1;                                              /**< ������� "������ � ���������" */
    volatile uint16_t  EP_addr:5;                                               /**< ����� ���������� ���������� */
};

/**
 * @brief ��������� �������� ��������� �������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param sys_clk: ������� (� ���)
 * @retval None
 */   
void MKPD_Set_System_Clock(MKPD_T *pMKPD, uint32_t sys_clk);

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
void MKPD_Set_Channel(MKPD_T *pMKPD, uint32_t channel);

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
void MKPD_Set_Mode(MKPD_T *pMKPD, uint32_t mode);

/**
 * @brief	��������� ������� ����������
 * @param	pMKPD           : ��������� �� ��������� � ���������� MKPD
 * @param       index           : ����� ���������� ��� ��������. TX_ONE ���� TX_TWO 
 * @param	type_trans      : ������ ����������, �������� �������� �� 1 �� 10 � ������������ � ���� � 52070-2003
 * @param       manage_code     : ������ �������� ������ ���������� � ��������� �����. 0 = 00000 ���� 1 = 11111
 */   
void MKPD_Set_BC_Transaction_Format2(MKPD_T *pMKPD, MKPD_TX_T index, unsigned int type_trans, unsigned int manage_code);

/**
 * @brief ��������� ������ ���������� ����������. 
 * @note ����� �������� ������ � ������ ������ ��.
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param ep_addr: ����� �� (0..31)
 * @retval None
 */   
void MKPD_Set_EP_Address(MKPD_T *pMKPD, uint32_t ep_addr);
/**
 * @brief ��������� ���������� ��������� ����� ��������� �������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param time: ����� (� ���). ���������� �������� �� 4 �� 15
 * @retval None
 */   
void MKPD_Set_Interpacket_Time(MKPD_T *pMKPD, uint32_t time);
   
/**
 * @brief ��������� ������� �������� �� ��� �� � ������ ������ �� � ��
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param rwait: ����� (� ���). ���������� �������� �� 34 �� 255
 * @retval None
 */   
void MKPD_Set_Wait_Time(MKPD_T *pMKPD, uint32_t rwait);

/**
 * @brief ��������� ������� ������������ ��������� ����������������� �������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param edge: ����� (� ������ ��������� �������). ���������� �������� �� 0 �� 255
 * @retval None
 */   
void MKPD_Set_Edge_Time(MKPD_T *pMKPD, uint32_t edge);


/**
 * @brief	��������� ������� ���������� ��������
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	IncWith	: 1 - ����������� �������� �������; 0 - ������������ � ���. ��������
 */   
void MKPD_Set_IncWith(MKPD_T *pMKPD, unsigned int IncWith);

/**
 * @brief	����������� ���������� ���������
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Disable_mask	: 4 ����, �� ������ �� �������, ������ 1 ��������� 
 *              �������, ������ 0 ��������: ��� 0 - �, ��� 1 - B, ��� 2 - C, ��� 3 - D
 */   
void MKPD_Set_DecoderDisable(MKPD_T *pMKPD, unsigned int Disable_mask);

/**
 * @brief	��������� ������� �������� ���������� ���������� �� �����, �� ����� 1.3 ���
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Noacttime	: ����� ��������, � ������ ��������� �������
 */   
void MKPD_Set_NoActivity_Time(MKPD_T *pMKPD, unsigned int Noacttime);

/**
 * @brief	��������� ������� �������� �� � ������ ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Bcwaitreply	: ����� �������� ��, � ������ ��������� �������, � ���
 */   
void MKPD_Set_BCWaitReply_Time(MKPD_T *pMKPD, unsigned int Bcwaitreply);

/**
 * @brief	������ ��������� ���������� ������ ��������� ������� � 500 ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Clk	: ���������� ������ ��������� �������
 */   
void MKPD_Set_Clk_500NS(MKPD_T *pMKPD, unsigned int Clk);

/**
 * @brief	������ ��������� ���������� ������ ��������� ������� � 1250 ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Clk	: ���������� ������ ��������� �������
 */   
void MKPD_Set_Clk_1250NS(MKPD_T *pMKPD, unsigned int Clk);
/**
 * @brief	������ ��������� ���������� ������ ��������� ������� � 1500 ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Clk	: ���������� ������ ��������� �������
 */   
void MKPD_Set_Clk_1500NS(MKPD_T *pMKPD, unsigned int Clk);

/**
 * @brief	������ ��������� ���������� ������ ��������� ������� � 1750 ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Clk	: ���������� ������ ��������� �������
 */   
void MKPD_Set_Clk_1750NS(MKPD_T *pMKPD, unsigned int Clk);

/**
 * @brief	������ ��������� ���������� ������ ��������� ������� � 2250 ��
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	Clk	: ���������� ������ ��������� �������
 */   
void MKPD_Set_Clk_2250NS(MKPD_T *pMKPD, unsigned int Clk);

/**
 * @brief ���������� ���������� ����������� ���� � ����� ����������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO)  
 * @return SET or RESET - ��������� ���������� � ��������
 */   
int MKPD_BC_IsReady(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief ��������� ������� ������� �������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param clkrx: ������� (� ���). 
 * @note ������� ������� ������ ��������� ������� ����������� ����� ��� � 5 ���
 * @retval None
 */ 
//void MKPD_Set_Clock_RX(MKPD_T *pMKPD, uint32_t clkrx);
 
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
uint32_t MKPD_Get_Interrupt(MKPD_T *pMKPD);

/**
 * @brief ��������� ���������� �������������� ����������������� �������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param invert_params: ��������� ��������������.
 *         �������� invert_params ����� ��������� ��������:
 *          @arg MKPD_LOOPBACK_INVTX: �������������� ���. ������� ��� ��������
 *          @arg MKPD_LOOPBACK_INVRX0: �������������� ���. ������� � �������� 0 ������
 *          @arg MKPD_LOOPBACK_INVRX1: �������������� ���. ������� � �������� 1 ������
 *          @arg MKPD_LOOPBACK_AUTO_ENA: ��������� ��������������� ����� ���. ������� � ��������
 * @retval None
 */   
void MKPD_Set_Inverting(MKPD_T *pMKPD, uint32_t invert_params);

/**
 * @brief ��������� �������� �������� �����
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @retval None
 */   
void MKPD_Loopback_Enable(MKPD_T *pMKPD);

/**
 * @brief ���������� �������� �������� �����
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @retval None
 */   
void MKPD_Loopback_Disable(MKPD_T *pMKPD);

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
                                     uint32_t num);
/**
 * @brief ��������� ������ DMA
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @param dma_addr: ����� ������� ����� � ������� ������ ��
 * @retval None
 */   
void MKPD_Set_BC_DMA_Address(MKPD_T *pMKPD, MKPD_TX_T index, uint32_t dma_addr);

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
void MKPD_ConfigBusController(MKPD_T *pMKPD, uint32_t address_one, uint32_t address_two, uint32_t channel);

/**
 * @brief ��������� ����� ������ ��� �������� � ����������� ������� 6 ��� 10.
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO)  
 * @param com_data: ���������� ����� ������, 16 ���
 * @retval None
 */   
void MKPD_Set_BC_COM_Data(MKPD_T *pMKPD, MKPD_TX_T index, uint32_t com_data);

/**
 * @brief ��������� ������� ����������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO)  
 * @param type_trans: ������ ���������� (1..10)
 * @retval None
 */   
void MKPD_Set_BC_Transaction_Format(MKPD_T *pMKPD, MKPD_TX_T index, uint32_t type_trans);

/**
 * @brief ��������� ������� ����������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO)  
 * @retval None
 */   
void MKPD_BC_Start_Transaction(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief ����������, ��������� �� ���������� � ������� �� ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return SET or RESET - ��������� �������� ����������
 */   
FlagStatus MKPD_BC_IsWaiting(MKPD_T *pMKPD, MKPD_TX_T index);
/**
 * @brief ����������, ���������� �� ���������� � ��������� ������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return SET or RESET - ��������� �������� ����������
 */  
FlagStatus MKPD_BC_IsSending(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief ���������� �������� ����� ������ ���������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return SET or RESET - ��������� �������� ����������
 */  
FlagStatus MKPD_BC_IsError(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief ���������� �������� ����� �������� ���������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return SET or RESET - ��������� �������� ����������
 */    
FlagStatus MKPD_BC_IsTimeout(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief ���������� �������� �����, ���������� �� ��
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return ���������� ��������� �����, 16 ���
 */   
uint32_t MKPD_BC_Reply_Word(MKPD_T *pMKPD, MKPD_TX_T index);

/**
 * @brief ���������� �������� ������, ���������� �� �� (��� ���������� ������� 5)
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param index: ����� ���������� ��� �������� (TX_ONE/TX_TWO) 
 * @return ���������� ��������� �����, 16 ���
 */     
uint32_t MKPD_BC_Reply_Data(MKPD_T *pMKPD, MKPD_TX_T index);

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
                       unsigned int manage_code);
                       

/**
 * @brief ��������� ������ ������� ����� ������� ������ ��
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param dma_ep: �����. ��� ���� ���������� ������������ ����� ������
 * @retval None
 */   
void MKPD_Set_Endpoint_DMA_Address(MKPD_T *pMKPD, uint32_t dma_ep);
/**
 * @brief ��������� ���������� ����������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param address: ��������� ����� � ������ ��� �������� ���� ������
 * @param ep_address: ����� ���������� ���������� (0..31)
 * @retval None
 */
void MKPD_ConfigEndpoint(MKPD_T *pMKPD, uint32_t address, uint32_t ep_address);

/**
 * @brief ��������� ����� ������ ��� �������� �� ��
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @param rdata: ���������� ����� ������, 16 ���
 * @retval None
 */   
void MKPD_Set_Endpoint_RDATA(MKPD_T *pMKPD, uint32_t rdata);

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
void MKPD_Set_Endpoint_Attributes(MKPD_T *pMKPD, uint32_t attributes);
/**
 * @brief	��������� �������������� ����������������� ������� �� ��������
 * @param	pMKPD	: ��������� �� ��������� � ���������� MKPD
 * @param	invTX	: 1 - ������������� ������ �� ��������; 0 - �� �������������
 */   
void MKPD_Set_InvTX(MKPD_T *pMKPD, unsigned int invTX);

/**
 * @brief ���������� �������� �� �� ����� ������ 
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD
 * @return ���������� ��������� �����, 16 ���
 */   
uint32_t MKPD_Get_Endpoint_COM_Data(MKPD_T *pMKPD);

/**
 * @brief ���������� �������� ����� ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD  
 * @return SET or RESET - ��������� ���������� � ��������
 */   
FlagStatus MKPD_Get_Endpoint_COM_Timeout(MKPD_T *pMKPD);

/**
 * @brief ���������� �������� ����� ������ � ����� ������ (������������ � ����������� �6, 10)
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD  
 * @return SET or RESET - ��������� ���������� � ��������
 */   
FlagStatus MKPD_Get_Endpoint_COM_Error(MKPD_T *pMKPD);

/**
 * @brief ���������� ��������� �����, �������� ��
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD  
 * @return SET or RESET - ��������� ���������� � ��������
 */  
uint32_t MKPD_Get_Endpoint_Command_Word(MKPD_T *pMKPD);

/**
 * @brief ������� ���������� ������ DMA ��� ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD  
 * @param dma_monitor_addr: ��������� ����� � ������ ��� ������
 * @retval None
 */   
void MKPD_Set_Monitor_DMA_Address(MKPD_T *pMKPD, uint32_t dma_monitor_addr);

/**
 * @brief ������� ������� ������ ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD 
 * @param memory_size: ���������� 32-������ ����, ���������� ��� ��������
 * @retval None
 */   
void MKPD_Set_Monitor_Memory_Size(MKPD_T *pMKPD, uint32_t memory_size);

/**
 * @brief ������� ���������� �������� ��� ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD 
 * @param threshold: ���������� ���������� ����, ��� ������� ����������� ���������� ��������
 * @retval None
 */   
void MKPD_Set_Monitor_Threshold(MKPD_T *pMKPD, uint32_t threshold);

/**
 * @brief ��������� ��������
 * @param pMKPD: ��������� �� ��������� � ���������� MKPD 
 * @param address: ��������� ����� � ������ ��� �������� ���� ������
 * @param size: ���������� 32-������ ����, ���������� ��� ��������
 * @param threshold: ���������� ���������� ����, ��� ������� ����������� ���������� ��������
 * @retval None
 */
void MKPD_ConfigMonitor(MKPD_T *pMKPD, uint32_t address, uint32_t size, uint32_t threshold);


#endif /* MKPD_H_ */
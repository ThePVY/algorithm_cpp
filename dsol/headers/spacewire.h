/*!\file
 * \brief ���� ���� �������� ���������, ������� � �������, ����������� ��� �������������� � ���������� ������� SpaceWire.
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

#ifndef SPACEWIRE_H_
#define SPACEWIRE_H_

#include "types.h"



#define SPW_DSC_COUNT 32

/** \brief  ��������� ��� ������� � ��������� Spacewire
 */
typedef struct
{
    __RW uint32_t CONTROL;                                                      /**< ��������: 0x00 ������� ���������� */
    __RW uint32_t STATUS;                                                       /**< ��������: 0x04 ������� ������� */
    __RW uint32_t TXSCALER;                                                     /**< ��������: 0x08 ������� �������� �������� �������� */
    __RW uint32_t TIMECODE;                                                     /**< ��������: 0x0C ������� ��������� ����� */
    __RW uint32_t RXDESCPTR;                                                    /**< ��������: 0x10 ������� ��������� �� ������� ������������ ������ */
    __RW uint32_t TXDESCPTR;	                                                /**< ��������: 0x14 ������� ��������� �� ������� ������������ �������� */
    __RW uint32_t TXSCALERLINK;                                                 /**< ��������: 0x18 ������� �������� �������� ��������  �� ����� Link*/
    __RW uint32_t RESETTIME;                                                    /**< ��������: 0x1C ������� ������� ������� �������� ��� Link (6,4 ���) � ������ ��������� ������� */
    __RW uint32_t DISCONNECTTIME;                                               /**< ��������: 0x20 ������� ������� ������� �������� ���������  (850 ��) (� ������ ��������� �������) */
    __RW uint32_t ENDIANNES;                                                    /**< ��������: 0x24 ������� ������� ����������� �� ������ � �� �������� */      
} SPW_T;

/**
 * @brief ������� ��� CONTROL
 */
#define SW_CONTROL_RESET_AMBA               ((uint32_t)(1 << 0))                /**< ������ �1� ���������� ���������� */
#define SW_CONTROL_RESET_DMA                ((uint32_t)(1 << 1))                /**< ������ �1� ���������� ���������� DMA */
#define SW_CONTROL_LINK_START               ((uint32_t)(1 << 2))                /**< Linkstart; ������ �1� ��������� ��������� ����������. */
#define SW_CONTROL_AUTOSTART                ((uint32_t)(1 << 3))                /**< Autostart; ������ �1� ��������� �������������� ��������� ���������� � ������ ������.*/
#define SW_CONTROL_LINK_DISABLE             ((uint32_t)(1 << 4))                /**< Linkdisable; ������ �1� ��������� ������ Link �����������. */
#define SW_CONTROL_ALLOW_TIMECODE_TX        ((uint32_t)(1 << 5))                /**< ���������� �������� ��������� ����� */
#define SW_CONTROL_RESTART_RX_DMA           ((uint32_t)(1 << 6))                /**< ������ RXDMA */
#define SW_CONTROL_RESTART_TX_DMA           ((uint32_t)(1 << 7))                /**< ������ TXDMA */
#define SW_CONTROL_CANCEL_TX_DMA            ((uint32_t)(1 << 8))                /**< ������ �1� ��������� ������ TXDMA � RXDMA */
#define SW_CONTROL_INT_EN_LINK_UP_DOWN      ((uint32_t)(1 << 9))                /**< ���������� ���������� ��� ��������� ���������� */
#define SW_CONTROL_INT_EN_TIME_CODE         ((uint32_t)(1 << 10))               /**< ���������� ���������� ��� ������ ��������� �����*/
#define SW_CONTROL_INT_EN_RX_DSCR_COMPLETE  ((uint32_t)(1 << 11))               /**< ���������� ���������� �� ���������� RX ����������� ��� IE = �1� */
#define SW_CONTROL_INT_EN_TX_DSCR_COMPLETE  ((uint32_t)(1 << 12))               /**< ���������� ���������� �� ���������� TX ����������� ��� IE = �1� */
#define SW_CONTROL_INT_EN_RX_PACKET         ((uint32_t)(1 << 13))               /**< ���������� ���������� ��� ������ ������ �� ���������� ������ TX ����������� */
#define SW_CONTROL_DESCTABLESIZE(x)         (__RO (uint32_t)((x) & 0xF << 24))    /**< ������ ������� ������������, �������� ������ �� ������ */

/**
 * @brief ������� ��� STATUS
 */
#define SW_STATUS_LINK_STATUS_DISABLED      ((uint32_t)(0x0 << 0))              /**< ������ Link �����������: �������� */
#define SW_STATUS_LINK_STATUS_START         ((uint32_t)(0x1 << 0))              /**< ������ Link �����������: ����� */
#define SW_STATUS_LINK_STATUS_CONNECTED     ((uint32_t)(0x2 << 0))              /**< ������ Link �����������: ���������� ����������� */
#define SW_STATUS_LINK_STATUS_ENABLED       ((uint32_t)(0x3 << 0))              /**< ������ Link �����������: ������� */
#define SW_STATUS_DISCONNECT_ERR            ((uint32_t)(1 << 2))                /**< ������ ���������� */
#define SW_STATUS_PARITY_ERR                ((uint32_t)(1 << 3))                /**< ������ �������� */
#define SW_STATUS_ESCAPE_ERR                ((uint32_t)(1 << 4))                /**< ������ escape */          
#define SW_STATUS_CREDIT_ERR                ((uint32_t)(1 << 5))                /**< ������ credit */           
#define SW_STATUS_RX_DMA_RUNNING            ((uint32_t)(1 << 6))                /**< RXDMA ������� */   
#define SW_STATUS_TX_DMA_RUNNING            ((uint32_t)(1 << 7))                /**< TXDMA ������� */              
#define SW_STATUS_AHB_ERR                   ((uint32_t)(1 << 8))                /**< ������ ���� AHB */             
#define SW_STATUS_RECEIVED_TIMECODE         ((uint32_t)(1 << 10))               /**< ������� ����� � ��������� ������. ��� ������ ���� ���������� �������� �1�*/            
#define SW_STATUS_RX_COMPLETE               ((uint32_t)(1 << 11))               /**< RX ���������� �������� ��� IE = �1�. ��� ������ ���� ���������� �������� �1� */             
#define SW_STATUS_TX_COMPLETE               ((uint32_t)(1 << 12))               /**< TX ���������� �������� ��� IE = �1�. ��� ������ ���� ���������� �������� �1� */  
#define SW_STATUS_PACKET_RX                 ((uint32_t)(1 << 13))               /**< ������� �����. ��� ������ ���� ���������� �������� �1�*/            
#define SW_STATUS_RXFIFO_EMPTY              ((uint32_t)(1 << 14))               /**< (������ ������) - ������ RXFIFO �� �������� ������, � ��������� ����� ��� ��������� �� RXDMA */

           
/**
 * @brief ������� ��� TXSCALER
 */
#define SW_TXSCALER_DIVISOR(x)               ((uint32_t)(((x) & 0xFF) << 0))        /**< �������� ������� ��������� ������� ����������� */

/**
 * @brief ������� ��� RXDESCPTR
 */
#define SW_RXDESCPTR_DSCR_NUM(x)             ((uint32_t)(((x) & 0x1F) << 3))      /**< ����� ����������� */
#define SW_RXDESCPTR_DSCR_ADDR(x)            ((uint32_t)(((x) & 0xFFFFFF) << 8)) /**< ����� ������ ������� ������������ */

/**
 * @brief ������� ��� TXDESCPTR
 */
#define SW_TXDESCPTR(x)                       ((uint32_t)(((x) & 0x1F) << 3))               /**< ����� ����������� */
#define SW_TXDESCPTR_DSCR_ADDR(x)             ((uint32_t)(((x) & 0xFFFFFF) << 8)) /**< ����� ������ ������� ������������ */

/**
 * @brief ������� ��� TxScalerLink
 */
#define SW_TxScalerLink_DIVISOR(x)             ((uint32_t)(((x) & 0xFF) << 0))    /**< TxScalerLink*/

/**
 * @brief ������� ��� ResetTime
 */
#define SW_ResetTime_RESET_TIME(x)             ((uint32_t)(((x) & 0x3FF) << 0))   /**< ResetTime*/

/**
 * @brief ������� ��� DISCONNECTTIME
 */
#define SW_DISCONNECTTIME_DISCONNECT_TIME(x)   ((uint32_t)(((x) & 0xFF) << 0))  /**< DisconnectTime*/

/**
 * @brief ������� ��� Endianness
 */
#define SW_Endianness_RX_ENDIAN(x)              ((uint32_t)((x) << 1))            /**< RxEndianness. �������� 0 - little endian, 1 - big endian*/
#define SW_Endianness_TX_ENDIAN(x)              ((uint32_t)((x) << 0))            /**< TxEndianness. �������� 0 - little endian, 1 - big endian*/

   
   
/** \brief  ��������� ��� DMA ����������� SpaceWire
 */
typedef struct
{
    volatile uint32_t HEADER;
    unsigned char*        DATA_PTR;	
} SPW_DMA_DSC_T;


/** \brief  ��������� ��� ������� DMA ������������ Spacewire
 */
typedef struct
{
    SPW_DMA_DSC_T TXDsc[SPW_DSC_COUNT];
    SPW_DMA_DSC_T RXDsc[SPW_DSC_COUNT];
} SPW_DMA_DSC_TBL_T;


/**
 * @brief ������� ��� HEADER �����������
 */
#define SW_DMA_DSC_HEADER_NUM(x)            ((uint32_t)(((x) & 0xFFFF) << 0))     /**< ���������� ���� */
#define SW_DMA_DSC_HEADER_EN                ((uint32_t)(1 << 16))               /**< ���������� ������������ ������������ */
#define SW_DMA_DSC_HEADER_WR                ((uint32_t)(1 << 17))               /**< ���������� ������ ������������ */
#define SW_DMA_DSC_HEADER_IE                ((uint32_t)(1 << 18))               /**< ���������� ���������� � ����������� ������� �� ���������� */
#define SW_DMA_DSC_HEADER_DONE              ((uint32_t)(1 << 19))               /**< ������ ���������� */
#define SW_DMA_DSC_HEADER_EOP               ((uint32_t)(1 << 20))               /**< ������� EOP */
#define SW_DMA_DSC_HEADER_EEP               ((uint32_t)(1 << 21))               /**< ������� EEP */   
   
/**
 * @brief ������������� SpaceWire
 * @param pSPW : ��������� �� ��������� � ���������� SpaceWire
 */
void SPW_Init(SPW_T *pSPW);

/**
 * @brief �������������� SpaceWire
 * @param pSPW : ��������� �� ��������� � ���������� SpaceWire
 */
void SPW_DeInit(SPW_T *pSPW);

/**
 * @brief ����� �������� ������� ������ Spacewire
 * @param pSPW : ��������� �� ��������� � ���������� SpaceWire
 */
void SPW_freq(uint8_t freq_num);





#endif
/*!\file
 * \brief ���� ���� �������� ���������, ������� � �������, ����������� ��� �������������� � ���������� ������� UART.
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

#ifndef UART_H_
#define UART_H_

#include "types.h"
#include "ringbuffer.h"
    
#define UART_DR_MASK_DATA                ((uint32_t)(0x00FF))                   /**< ������������ ������ ��� ������� ��� �������� ������ DR */

/** \brief  ��������� ��� ������� � ��������� UART
 */
typedef struct
{
    __RW uint32_t DR;                                                           /**< ��������: 0x000 ������� ������. */
    __RW uint32_t RSR_ECR;                                                      /**< ��������: 0x004 ������� ��������� ���������/������ ������. */
    uint32_t RESERVED0[4];                                                      
    __RO  uint32_t FR;                                                          /**< ��������: 0x018 ������� ������. */
    uint32_t RESERVED1[2];                                                
    __RW uint32_t IBRD;                                                         /**< ��������: 0x024 ����� ����� �������� �������� ������ �������. */
    __RW uint32_t FBRD;                                                         /**< ��������: 0x028 ������� ����� �������� �������� �������������. */
    __RW uint32_t LCR_H;                                                        /**< ��������: 0x02C ������� ���������� ������ LCR_H. */
    __RW uint32_t CR;                                                           /**< ��������: 0x030 ������� ���������� ������� CR. */
    __RW uint32_t IFLS;                                                         /**< ��������: 0x034 ������� ������ ���������� �� ���������� ������ FIFO. */
    __RW uint32_t IMSC;                                                         /**< ��������: 0x038 ������� ����� ����������. */
    __RO uint32_t RIS;                                                          /**< ��������: 0x03C ������� ��������� ����������. */
    __RO uint32_t MIS;                                                          /**< ��������: 0x040 ������� ��������� ���������� � �������������. */
    __WO uint32_t ICR;                                                          /**< ��������: 0x044 ������� ������ ����������. */
    __RW uint32_t DMACR;                                                        /**< ��������: 0x048 ������� ���������� DMA. */
}UART_T;                                                                             
                                                                                     
/**                                                                                  
 * @brief ������� ��� �������� DR                                                    
 */                                                                                  
#define UART_DR_DATA(x)                  ((uint32_t)((x) & 0xFF))               /**< �����������/������������ ������ */     
#define UART_DR_FE                       ((uint32_t)(1 << 8))                   /**< ������ � ��������� ����� */
#define UART_DR_PE                       ((uint32_t)(1 << 9))                   /**< ������ �������� �������� */
#define UART_DR_BE                       ((uint32_t)(1 << 10))                  /**< ������ ����� */
#define UART_DR_OE                       ((uint32_t)(1 << 11))                  /**< ������������ ������ ��������� */
//#define UART_DR_MASK_DATA                ((uint32_t)(0x00FF))                   /**< ������������ ������ ��� ������� ��� �������� ������ DR */

/**
 * @brief ������� � ���� ��� �������� RSR_ECR
 */
typedef enum  
{
    UART_RSR_FE = ((uint32_t)(1 << 0)),                                         /**< ������ � ��������� ����� */
    UART_RSR_PE = ((uint32_t)(1 << 1)),                                         /**< ������ �������� �������� */
    UART_RSR_BE = ((uint32_t)(1 << 2)),                                         /**< ������ ����� */
    UART_RSR_OE = ((uint32_t)(1 << 3)),                                         /**< ������������ ������ ��������� */
}UART_REC_STATUS_T;

/**
 * @brief ������� � ���� ��� �������� FR
 */
typedef enum 
{
    UART_FR_BUSY = ((uint32_t)(1 << 3)),                                        /**< UART ����� */
    UART_FR_RXFE = ((uint32_t)(1 << 4)),                                        /**< ����� FIFO ��������� ����. */
    UART_FR_TXFF = ((uint32_t)(1 << 5)),                                        /**< ����� FIFO ����������� ��������.  */
    UART_FR_RXFF = ((uint32_t)(1 << 6)),                                        /**< ����� FIFO ��������� �������� */
    UART_FR_TXFE = ((uint32_t)(1 << 7)),                                        /**< ����� FIFO ����������� ���� */
    UART_FR_RI   = ((uint32_t)(1 << 8)),                                        /**< �������� ����� nUARTRI */
}UART_STATUS_T;

/**
 * @brief ������� ��� �������� UARTBIRD 
 */
#define UART_IBRD_BAUDDIV_INT(x)         ((uint32_t)((x) & 0xFFFF))               /**< ����� ����� ������������ �������  */

/**
 * @brief ������� ��� �������� UARTx_FBRD 
 */
#define UART_FBRD_BAUDDIV_FRAC(x)        ((uint32_t)((x) & 0x1F))                 /**< ������� ����� ������������ �������  */

/**
 * @brief ������� � ���� ��� �������� UARTx_LCR_H 
*/
#define UART_LCR_H_BRK                   ((uint32_t)(1 << 0))                   /**< ������ ����� */
#define UART_LCR_H_PEN                   ((uint32_t)(1 << 1))                   /**< ���������� �������� �������� */
#define UART_LCR_H_PDIS                  ((uint32_t)(0 << 1))                   /**< ���������� �������� �������� */
#define UART_LCR_H_EPS_EVEN              ((uint32_t)(1 << 2))                   /**< ���������� �� ������� */
#define UART_LCR_H_EPS_ODD               ((uint32_t)(0 << 2))                   /**< ���������� �� ��������� */
#define UART_LCR_H_STP2                  ((uint32_t)(1 << 3))                   /**< ����� �������� ���� �������� ��� */
#define UART_LCR_H_STP1                  ((uint32_t)(0 << 3))                   /**< ����� �������� ������ ��������� ���� */
#define UART_LCR_H_FEN                   ((uint32_t)(1 << 4))                   /**< ���������� ������ ������ FIFO ��������� � ����������� */
#define UART_LCR_H_FDIS                  ((uint32_t)(0 << 4))                   /**< ���������� ������ ������ FIFO ��������� � ����������� */

typedef enum 
{
    UART_LCR_H_WLEN5 = ((uint32_t)(0 << 5)),                                    /**< ����� ����� 5 ��� */
    UART_LCR_H_WLEN6 = ((uint32_t)(1 << 5)),                                    /**< ����� ����� 6 ��� */
    UART_LCR_H_WLEN7 = ((uint32_t)(2 << 5)),                                    /**< ����� ����� 7 ��� */
    UART_LCR_H_WLEN8 = ((uint32_t)(3 << 5)),                                    /**< ����� ����� 8 ��� */
}UART_WLEN;

#define UART_LCR_H_SPS_EN                ((uint32_t)(1 << 7))                   /**< ���������� �������� ���� �������� � ������������� ��������� */
#define UART_LCR_H_SPS_DIS               ((uint32_t)(0 << 7))                   /**< ���������� �������� ���� �������� � ������������� ��������� */

/*
 * @brief ������� ��� �������� UARTx_CR 
 */
#define UART_CR_UARTEN                   ((uint32_t)(1 << 0))                   /**< ���������� ������ ����������������� */
#define UART_CR_LBE                      ((uint32_t)(1 << 7))                   /**< ���������� ������ � ������ loopback */
#define UART_CR_TXE                      ((uint32_t)(1 << 8))                   /**< ���������� ������ ����������� */
#define UART_CR_RXE                      ((uint32_t)(1 << 9))                   /**< ���������� ������ ��������� */
#define UART_CR_BITMASK                  ((uint32_t)(0x381))

/**
 * @brief ��� UART_IFLS ��� �������� UARTx_IFLS 
*/
typedef enum 
{
    UART_IFLS_1DIV8 = ((uint32_t)(0 << 0)),                                     /**< ����� �������� �� 1/8  */
    UART_IFLS_1DIV4 = ((uint32_t)(1 << 0)),                                     /**< ����� �������� �� 1/4  */
    UART_IFLS_1DIV2 = ((uint32_t)(2 << 0)),                                     /**< ����� �������� �� 1/2  */
    UART_IFLS_3DIV4 = ((uint32_t)(3 << 0)),                                     /**< ����� �������� �� 3/4  */
    UART_IFLS_7DIV8 = ((uint32_t)(4 << 0)),                                     /**< ����� �������� �� 7/8  */
}UART_IFLS;   

/**
 * @brief ������� � ���� ��� �������� UARTx_IMSC 
*/
typedef enum 
{
    UART_IMSC_RXIM = ((uint32_t)(1 << 4)),                                      /**< ������������ ���������� ���������� �� ��������� UARTRXINTR*/
    UART_IMSC_TXIM = ((uint32_t)(1 << 5)),                                      /**< ������������ ���������� �� ����������� UARTTXINTR */
    UART_IMSC_RTIM = ((uint32_t)(1 << 6)),                                      /**< ������������ ���������� �� �������� ������ ������ UARTRTINTR */
    UART_IMSC_FEIM = ((uint32_t)(1 << 7)),                                      /**< ������������ ���������� �� ������ � ��������� ����� UARTFEINTR */
    UART_IMSC_PEIM = ((uint32_t)(1 << 8)),                                      /**< ������������ ���������� �� ������ �������� �������� UARTPEINTR */
    UART_IMSC_BEIM = ((uint32_t)(1 << 9)),                                      /**< ������������ ���������� �� ������� ����� UARTBEINTR */
    UART_IMSC_OEIM = ((uint32_t)(1 << 10)),                                     /**< ������������ ���������� �� ������������ ������ UARTOEINTR */
    UART_IMSC_BITMASK = ((uint32_t)(0x7F << 4)),
}UART_INTMASK_T;

/**
 * @brief ������� � ���� ��� �������� UARTx_RIS  
*/
typedef enum 
{
    UART_RIS_RXRIS = ((uint32_t)(1 << 4)),                                      /**< ��������� ���������� ���������� �� ��������� UARTRXINTR*/
    UART_RIS_TXRIS = ((uint32_t)(1 << 5)),                                      /**< ��������� ���������� �� ����������� UARTTXINTR */
    UART_RIS_RTRIS = ((uint32_t)(1 << 6)),                                      /**< ��������� ���������� �� �������� ������ ������ UARTRTINTR */
    UART_RIS_FERIS = ((uint32_t)(1 << 7)),                                      /**< ��������� ���������� �� ������ � ��������� ����� UARTFEINTR */
    UART_RIS_PERIS = ((uint32_t)(1 << 8)),                                      /**< ��������� ���������� �� ������ �������� �������� UARTPEINTR */
    UART_RIS_BERIS = ((uint32_t)(1 << 9)),                                      /**< ��������� ���������� �� ������� ����� UARTBEINTR */
    UART_RIS_OERIS = ((uint32_t)(1 << 10)),                                     /**< ��������� ���������� �� ������������ ������ UARTOEINTR */
    UART_RIS_BITMASK = ((uint32_t)(0x7F << 4)),
}UART_INTSTATUS_T;

/**
 * @brief ������� � ���� ��� �������� UARTx_MIS  
*/
typedef enum 
{
    UART_MIS_RXMIS = ((uint32_t)(1 << 4)),                                      /**< ������������� ��������� ���������� ���������� �� ��������� UARTRXINTR*/
    UART_MIS_TXMIS = ((uint32_t)(1 << 5)),                                      /**< ������������� ��������� ���������� �� ����������� UARTTXINTR */
    UART_MIS_RTMIS = ((uint32_t)(1 << 6)),                                      /**< ������������� ��������� ���������� �� �������� ������ ������ UARTRTINTR */
    UART_MIS_FEMIS = ((uint32_t)(1 << 7)),                                      /**< ������������� ��������� ���������� �� ������ � ��������� ����� UARTFEINTR */
    UART_MIS_PEMIS = ((uint32_t)(1 << 8)),                                      /**< ������������� ��������� ���������� �� ������ �������� �������� UARTPEINTR */
    UART_MIS_BEMIS = ((uint32_t)(1 << 9)),                                      /**< ������������� ��������� ���������� �� ������� ����� UARTBEINTR */
    UART_MIS_OEMIS = ((uint32_t)(1 << 10)),                                     /**< ������������� ��������� ���������� �� ������������ ������ UARTOEINTR */
    UART_MIS_BITMASK = ((uint32_t)(0x7F << 4)),        
}UART_MASKINTSTATUS_T;

/**
 * @brief ������� � ���� ��� �������� UARTx_ICR  
*/
typedef enum 
{
    UART_ICR_RXIC = ((uint32_t)(1 << 4)),                                       /**< ����� ���������� ���������� �� ��������� UARTRXINTR*/
    UART_ICR_TXIC = ((uint32_t)(1 << 5)),                                       /**< ����� ���������� �� ����������� UARTTXINTR */
    UART_ICR_RTIC = ((uint32_t)(1 << 6)),                                       /**< ����� ���������� �� �������� ������ ������ UARTRTINTR */
    UART_ICR_FEIC = ((uint32_t)(1 << 7)),                                       /**< ����� ���������� �� ������ � ��������� ����� UARTFEINTR */
    UART_ICR_PEIC = ((uint32_t)(1 << 8)),                                       /**< ����� ���������� �� ������ �������� �������� UARTPEINTR */
    UART_ICR_BEIC = ((uint32_t)(1 << 9)),                                       /**< ����� ���������� �� ������� ����� UARTBEINTR */
    UART_ICR_OEIC = ((uint32_t)(1 << 10)),                                      /**< ����� ���������� �� ������������ ������ UARTOEINTR */        
    UART_ICR_BITMASK = ((uint32_t)(0x7F << 4)),                                 /**< BITMASK*/
}UART_INTCLEAR_T;

/**
 * @brief ������� � ���� ��� �������� UARTx_DMACR 
*/
typedef enum 
{
    UART_DMACR_RXDMAE = ((uint32_t)(1 << 0)),                                   /**< ���������� ������������� DMA ��� ������ */	
    UART_DMACR_TXDMAE = ((uint32_t)(1 << 1)),	                                /**< ���������� ������������� DMA ��� �������� */
    UART_DMACR_DMAONERR = ((uint32_t)(1 << 2)),	                                /**< ���� ��� ���������� � 1, �� � ������ ������������� ���������� �� ����������� ������ ����������� ������� DMA �� ��������� UARTRXDMASREQ � UARTRXDMABREQ.*/
    UART_DMACR_BITMASK = ((uint32_t)(3 << 0)),                                  /**< ���������� ������������� DMA ��� ������ � �������� */
}UART_DMACR_T;

#define UART_DMACR_DMAONERR              ((uint32_t)(1 << 2))                   /**< ���������� ���������� �������� DMA �� ��������� UARTRXDMASREQ � UARTRXDMABREQ � ������ ������������� ���������� �� ����������� ������ */  
#define BAUDRATE_921600                  (921600)                               /**< 921600 (���/�) */
#define BAUDRATE_460800                  (460800)                               /**< 460800 (���/�) */
#define BAUDRATE_230400                  (230400)                               /**< 230400 (���/�) */
#define BAUDRATE_115200                  (115200)                               /**< 115200 (���/�) */
#define BAUDRATE_57600                   (57600)                                /**< 57600 (���/�) */
#define BAUDRATE_38400                   (38400)                                /**< 38400 (���/�) */   
#define BAUDRATE_19200                   (19200)                                /**< 19200 (���/�) */
#define BAUDRATE_14400                   (14400)                                /**< 14400 (���/�) */
#define BAUDRATE_9600                    (9600)                                 /**< 9600 (���/�) */
#define BAUDRATE_2400                    (2400)                                 /**< 2400 (���/�) */
#define BAUDRATE_1200                    (1200)                                 /**< 1200 (���/�) */
#define BAUDRATE_110                     (110)                                  /**< 110 (���/�) */ 


/**
 * @brief ���������� ������ �����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
 void UART_TXEnable(UART_T *pUART);

/**
 * @brief ���������� ������ �����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
 void UART_TXDisable(UART_T *pUART);

/**
 * @brief ���������� ������ ���������
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
 void UART_RXEnable(UART_T *pUART);
   
/**
 * @brief ���������� ������ ���������
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
 void UART_RXDisable(UART_T *pUART);

/**
 * @brief ���������� ������ UART
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
 void UART_Enable(UART_T *pUART);

/**
 * @brief ���������� ������ UART
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
 void UART_Disable(UART_T *pUART);

/**
 * @brief �������� ������ ����� �� UART'�
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param data: ���� ��� ��������
 */
 void UART_SendByte(UART_T *pUART, uint8_t data);


/**
 * @brief ����� ������ ����� �� UART'�
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @return �������� ����
 */
 uint8_t UART_ReadByte(UART_T *pUART);

/**
 * @brief ���������� ���������� �� UART'�
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param IntMask: ��� ����������, ��������� ��������� ��������:
                                                - UART_IMSC_RXIM 
                                                - UART_IMSC_TXIM 
                                                - UART_IMSC_RTIM 
                                                - UART_IMSC_FEIM 
                                                - UART_IMSC_PEIM 
                                                - UART_IMSC_BEIM 
                                                - UART_IMSC_OEIM 
                                                - UART_IMSC_BITMASK 
 */
 void UART_IntEnable(UART_T *pUART, UART_INTMASK_T IntMask);

/**
 * @brief ���������� ���������� �� UART'�
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param IntMask: ��� ����������, ��������� ��������� ��������:
                                                - UART_IMSC_RXIM 
                                                - UART_IMSC_TXIM 
                                                - UART_IMSC_RTIM 
                                                - UART_IMSC_FEIM 
                                                - UART_IMSC_PEIM 
                                                - UART_IMSC_BEIM 
                                                - UART_IMSC_OEIM 
                                                - UART_IMSC_BITMASK
 */
 void UART_IntDisable(UART_T *pUART, UART_INTMASK_T IntMask);


/**
 * @brief ��������� ������� �������������� ����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param MaskInt: ��� ����������, ��������� ��������� ��������:
 *						- UART_MIS_RXMIS
 *						- UART_MIS_TXMIS
 *						- UART_MIS_RTMIS
 *						- UART_MIS_FEMIS
 *                                              - UART_MIS_PEMIS 
 *                                              - UART_MIS_BEMIS 
 *                                              - UART_MIS_OEMIS 
 * @return ������ ����������, SET or RESET
 */
 uint32_t UART_GetIntStatus(UART_T *pUART, UART_MASKINTSTATUS_T MaskInt);

/**
 * @brief ����� ������ ����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param IntClear: ��� ���������� ��� ������, ��������� ��������� ��������:
 *						- UART_ICR_RXIC
 *						- UART_ICR_TXIC
 *						- UART_ICR_RTIC
 *						- UART_ICR_FEIC
 *                                              - UART_ICR_PEIC  
 *                                              - UART_ICR_BEIC  
 *                                              - UART_ICR_OEIC  
 *                                              - UART_ICR_BITMASK        
*/
 void UART_ClearIntPending(UART_T *pUART, UART_INTCLEAR_T IntClear);

/**
 * @brief ��������� ������� ���������� �� ���������� ������ ���������/�����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param rxfifolimit: ����� ���������� �� ���������� ������ ���������
 * @param txfifolimit: ����� ���������� �� ���������� ������ �����������
 */
 void UART_SetupFIFOS(UART_T *pUART, UART_IFLS rxfifolimit, UART_IFLS txfifolimit);

/**
 * @brief ��������� ����� ����� ������, ����� �������� ��� � �������� ��������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param config: ��������� UART, ���������� �������� ��������, ������������ ��� LCR_H, ��������: (UART_LCR_H_PEN | UART_LCR_H_EPS_EVEN | UART_LCR_H_STP1 | UART_LCR_H_FEN | UART_LCR_H_WLEN8 | UART_LCR_H_SPS_DIS)
 */
 void UART_Config(UART_T *pUART, uint32_t config);

/**
 * @brief ��������� �������� �������� �������� ������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param IBRD: ����� ����� �������� �������� �������� ������
 * @param FBRD: ������� ����� �������� �������� �������� ������
 */
 void UART_SetDivisor(UART_T *pUART, uint32_t IBRD, uint32_t FBRD);

/**
 * @brief ��������� �������� ������� UART �����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param Stat: ��� �������, ��������� ��������� ��������:
 *						- UART_FR_BUSY
 *						- UART_FR_RXFE
 *						- UART_FR_TXFF
 *						- UART_FR_RXFF
 *						- UART_FR_TXFE
                                                - UART_FR_RI   
 * @return ������ UART �����������, SET or RESET

 */
FlagStatus UART_GetStatus(UART_T *pUART, UART_STATUS_T Stat);

/**
 * @brief ������������� UART
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
void UART_Init(UART_T *pUART);


/**
 * @brief ��������������� UART
 * @param pUART: ��������� �� ��������� � ���������� UART
 */
void UART_DeInit(UART_T *pUART);

/**
 * @brief ��������� ����� � ������� ������ �������� ��� ��������� �������� �������� ����������������� ������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param baud: ����������� �������� ����������������� ������, ��������: BAUDRATE_921600..BAUDRATE_110
 * @return ���������� �������� � ������ ������ ��� 0, ���� �������� ��������� �� �������
 */
uint32_t UART_SetBaud(UART_T *pUART, uint32_t baud,const uint32_t sys_freq);

/**
 * @brief �������� ������� ���� �� UART'�, ��� �������� ������������ FIFO �����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param data: ��������� �� ������ ��� ��������
 * @param numBytes: ����� ������ ��� ��������
 * @return ����� ���������� ������
 */
uint32_t UART_Send(UART_T *pUART, const void *data, uint32_t numBytes);

/**
 * @brief ����� ������� ���� �� UART'�, ��� �������� ���������� ���������� ������� ���������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param data: ��������� �� ������ ��� ������ ������
 * @param numBytes: ����� ������ ��� ������
 * @return ����� �������� ������
 */
uint32_t UART_Read(UART_T *pUART, void *data, uint32_t numBytes);

/**
 * @brief �������� ������� ���� �� UART'�, � ��������� ������������ FIFO �����������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param data: ��������� �� ������ ��� ��������
 * @param numBytes: ����� ������ ��� ��������
 * @return ����� ���������� ������
 */
uint32_t UART_SendBlocking(UART_T *pUART, const void *data, uint32_t numBytes);

/**
 * @brief ����� ������� ���� �� UART'�, � ��������� ���������� ���������� ������� ���������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param data: ��������� �� ������ ��� ������ ������
 * @param numBytes: ����� ������ ��� ������
 * @return ����� �������� ������
 */
uint32_t UART_ReadBlocking(UART_T *pUART, void *data, uint32_t numBytes);

/**
 * @brief ���������� ���������� UART �� ������ ������ ��� ��������� �������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param pRB: ��������� �� ��������� ���������� ������
 */
void UART_RXIntHandlerRB(UART_T *pUART, RINGBUFF_T *pRB);

/**
 * @brief ���������� ���������� UART �� �������� ������ ��� ��������� �������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param pRB: ��������� �� ��������� ���������� ������
 */
void UART_TXIntHandlerRB(UART_T *pUART, RINGBUFF_T *pRB);

/**
 * @brief ���������� ���������� UART �� ������/�������� ������ ��� ��������� �������
 * @param pUART: ��������� �� ��������� � ���������� UART
 * @param pRXRB: ��������� �� ��������� ���������� ������ ��� ������
 * @param pTXRB: ��������� �� ��������� ���������� ������ ��� ��������
 */
void UART_IRQRBHandler(UART_T *pUART, RINGBUFF_T *pRXRB, RINGBUFF_T *pTXRB);

/**
 * @brief ������ ������ � ��������� ����� � ������ ��������
 * @param pUART	: ��������� �� ��������� � ���������� UART
 * @param pRB: ��������� �� ��������� ���������� ������
 * @param data: ������ ��� ������
 * @param bytes: ����� ������
 * @return ����� ������, ���������� � �����
 */
uint32_t UART_SendRB(UART_T *pUART, RINGBUFF_T *pRB, const void *data, uint32_t bytes);

/**
 * @brief ������ ������ �� ���������� ������ ����� ������
 * @param pUART	: ��������� �� ��������� � ���������� UART
 * @param pRB: ��������� �� ��������� ���������� ������
 * @param data: ��������� �� ������ ��� ������ ������
 * @param bytes: ����� ������ ��� ������
 * @return ����� �������� ������
 */
uint32_t UART_ReadRB(UART_T *pUART, RINGBUFF_T *pRB, void *data, uint32_t bytes);


#endif 
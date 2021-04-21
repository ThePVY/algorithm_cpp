/*!\file
 * \brief ���� ���� �������� ���������, ������� � �������, ����������� ��� �������������� � ���������� CAN.
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

#ifndef CAN_H
#define CAN_H

#include "types.h"



/**
 * @brief ��������� ��� ������� � ��������� ����������� CAN � ������� ������.
 */
typedef struct
{
    __RW uint32_t CONTROL;                                                      /**< ��������: 0x00 ����������� ������� */
    __WO uint32_t COMMAND;                                                      /**< ��������: 0x04 ������� ������ */
    __RO uint32_t STATUS;                                                       /**< ��������: 0x08 ������� ������� */
    __RO uint32_t INTERRUPT;                                                    /**< ��������: 0x0C ������� ���������� */
    __RW uint32_t ACEPTANCE_CODE;                                               /**< ��������: 0x10 ������� ��������� ����. ������ � ��������� ������ */
    __RW uint32_t ACEPTANCE_MASK;                                               /**< ��������: 0x14 ������� �������� �����. ������ � ��������� ������ */
    __RW uint32_t BUS_TIMING_0;                                                 /**< ��������: 0x18 ������ ������� ��������� ���������� ����. ������ � ��������� ������ */
    __RW uint32_t BUS_TIMING_1;                                                 /**< ��������: 0x1C ������ ������� ��������� ���������� ����. ������ � ��������� ������ */
    uint32_t reserved[2];                                                       /**< ������*/
    __RW uint32_t TX_id1;                                                       /**< ��������: 0x28 ������ ������� ��������� ������ ��� ��������. ������ � ������� ��������� */
    __RW uint32_t TX_id2_rtr_dlc;                                               /**< ��������: 0x2C ������ ������� ��������� ������ ��� ��������. ������ � ������� ��������� */
    __RW uint32_t TX_data_byte_1;                                               /**< ��������: 0x30 �������� ����������� ������ ��� �������� */
    __RW uint32_t TX_data_byte_2;                                               /**< ��������: 0x34 �������� ����������� ������ ��� �������� */
    __RW uint32_t TX_data_byte_3;                                               /**< ��������: 0x38 �������� ����������� ������ ��� �������� */
    __RW uint32_t TX_data_byte_4;                                               /**< ��������: 0x3C �������� ����������� ������ ��� �������� */
    __RW uint32_t TX_data_byte_5;                                               /**< ��������: 0x40 �������� ����������� ������ ��� �������� */
    __RW uint32_t TX_data_byte_6;                                               /**< ��������: 0x44 �������� ����������� ������ ��� �������� */
    __RW uint32_t TX_data_byte_7;                                               /**< ��������: 0x48 �������� ����������� ������ ��� �������� */
    __RW uint32_t TX_data_byte_8;                                               /**< ��������: 0x4C �������� ����������� ������ ��� �������� */
    __RO uint32_t RX_id1;                                                       /**< ��������: 0x50 ������ ������� ��������� ������ ��� ������ */
    __RO uint32_t RX_id2_rtr_dlc;                                               /**< ��������: 0x54 ������ ������� ��������� ������ ��� ������ */
    __RO uint32_t RX_data_byte_1;                                               /**< ��������: 0x58 �������� ����������� ������������ ������ */
    __RO uint32_t RX_data_byte_2;                                               /**< ��������: 0x5C �������� ����������� ������������ ������ */
    __RO uint32_t RX_data_byte_3;                                               /**< ��������: 0x60 �������� ����������� ������������ ������ */
    __RO uint32_t RX_data_byte_4;                                               /**< ��������: 0x64 �������� ����������� ������������ ������ */
    __RO uint32_t RX_data_byte_5;                                               /**< ��������: 0x68 �������� ����������� ������������ ������ */
    __RO uint32_t RX_data_byte_6;                                               /**< ��������: 0x6C �������� ����������� ������������ ������ */
    __RO uint32_t RX_data_byte_7;                                               /**< ��������: 0x70 �������� ����������� ������������ ������ */
    __RO uint32_t RX_data_byte_8;                                               /**< ��������: 0x74 �������� ����������� ������������ ������ */
    uint32_t reserved2;                                                         /**< ������*/
    __RW uint32_t Clock_divider;                                                /**< ��������: 0x78 ������� �������� ������� ������� */
    
}CAN_T;

/**
 * @brief ������� � ���� ��� �������� CONTROL
 */
#define Reset_request(x)      ((uint32_t)((x) << 0))                              /**< ������ 1 � ���� ��� ��������� ����� ������� �������� ������ � ��������� ��������� � ��������� ������. ������ 0 ��������� ���������� � ������� ���������. �� ��������� ������� ��������� ������, ��� ����� �������� 1 */
#define Receive_Interrupt_Enable(x)      ((uint32_t)((x) << 1))                   /**< ��������� ���������� ������. 1 - ��������, 0 - ���������*/
#define Transmit_Interrupt_Enable(x)      ((uint32_t)((x) << 2))                  /**< ��������� ���������� ��������. 1 - ��������, 0 - ���������*/
#define Error_Interrupt_Enable(x)      ((uint32_t)((x) << 3))                     /**< ��������� ���������� ������. 1 - ��������, 0 - ���������*/
#define Overrun_Interrupt_Enable(x)      ((uint32_t)((x) << 4))                   /**< ��������� ���������� ������������. 1 - ��������, 0 - ���������*/

/**
 * @brief ������� � ���� ��� �������� COMMAND
 */
#define Transmission_request(x)      ((uint32_t)((x) << 0))                       /**< ������ 1 ��������� �������� ��������� � ����� ��� �������� (TX buffer)*/
#define Abort_transmission(x)      ((uint32_t)((x) << 1))                         /**< ������ 1 ��������� ��������, ������� ��� �� ���� ��������*/
#define Release_receive_buffer(x)      ((uint32_t)((x) << 2))                     /**< ������ 1 ������� �������� ����� ��� ����� ������*/
#define Clear_data_overrun(x)           ((uint32_t)((x) << 3))                    /**< ������ 1 ������� ��� ������������ (Data overrun status) � �������� �������*/

/**
 * @brief ������� � ���� ��� �������� STATUS
 */
#define Receive_buffer_status(x)           ((uint32_t)((x) << 0))                 /**< �������� 1 ��������, ��� � �������� FIFO ������������ �������� ���������
                                                                                    ��� ������������ � 0, ���� ���� ������ ������� Release receive buffer ����� ��� � �������� Command. ���� ��� ���� � �������� FIFO ������������ ����������� ���������, ��� ����� ���������� � 1 ��������.
                                                                                    */
#define Data_overrun_status(x)           ((uint32_t)((x) << 1))                   /**<�������� 1 ��������, ��� ��������� ���� �������� ��-�� ���������� ���������� ����� � FIFO
                                                                                    ��� ��������, ��� ���������� ������������ ��������� ���� �������, ��������� � �������� FIFO ������������� ��������� �����. ������ ���  ��������������� � ������ ����������� ������ �� FIFO.
                                                                                    */
#define Transmit_buffer_status(x)           ((uint32_t)((x) << 2))                /**<�������� 1 ��������, ��� ������ � ���������� ����� ���������
                                                                                �� ����� �������� ��������� ���������� ����� ���������� � ��� ����� �������� 0. ���� ���������� �� �������� ���������, ��� ����� �������� 1 � �������� ������ ��������� ��������� �� ��������.
                                                                                    */
#define Transmission_complete(x)           ((uint32_t)((x) << 3))                 /**< �������� 1 ����� ���������� ��������� ���� ������� ��������
                                                                                    ��� ������������ � 0 ����� ����� ������ �������� � �� ��������������� � 1 �� ��� ���, ���� ��������� �� ����� ������� ��������.
                                                                                    */
#define Receive_status(x)           ((uint32_t)((x) << 4))                        /**< �������� 1 �� ����� ����� ��������� ������������*/
#define Transmit_status(x)           ((uint32_t)((x) << 5))                        /**< �������� 1 �� ����� ����� ��������� ������������*/
#define Error_Status(x)           ((uint32_t)((x) << 6))                          /**< �������� 1 ����� ���� �� ���� �� ��������� ������ �������� �������� CPU warning limit = 96*/
#define Bus_status(x)           ((uint32_t)((x) << 7))                            /**< �������� 1 ����� ���� �� ���� �� ��������� ������ �������� �������� CPU warning limit = 96*/

/**
 * @brief ������� � ���� ��� �������� INTERRUPT
 */
#define Receive_interrupt(x)           ((uint32_t)((x) << 0))                     /**< ��������������� �������� 1, ���� � �������� FIFO ������������ �������� ���������*/
#define Transmit_interrupt(x)           ((uint32_t)((x) << 1))                    /**< ��������������� �������� 1 � ������ ������������ ����������� ������*/
#define Error_interrupt(x)           ((uint32_t)((x) << 2))                       /**<��������������� �������� 1 ���� ���������� ������ ���� ��� ������ ������*/
#define Data_overrun_interrupt(x)      ((uint32_t)((x) << 3))                     /**< ��������������� � 1 ����� ��� Data overrun status � �������� Status ��������� �� 0 � 1*/


/**
 * @brief ��������� ��� ������� � ��������� ����������� CAN � ���������� ����� ������.
 */
typedef struct
{
    __RW uint32_t Mode;                                                         /**< ��������: 0x00 ������� ������ ������ */
    __WO uint32_t COMMAND;                                                      /**< ��������: 0x04 ������� ������ */
    __RO uint32_t STATUS;                                                       /**< ��������: 0x08 ������� ������� */
    __RO uint32_t INTERRUPT;                                                    /**< ��������: 0x0C ������� ���������� */
    __RW uint32_t Interrupt_enable;                                             /**< ��������: 0x10 ������� ��������� ����������*/
    __RW uint32_t reserved;                                                     /**< ��������: 0x14 */
    __RW uint32_t BUS_TIMING_0;                                                 /**< ��������: 0x18 ������ ������� ��������� ���������� ����. ������ � ��������� ������ */
    __RW uint32_t BUS_TIMING_1;                                                 /**< ��������: 0x1C ������ ������� ��������� ���������� ����. ������ � ��������� ������ */
    uint32_t reserved3[3];
    __RO uint32_t Arbitration_lost_capture;                                     /**< ��������: 0x2C ������� �������� ������� ������ ����������*/
    __RO uint32_t Error_code_capture;                                           /**< ��������: 0x30 ������� ���� ������ */
    __RW uint32_t Error_warning_limit;                                          /**< ��������: 0x34 ������� ������������� ���������� ��������������. �������� �� ������ ������ � ��������� ������ */
    __RW uint32_t RX_error_counter;                                             /**< ��������: 0x38 ������� ������ ��� ������. �������� �� ������ ������ � ��������� ������ */
    __RW uint32_t TX_error_counter;                                             /**< ��������: 0x3C ������� ������ ��� ��������. �������� �� ������ ������ � ��������� ������ */
    
    /*� ����������� �� ��������� ����������� � ������� ��������� ������ �������� ����� ��������� ����������. 
    � ��������� ������ ����� ��������� ������ �������� ��� � �����. 
    � ������� ��������� ��� ������ ����������� ���������� ��������� ��� ��������, ��� ������ - ������������ �������� ��������� ���������. 
    ���������� ��������� �������� ��� ������������ (SFF) � ������������ (EFF) �������� ���������.*/

    __RW uint32_t FI_SFF_FI_EFF_Acceptance_code_0;                              /**< ��������: 0x40*/                                          
    __RW uint32_t ID_1_Acceptance_code_1;                                       /**< ��������: 0x44*/                        
    __RW uint32_t ID_2_Acceptance_code_2;                                       /**< ��������: 0x48*/ 
    __RW uint32_t Data1_ID_3_Acceptance_code_3;                                 /**< ��������: 0x4�*/ 
    __RW uint32_t Data2_ID_4_Acceptance_mask_0;                                 /**< ��������: 0x50*/               
    __RW uint32_t Data3_Data1_Acceptance_mask_1;                                /**< ��������: 0x54*/               
    __RW uint32_t Data4_Data2_Acceptance_mask_2;                                /**< ��������: 0x58*/               
    __RW uint32_t Data5_Data3_Acceptance_mask_3;                                /**< ��������: 0x5�*/               
    __RW uint32_t Data6_Data4;                                                  /**< ��������: 0x60*/   
    __RW uint32_t Data7_Data5;                                                  /**< ��������: 0x64*/ 
    __RW uint32_t Data8_Data6;                                                  /**< ��������: 0x68*/ 
    __RW uint32_t FIFO1_Data7;                                                  /**< ��������: 0x6�*/ 
    __RW uint32_t FIFO2_Data8;                                                  /**< ��������: 0x70*/ 
    __RO uint32_t RX_message_counter;                                           /**< ��������: 0x74 ������� �������� ����������� ��������� */
    uint32_t reserved2;                                                         /**< ������*/ 
    __RW uint32_t Clock_divider;                                                /**< ��������: 0x7C ������� �������� ������� ������� */
    
}CAN_EXTANDED_T;

/**
 * @brief ������� � ���� ��� �������� Mode
 */
#define Reset_mode(x)      ((uint32_t)((x) << 0))                                 /**< ������ 1 � ���� ��� ��������� ����� ������� �������� ������ � ��������� ��������� � ��������� ������. 
                                                                                ������ 0 ��������� ���������� � ������� ���������. �� ��������� ������� ��������� ������, ��� ����� �������� 1*/
#define Listen_only_mode(x)      ((uint32_t)((x) << 1))                           /**< ������ 1 ��������� ���������� � ��������� ������������� ����*/
#define Self_test_mode(x)      ((uint32_t)((x) << 2))                             /**< ������ 1 ��������� ���������� � ����� ���������������*/
#define Acceptance_filter_mode(x)      ((uint32_t)((x) << 3))                     /**< �������� 1 - ����� ��������� ����������, 0 - ����� ������� ����������*/

/**
 * @brief ������� � ���� ��� �������� CONTROL
 */
#define Transmission_request(x)      ((uint32_t)((x) << 0))                       /**< ������ 1 ��������� �������� ��������� � ����� ��� �������� (TX buffer)*/
#define Abort_transmission(x)           ((uint32_t)((x) << 1))                    /**< ������ 1 ��������� ��������, ������� ��� �� ���� ��������*/
#define Release_receive_buffer(x)      ((uint32_t)((x) << 2))                     /**< ������ 1 ������� �������� ����� ��� ����� ������*/
#define Clear_data_overrun(x)      ((uint32_t)((x) << 3))                         /**< ������ 1 ������� ��� ������������ (Data overrun status) � �������� �������*/
#define Self_reception_request(x)      ((uint32_t)((x) << 4))                     /**< ������ 1 ��������� �������� � ������������ ����� ���������*/

/*
 * @brief ������� � ���� ��� �������� STATUS
 */
// ������� ������� � ����������� ������ ��������� �� ��������� �������� ������� � ������� ������.

/**
 * @brief ������� � ���� ��� �������� INTERRUPT
 */
#define Receive_interrupt_ext(x)           ((uint32_t)((x) << 0))                 /**< ��������������� �������� 1, ���� � �������� FIFO ������������ �������� ���������*/
#define Transmit_interrupt_ext(x)           ((uint32_t)((x) << 1))                /**< ��������������� �������� 1 � ������ ������������ ����������� ������*/
#define Error_warning_interrupt(x)           ((uint32_t)((x) << 2))               /**<��������������� �������� 1 ���� ���������� ������ ���� ��� ������ ������*/
#define Data_overrun_interrupt_ext(x)      ((uint32_t)((x) << 3))                 /**< ��������������� � 1 ����� ��� Data overrun status � �������� Status ��������� �� 0 � 1*/
#define Error_passive_interrupt(x)      ((uint32_t)((x) << 5))                    /**< ��������������� � 1 ����� ��� Data overrun status � �������� Status ��������� �� 0 � 1*/
#define Arbitration_lost_interrupt(x)      ((uint32_t)((x) << 6))                 /**< ��������������� � 1 ��� ������ ���������� ������������*/
#define Bus_error_interrupt(x)          ((uint32_t)((x) << 7))                    /**< ��������������� � 1 ���� �� ���� ���������� ������*/

/*
 * @brief ������� � ���� ��� �������� Interrupt_enable
 */
// ���������� ����� ��� �������� INTERRUPT

/**
 * @brief ������� � ���� ��� �������� Arbitration_lost_capture
 */
#define Bit_number(x)           ((uint32_t)(((x)&0x1F) << 0))                     /**<���, � ������� ���� �������� ����������*/

/**
 * @brief ������� � ���� ��� �������� Error_code_capture
 */
#define Segment(x)           ((uint32_t)(((x)&0x1F) << 0))                     
/**<�������������� ������ ������ ������:
0x03 - Start of frame
0x02 - ID.28 - ID.21
0x06 - ID.20 - ID.18
0x04 - Bit SRTR
0x05 - Bit IDE
0x07 - ID.17 - ID.13
0x0F - ID.12 - ID.5
0x0E - ID.4 - ID.0
0x0C - Bit RTR
0x0D - Reserved bit 1
0x09 - Reserved bit 0
0x0B - Data length code
0x0A - Data field
0x08 - CRC sequence
0x18 - CRC delimiter
0x19 - Acknowledge slot
0x1B - Acknowledge delimiter
0x1A - End of frame
0x12 - Intermission
0x11 - Active error flag
0x16 - Passive error flag
0x13 - Tolerate dominant bits
0x17 - Error delimiter
0x1C - Overload flag4
*/
#define Direction(x)           ((uint32_t)((x) << 5))                           ///< ���, � ������� ���� �������� ����������                  
#define Error_Code(x)           ((uint32_t)(((x)&0x3) << 6))                      
/**<��� ������:
0 - Bit error
1 - Form error
2 - Stuff error
3 - ������
*/            


/**
 * @brief ������� � ���� ��� �������� Clock_divider
 */
#define Clock_divisor(x)           ((uint32_t)(((x)&0x7) << 0))                   /**<����� ������� (�� ������������)*/
#define Clock_off(x)           ((uint32_t)((x) << 3))                           /**<���������� ������ clkout*/
#define CAN_mode(x)           ((uint32_t)((x) << 7))                            /**<1 - ����������� �����, 0 - ������� �����*/

/**
 * @brief ������� � ���� ��� �������� Bus_timing_0
 */
#define BRP(x)           ((uint32_t)(((x)&0x3F) << 0))                            /**<������������ Baud rate*/
#define SJW(x)           ((uint32_t)(((x)&0x3) << 6))                             /**<Synchronization jump width*/

/**
 * @brief ������� � ���� ��� �������� Bus_timing_1
 */
#define TSEG1(x)           ((uint32_t)(((x)&0xF) << 0))                           /**<Time segment 1*/
#define TSEG2(x)           ((uint32_t)(((x)&0x3) << 4))                           /**<Time segment 2*/
#define SAM(x)                ((uint32_t)((x) << 7))                              /**<1 - ���� ������������ 3 ����, 0 - ��������� �������������*/


#endif /* CAN_H */
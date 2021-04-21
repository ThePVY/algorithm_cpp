/*!\file
 * \brief ���� ���� �������� ���������, ������� � �������, ����������� ��� �������������� � ����������� SPI.
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

#ifndef SPI_H
#define SPI_H
#include "types.h"
#include "system.h"


/**
 * @brief ��������� ��� ������� � ��������� SPI.
 */
typedef struct
{
    __RW uint32_t CR0;                                                          /**< ��������: 0x0000 ������� ���������� 0 */
    __RW uint32_t CR1;                                                          /**< ��������: 0x0004 ������� ���������� 1 */
    __RW uint32_t DR;                                                           /**< ��������: 0x0008 ����� FIFO ����������������� */
    __RO uint32_t SR;                                                           /**< ��������: 0x000C ������� ��������� */
    __RW uint32_t CPSR;                                                         /**< ��������: 0x0010 ������� �������� �������� ������� */
    __RW uint32_t IMSC;                                                         /**< ��������: 0x0014 ������� ����� ���������� */
    __RO uint32_t RIS;                                                          /**< ��������: 0x0018 ������� ��������� ���������� ��� ����� ������������ */
    __RO uint32_t MIS;                                                          /**< ��������: 0x001C ������� ��������� ���������� � ������ ������������ */
    __WO uint32_t ICR;                                                          /**< ��������: 0x0020 ������� ������ ���������� */
    __RW uint32_t DMACR;                                                        /**< ��������: 0x0024 ������� ���������� ������ �������� � ������ */
}SPI_T;                                                                             

/**
 * @brief ������� � ���� ��� �������� CR0
 */
#define SPI_CR0_DSS(x)  ((uint32_t)((x) & 0x0F))                                /**< ������ ����� ������ 4-16 ���� */
#define SPI_CR0_SCR(x)  ((uint32_t)(((x) & 0xFF) << 8))                           /**< c������� ����������������� ������ */

typedef enum 
{
    SPI_BITS_4 = ((uint32_t)(3 << 0)),		                                /**< ������ ����� ������ 4 ���� */
    SPI_BITS_5 = ((uint32_t)(4 << 0)),		                                /**< ������ ����� ������ 5 ��� */
    SPI_BITS_6 = ((uint32_t)(5 << 0)),		                                /**< ������ ����� ������ 6 ��� */
    SPI_BITS_7 = ((uint32_t)(6 << 0)),		                                /**< ������ ����� ������ 7 ��� */
    SPI_BITS_8 = ((uint32_t)(7 << 0)),		                                /**< ������ ����� ������ 8 ��� */
    SPI_BITS_9 = ((uint32_t)(8 << 0)),		                                /**< ������ ����� ������ 9 ��� */
    SPI_BITS_10 = ((uint32_t)(9 << 0)),	                                        /**< ������ ����� ������ 10 ��� */
    SPI_BITS_11 = ((uint32_t)(10 << 0)),	                                /**< ������ ����� ������ 11 ��� */
    SPI_BITS_12 = ((uint32_t)(11 << 0)),	                                /**< ������ ����� ������ 12 ��� */
    SPI_BITS_13 = ((uint32_t)(12 << 0)),	                                /**< ������ ����� ������ 13 ��� */
    SPI_BITS_14 = ((uint32_t)(13 << 0)),	                                /**< ������ ����� ������ 14 ��� */
    SPI_BITS_15 = ((uint32_t)(14 << 0)),	                                /**< ������ ����� ������ 15 ��� */
    SPI_BITS_16 = ((uint32_t)(15 << 0)),	                                /**< ������ ����� ������ 16 ��� */
}SPI_BITS_T;

typedef enum 
{
    SPI_FRF_SPI = ((uint32_t)(0 << 4)), 			                /**< �������� SPI ����� Motorola */
    SPI_FRF_TI = ((uint32_t)(1 << 4)),     	                                /**< �������� SPI ����� Texas Instruments */
    SPI_FRF_MICROWIRE = ((uint32_t)(2 << 4)),                                   /**< �������� Microwire ����� National Semiconductor */
}SPI_FRAME_FORMAT_T;

typedef enum {
    SPI_CLOCK_SPH0_SPO0 = ((uint32_t)(0 << 6)),		                        
    SPI_CLOCK_SPH0_SPO1 = ((uint32_t)(1 << 6)),		                        
    SPI_CLOCK_SPH1_SPO0 = ((uint32_t)(2 << 6)),		                       
    SPI_CLOCK_SPH1_SPO1 = ((uint32_t)(3 << 6)),		                        
    SPI_CLOCK_MODE0 = SPI_CLOCK_SPH0_SPO0,                                      
    SPI_CLOCK_MODE1 = SPI_CLOCK_SPH0_SPO1,                                      
    SPI_CLOCK_MODE2 = SPI_CLOCK_SPH1_SPO0,                                      
    SPI_CLOCK_MODE3 = SPI_CLOCK_SPH1_SPO1,                                      
}SPI_CLOCK_MODE_T;

/**
 * @brief ������� � ���� ��� �������� CR1
 */
#define SPI_CR1_LBM_EN  ((uint32_t)(1 << 0))                                    /**< ��������� ������ loopback */
#define SPI_CR1_SSE_EN  ((uint32_t)(1 << 1))                                    /**< ���������� ������ ����������������� */
#define SPI_CR1_SOD_DIS ((uint32_t)(1 << 3))                                    /**< ������ �������� ����� � ������ �������� ���������� */
#define SPI_CR1_BITMASK ((uint32_t)(0x0F))

typedef enum 
{
    SPI_MODE_MS_MASTER = ((uint32_t)(0 << 2)),	                                /**< ����� ������ - ������� */
    SPI_MODE_MS_SLAVE = ((uint32_t)(1 << 2)),	                                /**< ����� ������ - ������� */
}SPI_MODE_T;

/**
 * @brief ������� ��� �������� DR
 */
#define SPI_DR_DATA(x)  ((uint32_t)((x) & 0xFFFF))                              /**< �����������/������������ ������ */

/**
 * @brief ��� ��� �������� SR
 */
typedef enum 
{
    SPI_SR_TFE = ((uint32_t)(1 << 0)),                                          /**< ����� ��� ������ ��������� ������ FIFO ����������� (1 - ����) */
    SPI_SR_TNF = ((uint32_t)(1 << 1)),                                          /**< ����� ��� ������ ��������� ������ FIFO ����������� (1 - �� ��������) */
    SPI_SR_RNE = ((uint32_t)(1 << 2)),                                          /**< ����� ��� ������ ��������� ������ FIFO ��������� (1 - �� ����) */
    SPI_SR_RFF = ((uint32_t)(1 << 3)),                                          /**< ����� ��� ������ ��������� ������ FIFO ��������� (1 - ��������) */
    SPI_SR_BSY = ((uint32_t)(1 << 4)),                                          /**< ����� ��� ������ ��������� ������ SPI (1 - � ��������� ����� �������� �/��� ��������� ������, ���� ����� FIFO ����������� �� ����) */
}SPI_STATUS_T;

/**
 * @brief ������� ��� �������� CPSR
 */
#define SPI_CPSR_CPSDVSR(x)     ((x) & 0xFF)                                      /**< ����������� ������� �������� ������� */

/**
 * @brief ��� ��� �������� IMSC
 */
typedef enum 
{
    SPI_IMSC_RORIM = ((uint32_t)(1 << 0)),                                      /**< ������������ ���������� �� ������������ ������ ��������� */
    SPI_IMSC_RTIM = ((uint32_t)(1 << 1)),                                       /**< ������������ ���������� �� �������� ��������� */
    SPI_IMSC_RXIM = ((uint32_t)(1 << 2)),                                       /**< ������������ ���������� �� ���������� �� 50% � ����� ������ FIFO ��������� */
    SPI_IMSC_TXIM = ((uint32_t)(1 << 3)),                                       /**< ������������ ���������� �� ���������� �� 50% � ����� ������ FIFO ����������� */
    SPI_IMSC_BITMASK = ((uint32_t)(0xF << 0)),
}SPI_INTMASK_T;

/**
 * @brief ��� ��� �������� RIS
 */
typedef enum 
{
    SPI_RIS_RORRIS = ((uint32_t)(1 << 0)),	                                /**< ��������� ���������� �� ������������ ������ ��������� ��� ����� */
    SPI_RIS_RTRIS = ((uint32_t)(1 << 1)),	                                /**< ��������� ���������� �� �������� ��������� ��� ����� */
    SPI_RIS_RXRIS = ((uint32_t)(1 << 2)),	                                /**< ��������� ���������� �� ���������� �� 50% � ����� ������ FIFO ��������� ��� ����� */
    SPI_RIS_TXRIS = ((uint32_t)(1 << 3)),	                                /**< ��������� ���������� �� ���������� �� 50% � ����� ������ FIFO ����������� ��� ����� */
}SPI_RAWINTSTATUS_T;

/**
 * @brief ��� ��� �������� MIS
 */
typedef enum 
{
    SPI_MIS_RORMIS = ((uint32_t)(1 << 0)),	                                /**< ������������� ��������� ���������� �� ������������ ������ ���������*/
    SPI_MIS_RTMIS = ((uint32_t)(1 << 1)),	                                /**< ������������� ��������� ���������� �� �������� ��������� */
    SPI_MIS_RXMIS = ((uint32_t)(1 << 2)),	                                /**< ������������� ��������� ���������� �� ���������� �� 50% � ����� ������ FIFO ��������� */
    SPI_MIS_TXMIS = ((uint32_t)(1 << 3)),	                                /**< ������������� ��������� ���������� �� ���������� �� 50% � ����� ������ FIFO ����������� */
}SPI_MASKINTSTATUS_T;

/**
 * @brief ��� ��� �������� ICR
 */
typedef enum 
{
    SPI_ICR_RORIC = ((uint32_t)(1 << 0)),                                       /**< c���� ���������� �� ������������ ������ ��������� */
    SPI_ICR_RTIC = ((uint32_t)(1 << 1)),                                        /**< c���� ���������� �� �������� ��������� */
    SPI_ICR_BITMASK = ((uint32_t)(3 << 0)),                                     /**< c���� ���� ���������� */
}SPI_INTCLEAR_T;

/**
 * @brief ��� ��� �������� DMACR
 */
typedef enum 
{
    SPI_DMACR_RXDMAE = ((uint32_t)(1 << 0)),                                    /**< ���������� ������������� DMA ��� ������ */
    SPI_DMACR_TXDMAE = ((uint32_t)(1 << 1)),	                                /**< ���������� ������������� DMA ��� �������� */
    SPI_DMACR_BITMASK = ((uint32_t)(3 << 0)),                                   /**< ���������� ������������� DMA ��� ������ � �������� */
}SPI_DMACR_T;

/**
 * @brief ��������� ��������� SPI
 */
typedef struct 
{
    SPI_BITS_T bits;					                        /**< ������ ����� ������ */
    SPI_CLOCK_MODE_T clockMode;	                                                /**< ������� ��������� ������� */
    SPI_FRAME_FORMAT_T frameFormat;	                                        /**< ������ ����� ������ */
}SPI_CONFIG_T;

/**
 * @brief ��������� ��� ������ � ������� SPI
 */
typedef struct 
{
    void      *tx_data;	                                                        /**< ��������� �� ������������ ������ */
    uint32_t  tx_cnt;	                                                        /**< ������� ���������� ������ */
    void      *rx_data;	                                                        /**< ��������� �� �������� ������ */
    uint32_t  rx_cnt;	                                                        /**< ������� �������� ������ */
    uint32_t  length;	                                                        /**< ����� ������������ ������ */
}SPI_DATA_SETUP_T;
  
/** ���������� ������ ����������������� */   
#define	SPI_Enable(gl_spi_t) (((SPI_T *)(gl_spi_t))->CR1 |= SPI_CR1_SSE_EN)
   
/** ���������� ������ ����������������� */
#define	SPI_Disable(gl_spi_t) (((SPI_T *)(gl_spi_t))->CR1 &= (~SPI_CR1_SSE_EN) & SPI_CR1_BITMASK)

/** ��������� ������ loopback */
#define	SPI_LoopBackEnable(gl_spi_t) (((SPI_T *)(gl_spi_t))->CR1 |= SPI_CR1_LBM_EN)

/** ��������� DMA ��� SPI */
#define	SPI_DMA_Enable(gl_spi_t) (((SPI_T *)(gl_spi_t))->DMACR |= SPI_DMACR_BITMASK)

/** ���������� DMA ��� SPI */
#define	SPI_DMA_Disable(gl_spi_t) (((SPI_T *)(gl_spi_t))->DMACR &= ~SPI_DMACR_BITMASK)

/** ��������� ���������� �� ���������� �� 50% � ����� ������ FIFO ����������� */
#define	SPI_TXInt_Enable(gl_spi_t) (((SPI_T *)(gl_spi_t))->IMSC |= SPI_IMSC_TXIM)

/** ���������� ���������� �� ���������� �� 50% � ����� ������ FIFO ����������� */
#define	SPI_TXInt_Disable(gl_spi_t) (((SPI_T *)(gl_spi_t))->IMSC &= (~SPI_IMSC_TXIM) & SPI_IMSC_BITMASK)

/** ��������� ���������� �� ���������� �� 50% � ����� ������ FIFO ��������� */
#define	SPI_RXInt_Enable(gl_spi_t) (((SPI_T *)(gl_spi_t))->IMSC |= SPI_IMSC_RXIM)

/** ���������� ���������� �� ���������� �� 50% � ����� ������ FIFO ��������� */
#define	SPI_RXInt_Disable(gl_spi_t) (((SPI_T *)(gl_spi_t))->IMSC &= (~SPI_IMSC_RXIM) & SPI_IMSC_BITMASK)

/** ����� ������ ���������� 
 *   ��� ���������� ��� ������, ��������� ��������� ��������:
 *    SPI_ICR_RORIC 
 *    SPI_ICR_RTIC 	
 */
#define	SPI_ClearIntPending(gl_spi_t,gl_spi_intclr) (((SPI_T *)(gl_spi_t))->ICR = (SPI_INTCLEAR_T)gl_spi_intclr)

/**
 * @brief ����� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @retval None.
 */
void SPI_DeInit(SPI_T *pSPI);

/**
 * @brief ������������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @retval None.
 */
void SPI_Init(SPI_T *pSPI);

/**
 * @brief ���������� ����� ������ ��� ������������� � �������� ���������/���������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @retval CtrlSPI: ����� ������.
 */
CTRL_T SPI_GetCtrlNum(SPI_T *pSPI);

/**
 * @brief ��������� ������� ��������������� �����
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param pbits: ������ ����� ������, ����� ���� SPI_BITS_4..SPI_BITS_16.
 * @param pframeFormat: ������ ��������������� �����.
 *         �������� pframeFormat ����� ��������� ��������:
 *          @arg SPI_FRF_SPI: �������� SPI ����� Motorola
 *          @arg SPI_FRF_TI: �������� SSI ����� Texas Instruments
 *          @arg SPI_FRF_MICROWIRE: �������� Microwire ����� National Semiconductor
 * @param pclockMode: ���������� � ���� ��������� �������. ������������ ������ � ������ ������ SPI ����� Motorola
 *         �������� pclockMode ����� ��������� ��������:
 *	    @arg SPI_CLOCK_MODE0: ������ ������������� (CPOL) - ������ �������, ������� ������ (CPHA) - ������ ����� ������� �������������
 *	    @arg SPI_CLOCK_MODE1: ������ ������������� (CPOL) - ������� �������, ������� ������ (CPHA) - ������ ����� ������� �������������
 *	    @arg SPI_CLOCK_MODE2: ������ ������������� (CPOL) - ������ �������, ������� ������ (CPHA) - �������� ����� ������� �������������
 *	    @arg SPI_CLOCK_MODE3: ������ ������������� (CPOL) - ������� �������, ������� ������ (CPHA) - �������� ����� ������� �������������
 * @retval None.         
 */
void SPI_SetFormat(SPI_T *pSPI, uint32_t pbits, uint32_t pframeFormat, uint32_t pclockMode);

/**
 * @brief ��������� ������ ������ (������� ��� �������).
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param pmode: ����� ������, ��������� ��������� ��������:
 *         �������� pmode ����� ��������� ��������:
 *          @arg SPI_MODE_MASTER: ����� ������ - �������
 *          @arg SPI_MODE_SLAVE: ����� ������ - �������
 * @retval None.
 */
void SPI_Set_Mode(SPI_T *pSPI, uint32_t pmode);

/**
 * @brief ��������� �������� ����������������� ������: FSSPCLKOUT=FSSPCLK/(CPSDVR*(1+SCR))
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param clk_rate: SCR - �������� ������� (1..256).
 * @param prescale: CPSDVR - ������ ����������� (2..254).
 * @retval None.
 */
void SPI_SetClockRate(SPI_T *pSPI, uint32_t clk_rate, uint32_t prescale);

/**
 * @brief ��������� ������� ��������� ������� ��� ���������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param bitRate: ������� ������.
 * @retval None.
 */
void SPI_SetBitRate(SPI_T *pSPI, uint32_t bitRate);

/**
 * @brief ��������� ����� ��� � ����� ����� ������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @retval ���������� ��� � ����� ����� ������ ����� ����
 */
inline uint8_t SPI_GetDataSize(SPI_T *pSPI);

/**
 * @brief �������� ����� ������ �� ���������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param tx_data: ������ ��� ��������
 * @retval None.
 */
void SPI_SendFrame(SPI_T *pSPI, uint16_t tx_data);

/**
 * @brief ����� ����� ������ �� ���������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @retval ����� ������.
 */
uint16_t SPI_ReceiveFrame(SPI_T *pSPI);

/**
 * @brief ������ ������ ����� � ����� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
 * @retval None.
 */
void SPI_Write1BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);
/**
 * @brief ������ ������ ����� �� ������ SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
 * @retval None.
 */
void SPI_Read1BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);

/**
 * @brief ������ ���� ���� � ����� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
 * @retval None.
 */
void SPI_Write2BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);
/**
 * @brief ������ ���� ���� �� ������ SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
 * @retval None.
 */
void SPI_Read2BFifo(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);

/**
 * @brief ������ ������� ����������� ������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param buffer: ��������� �� ������������ ������.
 * @param buffer_len: ������ ������������ ������.
 * @retval tx_cnt - ���������� ���������� ������.
 */
uint32_t SPI_WriteFrames_Blocking(SPI_T *pSPI, uint8_t *buffer, uint32_t buffer_len);

/**
 * @brief ������ ������� ����������� ������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param buffer: ��������� �� ����������� ������.
 * @param buffer_len: ������ ����������� ������.
 * @retval rx_cnt - ���������� �������� ������.
 */
uint32_t SPI_ReadFrames_Blocking(SPI_T *pSPI, uint8_t *buffer, uint32_t buffer_len);

/**
 * @brief ������/������ 8 ��� ������ ��� ������ ����������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
 * @retval C����� ��������.
 */
Status SPI_Int_RWFrames8Bits(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);

/**
 * @brief ������/������ 16 ��� ������ ��� ������ ����������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param xf_setup: ��������� �� ��������� ��� ������ � ������� SPI.
 * @retval C����� ��������.
 */
Status SPI_Int_RWFrames16Bits(SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);

/**
 * @brief ������� ������ ��������� � ����� ������ ����������.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @retval None.
 */
void SPI_Int_FlushData(SPI_T *pSPI);

/**
 * @brief ��������� �������� ������� ����������� SPI.
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param pStat: ��� �������.
 *         �������� pStat ����� ��������� ��������:
 *          @arg SPI_SR_TFE: ����� FIFO ����������� ����
 *          @arg SPI_SR_TNF: ����� FIFO ����������� �� ��������
 *          @arg SPI_SR_RNE: ����� FIFO ��������� �� ����
 *          @arg SPI_SR_RFF: ����� FIFO ��������� ��������
 *          @arg SPI_SR_BSY: ���� ���������� �������� ��� ������
 * @retval SET or RESET, c����� ����������� SPI.
 */
FlagStatus SPI_GetStatus(SPI_T *pSPI, SPI_STATUS_T pStat);

/**
 * @brief ��������� ������� �������������� ����������. 
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param pMaskInt: ��� �������������� ����������. 
 *         �������� pMaskInt ����� ��������� ��������:
 *          @arg SPI_MIS_RORMIS: ��������� �������������� ���������� SSPRORINTR
 *	    @arg SPI_MIS_RTMIS: ��������� �������������� ���������� SSPRTINTR
 *          @arg SPI_MIS_RXMIS: ��������� �������������� ���������� SSPRXINTR
 *          @arg SPI_MIS_TXMIS: ��������� �������������� ���������� SSPTXINTR
 * @retval SET or RESET, c����� ����������.
 */
IntStatus SPI_GetIntStatus(SPI_T *pSPI, SPI_MASKINTSTATUS_T pMaskInt);

/**
 * @brief ��������� ������� ����������. 
 * @param pSPI: ��������� �� ��������� � ���������� SPI.
 * @param pRawInt: ��� ����������. 
 *         �������� pMaskInt ����� ��������� ��������:
 *	    @arg SPI_MIS_RORRIS: ��������� �� ������������ ���������� SSPRORINTR
 *          @arg SPI_MIS_RTRIS: ��������� �� ������������ ���������� SSPRTINTR
 *          @arg SPI_MIS_RXRIS: ��������� �� ������������ ���������� SSPRXINTR
 *	    @arg SPI_MIS_TXRIS: ��������� �� ������������ ���������� SSPTXINTR
 * @retval SET or RESET, c����� ����������.
 */
IntStatus SPI_GetRawIntStatus(SPI_T *pSPI, SPI_RAWINTSTATUS_T pRawInt);


#endif /* SPI_H */

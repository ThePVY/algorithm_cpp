	NAME startup

	//Stack
	SECTION CSTACK:DATA:NOROOT(3)

	//Interrupt Table
	SECTION .intvec:CODE:NOROOT(2)
        
	EXTERN __iar_program_start
	EXTERN SystemInit
        
	PUBLIC __vector_table

	DATA

__vector_table
		DCD sfe(CSTACK)
		DCD Reset_Handler       
	REPT 14
		DCD Exception
	ENDR
	//Ext Interrupts
		DCD Timer_1_IRQ
		DCD Watchdog_IRQ 
		DCD UART_1_IRQ
		DCD UART_2_IRQ
		DCD Timer_2_IRQ
		DCD Timer_3_IRQ
		DCD Timer_4_IRQ
		DCD SPI_2_IRQ
		DCD GPIO_A_IRQ
		DCD GPIO_B_IRQ
                
		DCD GPIO_C_IRQ
		DCD GPIO_D_IRQ
		DCD GPIO_E_IRQ
		DCD GPIO_F_IRQ
		DCD GPIO_G_IRQ
		DCD GPIO_H_IRQ
		DCD Spacewire1_IRQ
		DCD Spacewire2_IRQ     

	
        DCD CAN1_IRQ            //  DCD TMTX_IRQ  
		DCD CAN2_IRQ            //  DCD TCRX_IRQ
                
		DCD MKPD1_IRQ    
		DCD MKPD2_IRQ     
		DCD MKPD3_IRQ      
		DCD MKPD4_IRQ     
	REPT 2
		DCD Unknown_INTR
	ENDR
		DCD DMA_DONE_Timer_4_IRQ
		DCD DMA_DONE_SPI_2_IRQ
		DCD DMA_DONE_UART_1_IRQ
		DCD DMA_DONE_UART_2_IRQ
                
		DCD DMA_DONE_Timer_2_IRQ
		DCD DMA_DONE_Timer_3_IRQ	
	THUMB
        
        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
        
Reset_Handler
        
        LDR R0,=SystemInit
        BLX R0
        LDR R0,=__iar_program_start
        BX R0

        PUBWEAK Exception                               //0
        PUBWEAK Watchdog_IRQ                            //2
        PUBWEAK UART_1_IRQ                              //3
        PUBWEAK UART_2_IRQ
        PUBWEAK Timer_2_IRQ
        PUBWEAK Timer_3_IRQ
        PUBWEAK Timer_4_IRQ
        PUBWEAK SPI_2_IRQ
        PUBWEAK GPIO_A_IRQ
        
        PUBWEAK GPIO_B_IRQ
        PUBWEAK GPIO_C_IRQ
        PUBWEAK GPIO_E_IRQ 
        PUBWEAK GPIO_D_IRQ
        PUBWEAK GPIO_F_IRQ
        PUBWEAK GPIO_G_IRQ
        PUBWEAK GPIO_H_IRQ
        PUBWEAK Spacewire2_IRQ          
     
        
  
        PUBWEAK CAN1_IRQ                //  PUBWEAK TMTX_IRQ
        
        PUBWEAK CAN2_IRQ                
     
        PUBWEAK DMA_DONE_Timer_4_IRQ
        PUBWEAK DMA_DONE_SPI_2_IRQ
        PUBWEAK DMA_DONE_UART_1_IRQ
        PUBWEAK DMA_DONE_UART_2_IRQ
        PUBWEAK DMA_DONE_Timer_2_IRQ
        
        PUBWEAK DMA_DONE_Timer_3_IRQ        
        SECTION .text:CODE:REORDER:NOROOT(1)
Exception
		B Exception

Unknown_INTR
		B Unknown_INTR
        PUBWEAK Timer_1_IRQ                               //1
Timer_1_IRQ  
        BL Timer_1_IRQ

Watchdog_IRQ  
UART_1_IRQ  
UART_2_IRQ   

Timer_2_IRQ  
Timer_3_IRQ  
Timer_4_IRQ  
SPI_2_IRQ  
GPIO_A_IRQ  
GPIO_B_IRQ  
GPIO_C_IRQ  
GPIO_D_IRQ  
GPIO_E_IRQ  
GPIO_F_IRQ  
GPIO_G_IRQ  
GPIO_H_IRQ  
        PUBWEAK Spacewire1_IRQ
Spacewire1_IRQ  
    BL Spacewire1_IRQ
Spacewire2_IRQ  
    BL Spacewire2_IRQ
CAN1_IRQ  //TMTX_IRQ 
CAN2_IRQ  //TCRX_IRQ  
 
            PUBWEAK MKPD1_IRQ         
MKPD1_IRQ  
                BL MKPD1_IRQ

            PUBWEAK MKPD2_IRQ         
MKPD2_IRQ  
                BL MKPD2_IRQ
            PUBWEAK MKPD3_IRQ         
MKPD3_IRQ  
                BL MKPD3_IRQ
            PUBWEAK MKPD4_IRQ         
MKPD4_IRQ  
                BL MKPD4_IRQ   
DMA_DONE_Timer_4_IRQ  
DMA_DONE_SPI_2_IRQ  
DMA_DONE_UART_1_IRQ  
DMA_DONE_UART_2_IRQ  
DMA_DONE_Timer_2_IRQ  
DMA_DONE_Timer_3_IRQ  
	END

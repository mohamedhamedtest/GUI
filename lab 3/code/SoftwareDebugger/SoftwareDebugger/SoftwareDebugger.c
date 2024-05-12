/*** Software Debugger using usart ***/ 

// Including libraries
#include <avr/io.h>
#include <stdlib.h>
#include "softwaredebugger.h"
#include "uart.h"

// Define values
#define F_CPU 8000000UL
#define _CMD_START_CNT   1
#define _CMD_END_CNT     1
#define _CMD_DIR_CNT     1
#define _CMD_ADDRESS_CNT 2
#define _CMD_DATA_CNT    3
#define FULL_CMD_CNT (_CMD_START_CNT + _CMD_END_CNT + _CMD_DIR_CNT + _CMD_ADDRESS_CNT + _CMD_DATA_CNT)
#define ADDRESS_OFFSET (_CMD_START_CNT + _CMD_DIR_CNT)
#define DATA_OFFSET (_CMD_START_CNT + _CMD_DIR_CNT + _CMD_ADDRESS_CNT)
#define BAUD_RATE 9600

/* Full command will be 
 *  @ W/R XX YYY;
 * Spaces will be ignored by the driver, and the 
 * address XX will be send in decimal
 */
static uint8_t cmd_buffer[FULL_CMD_CNT];

// Function to initialize debugger
void SDEBUG_Init(void)
{
    uint8_t i;
    
    // Initialize UART driver
    UART_cfg my_uart_cfg;
    
    // Set USART mode
    my_uart_cfg.UBRRL_cfg = (BAUD_RATE_VALUE)&0x00FF;
    my_uart_cfg.UBRRH_cfg = (((BAUD_RATE_VALUE)&0xFF00)>>8);
    
    my_uart_cfg.UCSRA_cfg = 0;
    my_uart_cfg.UCSRB_cfg = (1<<RXEN)  | (1<<TXEN) | (1<<TXCIE) | (1<<RXCIE);
    my_uart_cfg.UCSRC_cfg = (1<<URSEL) | (3<<UCSZ0);
    
    UART_Init(&my_uart_cfg);
    
    // Clear cmd_buffer
    for(i = 0; i < FULL_CMD_CNT; i += 1)
    {
        cmd_buffer[i] = 0;
    }
}

// Debugger main
void SDEBUG_MainFunction(void)
{
    volatile uint8_t *address;
    uint8_t value;
    
    // Send terminal prompt
    UART_SendPayload((uint8_t *)">", 1);
    while (0 == UART_IsTxComplete());
    
    // Receive the full buffer command
    UART_ReceivePayload(cmd_buffer, FULL_CMD_CNT);
    
    // Pull until reception is complete
    while(0 == UART_IsRxComplete());

    // Compute address
    {
        char address_buffer[_CMD_ADDRESS_CNT];
        
        address_buffer[0] = cmd_buffer[ADDRESS_OFFSET];
        address_buffer[1] = cmd_buffer[ADDRESS_OFFSET+1];
        
        address = ((volatile uint8_t *)atoi(address_buffer));
    }
    
    // Compute value
    {
        char value_buffer[_CMD_DATA_CNT];
        
        value_buffer[0] = cmd_buffer[DATA_OFFSET];
        value_buffer[1] = cmd_buffer[DATA_OFFSET + 1];
        value_buffer[2] = cmd_buffer[DATA_OFFSET + 2];
        
        value = (uint8_t)atoi(value_buffer);
    }

    // Parse command buffer
    switch(cmd_buffer[1])
    {
        case 'w':
        case 'W':
        {
            /* Write received value to selected address. */
            *(address) = value;
            break;
        }
        case 'r':
        case 'R':
        {
            value = *(address);
            
            /* Send read value from received address. */
            UART_SendPayload(&value, 1);
            
            break;
            
        }
        default:  { /* Do nothing. */}
    }
    
    UART_SendPayload((uint8_t *)"\r", 1);
}

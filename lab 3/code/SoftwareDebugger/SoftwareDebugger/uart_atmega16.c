// Including libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

// Static values
static volatile uint8_t  *tx_buffer;
static volatile uint16_t tx_len;
static volatile uint16_t tx_cnt;
static volatile uint8_t *rx_buffer;
static volatile uint16_t rx_len;
static volatile uint16_t rx_cnt;

// UART interrupt
ISR(USART_RXC_vect)
{
    uint8_t rx_data;
    
    cli();
    
    /* Read rx_data. */
    rx_data = UDR;
    
    /* Ignore spaces */
    if((rx_cnt < rx_len) && (rx_data != ' '))
    {
        rx_buffer[rx_cnt] = rx_data;
        rx_cnt++;
    }
    else
    {
        /* Do nothing. */
    }
    
    sei();
}

// UART interrupt
ISR(USART_TXC_vect)
{
    cli();
    
    tx_cnt++;
    
    if(tx_cnt < tx_len)
    {
        /* Send next byte. */
        UDR = tx_buffer[tx_cnt];
    }
    sei();
}

// UART initialize
void UART_Init(UART_cfg *my_cfg)
{
    /* Set baud rate */
    UBRRH = my_cfg->UBRRH_cfg;
    UBRRL = my_cfg->UBRRL_cfg;
    
    UCSRA = my_cfg->UCSRA_cfg;
    UCSRB = my_cfg->UCSRB_cfg;
    UCSRC = my_cfg->UCSRC_cfg;
    
}

// UART transmitter
void UART_SendPayload(uint8_t *tx_data, uint16_t len)
{
    tx_buffer = tx_data;
    tx_len    = len;
    tx_cnt    = 0;
    
    /* Wait for UDR is empty. */
    while(0 == (UCSRA & (1 << UDRE)));
    
    /* Send the first byte to trigger the TxC interrupt. */
    UDR = tx_buffer[0];
    
}

// UART receiver
void UART_ReceivePayload(uint8_t *rx_data, uint16_t len)
{
    rx_buffer = rx_data;
    rx_len    = len;
    rx_cnt    = 0;
}

// Check if transmitter is complete
uint8_t UART_IsTxComplete(void)
{
    return ( (tx_cnt >= tx_len) ? 1 : 0 );
}

// Check if receiver is complete
uint8_t UART_IsRxComplete(void)
{
    return ( (rx_cnt >= rx_len) ? 1 : 0 );
}

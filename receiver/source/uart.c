#include <avr/io.h>
//#include <avr/interrupt.h>
#include "uart.h"

/**
 * \brief Initialize the uart with correct baud rate settings
 *
 * This function will initialize the UART baud rate registers with the correct
 * values using the AVR libc setbaud utility. In addition set the UART to 8-bit,
 * 1 stop and no parity.
 */
void uart_init(void)
{
#if defined UBRR0H
	/* These values are calculated by the setbaud tool based on the values
	defined in uart.h. The only thing that the application
	need to do is to load these values into the correct registers.*/
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
#else
#error "Device is not supported by the driver"
#endif

	/* Check if the setbaud tool require that the 2x speed bit has to be set in
	order to reach the specified baudrate. */
#if USE_2X
	UCSR0A |= (1 << U2X0);
#endif

	// Enable RX and TX and set up port
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	// Set the TX pin as output
	//UART_PORT_DDR |= (1 << UART_TX_PIN);
	// Set the RX pin as input
	//UART_PORT_DDR &= ~(1 << UART_RX_PIN);

	// 8-bit, 1 stop bit, no parity, asynchronous UART
	UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) | (0 << UPM01) | (0 << UPM00) | (0 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00) | (0 << UCPOL0);
}

/**
 * \brief Function for sending a char over the UART
 *
 * \param data the data to send over UART
 */
void uart_putchar(char data)
{
	// Make sure that the UART buffer is empty
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

/**
 * \brief Function for sending a string from Flash ROM over the UART with LF/CR
  */
void uart_putstring(char *s)
{
	while ( *s )
	{
		uart_putchar( *s++ );
	}
	/**uart_putchar(' ');
	uart_putchar('\n');
	uart_putchar('\r'); **/
}

/**
 * \brief Function for getting a char from the UART
 *
 * \note This function is blocking and will expect to receive something
 * on the UART.
 *
 * \retval uint8_t the data received from the UART
 * \retval 0       if timeout
 */
char uart_getchar(void)
{
	uint8_t timeout = TIMEOUT;
	// Wait for RX to complete
	while ((!(UCSR0A & (1 << RXC0))) && timeout) {
		timeout--;
	}
	if (timeout) {
		return UDR0;
	} else {
		// No data, timeout
		return 0;
	}
}


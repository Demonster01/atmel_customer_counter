#ifndef CONF_UART_H_INCLUDED
#define CONF_UART_H_INCLUDED

/**
 * \brief Set the desired baud rate value
 *
 * set the desired baudrate, the define is used by the util/setbaud.h to calculate the
 * register values.
 */
//#define BAUD 9600
#define BAUD 115200

//! set the baud rate tolerance to 2%
#define BAUD_TOL 2

//! define what PORT the UART0 is connected to
//#define UART_PORT_DDR DDRD

//! define what pins are used for UART0 TX and RX
//#define UART_RX_PIN PIND0
//#define UART_TX_PIN PIND1

#endif /* CONF_UART_H_INCLUDED */

#ifndef CONF_CLOCK_H_INCLUDED
#define CONF_CLOCK_H_INCLUDED

/**
 * \brief Define the current CPU clock speed based on device settings
 *
 * This define is used by e.g. the libc delay functions to calculate the correct
 * amount of cycles to busy wait for a given delay.
 *
 * \note This value needs to reflect the device fuse settings, that is it needs to
 * be the correct value for either the current internal RC setting or external
 * clock or crystal settings. Functions that rely on this define will not work
 * correctly with an incorrect value.
 */
#define F_CPU 14745600UL

#endif /* CONF_CLOCK_H_INCLUDED */

#include <util/setbaud.h>

#define TIMEOUT 250

void uart_init(void);
void uart_putchar(char data);
void uart_putstring(char *s);
char uart_getchar(void);

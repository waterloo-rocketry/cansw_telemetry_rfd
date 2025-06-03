#ifndef ROCKETLIB_UART_H
#define ROCKETLIB_UART_H

#include <stdbool.h>
#include <stdint.h>

#ifndef ROCKETLIB_COMMON_H
#define ROCKETLIB_COMMON_H

#define ROCKETLIB_VERSION_MAJOR 2025
#define ROCKETLIB_VERSION_MINOR 1

typedef enum {
    W_SUCCESS = 0,
    W_FAILURE,
    W_INVALID_PARAM,
    W_IO_ERROR,
    W_IO_TIMEOUT,
    W_MATH_ERROR,
    W_OVERFLOW
} w_status_t;

void w_assert_fail(const char *file, int line, const char *statement);

#ifdef W_DEBUG

#define w_assert(statement)                                                                        \
    if (!(statement)) {                                                                            \
        w_assert_fail(__FILE__, __LINE__, #statement);                                             \
    }

#else

#define w_assert(statement)

#endif

#endif

/*
 * Initialize UART module. Set up rx and tx buffers, set up module,
 * and enable the requisite interrupts
 */
w_status_t uart_init(uint32_t baud_rate, uint32_t fosc, bool enable_flow_control);

/*
 * A lot like transmitting a single byte, except there are multiple bytes. tx does
 * not need to be null terminated, that's why we have the len parameter
 *
 * tx: pointer to an array of bytes to send
 * len: the number of bytes that should be sent from that array
 */
void uart_transmit_buffer(uint8_t *tx, uint8_t len);

/*
 * returns true if there's a byte waiting to be read from the UART module
 */
bool uart_byte_available(void);

/*
 * pops a byte from the receive buffer and returns it. Don't call this
 * function unless uart_byte_available is returning true. Don't call this
 * function from an interrupt context.
 */
uint8_t uart_read_byte(void);

/*
 * handler for all UART1 module interrputs. That is, PIR3:U1IF, U1EIF, U1TXIF, and U1RXIF
 * this function clears the bits in PIR3 that it handles.
 */
void uart_interrupt_handler(void);

#endif /* ROCKETLIB_UART_H */

    
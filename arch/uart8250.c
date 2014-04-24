#include <mips/uart8250.h>

/* === CONFIG === */

#define         BASE                    0xb8000200
#define         MAX_BAUD                1152000
#define			REG_OFFSET				4

#define         OFS_SEND_BUFFER         0x1f8

/* memory-mapped read/write of the port */
#define         UART8250_READ(y)    (*((volatile uint8*)(BASE + y)))
#define         UART8250_WRITE(y, z)  ((*((volatile uint8*)(BASE + y))) = z)

void Uart8250Put(uint8 byte)
{
    UART8250_WRITE(OFS_SEND_BUFFER, byte);
}

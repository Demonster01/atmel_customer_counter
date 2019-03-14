#ifndef _AVR035_H_
#define _AVR035_H_

// From AVR035: Efficient C Coding for AVR
// http://www.atmel.com/dyn/resources/prod_documents/doc1497.pdf

// Bit manipulation with I/O registers
#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))     // Set bit (set to 1)
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))  // Clear bit (set to 0)
#define FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))    // Invert bit
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))    // Test of single bit

/* Example usage
if (CHECKBIT(PORTD,PIND1))    // Test if PIN 1 is set
{
      CLEARBIT(PORTD,PIND1);  // Clear PIN 1 on PORTD
}
if (!CHECKBIT(PORTD,PIND1))    // Test if PIN 1 is cleared
{
      SETBIT(PORTD,PIND1);     // Set PIN 1 on PORTD
}
*/

// Use of bit-mask for status bits
#define SETBITMASK(x,y) (x |= (y))      // Set bit y in byte x
#define CLEARBITMASK(x,y) (x &= (~y))   // Clear bit y in byte x
#define FLIPBITMASK(x,y) (x ^= (y))     // Invert bit y in byte x
#define CHECKBITMASK(x,y) (x & (y))     // Check bit y in byte x

/* Example usage
// Define status bit mask constants (flags)
#define RETRANS   0x01  // bit 0
#define WRITEFLAG 0x02  // bit 1
#define EMPTY     0x04  // bit 2
#define FULL      0x08  // bit 3

// main loop
__C_task void main(void)
{
      char status;
      CLEARBITMASK(status,RETRANS);
      if (!(CHECKBITMASK(status,RETRANS)))
      {
             SETBITMASK(status,WRITEFLAG);
      }
}
*/

#endif

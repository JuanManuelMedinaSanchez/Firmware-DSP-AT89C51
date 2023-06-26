#include <ioAT89C51.h>

//Test Microcontroller input / output Pins and Memory Allocation @Juan Manuel Medina - Prismatiklab.com
void delay(unsigned int ms)
{
    unsigned int i;
    while (ms--)
    {
        for (i = 0; i < 123; i++);  // Delay loop (adjust this value based on your clock frequency)
    }
}

void main()
{
    /* Declare Pin Directions */
    P0DIR = 0xFF;  // Set all pins of P0 as outputs
    P1DIR = 0x00;  // Set all pins of P1 as inputs

    /* Define Output States */
    P0 = 0x00;  // Set all pins of P0 initially to low

    while (1)
    {
        if (P1 & 0x02)  // Check if P1.1 is high (toggle switch is pressed)
        {
            P0 ^= 0xFF;  // Toggle all pins of P0 together (invert the values)
            delay(100);  // Delay for 100 milliseconds
        }
        else
        {
            P0 = 0x00;  // Set all pins of P0 to low
        }
    }
}

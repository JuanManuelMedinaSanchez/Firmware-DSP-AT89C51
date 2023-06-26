#include <ioAT89C51.h>

//Test Microcontroller input / output Pins and Memory Allocation @Juan Manuel Medina - Prismatiklab.com
void delay(unsigned int ms)
{
    unsigned int i;
    while (ms--)
    {
        for (i = 0; i < 123; i++); 
    }
}

void main()
{
    /* Pins*/
    P0DIR = 0xFF;  // P0, outputs
    P1DIR = 0x00;  // P1, inputs

   
    P0 = 0x00;  
    while (1)
    {
        if (P1 & 0x02)  
        {
            P0 ^= 0xFF;  
            delay(100);  
        }
        else
        {
            P0 = 0x00; 
        }
    }
}

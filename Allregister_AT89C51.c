/*****************************************************************************************************************************************************************************************
                            **NOTES**

Register &= ~bitmask;    // Clear specific bits
Register |= bitmask;     // Set specific bits
Register ^= bitmask;     // Toggle specific bits

**Stack  manipulation.
- SP = Stack pointer
- DP = Data pointer(L-H, 01)

**Program Status Words->Flags.
P->Parity bit.
OV->Overflow. 
CY->Carry.
F0->User defined General  purpose flag.
AC,CY->Auxiliary Carry Bit

**ACCUMULATOR & REGISTER -> ACC, R.

**TCON->TCON_bit.TR0 ->Timer 0 Run Control:
	 Start Timer 0 by setting the TR0 bit in the TCON register to 1. This enables Timer 0 and allows it to start counting.
	 Inside the infinite while loop, we check if the TF0 bit in the TCON register is set to 1. This indicates that Timer 0 has overflowed, 
	 meaning it has reached its maximum value and reset back to zero. If the overflow flag is set, we clear it by assigning 0 to the TF0 bit.

**TMOD->Timer/Counter Mode Control (TMOD) and the Timer/Counter registers (TL0, TL1, TH0, TH1) in the AT89C51 microcontroller.
The TMOD register is used to configure the operating modes of Timer/Counter 0 and Timer/Counter 1. 
The structure TMOD_bit defines the individual bitfields within the TMOD register, such as M00, M10, C_T0, GATE0, M01, M11, C_T1, and GATE1. 
These bitfields control various aspects of the timer/counters, including their modes, clock sources, and gating options.
The TL0, TL1, TH0, and TH1 registers are the low and high byte registers for Timer/Counter 0 and Timer/Counter 1. 
These registers store the current values of the timers/counters.
*****************************************************************************************************************************************************************************************/

#include <ioAT89C51.h>
#include <stdio.h>

#include <ioAT89C51.h>
#include <stdio.h>

unsigned char counter = 0;

// Function to initialize I/O ports
void IO()
{
    P0 = 0xFF;  // Set all pins on Port 0 to high (outputs)
    P1 = 0x00;  // Set all pins on Port 1 to low (inputs)
    P2 = 0xFF;  // Set all pins on Port 2 to high
}

// Function to set up the stack pointer
void StackPointer()
{
    unsigned char *SP;
    SP = (unsigned char *)0x82;
    *SP = 0x55;

    unsigned char *DP;
    DP = (unsigned char *)0x82;  // Assign the desired memory address to DP
    *DP = 0x55;  // Store the value 0x55 at the memory location pointed to by DP

    // Access the stored value
    unsigned char value = *DP;

    DP0L = 0x00;
}

void main()
{
    TMOD_bit.M00 = 0;  // Set Timer/Counter 0 to 16-bit mode
    TMOD_bit.M10 = 1;
    TMOD_bit.GATE0 = 0;  // Disable GATE0
    TMOD_bit.C_T0 = 0;  // Set Timer/Counter 0 as Timer

    TCON_bit.TR0 = 1;  // Enable Timer/Counter 0

    IO();  // Initialize I/O ports

    StackPointer();  // Set up the stack pointer once

    ACC = 0x55;  // Assign a value to ACC
    B = ACC;     // Copy the value of ACC to B

    // Use the B register and its bits in your program logic
    B_bit.B3 = 1;

    if (B_bit.B3 == 1) {
        ACC = 0;  // Set ACC to 0 if B3 is set
    } else {
        ACC = 1;  // Set ACC to 1 if B3 is cleared
    }

    TCON_bit.TR0 = 1;  // Start Timer 0

    while (1)
    {
        // Wait for Timer/Counter 0 overflow
        while (TCON_bit.TF0 == 0) {
            // Do nothing
        }

        TCON_bit.TF0 = 0;  // Clear Timer/Counter 0 overflow flag
        counter++;  // Increment counter

        if (TCON_bit.TF0 == 1) {
            TCON_bit.TF0 = 0;  // Clear the Timer 0 overflow flag

            // Perform desired actions when Timer 0 overflows
            // This could include updating variables, generating an interrupt, etc.
        }

        // Your main program logic here
    }
}

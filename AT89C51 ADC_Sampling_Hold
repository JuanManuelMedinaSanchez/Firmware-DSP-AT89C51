//ADC configutation for sampling & Hold of Analog pulses, maked in IAR compiler for AT89C51 microcontroller

#include <ioAT89C51.h>
#include <math.h>

// Define memory location
unsigned char memory_location = 0x55; // Data memory location

void ADC_Init()
{
    // Your ADC initialization code here
}

unsigned int ADC_Read(unsigned char channel)
{
    // Your ADC read code here
    return 0; // Replace with the appropriate return value
}

void main()
{
    // Configure I/O ports
    P0 = 0x00;  // Set Port 0 as output
    P1 = 0xFD;  // Set Port 1 as input (P1.0 = output, P1.1 = input)
    P3 &= 0xFE; // Set Port 3 (P3.0) as output, keeping other pins as input

    // Initialize ADC
    ADC_Init();

    // Sampling variables
    const float sampling_period = 1.0 / 2000.0; // Sampling period of 2 ms (500 Hz sampling frequency)
    float time = 0.0;                            // Current time for sampling

    // Digital output variables
    unsigned char pulse_active = 0; // Flag to indicate pulse is active

    while (1)
    {
        // Read analog input value from channel 0 (ADC0)
        unsigned int analog_value = ADC_Read(0);

        // Convert analog value to voltage (assuming a 5V reference)
        float voltage = (float)analog_value * 5.0 / 1023.0;

        // Determine current input value based on voltage level
        unsigned char curr_input = (P1 & 0x02) ? 1 : 0;

        // Check for rising edge (transition from low to high) on P1.1
        if (curr_input == 1 && pulse_active == 0)
        {
            // Store the captured value in memory
            memory_location = analog_value;

            // Set the pulse active flag
            pulse_active = 1;
        }

        // Check for falling edge (transition from high to low) on P1.1
        if (curr_input == 0 && pulse_active == 1)
        {
            // Clear the pulse active flag
            pulse_active = 0;
        }

        // Update digital output on Port 3 (P3.0) based on pulse_active flag
        P3 = (P3 & 0xFE) | pulse_active;

        // Delay to achieve desired sampling rate
        // Adjust the delay value as per your requirement
        for (unsigned int i = 0; i < 1000; i++)
            ;

        // Update time for next sampling
        time += sampling_period;
    }
}

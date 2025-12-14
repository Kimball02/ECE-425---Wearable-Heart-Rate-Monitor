// Pulse Sensor driver for PE3 (AIN0)
// Sets up ADC0 SS3 to read the analog signal from the sensor
// Returns a 12-bit value (0–4095)

#include "TM4C123GH6PM.h"
#include "pulse_sensor.h"

void Pulse_Sensor_Init(void)
{
    volatile uint32_t delay;

    // enable clocks for Port E and ADC0
    SYSCTL->RCGCGPIO |= (1 << 4);
    SYSCTL->RCGCADC  |= (1 << 0);

    // small delay after enabling clocks
    delay = SYSCTL->RCGCGPIO;
    (void)delay;

    // set PE3 as analog input (AIN0)
    GPIOE->DIR   &= ~(1 << 3);   // input
    GPIOE->AFSEL |=  (1 << 3);   // alternate function
    GPIOE->DEN   &= ~(1 << 3);   // disable digital
    GPIOE->AMSEL |=  (1 << 3);   // enable analog mode

    // configure ADC0 SS3
    ADC0->ACTSS  &= ~(1 << 3);   // disable SS3 while setting up
    ADC0->EMUX   &= ~(0xF << 12); // processor trigger
    ADC0->SSMUX3  = 0x0;         // read from AIN0
    ADC0->SSCTL3  = 0x06;        // IE0 + END0
    ADC0->ACTSS  |=  (1 << 3);   // enable SS3
    ADC0->ISC     =  (1 << 3);   // clear any old flags
}

uint32_t Pulse_Sensor_Read(void)
{
    uint32_t result;

    // start conversion on SS3
    ADC0->PSSI = (1 << 3);

    // wait until conversion is done
    while ((ADC0->RIS & (1 << 3)) == 0)
    {
        // waiting
    }

    // read 12-bit result
    result = ADC0->SSFIFO3 & 0xFFF;

    // clear the completion flag
    ADC0->ISC = (1 << 3);

    return result;
}
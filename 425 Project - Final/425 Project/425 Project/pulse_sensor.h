/**
 * @file pulse_sensor.h
 *
 * @brief Header file for the Pulse Sensor driver.
 *
 * Provides initialization and sampling functions for a Pulse Sensor
 * connected to PE3 (AIN0) of the TM4C123G LaunchPad.
 *
 * The driver configures ADC0 Sample Sequencer 3 (SS3) to read
 * the analog pulse waveform and return a 12-bit digital sample (0..4095).
 */

#ifndef PULSE_SENSOR_H
#define PULSE_SENSOR_H

#include <stdint.h>

/**
 * @brief Initializes ADC0 to sample the Pulse Sensor on PE3 (AIN0).
 *
 * - Enables clock for Port E and ADC0
 * - Configures PE3 as an analog input
 * - Configures ADC0 Sample Sequencer 3 (SS3) for processor trigger
 *
 * After initialization, Pulse_Sensor_Read() can be used to obtain samples.
 */
void Pulse_Sensor_Init(void);

/**
 * @brief Reads a 12-bit sample from the Pulse Sensor.
 *
 * Triggers ADC0 SS3, waits for the conversion to complete,
 * and returns the 12-bit ADC value (0..4095).
 *
 * @return uint32_t : ADC sample from the pulse sensor.
 */
uint32_t Pulse_Sensor_Read(void);

#endif /* PULSE_SENSOR_H */

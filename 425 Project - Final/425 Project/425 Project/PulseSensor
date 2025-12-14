// Heart Rate Monitor using Pulse Sensor and EduBase LCD
// Reads the Pulse Sensor on PE3 (AIN0) using ADC0,
// finds heart beats, calculates BPM, and shows a smoothed
// value + status message on the EduBase 16x2 LCD.
//
// Row 0: BPM value
// Row 1: Status ("High HR", "Normal", "Low HR", "No Pulse", "Measuring...")

#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "pulse_sensor.h"
#include "LCD.h"

// ------------------- Settings -------------------
#define SAMPLE_PERIOD_MS        10      // time between ADC samples (ms)

// lower threshold so it's easier to detect beats
#define THRESHOLD               1600    // threshold on filtered signal
#define HYSTERESIS              100     // helps avoid double-counting

// valid range for time between beats
#define MIN_BEAT_INTERVAL_MS    250     // minimum time between beats (ms)
#define MAX_BEAT_INTERVAL_MS    2000    // maximum time between beats (ms)

// timeout for no pulse detected
#define NO_BEAT_TIMEOUT_MS      2500    // if no beat in this time -> BPM = 0

// how we average and display BPM
#define NUM_INTERVALS           2       // number of intervals to average
#define DISPLAY_UPDATE_MS       100     // LCD refresh rate (ms)

// status thresholds
#define HIGH_HR_THRESHOLD       110     // >110 BPM -> "High HR"
#define LOW_HR_THRESHOLD        60      // <60 BPM  -> "Low HR"
// ------------------------------------------------

int main(void)
{
    uint32_t sample;              // raw ADC sample (0..4095)
    uint32_t filtered       = 0;  // filtered signal
    uint32_t prev_filtered  = 0;
    uint32_t timeMs         = 0;  // global time in ms
    uint32_t lastBeatTimeMs = 0;  // time of last detected beat

    uint32_t instantBpm     = 0;  // BPM from latest interval
    uint32_t displayBpm     = 0;  // smoothed BPM for LCD
    uint8_t  inBeat         = 0;  // 1 when we are inside a beat

    uint32_t intervals[NUM_INTERVALS] = {0};  // stores last few beat intervals
    uint8_t  intervalIndex = 0;

    uint32_t displayTimer = 0;   // timer for LCD updates

    uint8_t bpmValid = 0;        // set to 1 after we see a real beat

    // init drivers
    SysTick_Delay_Init();
    Pulse_Sensor_Init();
    EduBase_LCD_Init();

    EduBase_LCD_Clear_Display();

    while (1)
    {
        // fixed sample timing
        SysTick_Delay1ms(SAMPLE_PERIOD_MS);
        timeMs       += SAMPLE_PERIOD_MS;
        displayTimer += SAMPLE_PERIOD_MS;

        // read pulse sensor (0..4095)
        sample = Pulse_Sensor_Read();

        // low-pass filter (about 0.75 old + 0.25 new)
        filtered = filtered - (filtered >> 2) + (sample >> 2);

        // beat detection
        if (inBeat == 0)
        {
            // check for rising edge crossing threshold
            if ((filtered > THRESHOLD) && (prev_filtered <= THRESHOLD))
            {
                uint32_t interval = timeMs - lastBeatTimeMs;

                // ignore first beat and keep only reasonable intervals
                if ((lastBeatTimeMs != 0) &&
                    (interval > MIN_BEAT_INTERVAL_MS) &&
                    (interval < MAX_BEAT_INTERVAL_MS))
                {
                    // store interval for averaging
                    intervals[intervalIndex] = interval;
                    intervalIndex = (intervalIndex + 1) % NUM_INTERVALS;

                    // average non-zero intervals
                    uint32_t sum   = 0;
                    uint32_t count = 0;
                    for (int i = 0; i < NUM_INTERVALS; i++)
                    {
                        if (intervals[i] > 0)
                        {
                            sum += intervals[i];
                            count++;
                        }
                    }

                    if (count > 0)
                    {
                        uint32_t avgInterval = sum / count;
                        instantBpm = 60000 / avgInterval;   // BPM from avg interval

                        if (displayBpm == 0)
                        {
                            // first time, just jump to measured BPM
                            displayBpm = instantBpm;
                        }
                        else
                        {
                            // smooth the changes in BPM
                            displayBpm = (3 * displayBpm + instantBpm) / 4;
                        }

                        // we have seen at least one valid beat
                        bpmValid = 1;
                    }
                }

                lastBeatTimeMs = timeMs;
                inBeat = 1;  // now we are inside a beat
            }
        }
        else
        {
            // wait until signal drops below threshold - hysteresis to re-arm
            if (filtered < (THRESHOLD - HYSTERESIS))
            {
                inBeat = 0;
            }
        }

        prev_filtered = filtered;

        // if no beat for a while, set BPM = 0
        if (lastBeatTimeMs != 0 &&
            (timeMs - lastBeatTimeMs) > NO_BEAT_TIMEOUT_MS)
        {
            displayBpm = 0;
            // bpmValid stays 1: we had beats before, now lost them
        }

        // update LCD every DISPLAY_UPDATE_MS
        if (displayTimer >= DISPLAY_UPDATE_MS)
        {
            displayTimer = 0;

            // row 0: BPM
            EduBase_LCD_Set_Cursor(0, 0);
            EduBase_LCD_Display_String("BPM:            ");
            EduBase_LCD_Set_Cursor(5, 0);
            EduBase_LCD_Display_Integer(displayBpm);

            // row 1: status message
            EduBase_LCD_Set_Cursor(0, 1);

            if (bpmValid == 0)
            {
                // still trying to lock onto a beat
                EduBase_LCD_Display_String("Measuring...   ");
            }
            else if (displayBpm == 0)
            {
                // lost pulse for a while
                EduBase_LCD_Display_String("No Pulse       ");
            }
            else if (displayBpm > HIGH_HR_THRESHOLD)
            {
                EduBase_LCD_Display_String("High HR        ");
            }
            else if (displayBpm < LOW_HR_THRESHOLD)
            {
                EduBase_LCD_Display_String("Low HR         ");
            }
            else
            {
                EduBase_LCD_Display_String("Normal         ");
            }
        }
    }
}

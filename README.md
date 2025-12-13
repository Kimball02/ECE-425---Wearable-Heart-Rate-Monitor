# ECE 425 Wearable Heart Rate Monitor

# Introduction
This project utilizes a pulse sensor connected to the TM4C123GH6PM microcontroller to measure the user's heart rate. After measuring, the system displays the beats per minute on an LCD screen as well as the status of their heart rate depending on whether the user has a: high heart rate, normal heart rate, low heart rate, or no pulse at all.

This is the final project for ECE 425 at California State University, Northridge (CSUN).

Completed by:
- David Kimball
- Kenneth Gayol

Professor
- Aaron Nanas

# Project Goals
- To design a user friendly wearable device that measures and displays the beats per minute of its wearer.
- To gain experience in using embedded systems fundamentals learned in class to design practical systems and devices.

# Block Diagram

<img width="721" height="722" alt="Screenshot 2025-12-13 153004" src="https://github.com/user-attachments/assets/195de08d-dd9d-4bea-bbcb-97d4b7e50261" />

# Results
The heart rate monitor performed well during testing. The system was able to detect heartbeats in real time and generate a stable BPM reading after we applied the low-pass filter and averaged the most recent intervals. This significantly reduced noise and eliminated the large BPM jumps we saw before filtering. The LCD updated smoothly every 100 ms and consistently displayed both the current BPM and the corresponding heart rate condition. Overall, the results showed that the pulse sensor and beat detection logic worked reliably, providing an accurate and functional heart-rate display under normal operating conditions.
Several challenges were encountered during the process, the main one being the sensitivity of the pulse sensor to finger placement. Small changes in pressure or slight finger movement often introduced noise into the signal. Ambient lighting and motion also added interference, sometimes leading to false beat detections. By adjusting the filtering, tuning the threshold levels, and securing the wiring, we were able to stabilize the sensor readings and allow the monitor to provide more reliable and accurate results.

# Video Demonstration
- Heart Rate Monitor Demo: [Link](https://youtube.com/shorts/SDyr98laGNo?feature=share)

# Photos
### No Pulse:
<img width="698" height="563" alt="Screenshot 2025-12-13 152338" src="https://github.com/user-attachments/assets/e0597717-8ca3-4eb1-ae31-e9a937ce81b3" />

### High Heart Rate:
<img width="686" height="561" alt="Screenshot 2025-12-13 152411" src="https://github.com/user-attachments/assets/91c960be-aa1f-4e9e-b434-df584248b53a" />

### Normal Heart Rate:
<img width="598" height="559" alt="image" src="https://github.com/user-attachments/assets/3235c9cb-0643-4370-b103-fe703153e676" />

# Background and Methodology
In this project, we will apply embedded systems concepts such as analog-to-digital conversion (ADC), signal processing, and LCD interfacing to create a wearable heart rate monitor. We will use a pulse sensor which will detect the heartbeat signal and send it to the microcontroller through the ADC pin. It will then count the number of heartbeats over a set period and calculate the BPM. The measured heart rate will be displayed on an LCD screen for the user to read. We will be using the TMC4C123GH6PM microcontroller, a pulse sensor, an LCD display, connecting wires, and a power supply. The microcontroller will use peripherals such as GPIO for LCD, ADC for the pulse sensor input, and Timers to measure the time between heartbeats. The software we will be using is Keil µVision and will be written in the C Programming language.

# Components Used
| Microcontroller | Sensor |Screen| Wiring |
| --- | --- | --- | --- |
| TM4C123GH6PM | Pulse Sensor | EduBase 16x2 LCD  | Breadboard  and Jumper Wires |

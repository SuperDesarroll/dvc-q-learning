# Q-Learning Voltage Control Project

This repository contains the code and hardware documentation for the Q-Learning based voltage control system using ESP32.

## Hardware Setup

### Circuit Components

*   **ESP32**: Microcontroller running the Q-learning algorithm.
*   **Servo Motor**: Adjusts the position of the controlled potentiometer.
*   **Manual Potentiometer**: Allows manual adjustment of the input voltage.
*   **Servo-Controlled Potentiometer**: Adjusts the output voltage.
*   **Voltage Source**: Provides the necessary power.
*   **Voltage Sensor**: Measures the output voltage.
*   **Display**: Shows the current voltage.

### Connection Description

*   **ESP32**:
    *   **Servo Control Pin (PWM Pin 4)**: Connected to the control pin of the servo motor.
    *   **Controlled Potentiometer Reading Pin (ADC Pin 15)**: Connected to the central pin of the servo-controlled potentiometer to read the voltage.
    *   **Manual Potentiometer Reading Pin (ADC Pin 15)**: Connected to the central pin of the manual potentiometer to read the voltage.
*   **Servo Motor**:
    *   **Control Pin (PWM Pin 4)**: Connected to the PWM pin of the ESP32.
    *   **VCC**: Connected to the voltage source.
    *   **GND**: Connected to the ground (GND) of the ESP32.
*   **Manual Potentiometer**:
    *   **Terminal 1**: Connected to the voltage source.
    *   **Terminal 2 (Central)**: Connected to the input of the servo-controlled potentiometer.
    *   **Terminal 3**: Connected to the ground (GND).
*   **Servo-Controlled Potentiometer**:
    *   **Terminal 1**: Connected to the output of the manual potentiometer.
    *   **Terminal 2 (Central)**: Connected to the ADC reading pin of the ESP32.
    *   **Terminal 3**: Connected to the ground (GND).
*   **Voltage Source**:
    *   **Positive Output**: Connected to the terminals of the manual potentiometer and the VCC of the servo motor.
    *   **Negative Output (GND)**: Connected to the ground of the ESP32 and the GND of the servo motor.
*   **Voltage Sensor**:
    *   **Input**: Connected to the output of the servo-controlled potentiometer.
    *   **Output**: Connected to the reading pin of the ESP32 (if necessary).
*   **Display**:
    *   **Data Input**: Connected to the communication pins of the ESP32 (if it's a digital display).
    *   **Power Supply**: Connected to the same voltage source or a separate power supply if needed.

# Autonomous Edge Cybersecurity: LLM-Guided Q-Learning for Resilient Device Control

## Overview

This project presents a novel approach to Edge Cybersecurity by deploying autonomous Q-learning agents capable of operating in isolation to mitigate cyber-physical attacks. The system features a hierarchical architecture where a **Large Language Model (LLM)** at a superior level acts as a supervisor, defining reward functions and guiding the training process. The edge device, implemented on an **ESP32 microcontroller**, utilizes this pre-trained or periodically updated policy to autonomously detect and correct anomalies—such as voltage instability—even when disconnected from the central network.

This repository contains the source code and documentation for the proof-of-concept implementation that stabilizes voltage against external perturbations simulating cyber-physical attacks.

## Table of Contents

- [Features](#features)
- [Hardware Setup](#hardware-setup)
- [Software Architecture](#software-architecture)
- [Installation](#installation)
- [Usage & Attack Simulation](#usage--attack-simulation)
- [Experimental Results](#experimental-results)
- [References](#references)
- [License](#license)

## Features

- **Autonomous Edge Defense**: The Q-learning agent operates locally on the ESP32, detecting and mitigating anomalies without needing continuous external commands.
- **LLM-Guided Reward Structure**: Uses high-level security policies defined by an LLM (Cloud/Fog layer) to shape the reward function for the local agent.
- **Resilience in Isolation**: Capable of maintaining system stability (e.g., voltage regulation) even when network connections to the supervisor are severed.
- **Real-Time Mitigation**: Rapid response to sudden, malicious changes in input voltage (simulated cyber-physical attacks).
- **Resource-Constrained Optimization**: Lightweight C++ implementation suitable for low-power edge hardware.

## Hardware Setup

The prototype consists of:
- **ESP32 Microcontroller**: Runs the Q-learning algorithm.
- **Servo Motor**: Physically adjusts the controlled potentiometer to regulate voltage.
- **Manual Potentiometer**: Used to introduce external disturbances (simulate attacks).
- **Servo-Controlled Potentiometer**: The actuator for voltage correction.
- **Voltage Sensor & Display**: For real-time feedback and monitoring.

*(See `schema01.png` in the `docs` folder for the detailed circuit diagram)*

## Software Architecture

The system follows a hierarchical intelligence model:
1.  **Superior Layer (LLM with n8n & MCP)**: Analyzes threat intelligence and system logs to define the "Cyber-Defense Policy" (reward function). In this demo, it sets the goal: minimize deviation from 1.8V.
2.  **Edge Layer (ESP32)**: Executes the Q-learning agent. It interacts with the physical environment, updates its Q-table based on the LLM-defined rewards, and takes actions (Increase, Decrease, or Hold angle) to stabilize the system.

<img width="990" height="710" alt="image" src="https://github.com/user-attachments/assets/114a6641-9a75-4dd2-a8dc-a28d41f82df2" />


## Installation

1.  **Clone the repository**:
    ```bash
    git clone https://github.com/SuperDesarroll/dvc-q-learning.git
    cd dvc-q-learning
    ```

2.  **Hardware Assembly**: Connect components according to the circuit diagram.

3.  **Firmware Upload**:
    - Open the project in **PlatformIO** or **Arduino IDE**.
    - Install necessary libraries (e.g., `ESP32Servo`).
    - Upload the code to your ESP32 board.

## Usage & Attack Simulation

1.  **Power On**: Start the ESP32. The agent will begin exploring and learning to maintain the target voltage (e.g., 1.8V).
2.  **Simulate Attack**: Use the *Manual Potentiometer* to drastically change the input voltage. This simulates a physical hack or sensor spoofing attack.
3.  **Observe Defense**: Watch how the servo motor (controlled by the agent) reacts to counteract the disturbance and restore the voltage to the safe baseline.
4.  **Isolation Test**: Disconnect the ESP32 from any network/serial command stream. The device should continue to defend itself using the learned Q-table.

## Experimental Results

The system successfully demonstrates:
- **Self-Healing**: Returning voltage to 1.8V after significant deviations.
- **Learned Policy**: The Q-table converges to a robust policy where specific states (voltage errors) map to optimal corrective actions.
- **Low Latency**: Decision-making occurs in milliseconds, suitable for real-time protection.

## References

This work is part of the research:
> **Autonomous Edge Cybersecurity: LLM-Guided Q-Learning for Resilient Device Control**  
> *Dewins Murillo García, Angel Arroyo Puente, Anita Herrera Vaca, Álvaro Herrero Cosio*  
> Universidad de Burgos (UBU), Spain.

Supported by the **AI4SECIoT project** (INCIBE/NextGenerationEU).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```

Feel free to modify the content to better fit your project's specifics, including the repository name, your GitHub username, and any additional details you want to include.

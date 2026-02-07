# Software Implementation

This directory contains the C++ code for the Q-Learning algorithm and the main ESP32 control logic.

## cpp/qlearning.h

### Code Description
The provided code defines a `QLearning` class used for implementing a Q-learning algorithm. This class is crucial for reinforcement learning tasks, where an agent learns to make decisions by interacting with an environment.

*   **Constructor:** Initializes the Q-learning parameters including the number of actions, learning rate, discount factor, exploration rate (epsilon), reward value, and the angle increment (`angleDelta`). The Q-table is also initialized, which stores the Q-values for different state-action pairs.
*   **chooseAction(int state):** Chooses an action based on the current state. It uses an epsilon-greedy strategy where a random action is chosen with probability epsilon and the action with the highest Q-value is chosen otherwise. This balances exploration and exploitation during learning.
*   **getReward(double currentValue):** Computes the reward based on the current value of the system. The reward is calculated as the negative absolute difference between the target reward value and the current value, encouraging the agent to minimize this difference.
*   **updateQTable(int state, int action, int newState, double reward):** Updates the Q-table using the Q-learning formula. It adjusts the Q-value for a given state-action pair based on the received reward and the maximum Q-value for the new state. This update is essential for refining the agent’s policy over time.
*   **showQTable():** Prints out the current Q-table to visualize the learned Q-values. This helps in understanding how the agent values different state-action pairs and is useful for debugging and analysis.

The `QLearning` class demonstrates fundamental reinforcement learning concepts and serves as the backbone of the Q-learning algorithm implementation in the project.

## main.cpp

### Explanation
The code initializes the servo and sets up the analog pin for voltage reading. It then enters a loop where it:
- Chooses an action based on the current state (potentiometer position).
- Adjusts the servo angle based on the action (decrease, maintain, or increase).
- Reads the current voltage and calculates a reward based on how close it is to the target voltage.
- Updates the Q-table using the chosen action and observed reward.
- Prints out the current status including voltage, potentiometer position, servo angle, chosen action, and received reward.

### Code Description

The provided C++ code implements a Q-learning algorithm to control a servo motor and adjust the position of a potentiometer based on feedback from a voltage sensor. The code is designed to run on an ESP32 microcontroller and utilizes the ESP32Servo library for controlling the servo motor.

Key components and their functionality are as follows:

*   **Library Initialization**: The code initializes the **Library** object **lib** and the **Servo** object **myservo**. The analog pin for reading voltage is set to 15.
*   **Algorithm Parameters**: Parameters for the Q-learning algorithm are defined, including the number of actions (**NUM_ACTIONS**), learning rate (**LEARNING_RATE**), discount factor (**DISCOUNT_FACTOR**), reward threshold (**VOLTAGE_REWARD**), exploration probability (**EPSILON**), and servo angle change (**angleDelta**).
*   **Q-learning Setup**: An instance of the **QLearning** class is created, and initial values for the servo angle and potentiometer position are set.
*   **Utility Function**: The **getVoltage()** function reads the analog value from the specified pin, converts it to voltage, and returns it.
*   **Setup Function**: The **setup()** function initializes serial communication, attaches the servo to pin 4, configures the analog pin, and positions the servo. It also includes a delay to ensure the servo reaches its initial position.
*   **Main Loop**: The **loop()** function performs the following tasks:
    *   Chooses an action based on the current potentiometer position.
    *   Updates the potentiometer position and servo angle based on the chosen action.
    *   Reads the current voltage and computes the reward.
    *   Updates the Q-table with the new state and reward.
    *   Prints the current status, including voltage, potentiometer position, servo angle, action taken, and reward.
    *   Every 100 iterations, if the voltage matches the reward threshold (rounded to one decimal place), the Q-table is displayed, and the count loop is reset.

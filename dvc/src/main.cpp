#include "lib.h"
#include "../../cpp/qlearning.h"
#include <Arduino.h>
#include <ESP32Servo.h>
#include <iostream>

Library lib;
Servo myservo;            // Crear objeto Servo para controlar un servo
const int analogPin = 15; // Pin analógico para leer el voltaje

// Parámetros del algoritmo
const int NUM_ACTIONS = 3; // Reducir, mantener, aumentar
const double LEARNING_RATE = 0.2;
const double DISCOUNT_FACTOR = 0.8;
const double VOLTAGE_REWARD = 1.80; // Umbral de voltaje para la recompensa
double EPSILON = 0.0;               // Probabilidad de elegir una acción aleatoria (exploración)
double angleDelta = 5;             // Cambio en el ángulo del servo

QLearning qlearning(NUM_ACTIONS, LEARNING_RATE, DISCOUNT_FACTOR, EPSILON, VOLTAGE_REWARD, angleDelta);
int angle = 180 - angleDelta;                                // Ángulo inicial del servo
int potentiometerPosition = qlearning.angleDeltaActions - 2; // Posición inicial del potenciómetro al inicio

// Funciones de utilidad
double getVoltage()
{
    int analogValue = analogRead(analogPin);
    double voltage = analogValue * (3.3 / 4095.0);
    return voltage;
}

void setup()
{
    lib.Serial_begin();
    myservo.attach(4);         // Adjuntar el servo al pin 4
    pinMode(analogPin, INPUT); // Configurar el pin analógico como entrada
    myservo.write(angle);
    lib.println("Servo ready, ubicando en posición inicial");
    delay(5000);
    lib.println("Starting Q-Learning");
}
int countLoop = 0;
void loop()
{
    int action = qlearning.chooseAction(potentiometerPosition);
    int newPotentiometerPosition = potentiometerPosition;
    // Actualizar la posición del potenciómetro basada en la acción
    if (action == 0 && potentiometerPosition > angleDelta)
    { // Reducir
        newPotentiometerPosition--;
        angle -= angleDelta; // Reducir el ángulo del servo
    }
    else if (action == 2 && potentiometerPosition < qlearning.angleDeltaActions - 1)
    { // Aumentar
        newPotentiometerPosition++;
        angle += angleDelta; // Aumentar el ángulo del servo
    }
    myservo.write(angle); // Mover el servo al nuevo ángulo
    delay(70);           // Esperar a que el servo se mueva
    double voltage = getVoltage();
    double reward = qlearning.getReward(voltage);
    // Actualización de la tabla Q
    qlearning.updateQTable(potentiometerPosition, action, newPotentiometerPosition, reward);
    potentiometerPosition = newPotentiometerPosition;
    // Imprimir el estado actual
    lib.println("Voltage:: " + std::to_string(voltage) + ", Potentiometer Position: " + std::to_string(potentiometerPosition) + ", Angle: " + std::to_string(angle) + ", Action: " + std::to_string(action) + ", Reward: " + std::to_string(reward));
    countLoop++;
    if (countLoop > 100 && lib.roundToOneDecimal(voltage) == lib.roundToOneDecimal(VOLTAGE_REWARD))
    {
        qlearning.showQTable();
        countLoop = 0;
    }
}
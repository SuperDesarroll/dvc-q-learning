#include <stdlib.h> // Asegúrate de incluir cmath en lugar de stdlib.h o math.h
#include "lib.h"
#include "qlearning.h"
#include "servo.h"

Library lib;
Servo myservo;            // Crear objeto Servo para controlar un servo
const int analogPin = 15; // Pin analógico para leer el voltaje
const int INPUT = 0;      // Modo de entrada
// Parámetros del algoritmo
const int NUM_ACTIONS = 3; // Reducir, mantener, aumentar
const double LEARNING_RATE = 0.2;
const double DISCOUNT_FACTOR = 0.8;
const double VOLTAGE_REWARD = 2.0; // Umbral de voltaje para la recompensa
double EPSILON = 0.0;              // Probabilidad de elegir una acción aleatoria (exploración)
double angleDelta = 10;            // Cambio en el ángulo del servo

QLearning qlearning(NUM_ACTIONS, LEARNING_RATE, DISCOUNT_FACTOR, EPSILON, VOLTAGE_REWARD, angleDelta);
int angle = 180 - angleDelta;                                // Ángulo inicial del servo
int potentiometerPosition = qlearning.angleDeltaActions - 2; // Posición inicial del potenciómetro al inicio

// Funciones de utilidad
double getVoltage()
{
    int states = qlearning.angleDeltaActions;
    int state = potentiometerPosition;
    int analogValue = lib.random(state * (4095 / states), (state + 1) * (4095 / states));
    double voltage = analogValue * (3.3 / 4095.0);
    return voltage;
}

void setup()
{
    lib.Serial_begin();
    myservo.attach(4);             // Adjuntar el servo al pin 4
    lib.pinMode(analogPin, INPUT); // Configurar el pin analógico como entrada
    myservo.write(angle);
    lib.println("Servo ready, ubicando en posición inicial");
    lib.delay(5000);
    lib.println("Starting Q-Learning");
}

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
    if (action == 2 && potentiometerPosition < qlearning.angleDeltaActions - 1)
    { // Aumentar
        newPotentiometerPosition++;
        angle += angleDelta; // Aumentar el ángulo del servo
    }
    myservo.write(angle); // Mover el servo al nuevo ángulo
    lib.delay(100);       // Esperar a que el servo se mueva
    double voltage = getVoltage();
    double reward = qlearning.getReward(voltage);
    // Actualización de la tabla Q
    qlearning.updateQTable(potentiometerPosition, action, newPotentiometerPosition, reward);
    potentiometerPosition = newPotentiometerPosition;
    // Imprimir el estado actual
    lib.println("Voltage: " + std::to_string(voltage) + ", Potentiometer Position: " + std::to_string(potentiometerPosition) + ", Angle: " + std::to_string(angle) + ", Action: " + std::to_string(action) + ", Reward: " + std::to_string(reward));
}

int main(int argc, char const *argv[])
{
    setup();
    while (true)
    {
        loop();
    }
    return 0;
}
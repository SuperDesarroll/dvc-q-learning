#include <stdlib.h> // Asegúrate de incluir cmath en lugar de stdlib.h o math.h
#include "lib.h"
#include "qlearning.h"

// Definición de la clase Servo
class Servo {
public:
    void attach(int pin) {
        // Simula la conexión del servo a un pin
        this->pin = pin;
    }

    void write(int angle) {
        // Simula el movimiento del servo a un ángulo específico
        this->angle = angle;
    }

    int read() {
        // Devuelve el ángulo actual del servo
        return angle;
    }

private:
    int pin;
    int angle;
};
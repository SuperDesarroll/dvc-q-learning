#ifndef LIBRARY_H // Si LIBRARY_H no está definido
#define LIBRARY_H // Define LIBRARY_H

#include <iostream>
#include <string>
#include <ctime> // Añadir para time(0) y rand()
#include <cmath>

class Library
{
public:
    void Serial_begin()
    {
        std::cout << "Serial begin at " << "0" << " bauds" << std::endl;
    }

    void randomseed()
    {
        unsigned long seed = time(0);
        std::cout << "Seed " << seed << std::endl;
        srand(seed);
    }

    int random(int min, int max)
    {
        return min + (rand() % (max - min + 1));
    }

    void print(std::string str)
    {
        std::cout << str;
    }

    void println(std::string str)
    {
        std::cout << str << std::endl;
    }

    void delay(int ms)
    {
        std::cout << "Delay " << ms << " ms" << std::endl;
    }

    double analogRead(int pin,int state)
    {
        return 0.0;
    }

    void analogWrite(int pin, int value)
    {
    }

    void pinMode(int pin, int mode)
    {
    }
};

#endif // Fin de la protección contra múltiples inclusiones
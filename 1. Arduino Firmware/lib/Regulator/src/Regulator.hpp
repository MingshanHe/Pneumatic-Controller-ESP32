#ifndef REGULATOR_HPP
#define REGULATOR_HPP

#include <Arduino.h>
#include <Configuration.hpp>
class Regulator
{
private:
    /* data */
public:
    Regulator(/* args */);
    ~Regulator();

    void Initialization();
    void Start(int Pressure);
};
#endif
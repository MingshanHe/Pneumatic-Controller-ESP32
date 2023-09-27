#ifndef VALVE_HPP
#define VALVE_HPP


#include <Arduino.h>
#include <Configuration.hpp>
class Valve
{
private:
    /* data */
public:
    Valve(/* args */);
    ~Valve();
    void Initialization();
    void Reset();
    void Release();
    void Shrink();
};
#endif
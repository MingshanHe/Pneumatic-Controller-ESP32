#include <Regulator.hpp>

// #include <Regulator.hpp>
Regulator::Regulator(/* args */)
{
}

Regulator::~Regulator()
{
}

void Regulator::Initialization()
{
    Serial.begin(115200);
    pinMode(RegulatorPin, OUTPUT);
    Serial.println("[System Information]: Initialized Regualator!");
    delay(1000);
}

void Regulator::Start(int Pressure)
{
    analogWrite(RegulatorPin, Pressure);
    delay(1000);
}
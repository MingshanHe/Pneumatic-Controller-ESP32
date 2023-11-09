#include <Valve.hpp>

Valve::Valve(/* args */)
{
}

Valve::~Valve()
{
}
void Valve::Initialization()
{
    Serial.begin(115200);
    // Serial.println("[System Information]: Initializing Valve!");
    // delay(1000); 
    pinMode(PositiveValvePin, OUTPUT);
    pinMode(NegativeValvePin, OUTPUT);

    pinMode(Valve1Pin, OUTPUT);
    pinMode(Valve2Pin, OUTPUT);
    pinMode(Valve3Pin, OUTPUT);
    Serial.println("[System Information]: Initialized Valve!");
    delay(1000);
}

void Valve::Reset()
{
    digitalWrite(PositiveValvePin, LOW);
    digitalWrite(NegativeValvePin, LOW);
    digitalWrite(Valve1Pin, LOW);
    digitalWrite(Valve2Pin, LOW);
    digitalWrite(Valve3Pin, LOW);
}

void Valve::Release()
{
    Reset();

    digitalWrite(PositiveValvePin, HIGH);
    digitalWrite(NegativeValvePin, LOW);

    digitalWrite(Valve1Pin, HIGH);
    delay(first_second_delay);
    digitalWrite(Valve2Pin, HIGH);
    delay(second_third_delay);
    digitalWrite(Valve3Pin, HIGH);

}

void Valve::Shrink()
{
    Reset();
    digitalWrite(PositiveValvePin, LOW);
    digitalWrite(NegativeValvePin, HIGH);

    digitalWrite(Valve3Pin, HIGH);
    delay(second_third_delay);
    digitalWrite(Valve2Pin, HIGH);
    delay(first_second_delay);
    digitalWrite(Valve1Pin, HIGH);
}
#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>

class Vehicle
{
public:
    Vehicle(int maxSpeed): speed(0)
    {
        setSpeed(maxSpeed);
    }

    virtual ~Vehicle(){}

    unsigned getSpeed() const
    {
        return speed;
    }

    void print() const
    {
        std::cout << "Vehicle. Max speed: " << getSpeed() << std::endl;
    }

    void setSpeed(int speed)
    {
        if (speed >= 0)
        {
            this->speed = speed;
        }
    }

protected:
    unsigned speed;
};

#endif // VEHICLE_H

#ifndef PLANE_H
#define PLANE_H

#include <iostream>

#include "Vehicle.hpp"

class Plane : public Vehicle
{
public:
    Plane(int height, int maxSpeed) 
		: Vehicle(maxSpeed)
    {
        setHeight(height);
    }

    virtual void print() const
    {
        std::cout 
            << "I can fly up to " << getHeight() << " and with "
            << getSpeed() << " km/h" << std::endl;
    }

    unsigned getHeight() const
    {
        return height;
    }

    void setHeight(int height)
    {
        if (height >= 0)
        {
            this->height = height;
        }
    }

private:
    unsigned height;
};

#endif // PLANE_H

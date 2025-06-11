#ifndef BOAT_H
#define BOAT_H

#include <iostream>
#include <string>

#include "Vehicle.hpp"

class Boat : public Vehicle
{
public:
    Boat(const char* name, unsigned maxSpeed) 
		: Vehicle(maxSpeed)
    {
        setName(name);
    }

    virtual void print() const
    {
        std::cout 
            << "I'm " << getName() << "  "
            << "My max speed is " << getSpeed() << std::endl;
    }
	
    void setName(const char* name)
    {
		if(name)
			this->name = name;
    }

    const char* getName() const
    {
        return name.c_str();
    }

private:
    std::string name;
};

#endif // BOAT_H

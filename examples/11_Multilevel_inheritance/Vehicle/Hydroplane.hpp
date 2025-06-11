#ifndef HYDROPLANE_H
#define HYDROPLANE_H

#include <iostream>

#include "Boat.hpp"
#include "Plane.hpp"

class Hydroplane : public Boat, public Plane
{
public:
    Hydroplane(int regNum)
      : Boat("St. Louise", 60)
      , Plane(3000, 350)
      , regNum(regNum)
    {
    }

    virtual void print() const
    {
        std::cout << "Hydroplane " << regNum << std::endl;
		
        Boat::print();
        Plane::print();
    }

    int getRegNum() const
    {
        return regNum;
    }

protected:
    const int regNum;
};

#endif // HYDROPLANE_H

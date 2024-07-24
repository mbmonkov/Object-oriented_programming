#include "Cow.h"  
#include <iostream>

void Cow::makeNoise() const
{
    std::cout << "Moo.." << std::endl; 
}

AnimalType Cow::getType() const
{
    return AnimalType::Cow;  // Връща типа на животното като Cow
}

Animal* Cow::clone() const
{
    return new Cow(*this);  // Създава и връща нов обект от тип Cow, който е клонинг на текущия обект
}

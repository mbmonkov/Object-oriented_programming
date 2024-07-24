#include "Dog.h" 
#include <iostream>  

void Dog::makeNoise() const
{
    std::cout << "Bark..." << std::endl;  
}

AnimalType Dog::getType() const
{
    return AnimalType::Dog;  // Връща типа на животното като Dog
}

Animal* Dog::clone() const
{
    return new Dog(*this);  // Създава и връща нов обект от тип Dog, който е клонинг на текущия обект
}

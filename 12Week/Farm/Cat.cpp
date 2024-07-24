#include "Cat.h"  
#include <iostream>  

void Cat::makeNoise() const
{
    std::cout << "Meow..." << std::endl;  
}

AnimalType Cat::getType() const
{
    return AnimalType::Cat;  // Връща типа на животното като Cat
}

Animal* Cat::clone() const
{
    return new Cat(*this);  // Създава и връща нов обект от тип Cat, който е клонинг на текущия обект. 
                                                            //Връща указател към новосъздадения обект.
}

#pragma once  
#include "Animal.h"  

class AnimalFactory
{
public:
	static Animal* create(AnimalType type);  // Статичен метод за създаване на обекти от тип Animal в зависимост от AnimalType
};

#pragma once 
#include "Animal.h"  


class Cat : public Animal
{
public:
	// Реализация на чисто виртуалния метод от базовия клас Animal
	void makeNoise() const override;

	// Реализация на чисто виртуалния метод от базовия клас Animal
	AnimalType getType() const override;

	// Реализация на чисто виртуалния метод от базовия клас Animal
	Animal* clone() const override;
};

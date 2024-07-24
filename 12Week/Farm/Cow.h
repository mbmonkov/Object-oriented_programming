#pragma once 
#include "Animal.h"  

class Cow : public Animal
{
public:
	// ���������� �� ����� ���������� ����� �� ������� ���� Animal
	void makeNoise() const override;

	// ���������� �� ����� ���������� ����� �� ������� ���� Animal
	AnimalType getType() const override;

	// ���������� �� ����� ���������� ����� �� ������� ���� Animal
	Animal* clone() const override;
};

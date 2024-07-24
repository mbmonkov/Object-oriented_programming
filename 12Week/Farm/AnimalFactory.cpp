#include "AnimalFactory.h"  
#include <stdexcept>  
#include "Animal.h"  
#include "Cat.h"  
#include "Dog.h"  
#include "Cow.h" 

// �������� ����� �� AnimalFactory �� ��������� �� ���� ������� ��� ������ �� AnimalType
Animal* AnimalFactory::create(AnimalType type)
{
	Animal* toReturn = nullptr;  // ������������ �������� ��� Animal � nullptr
	switch (type)  // ��������� ���� �� ���������
	{
	case AnimalType::Cat:  // ��� ����� � Cat
		toReturn = new Cat;  // ������� ��� ����� �� ��� Cat
		break;
	case AnimalType::Dog:  // ��� ����� � Dog
		toReturn = new Dog;  // ������� ��� ����� �� ��� Dog
		break;
	case AnimalType::Cow:  // ��� ����� � Cow
		toReturn = new Cow;  // ������� ��� ����� �� ��� Cow
		break;
	default:  // ��� ����� �� � �������
		throw std::invalid_argument("[Farm::addAnimal] - invalid type");  // ������ ���������� � ��������� ���������
		break;
	}
	return toReturn;  // ����� ��������� ��� �������������� �����
}

#include "AnimalFactory.h"  
#include <stdexcept>  
#include "Animal.h"  
#include "Cat.h"  
#include "Dog.h"  
#include "Cow.h" 

// Статичен метод на AnimalFactory за създаване на ново животно въз основа на AnimalType
Animal* AnimalFactory::create(AnimalType type)
{
	Animal* toReturn = nullptr;  // Инициализира указател към Animal с nullptr
	switch (type)  // Проверява типа на животното
	{
	case AnimalType::Cat:  // Ако типът е Cat
		toReturn = new Cat;  // Създава нов обект от тип Cat
		break;
	case AnimalType::Dog:  // Ако типът е Dog
		toReturn = new Dog;  // Създава нов обект от тип Dog
		break;
	case AnimalType::Cow:  // Ако типът е Cow
		toReturn = new Cow;  // Създава нов обект от тип Cow
		break;
	default:  // Ако типът не е валиден
		throw std::invalid_argument("[Farm::addAnimal] - invalid type");  // Хвърля изключение с подходящо съобщение
		break;
	}
	return toReturn;  // Връща указателя към новосъздадения обект
}

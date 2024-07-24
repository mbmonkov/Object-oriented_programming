#pragma once 

// Декларира enum клас AnimalType с три стойности: Cat, Dog и Cow
enum class AnimalType
{
	Cat,  
	Dog,  
	Cow  
};

// Абстрактен клас Animal
class Animal
{
public:
	// Чисто виртуален метод
	virtual void makeNoise() const = 0;

	// Виртуален деструктор
	virtual ~Animal() = default;

	// Чисто виртуален метод
	virtual AnimalType getType() const = 0;

	// Чисто виртуален метод
	virtual Animal* clone() const = 0;
};

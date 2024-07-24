#pragma once 
#include "Animal.h"
#include <stddef.h>  // Включва библиотеката за дефиниции на стандартни типове като size_t

class Farm
{
	Animal** data;  // Массив от указатели към обекти от тип Animal (или неговите наследници)
	size_t size;  // Текущият брой животни в фермата
	size_t capacity;  // Максималният брой животни, който фермата може да съхранява, преди да се наложи разширение

	void free();  // Метод за освобождаване на динамично заделената памет
	void copyFrom(const Farm& other);  // Метод за копиране на данни от друг обект Farm
	void moveFrom(Farm&& other);  // Метод за преместване на данни от друг обект Farm 

	void resize();  // Метод за разширяване на капацитета на масива от животни

public:
	Farm();  // Конструктор по подразбиране
	~Farm();  // Деструктор

	Farm(const Farm& other);  // Конструктор за копиране
	Farm& operator=(const Farm& other);  // Оператор за присвояване чрез копиране

	Farm(Farm&& other) noexcept;  // Конструктор за преместване
	Farm& operator=(Farm&& other) noexcept;  // Оператор за присвояване чрез преместване

	void addAnimal(AnimalType type);  // Метод за добавяне на ново животно от даден тип
	void makeSound() const;  // Метод за извършване на звуците на всички животни във фермата
	AnimalType getType(size_t idx) const;  // Метод за получаване на типа на животното на даден индекс
};

#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include <stdexcept>

class Person
{
public:
	Person() : Person("Unknown", 0) {}

	Person(const char* name, unsigned age)
		:age(age)
	{
		if (!name || !*name)
			throw std::invalid_argument("Empty name!");

		if (strlen(name) >= sizeof(this->name))
			throw std::invalid_argument("The name is too long!");

		if (age > 120)
			throw std::invalid_argument("Invalid age!");

		strcpy(this->name, name);
	}

	const char* getName() const { return this->name; }
	unsigned getAge() const { return this->age; }

	// set of numerical coordinates
	protected:
	char name[32];
	unsigned age;
};

// has-a
//class Student
//{
//public:
//	Student(const char* name, unsigned age, unsigned fn)
//		: person(name, age), fn(fn)
//	{
//	}
//
//	const char* getName() const { return person.getName(); }
//	unsigned getAge() const { return person.getAge(); }
//
//	operator Person() const { return person; }
//
//private:
//	// искаме да има име, възраст и факултетен номер
//	Person person;
//	unsigned fn;
//};

// is-a
class Student : public Person
{
public:
	Student(const char* name, unsigned age, unsigned fn)
		: Person(name, age), fn(fn)
	{
	}

	unsigned getFN() const { return this->fn; }

private:
	unsigned fn;
};

void print(const Person& person)
{
	std::cout
		<< "Name:" << person.getName() << '\n'
		<< "Age:" << person.getAge() << '\n';
}

int main()
{
	Person ivan("Ivan Ivanov", 20);
	//Student dragan("Dragan Ivanov", 21, 123);
	//print(dragan);

	Student s("Aleks", 23, 234);
	print(s);

	return 0;
}
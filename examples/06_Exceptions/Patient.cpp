#define _CRT_SECURE_NO_WARNINGS

#include "Patient.h"

#include <cassert>
#include <cctype>
#include <cstring>
#include <new>

Patient::Patient(const char* name, const char* id)
	: name(nullptr), id(nullptr)
{
	//if (!isValidName(name))
	//    throw "Invalid name!";
	//
	//if (!isValidID(id))
	//    throw "Invalid ID!";

	//this->id = new (std::nothrow) char[strlen(id) + 1];
	//if (this->id == nullptr)
	//{
	//    delete[] this->name;
	//    throw std::bad_alloc();
	//}

	//strcpy(this->id, id);

	try
	{
		this->setName(name);
		this->setID(id);
	}
	catch (...)
	{
		delete[] this->name;
		delete[] this->id;

		throw;
	}
}

Patient::Patient(const Patient& other)
	: Patient(other.name, other.id)
{}

Patient& Patient::operator=(const Patient & other)
{
	if (this != &other)
	{
		//Patient temp(other);
		//std::swap(this->name, temp.name);
		//std::swap(this->id, temp.id);
		//std::swap(this->age, temp.age);

		*this = Patient(other);
	}

	return *this;
}

Patient::Patient(Patient&& other) noexcept
	: name(other.name), id(other.id)
{
	other.name = nullptr;
	other.id = nullptr;
}

Patient& Patient::operator=(Patient&& other) noexcept
{
	std::swap(this->name, other.name);
	std::swap(this->id, other.id);

	return *this;
}

Patient::~Patient() noexcept
{
	delete[] this->name;
	delete[] this->id;
}

void Patient::setName(const char* name)
{
	if (!isValidName(name))
		throw "Invalid name!";

	char* temp = copy(name);

	delete[] this->name;
	this->name = temp;
}

bool Patient::isValidName(const char* name)
{
	return name && name[0] != '\0';
}

bool Patient::isValidID(const char* id)
{
	if (!id || strlen(id) != 10)
		return false;

	while (*id)
	{
		if (!isdigit(*id))
			return false;

		++id;
	}

	return true;
}

char* Patient::copy(const char* str)
{
	assert(str);

	char* dest = new char[strlen(str) + 1];
	strcpy(dest, str);

	return dest;
}

void Patient::setID(const char* id)
{
	if (!isValidID(id))
		throw "Invalid ID!";

	char* temp = copy(id);

	delete[] this->id;
	this->id = temp;
}

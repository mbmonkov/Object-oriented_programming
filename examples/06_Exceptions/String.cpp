#define _CRT_SECURE_NO_WARNINGS

#include "String.h"

#include <iostream>
#include <cstring>
#include <stdexcept>

String::String(const char* str)
{
	if (!isValid(str))
		throw "Invalid data!";

	this->data = new char[strlen(str) + 1];
	strcpy(this->data, str);
}

String::String(const String& other)
	: String(other.data)
{}

String& String::operator=(const String & other)
{
	if (this != &other)
	{
		*this = String(other);

		//String temp{ other };
		//*this = std::move(temp);
		
		//std::swap(this->data, temp.data);

		//char* temp = new char[strlen(other.data) + 1];
		//strcpy(temp, other.data);

		//delete[] this->data;
		//this->data = temp;
	}

	return *this;
}

String::String(String&& other) noexcept
	: data(other.data)
{
	other.data = nullptr;
}

String& String::operator=(String&& other) noexcept
{
	std::swap(this->data, other.data);

	//if (this != &other)
	//{
	//	delete[] this->data;

	//	this->data = other.data;
	//	other.data = nullptr;
	//}
	
	return *this;
}

String::~String()
{
	delete[] this->data;
}

char& String::at(size_t index)
{
	if (index >= length())
		throw "Index out of range!";

	return this->data[index];
}

const char& String::at(size_t index) const
{
	if (index >= length())
		throw "Index out of range";

	return this->data[index];
}

size_t String::length() const
{
	return strlen(this->data);
}

void String::print() const
{
	std::cout << this->data;
}

bool String::isValid(const char* str)
{
	return str != nullptr;
}

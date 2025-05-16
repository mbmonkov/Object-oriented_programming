#include "Array.h"

#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>

Array::Array(size_t cap)
	: allocated{ cap }, used{ 0 }, data{ nullptr }
{
	this->data = new int[cap];
}

Array::~Array() noexcept
{
	delete[] this->data;
}

Array& Array::operator+=(int elem)
{
	append(elem);
	return *this;
}

Array& Array::operator+=(const Array& other)
{
	if (this->used + other.used >= this->allocated)
		throw std::overflow_error("Cannot add all elements!");

	for (size_t i = 0; i < other.used; ++i)
	{
		append(other.data[i]);
	}

	return *this;
}

int& Array::operator[](size_t index)
{
	return this->data[index];
}

const int& Array::operator[](size_t index) const
{
	return this->data[index];
}

Array::Array(const Array& other)
	: allocated{ other.allocated }, used{ other.used }
{
	assert(allocated >= used);

	this->data = new int[other.allocated];
	for (size_t i = 0; i < other.used; ++i)
	{
		this->data[i] = other.data[i];
	}
}

Array& Array::operator=(const Array& other)
{
	if (this != &other)
	{
		if (this->allocated < other.allocated)
			throw std::overflow_error("The other array was too long!");

		this->used = other.used;
		for (size_t i = 0; i < other.used; ++i)
		{
			this->data[i] = other.data[i];
		}
	}

	return *this;
}

Array::Array(Array&& other) noexcept :
	allocated{ other.allocated }, 
	used{ other.used },
	data{ other.data }
{
	other.data = nullptr;
	other.used = 0;
}

int& Array::at(size_t index)
{
	if (index >= this->used)
		throw std::out_of_range("The index is out of range!");

	return this->data[index];
}

const int& Array::at(size_t index) const
{
	if (index >= this->used)
		throw std::out_of_range("The index is out of range!");

	return this->data[index];
}

int Array::operator()(int elem) const
{
	for (size_t i = 0; i < this->used; ++i)
	{
		if (this->data[i] == elem)
			return (int)i;
	}

	return -1;
}

Array Array::operator()(size_t start, size_t end) const
{
	if (start > end)
		throw std::invalid_argument("Invalid start and end!");

	if (end > this->used)
		end = this->used;

	size_t count = end - start + 1;

	Array result{ count };
	for (size_t i = 0; i < count; ++i)
	{
		result += this->data[i + start];
	}

	return result;
}

Array::Iterator Array::begin()
{
	return Iterator(this->data);
}

Array::Iterator Array::end()
{
	return Iterator(this->data + this->used);
}

void Array::append(int elem)
{
	if (this->used >= this->allocated)
		throw std::overflow_error("The array is full!");

	this->data[this->used] = elem;
	++this->used;
}

Array::Iterator& Array::Iterator::operator++()
{
	++this->position;
	return *this;
}

Array::Iterator Array::Iterator::operator++(int)
{
	Iterator old = *this;
	++(*this);
	return old;
}

bool Array::Iterator::operator==(const Iterator& other) const
{
	return this->position == other.position;
}

bool Array::Iterator::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

int Array::Iterator::operator*() const
{
	return *position;
}

int& Array::Iterator::operator*()
{
	return *position;
}
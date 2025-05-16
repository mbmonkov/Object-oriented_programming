#include "SortedArray.h"

#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>

SortedArray::SortedArray(size_t cap)
	: allocated{ cap }, used{ 0 }, data{ nullptr }
{
	this->data = new int[cap];
}

SortedArray::~SortedArray() noexcept
{
	delete[] this->data;
}

SortedArray& SortedArray::operator+=(int elem)
{
	add(elem);
	return *this;
}

SortedArray& SortedArray::operator+=(const SortedArray& other)
{
	if (this->used + other.used > this->allocated)
		throw std::overflow_error("Cannot add all elements!");

	//for (size_t i = 0; i < other.used; ++i)
	//{
	//	*this += other.data[i];
	//}

	// merge
	// отдясно наляво 
	int leftIndex = this->used - 1;
	int rightIndex = other.used - 1;

	int writingPos = this->used + other.used - 1;

	while (leftIndex >= 0 && rightIndex >= 0)
	{
		if (data[leftIndex] >= other.data[rightIndex])
		{
			data[writingPos--] = data[leftIndex--];
		}
		else
		{
			data[writingPos--] = other.data[rightIndex--];
		}
	}

	while (rightIndex >= 0)
	{
		data[writingPos--] = other.data[rightIndex--];
	}

	this->used += other.used;

	return *this;
}

SortedArray::Proxy SortedArray::operator[](size_t index)
{
	return Proxy(*this, index);
}

const int& SortedArray::operator[](size_t index) const
{
	return this->data[index];
}

SortedArray::SortedArray(const SortedArray& other)
	: allocated{ other.allocated }, used{ other.used }
{
	assert(allocated >= used);

	this->data = new int[other.allocated];
	for (size_t i = 0; i < other.used; ++i)
	{
		this->data[i] = other.data[i];
	}
}

SortedArray& SortedArray::operator=(const SortedArray& other)
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

SortedArray::SortedArray(SortedArray&& other) noexcept :
	allocated{ other.allocated }, 
	used{ other.used },
	data{ other.data }
{
	other.data = nullptr;
	other.used = 0;
}

SortedArray::Proxy SortedArray::at(size_t index)
{
	if (index >= this->used)
		throw std::out_of_range("The index is out of range!");

	return Proxy(*this, index);
}

const int& SortedArray::at(size_t index) const
{
	if (index >= this->used)
		throw std::out_of_range("The index is out of range!");

	return this->data[index];
}

int SortedArray::operator()(int elem) const
{
	for (size_t i = 0; i < this->used; ++i)
	{
		if (this->data[i] == elem)
			return (int)i;
	}

	return -1;
}

SortedArray SortedArray::operator()(size_t start, size_t end) const
{
	if (start > end)
		throw std::invalid_argument("Invalid start and end!");

	if (end > this->used)
		end = this->used;

	size_t count = end - start + 1;

	SortedArray result{ count };
	for (size_t i = 0; i < count; ++i)
	{
		result += this->data[i + start];
	}

	return result;
}

SortedArray::Iterator SortedArray::begin()
{
	return Iterator(this->data);
}

SortedArray::Iterator SortedArray::end()
{
	return Iterator(this->data + this->used);
}

void SortedArray::add(int elem)
{
	if (this->used >= this->allocated)
		throw std::overflow_error("The array is full!");

	this->data[this->used] = elem;
	++this->used;
	shiftRight(elem, used - 1);
}

void SortedArray::shiftRight(int elem, size_t pos)
{
	size_t i = pos;
	while (i > 0 && data[i - 1] > elem)
	{
		data[i] = data[i - 1];
		--i;
	}

	data[i] = elem;
}

void SortedArray::shiftLeft(int elem, size_t pos)
{
	size_t i = pos;
	while (i < used - 1 && data[i + 1] < elem)
	{
		data[i] = data[i + 1];
		++i;
	}

	data[i] = elem;
}

SortedArray::Iterator& SortedArray::Iterator::operator++()
{
	++this->position;
	return *this;
}

SortedArray::Iterator SortedArray::Iterator::operator++(int)
{
	Iterator old = *this;
	++(*this);
	return old;
}

bool SortedArray::Iterator::operator==(const Iterator& other) const
{
	return this->position == other.position;
}

bool SortedArray::Iterator::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

int SortedArray::Iterator::operator*() const
{
	return *position;
}

int& SortedArray::Iterator::operator*()
{
	return *position;
}

SortedArray::Proxy::operator int()
{
	return this->owner.data[currentIndex];
}

SortedArray::Proxy& SortedArray::Proxy::operator=(int elem)
{
	std::cout << "The element is to the left of =\n";

	int oldValue = this->owner.data[currentIndex];

	this->owner.data[currentIndex] = elem; 
	if (oldValue > elem)
	{
		owner.shiftRight(elem, currentIndex);
	}
	else
	{
		owner.shiftLeft(elem, currentIndex);
	}

	return *this;
}
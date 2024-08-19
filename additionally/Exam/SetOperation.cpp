#include "SetOperation.h"

void SetOperation::copyFrom(const SetOperation& other)
{
	sets = new Set * [other.count];
	for (size_t i = 0; i < other.count; i++)
		sets[i] = other.sets[i]->clone();
	count = other.count;
}

void SetOperation::moveFrom(SetOperation&& other)
{
	sets = other.sets;
	other.sets = nullptr;

	count = other.count;
	other.count = 0;
}

void SetOperation::free()
{
	for (unsigned i = 0; i < count; i++)
		delete sets[i];
	delete[] sets;
}

SetOperation::SetOperation(const Set** sets, size_t count)
{
	this->sets = new Set * [count];
	for (size_t i = 0; i < count; i++)
		this->sets[i] = sets[i]->clone();
}

SetOperation::SetOperation(Set**&& sets, size_t count)
{
	this->sets = sets;
	this->count = count;
}

SetOperation::SetOperation(const SetOperation& other)
{
	copyFrom(other);
}

SetOperation& SetOperation::operator=(const SetOperation& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

SetOperation::SetOperation(SetOperation&& other) noexcept
{
	moveFrom(std::move(other));
}

SetOperation& SetOperation::operator=(SetOperation&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

SetOperation::~SetOperation()
{
	free();
}
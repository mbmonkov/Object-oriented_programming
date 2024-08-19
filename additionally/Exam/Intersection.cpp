#include "Intersection.h"

Intersection::Intersection(const Set** sets, size_t count) : SetOperation(sets, count)
{

}

Intersection::Intersection(Set**&& sets, size_t count) : SetOperation(std::move(sets), count)
{

}

Set* Intersection::clone() const 
{
	return new Intersection(*this);
}

bool Intersection::accepts(unsigned num) const 
{
	for (size_t i = 0; i < count; i++)
	{
		if (!sets[i]->accepts(num))
			return false;
	}
	return true;
}
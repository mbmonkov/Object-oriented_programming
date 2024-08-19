#include "UnionOfSet.h"

Union::Union(const Set** sets, size_t count) : SetOperation(sets, count)
{

}

Union::Union(Set**&& sets, size_t count) : SetOperation(std::move(sets), count)
{

}

Set* Union::clone() const 
{
	return new Union(*this);
}

bool Union::accepts(unsigned num) const
{
	for (size_t i = 0; i < count; i++)
	{
		if (sets[i]->accepts(num))
			return true;
	}
	return false;
}
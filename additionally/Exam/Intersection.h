#pragma once
#include "SetOperation.h"

class Intersection : public SetOperation
{
public:
	Intersection(const Set** sets, size_t count);
	Intersection(Set**&& sets, size_t count);

	Set* clone() const override;
	bool accepts(unsigned num) const override;
};
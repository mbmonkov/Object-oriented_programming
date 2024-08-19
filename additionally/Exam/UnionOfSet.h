#pragma once
#include "SetOperation.h"

class Union : public SetOperation
{
public:

	Union(const Set** sets, size_t count);
	Union(Set**&& sets, size_t count);

	Set* clone() const override;
	bool accepts(unsigned num) const override;
};
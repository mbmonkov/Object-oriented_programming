#pragma once
#include <utility>


class Set
{
public:
	virtual Set* clone() const = 0;
	virtual bool accepts(unsigned num) const = 0;
	virtual ~Set() = default;
};
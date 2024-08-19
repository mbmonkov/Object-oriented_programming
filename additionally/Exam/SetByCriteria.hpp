#pragma once
#include "Set.h"

template <class T>
class SetByCriteria : public Set
{
	T criteria;

public:
	SetByCriteria(const T& cr);
	SetByCriteria(T&& cr);
	virtual Set* clone() const override;
	virtual bool accepts(unsigned num) const override;
};

template<class T>
SetByCriteria<T>::SetByCriteria(const T& cr) : criteria(cr) {}

template<class T>
SetByCriteria<T>::SetByCriteria(T&& cr) : criteria(std::move(cr)) {}

template<class T>
Set* SetByCriteria<T>::clone() const
{
	return new SetByCriteria<T>(*this);
}

template<class T>
bool SetByCriteria<T>::accepts(unsigned num) const
{
	return criteria(num);
}
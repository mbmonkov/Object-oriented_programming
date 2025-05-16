#include "Doctor.h"
#include "PatientS.h"

#include <cctype>

PatientS::PatientS(const String& name, const String& id)
	: name(name), id(id)
{
	if (!isValidName(name))
		throw "Invalid name!";

	if (!isValidID(id))
		throw "Invalid ID!";
}

PatientS::~PatientS()
{
	if (this->gp)
		this->gp->unregisterPatient(*this);
}

void PatientS::setName(const String& name)
{
	if (!isValidName(name))
		throw "Invalid name!";

	this->name = name;
}

bool PatientS::registerTo(Doctor& doctor)
{
	if (doctor.registerNewPatient(*this))
	{
		if (this->gp)
		{
			this->gp->unregisterPatient(*this);
		}

		this->gp = &doctor;
		return true;
	}

	return false;
}

bool PatientS::unregisterFromGP()
{
	if (!this->gp)
		return false;

	if (this->gp->unregisterPatient(*this))
	{
		this->gp = nullptr;
		return true;
	}

	return false;
}

bool PatientS::isValidName(const String& s)
{
	return !s.empty();
}

bool PatientS::isValidID(const String& id)
{
	if (id.empty())
		return false;

	size_t len = id.length();
	for (size_t i = 0; i < len; ++i)
	{
		if (!isdigit(id.at(i)))
			return false;
	}

	return true;
}

void PatientS::unregisterDirectly()
{
	this->gp = nullptr;
}

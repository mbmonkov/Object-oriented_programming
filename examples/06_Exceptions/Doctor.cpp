#include "Doctor.h"
#include "PatientS.h"

#include <exception>
#include <stdexcept>

Doctor::Doctor(const String& name)
	: name(name)
{
	if (name.empty())
		throw std::invalid_argument("Invalid name!");
}

Doctor::~Doctor()
{
	for (size_t i = 0; i < this->countPatients; ++i)
	{
		this->patients[i]->unregisterDirectly();
	}
}

bool Doctor::registerNewPatient(PatientS& patient)
{
	if(hasPatient(patient))
		return false;

	if (this->countPatients >= Doctor::MAX_PATIENTS_COUNT)
		return false;

	this->patients[this->countPatients] = &patient;
	++this->countPatients;

	return true;
}

bool Doctor::unregisterPatient(PatientS& patient)
{
	int i = findPatient(patient);
	if (i >= 0)
	{
		this->patients[i]->unregisterDirectly();

		this->patients[i] = this->patients[countPatients - 1];
		this->patients[countPatients - 1] = nullptr;
		--this->countPatients;

		return true;
	}

	return false;
}

void Doctor::closePractice()
{
	for (size_t i = 0; i < this->countPatients; ++i)
	{
		this->patients[i]->unregisterFromGP();
	}
}

int Doctor::findPatient(const PatientS& patient) const
{
	for (int i = 0; i < this->countPatients; ++i)
	{
		if (this->patients[i] == &patient)
			return i;
	}

	return -1;
}

bool Doctor::hasPatient(const PatientS& patient) const
{
	return findPatient(patient) >= 0;
}

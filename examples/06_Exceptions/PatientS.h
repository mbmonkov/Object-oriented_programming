#pragma once

#ifndef PATIENTS_H
#define PATIENTS_H

#include "String.h"

class Doctor;

class PatientS
{
	friend class Doctor;

public:
	PatientS(const String& name, const String& id);

	PatientS(const PatientS&) = delete;
	PatientS& operator=(const PatientS&) = delete;

	~PatientS() noexcept;

	String getName() const { return this->name; }
	String getID() const { return this->id; }

	void setName(const String& name);

	bool registerTo(Doctor& doctor);
	bool unregisterFromGP();

private: 
	static bool isValidName(const String& name);
	static bool isValidID(const String& id);

	void unregisterDirectly();
private:
	String name;
	const String id;

	Doctor* gp{ };
};

#endif // !PATIENTS_H


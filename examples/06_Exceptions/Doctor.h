#pragma once

#ifndef DOCTOR_H
#define DOCTOR_H

#include "String.h"

class PatientS;

class Doctor
{
public:
	Doctor(const String& name);

	Doctor(const Doctor&) = delete;
	Doctor& operator=(const Doctor&) = delete;

	~Doctor() noexcept;

	String getName() const { return name; }

	bool registerNewPatient(PatientS& patient);
	bool unregisterPatient(PatientS& patient);

	bool hasPatient(const PatientS& patient) const;

	void closePractice();
	
	static size_t getMaxPatientsCount() { return MAX_PATIENTS_COUNT; }

private:
	int findPatient(const PatientS& patient) const;

private:
	static const size_t MAX_PATIENTS_COUNT = 50;

private:
	String name;
	
	PatientS* patients[MAX_PATIENTS_COUNT]{ };
	size_t countPatients{ 0 };
};

#endif // !DOCTOR_H

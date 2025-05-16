#pragma once

#ifndef PATIENT_H
#define PATIENT_H

class Doctor;

class Patient
{
public:
	Patient(const char* name, const char* id);

	Patient(const Patient& other);
	Patient& operator=(const Patient& other);

	Patient(Patient&& other) noexcept;
	Patient& operator=(Patient&& other) noexcept;

	~Patient() noexcept;

	const char* getName() const { return name; }
	const char* getID() const { return id; }

	void setName(const char* name);

private:
	static bool isValidName(const char* name);
	static bool isValidID(const char* id);

	static char* copy(const char* str);

	void setID(const char* id);

private:
	char* name{ };
	char* id{ };
};

#endif // !PATIENT_H

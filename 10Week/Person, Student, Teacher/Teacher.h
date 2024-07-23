#pragma once
#include "Person.h"

class Teacher : public Person
{
    char** subjects;        // Динамичен масив от указатели към низове 
    size_t subjectsCount;   // Броят на темите

    void free();
    void copyFrom(const Teacher& other);// само нещата, които са от Teacher
    void moveFrom(Teacher&& other);

public:
	Teacher(const char* name, int age, const char* const* subjects, size_t subjectsCount);

	Teacher(const Teacher& other);
	Teacher& operator=(const Teacher& other);

	Teacher(Teacher&& other) noexcept;
	Teacher& operator=(Teacher&& other) noexcept;
	~Teacher();
};

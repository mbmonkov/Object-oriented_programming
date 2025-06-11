#pragma once

#ifndef STUDENT_H
#define STUDENT_H

#include "Address.h"

struct Student
{
	char fn[11];
	char name[30];
	int course;
	double grades;

	Address address;
};

void read(Student& s);
void print(const Student& s);

#endif // STUDENT_H

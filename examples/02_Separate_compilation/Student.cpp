#include "Student.h"

#include <iostream>

void read(Student& s)
{
	std::cin >> s.fn;
	// за да изчисти новия ред
	std::cin.ignore();

	std::cin.getline(s.name, sizeof(s.name));
	std::cin >> s.course;
	std::cin >> s.grades;
	std::cin.ignore();

	read(s.address);
}

void print(const Student& s)
{
	std::cout << "FN: " << s.fn << std::endl;
	std::cout << "Name: " << s.name << std::endl;
	std::cout << "Course: " << s.course << std::endl;
	std::cout << "Grades: " << s.grades << std::endl;

	print(s.address);
}
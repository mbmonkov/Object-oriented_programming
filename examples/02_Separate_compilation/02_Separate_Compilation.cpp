#define _CRT_SECURE_NO_WARNINGS

#include "Address.h"
#include "Student.h"

#include <iostream>
#include <cstring>

// да се създаде масив от студенти
// да се сортира по факултетен номер
// да се изведат студентите с успех >= 5.50

int main()
{
	std::cout << "sizeof(Address): " << sizeof(Address) << std::endl;
	std::cout << "sizeof(Student): " << sizeof(Student) << std::endl;

	Student me;
	read(me);
	print(me);
	
	Student inf[10] = { 
		{"1", "me", 2, 4.50},
		// оценката е 0
		{"2", "you", 2}
		// всички останали елементи на масива са нули
	};

	strcpy(inf[2].address.city, "Sofia");
	std::cout << "\nStudent[2]:\n";
	print(inf[2]);

	return 0;
}




#include <iostream>

int globalVar = 10;

void f(int value)
{
	std::cout << value << std::endl;
}

// не са видими в друг translation unit
static int globalStatic = 12;

// не са видими в друг translation unit
static void fStatic(int value)
{
	std::cout << value << std::endl;
}
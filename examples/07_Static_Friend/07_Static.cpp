#include <iostream>

// forward декларация на функция от друг translation unit
void f(int);

// променливата е дифинирана в друг translation unit
extern int globalVar;

// не можем да се свържем с функцията,
// тя е статична, т.е. не е видима извън файла, 
// в който е дефинирана
// extern и static са несъвместими

// extern void fStatic(int);

int main()
{
	f(5);
	f(globalVar);

	// fStatic(7);

	return 0;
}
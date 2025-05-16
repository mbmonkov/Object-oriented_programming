#include <iostream>

#include "Rational.h"

int main_()
{
    int x = 5, y = 6;
    (x -= y) = x;
	std::cout << "x = " << x << std::endl;

    Rational rat;
	std::cout << rat << std::endl;

	std::cout << "Change Rat: ";
    rat.setNumerator(3);
    rat.setDenominator(4);
	std::cout << rat << std::endl;

	std::cout << "5 + " << rat << " = " << 5 + rat << std::endl;
	std::cout << "5 - " << rat << " = " << 5 - rat << std::endl;
	std::cout << "5 * " << rat << " = " << 5 * rat << std::endl;
	std::cout << "5 / " << rat << " = " << 5 / rat << std::endl;

    Rational other(4, 5);
	std::cout << other << std::endl;

	std::cout << rat << " + " << other << " = " << rat + other << std::endl;
	std::cout << rat << " - " << other << " = " << rat - other << std::endl;
	std::cout << rat << " * " << other << " = " << rat * other << std::endl;
	std::cout << rat << " / " << other << " = " << rat / other << std::endl;

	std::cout << rat << " + " << 4 << " = " << rat + 4 << std::endl;

	std::cout << "++" << rat << " = ";
	++rat;
	std::cout << rat << std::endl;

	std::cout << rat << " == " << other << ": " << std::boolalpha << (rat == other) << std::endl;
	std::cout << rat << " != " << other << ": " << std::boolalpha << (rat != other) << std::endl;
	std::cout << rat << " < "  << other << ": " << std::boolalpha << (rat < other)  << std::endl;
	std::cout << rat << " <= " << other << ": " << std::boolalpha << (rat <= other) << std::endl;
	std::cout << rat << " > "  << other << ": " << std::boolalpha << (rat > other)  << std::endl;
	std::cout << rat << " >= " << other << ": " << std::boolalpha << (rat >= other) << std::endl;

    return 0;
}

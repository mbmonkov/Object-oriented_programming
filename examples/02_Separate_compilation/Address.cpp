#include "Address.h"

#include <iostream>

void read(Address& a)
{
	std::cin.getline(a.city, sizeof(a.city));
	std::cin.getline(a.street, sizeof(a.street));
	std::cin >> a.number;
	std::cin.ignore();
}

void print(const Address& a)
{
	std::cout << "\nAddress:\n";
	std::cout << "city: " << a.city << std::endl;
	std::cout << "street: " << a.street << std::endl;
	std::cout << "number: " << a.number << std::endl;
}
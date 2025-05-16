#include <iostream>

#include "Object.h"

int main()
{
	std::cout << "Live objects: " << Object::getLiveObjects() << std::endl;

	Object o1{ 1 };
	printID(o1);
	
	Object o2{ 2 };
	printID(o2);

	std::cout << "Live objects: " << Object::getLiveObjects() << std::endl;

	{
		Object o3 = o2;
		std::cout << "o3 was created as a copy of o2!\n";
		printID(o3);
		std::cout << "Live objects: " << Object::getLiveObjects() << std::endl;

		o1 = o2;
		std::cout << "o2 was assigned to o1!\n";
		
		FileWriter wr;
		wr.printToFile(o1);

		std::cout << "Live objects: " << Object::getLiveObjects() << std::endl;
	}

	std::cout 
		<< "Live objects after the block:" 
		<< Object::getLiveObjects() << std::endl;

	return 0;
}
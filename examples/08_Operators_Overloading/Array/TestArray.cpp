#include "Array.h"
#include <iostream>

void print(Array& array)
{
	//for (size_t i = 0; i < array.size(); ++i)
	//{
	//	std::cout << array[i] << ' ';
	//}

	for (Array::Iterator iter = array.begin(); iter != array.end(); ++iter)
	{
		std::cout << *iter << ' ';
	}

	std::cout << std::endl;
}

int main()
{
	Array array{ 5 };
	array += 1;
	array += 2;
	array += 3;
	array += 4;
	print(array);

	array[3] = 5;
	print(array);

	int index = array(2);
	std::cout << "Position of 2: " << index << std::endl;

	Array subArray = array(1, 3);
	print(subArray);

	return 0;
}

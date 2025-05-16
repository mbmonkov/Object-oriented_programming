#include "SortedArray.h"

#include <iostream>

void print(SortedArray& array)
{
	//for (size_t i = 0; i < array.size(); ++i)
	//{
	//	std::cout << array[i] << ' ';
	//}

	for (SortedArray::Iterator iter = array.begin(); iter != array.end(); ++iter)
	{
		std::cout << *iter << ' ';
	}

	std::cout << std::endl;
}

int main()
{
	try
	{
		SortedArray array{ 20 };
		array += 1;
		array += 2;
		array += 3;
		array += 4;
		print(array);

		SortedArray copy{ array };
		std::cout << "Change the element at position 2 with 5.\n";
		copy[2] = 5;
		print(copy);

		std::cout << "Change the element at position 1 with 7.\n";
		copy[1] = 7;
		print(copy);

		std::cout << "Adding two sorted arrays.\n";
		copy += array;
		print(copy);

		int index = array(2);
		std::cout << "\nPosition of 2: " << index << std::endl;

		SortedArray subArray = array(1, 3);
		print(subArray);

	}
	catch (std::exception& ex)
	{
		std::cerr << "Exception has occured! " << ex.what();
	}

	return 0;
}

#include <iostream>

#include <exception>
#include <stdexcept>

#include "Rat.h"

// пример 1.
int findFirstElement(const int* array, size_t size, int elem)
{
    if (!array)
        return -1;

    for (int i = 0; i < size; ++i)
    {
        if (array[i] == elem)
            return i;
    }

    return -1;
}

// пример 2.
bool divide(int x, int y, double& res)
{
    if (y == 0)
        return false;

    res = static_cast<double>(x) / y;
    return true;
}

// конструктори?

//int main()
//{
//    std::cout << "Point 1: Before the try block...\n";
//    try
//    {
//        std::cout 
//            << "Point 2: Inside the try block, before the throw...\n";
//        
//        throw "Error"; 
//
//        std::cout 
//            << "Point 3: Inside the try block, after the throw...\n";
//    }
//    catch (const char* ex)
//    {
//        std::cerr << "Exception caught: " << ex;
//    }
//
//    std::cout << "Point 4: After the try block, after the throw..." << std::endl;
//}

void throwException()
{
    int choice;
    std::cout
        << "What do you want to throw?\n"
        << "  [1] char\n"
        << "  [2] int\n"
        << "  [3] double\n"
        << "  [4] std::out_of_range object\n"
        << "Your choice: ";

    std::cin >> choice;

    switch (choice)
    {
    case 1: throw '!';
    case 2: throw 5;
    case 3: throw 5.5;
    case 4: throw std::out_of_range("Something is out of range!");

    default:
        throw std::exception("A number between 1 and 4 was expected!");
    }

    std::cout << "Will this line ever be executed? Never!\n";
}

void caller()
{
    try
    {
        // 1. double?
        // 2. char?
        // 3. out_of_range
        throwException();
    }
    catch (int ex)
    {
        std::cerr << "Caught an int: " << ex;
    }
    catch (double ex)
    {
        std::cerr << "Caught a double: " << ex;
    }
}

int main()
{
    Rat* r;
    try
    {
        r = new Rat{ 2, 3 };
        
        caller();

        delete r;
    }
    catch (const std::out_of_range& ex)
    {
        delete r;
        std::cerr << "Caught a std::out_of_range: " << ex.what();
    }
    catch (const std::exception& ex)
    {
        delete r;
        std::cerr << "Caught a std::exception: " << ex.what();
    }
    catch (...)
    {
        delete r;
        std::cerr << "Caught something the rest have failed to catch... \n";
    }
}















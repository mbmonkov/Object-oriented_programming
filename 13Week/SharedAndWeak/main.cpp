#include <iostream>
#include "WeakPtr.hpp" 


struct A
{
    A()
    {
        std::cout << "A()" << std::endl; 
    }


    ~A()
    {
        std::cout << "~A()" << std::endl; 
    }
};

int main()
{
    WeakPtr<A> wp; // Създава WeakPtr wp, който не управлява никакви ресурси в момента

    {
        SharedPtr<A> pt(new A()); // Създава SharedPtr pt, който управлява нов обект от тип A
        wp = pt; // Инициализира weak указател wp с помощта на shared указател pt

        std::cout << wp.expired() << std::endl; // Проверява дали weak указател wp е изтекъл и отпечатва резултата
        // False
    }

    std::cout << wp.expired() << std::endl; // Проверява дали weak указател wp е изтекъл след края на блока и отпечатва резултата 
    // True
}

#include <iostream> 
#include "MyStack.hpp"

int main()
{
    // Създаване на стек от тип int с капацитет 10
    MyStack<int, 10> s;

    s.push(3);

    std::cout << s.peek(); // Очакваме изход: 3

    return 0;
}

#include <iostream> 
#include "MyStack.hpp"

int main()
{
    // ��������� �� ���� �� ��� int � ��������� 10
    MyStack<int, 10> s;

    s.push(3);

    std::cout << s.peek(); // �������� �����: 3

    return 0;
}

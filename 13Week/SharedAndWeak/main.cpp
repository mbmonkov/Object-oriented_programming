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
    WeakPtr<A> wp; // ������� WeakPtr wp, ����� �� ��������� ������� ������� � �������

    {
        SharedPtr<A> pt(new A()); // ������� SharedPtr pt, ����� ��������� ��� ����� �� ��� A
        wp = pt; // ������������ weak �������� wp � ������� �� shared �������� pt

        std::cout << wp.expired() << std::endl; // ��������� ���� weak �������� wp � ������� � ��������� ���������
        // False
    }

    std::cout << wp.expired() << std::endl; // ��������� ���� weak �������� wp � ������� ���� ���� �� ����� � ��������� ��������� 
    // True
}

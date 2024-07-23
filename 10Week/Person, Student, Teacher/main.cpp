#include <iostream>
#include "Person.h"
#include "Student.h"
#include "Teacher.h"

int main()
{
    // �������� � ������������ ����� �� ������ (subjects)
    char subjects[3][20] = { "English", "Mathematics", "Physics" };

    // ������� ����� �� ��������� ��� ���� ������
    char** subjectsPointers = new char* [3];
    subjectsPointers[0] = subjects[0];
    subjectsPointers[1] = subjects[1];
    subjectsPointers[2] = subjects[2];

    // ������� ����� �� ��� Teacher
    Teacher t("Prof. Ivanov", 33, subjectsPointers, 3);

    // ������ ����� �� �������
    std::cout << t.getName() << std::endl;

    // ����������� ������� �� �����������, �� �� � ������ ������
    delete[] subjectsPointers; // only the pointers - not the data!

    return 0;
}

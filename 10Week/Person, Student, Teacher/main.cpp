#include <iostream>
#include "Person.h"
#include "Student.h"
#include "Teacher.h"

int main()
{
    // Дефинира и инициализира масив от низове (subjects)
    char subjects[3][20] = { "English", "Mathematics", "Physics" };

    // Създава масив от указатели към тези низове
    char** subjectsPointers = new char* [3];
    subjectsPointers[0] = subjects[0];
    subjectsPointers[1] = subjects[1];
    subjectsPointers[2] = subjects[2];

    // Създава обект от тип Teacher
    Teacher t("Prof. Ivanov", 33, subjectsPointers, 3);

    // Печата името на учителя
    std::cout << t.getName() << std::endl;

    // Освобождава паметта на указателите, но не и самите низове
    delete[] subjectsPointers; // only the pointers - not the data!

    return 0;
}

#include "Teacher.h"
#pragma warning (disable:4996)

// Копира динамичен масив от низове
static char** copyArrayOfString(const char* const* strings, size_t size)
{
    char** res = new char* [size];

    for (size_t i = 0; i < size; i++)
    {
        res[i] = new char[strlen(strings[i]) + 1];
        strcpy(res[i], strings[i]);
    }

    return res;
}

// Освобождава динамично заделената памет за масив от низове
static void freeArraysOfString(char** strings, unsigned stringsCount)
{
    for (size_t i = 0; i < stringsCount; i++)
        delete[] strings[i];
    delete[] strings;
}

// Конструктор на Teacher, инициализира с име, възраст, и списък с теми
Teacher::Teacher(const char* name, int age, const char* const* subjects, size_t subjectsCount) : Person(name, age)
{
    this->subjects = copyArrayOfString(subjects, subjectsCount);
    this->subjectsCount = subjectsCount;
}

// Освобождава динамично заделената памет за темите
void Teacher::free()
{
    freeArraysOfString(subjects, subjectsCount);
}

// Копира данните от друг Teacher
void Teacher::copyFrom(const Teacher& other)
{
    subjects = copyArrayOfString(other.subjects, other.subjectsCount);
    subjectsCount = other.subjectsCount;
}

// Конструктор за копиране, копира всички член данни от друг Teacher
Teacher::Teacher(const Teacher& other) : Person(other)
{
    copyFrom(other); // само частта от Teacher се копира
}

// Оператор за присвояване чрез копиране
Teacher& Teacher::operator=(const Teacher& other)
{
    if (this != &other)
    {
        Person::operator=(other); // първо копира данните от Person
        free(); // освобождава старите ресурси
        copyFrom(other); // копира новите ресурси
    }
    return *this;
}

// Премества данните от друг Teacher
void Teacher::moveFrom(Teacher&& other)
{
    subjects = other.subjects;
    subjectsCount = other.subjectsCount;
    other.subjects = nullptr; // освободете ресурса в другия обект
    other.subjectsCount = 0;
}

// Конструктор за преместване, инициализира с преместените ресурси
Teacher::Teacher(Teacher&& other) noexcept : Person(std::move(other))
{
    moveFrom(std::move(other));
}

// Оператор за присвояване чрез преместване
Teacher& Teacher::operator=(Teacher&& other) noexcept
{
    if (this != &other)
    {
        Person::operator=(std::move(other)); // премества данните от Person
        free(); // освобождава старите ресурси
        moveFrom(std::move(other)); // премества новите ресурси
    }
    return *this;
}

// Деструктор, освобождава динамично заделената памет
Teacher::~Teacher()
{
    free();
}

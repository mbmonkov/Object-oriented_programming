#include "SetByString.h"
#pragma warning (disable : 4996)

// Метод за извличане на числа от низ и добавяне в множеството
void SetByString::extractNumbersFromString()
{
    removeAll(); // Премахва всички съществуващи числа в множеството
    std::stringstream myStream(str); // Създава стрийм от низа

    // Извлича числата от стрийма и ги добавя в множеството
    while (!myStream.eof())
    {
        unsigned current;
        myStream >> current;
        add(current);
    }
}

void SetByString::copyFrom(const SetByString& other)
{
    str = new char[strlen(other.str) + 1];
    strcpy(str, other.str);
}

void SetByString::free()
{
    delete[] str;
    str = nullptr;
}

// Конструктор на SetByString, инициализиращ множеството и низа
SetByString::SetByString(unsigned n, const char* data) : DynamicSet(n)
{
    str = new char[strlen(data) + 1]; // Заделя памет за нов низ
    strcpy(str, data); // Копира входния низ в новата памет
    extractNumbersFromString(); // Извлича числата от низа и ги добавя в множеството
}

SetByString::SetByString(const SetByString& other) : DynamicSet(other)
{
    copyFrom(other);
}
void SetByString::moveFrom(SetByString&& other)
{
    str = other.str;
    other.str = nullptr;
}


SetByString::SetByString(SetByString&& other) : DynamicSet(std::move(other))
{
    moveFrom(std::move(other));
}

SetByString& SetByString::operator=(SetByString&& other)
{
    if (this != &other)
    {
        DynamicSet::operator=(std::move(other));
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

SetByString& SetByString::operator=(const SetByString& other)
{
    if (this != &other)
    {
        DynamicSet::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
}

SetByString::~SetByString()
{
    free();
}

bool SetByString::contains(int i) const
{
    return DynamicSet::contains(i); // Използва метода на базовия клас
}

void SetByString::print() const
{
    DynamicSet::print(); // Използва метода на базовия клас
}

// Метод за задаване на нов знак на определена позиция в низа и актуализиране на множеството
void SetByString::setAt(unsigned ind, char ch)
{
    str[ind] = ch; // Задава новия знак
    extractNumbersFromString(); // Актуализира множеството на базата на новия низ
}

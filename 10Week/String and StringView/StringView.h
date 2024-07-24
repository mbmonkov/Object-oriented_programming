#pragma once
#include <iostream>
#include "MyString.h"

// Клас за представяне на подниз от низ
class StringView
{
    const char* _begin;  // Начало на подниза
    const char* _end;    //  1 елемент след последния символ

public:
    // Конструктор, задаващ началото и края на подниза
    StringView(const char* begin, const char* end);

    // Конструктор, задаващ подниз от нулево терминиран низ
    StringView(const char* str);

    // Конструктор, създаващ подниз от MyString
    StringView(const MyString& string);


    size_t length() const;
    char operator[](size_t ind) const;
    StringView substr(size_t from, size_t length) const;

    friend std::ostream& operator<<(std::ostream&, const StringView& strView);
};

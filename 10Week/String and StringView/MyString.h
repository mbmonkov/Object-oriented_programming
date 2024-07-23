#pragma once
#include <iostream>

// Класът MyString представлява собствена имплементация на низ с управление на паметта.
class MyString
{
private:
    char* _data;
    size_t _size;
    size_t _allocatedDataSize;

    // Конструктор, който създава MyString с предварително зададена дължина.
    explicit MyString(size_t stringLength);

    void resize(unsigned newAllocatedDataSize);
    void free();
    void copyFrom(const MyString& other);
    void moveFrom(MyString&& other);

public:
    
    MyString();
    MyString(const char* data);

    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
   
    MyString& operator=(const MyString& other);   
    MyString& operator=(MyString&& other) noexcept;

    ~MyString();

    
    size_t getCapacity() const;
    size_t getSize() const;
    const char* c_str() const;

    
    MyString& operator+=(const MyString& other);

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    
    friend std::ostream& operator<<(std::ostream& os, const MyString& obj);

    friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
    friend std::istream& operator>>(std::istream& is, MyString& ref);
    friend MyString operator+(const MyString& lhs, const MyString& rhs);

    MyString substr(size_t begin, size_t howMany) const;
};

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);

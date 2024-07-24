#pragma once
#include <iostream>
#include <stdexcept>

// Структура, която управлява броячите на shared and weak указатели.
struct Counter
{
    unsigned useCount = 0; // Брояч на споделените указатели.
    unsigned weakCount = 0; // Брояч на слабите указатели.

    // Намалява броя на shared указатели и евентуално weak указатели.
    void removeSharedPtr()
    {
        useCount--;
        if (useCount == 0)
            weakCount--;
    }

    // Намалява броя на weak указатели.
    void removeWeakPtr()
    {
        weakCount--;
    }

    // Увеличава броя на shared указатели и евентуално weak указатели.
    void addSharedPtr()
    {
        useCount++;
        if (useCount == 1)
            weakCount++;
    }

    // Увеличава броя на weak указатели.
    void addWeakPtr()
    {
        weakCount++;
    }
};

// Декларация на шаблонния клас WeakPtr, който ще взаимодейства със SharedPtr.
template <class V>
class WeakPtr;

template <typename T>
class SharedPtr
{
    // Декларация на шаблонния клас WeakPtr, който има достъп до частните членове на SharedPtr.
    template <typename V> friend class WeakPtr;

    T* data; // Указател към управлявания обект.
    Counter* counter; // Указател към структурата за броене на указатели.

    void free(); 
    void copyFrom(const SharedPtr<T>& other); 
    void moveFrom(SharedPtr<T>&& other); 
    SharedPtr(WeakPtr<T>& ptr); // Конструктор, който създава SharedPtr от WeakPtr.

public:
    SharedPtr(); // Конструктор по подразбиране.
    SharedPtr(T* data); // Конструктор, който инициализира SharedPtr с указател към данни.

    SharedPtr(const SharedPtr<T>& other); // Конструктор за копиране.
    SharedPtr& operator=(const SharedPtr<T>& other); // Оператор за присвояване на SharedPtr.

    SharedPtr(SharedPtr<T>&& other); // Конструктор за преместване.
    SharedPtr& operator=(SharedPtr<T>&& other); // Оператор за присвояване чрез преместване.

    const T& operator*() const; // Константен оператор за dereference.
    T& operator*(); // Оператор за dereference.
    const T* operator->() const; // Константен оператор за достъп до члена на обекта.
    T* operator->(); // Оператор за достъп до члена на обекта.

    bool isInitlized() const; // Проверява дали указателят е инициализиран.

    ~SharedPtr(); 
};

template<class T>
inline SharedPtr<T>::SharedPtr(WeakPtr<T>& ptr)
{
    data = ptr.data;
    counter = ptr.counter;
    if (counter)
    {
        counter->addSharedPtr(); // Увеличаване на броя на shared указатели.
    }
}

template <typename T>
void SharedPtr<T>::free()
{
    if (data == nullptr && counter == nullptr)
        return;

    counter->removeSharedPtr(); // Намаляване на броя на shared указатели.

    if (counter->useCount == 0)
        delete data; // Изтриване на данните, ако няма shared указатели.

    if (counter->weakCount == 0)
        delete counter; // Изтриване на броячите, ако няма weak указатели.
}

template <typename T>
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other)
{
    data = other.data;
    counter = other.counter;
    if (counter)
        counter->addSharedPtr(); // Увеличаване на броя на shared указатели.
}

template <typename T>
SharedPtr<T>::SharedPtr()
{
    data = nullptr; 
    counter = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(T* data)
{
    this->data = data; 
    if (this->data)
    {
        counter = new Counter(); // Създаване на нови броячи.
        counter->addSharedPtr(); // Увеличаване на броя на shared указатели.
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
{
    copyFrom(other); 
}

template <typename T>
void SharedPtr<T>::moveFrom(SharedPtr<T>&& other)
{
    data = other.data; 
    other.data = nullptr;

    counter = other.counter; 
    other.counter = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other)
{
    moveFrom(std::move(other)); 
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other)
{
    if (this != &other)
    {
        free(); 
        moveFrom(std::move(other)); 
    }
    return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
    if (this != &other)
    {
        free(); 
        copyFrom(other);
    }
    return *this;
}

template <typename T>
const T& SharedPtr<T>::operator*() const
{
    if (data == nullptr)
    {
        throw std::runtime_error("Pointer not set"); 
    }
    return *data; // Връща стойността на обекта.
}

template <typename T>
T& SharedPtr<T>::operator*()
{
    if (data == nullptr)
    {
        throw std::runtime_error("Pointer not set"); 
    }
    return *data; // Връща стойността на обекта.
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    free(); 
}

template<typename T>
T* SharedPtr<T>::operator->() {
    return data; // Връща указателя към данните.
}

template<typename T>
const T* SharedPtr<T>::operator->() const {
    return data; // Връща указателя към данните (константен).
}

template<typename T>
bool SharedPtr<T>::isInitlized() const
{
    return data != nullptr; // Проверява дали указателят е инициализиран.
}

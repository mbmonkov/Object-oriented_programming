#pragma once
#include "SharedPtr.hpp"
#include <stdexcept>

template <typename T>
class WeakPtr
{
    // Обява на шаблонния клас SharedPtr, който има достъп до частните членове на WeakPtr.
    template<class V> friend class SharedPtr;

    T* data;        // Указател към обекта, на който WeakPtr сочи.
    Counter* counter; // Указател към структурата за броене на референции (Counter), която следи броя на Shared и Weak указатели.

    void copyFrom(const WeakPtr<T>& other);
    void free();
    void moveFrom(WeakPtr<T>&& other);

public:
    WeakPtr(); // Конструктор по подразбиране.

    WeakPtr(SharedPtr<T>& ptr); // Конструктор от SharedPtr.
    WeakPtr(const WeakPtr<T>& other); // Конструктор за копиране.
    WeakPtr& operator=(const WeakPtr<T>& other); // Оператор за присвояване.

    WeakPtr(WeakPtr<T>&& other); // Конструктор за преместване.
    WeakPtr& operator=(WeakPtr<T>&& other); // Оператор за присвояване чрез преместване.
    ~WeakPtr(); // Деструктор.

    // Функции за проверка на съществуването на обекта и за опит за получаване на SharedPtr
    SharedPtr<T> lock() const;
    bool expired() const;
};

template <typename T>
WeakPtr<T>::WeakPtr()
{
    data = nullptr; 
    counter = nullptr;
}

template <typename T>
void WeakPtr<T>::moveFrom(WeakPtr<T>&& other)
{
    data = other.data; 
    other.data = nullptr; 

    counter = other.counter; 
    other.counter = nullptr;
}

template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr<T>&& other)
{
    moveFrom(std::move(other));
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T>&& other)
{
    if (this != &other)
    {
        free(); 
        moveFrom(std::move(other)); 
    }
    return *this;
}

template <typename T>
WeakPtr<T>::WeakPtr(SharedPtr<T>& ptr)
{
    data = ptr.data; 
    counter = ptr.counter; 

    if (counter)
        counter->addWeakPtr(); // Увеличаване на броя на Weak указатели в брояча.
}

template <typename T>
void WeakPtr<T>::copyFrom(const WeakPtr<T>& other)
{
    data = other.data; 
    counter = other.counter; 

    if (counter)
        counter->addWeakPtr(); // Увеличаване на броя на Weak указатели в брояча.
}

template <typename T>
void WeakPtr<T>::free()
{
    if (data == nullptr && counter == nullptr)
        return;

    counter->removeWeakPtr(); // Намаляване на броя на Weak указатели в брояча.
    if (counter->weakCount == 0) // Проверка дали няма повече Weak указатели.
        delete counter; // Ако няма, изтриване на броячите.
}

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr<T>& other)
{
    copyFrom(other); 
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>& other)
{
    if (this != &other)
    {
        free(); 
        copyFrom(other); 
    }
    return *this;
}

template <typename T>
WeakPtr<T>::~WeakPtr()
{
    free(); 
}

template <typename T>
bool WeakPtr<T>::expired() const
{
    return counter && counter->useCount == 0; // Проверка дали обектът е изтекъл (няма повече SharedPtrs).
}

template <typename T>
SharedPtr<T> WeakPtr<T>::lock() const
{
    if (expired())
        return SharedPtr<T>(); // Връща празен SharedPtr ако обектът е изтекъл.
    else
        return SharedPtr<T>(*this); // Връща нов SharedPtr, ако обектът все още съществува.
}

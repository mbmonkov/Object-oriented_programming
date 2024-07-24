#pragma once
#include "SharedPtr.hpp"
#include <stdexcept>

template <typename T>
class WeakPtr
{
    // ����� �� ��������� ���� SharedPtr, ����� ��� ������ �� �������� ������� �� WeakPtr.
    template<class V> friend class SharedPtr;

    T* data;        // �������� ��� ������, �� ����� WeakPtr ����.
    Counter* counter; // �������� ��� ����������� �� ������ �� ���������� (Counter), ����� ����� ���� �� Shared � Weak ���������.

    void copyFrom(const WeakPtr<T>& other);
    void free();
    void moveFrom(WeakPtr<T>&& other);

public:
    WeakPtr(); // ����������� �� ������������.

    WeakPtr(SharedPtr<T>& ptr); // ����������� �� SharedPtr.
    WeakPtr(const WeakPtr<T>& other); // ����������� �� ��������.
    WeakPtr& operator=(const WeakPtr<T>& other); // �������� �� �����������.

    WeakPtr(WeakPtr<T>&& other); // ����������� �� �����������.
    WeakPtr& operator=(WeakPtr<T>&& other); // �������� �� ����������� ���� �����������.
    ~WeakPtr(); // ����������.

    // ������� �� �������� �� �������������� �� ������ � �� ���� �� ���������� �� SharedPtr
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
        counter->addWeakPtr(); // ����������� �� ���� �� Weak ��������� � ������.
}

template <typename T>
void WeakPtr<T>::copyFrom(const WeakPtr<T>& other)
{
    data = other.data; 
    counter = other.counter; 

    if (counter)
        counter->addWeakPtr(); // ����������� �� ���� �� Weak ��������� � ������.
}

template <typename T>
void WeakPtr<T>::free()
{
    if (data == nullptr && counter == nullptr)
        return;

    counter->removeWeakPtr(); // ���������� �� ���� �� Weak ��������� � ������.
    if (counter->weakCount == 0) // �������� ���� ���� ������ Weak ���������.
        delete counter; // ��� ����, ��������� �� ��������.
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
    return counter && counter->useCount == 0; // �������� ���� ������� � ������� (���� ������ SharedPtrs).
}

template <typename T>
SharedPtr<T> WeakPtr<T>::lock() const
{
    if (expired())
        return SharedPtr<T>(); // ����� ������ SharedPtr ��� ������� � �������.
    else
        return SharedPtr<T>(*this); // ����� ��� SharedPtr, ��� ������� ��� ��� ����������.
}

#pragma once
#include <iostream>
#include <stdexcept>

// ���������, ����� ��������� �������� �� shared and weak ���������.
struct Counter
{
    unsigned useCount = 0; // ����� �� ����������� ���������.
    unsigned weakCount = 0; // ����� �� ������� ���������.

    // �������� ���� �� shared ��������� � ���������� weak ���������.
    void removeSharedPtr()
    {
        useCount--;
        if (useCount == 0)
            weakCount--;
    }

    // �������� ���� �� weak ���������.
    void removeWeakPtr()
    {
        weakCount--;
    }

    // ��������� ���� �� shared ��������� � ���������� weak ���������.
    void addSharedPtr()
    {
        useCount++;
        if (useCount == 1)
            weakCount++;
    }

    // ��������� ���� �� weak ���������.
    void addWeakPtr()
    {
        weakCount++;
    }
};

// ���������� �� ��������� ���� WeakPtr, ����� �� ������������� ��� SharedPtr.
template <class V>
class WeakPtr;

template <typename T>
class SharedPtr
{
    // ���������� �� ��������� ���� WeakPtr, ����� ��� ������ �� �������� ������� �� SharedPtr.
    template <typename V> friend class WeakPtr;

    T* data; // �������� ��� ������������ �����.
    Counter* counter; // �������� ��� ����������� �� ������ �� ���������.

    void free(); 
    void copyFrom(const SharedPtr<T>& other); 
    void moveFrom(SharedPtr<T>&& other); 
    SharedPtr(WeakPtr<T>& ptr); // �����������, ����� ������� SharedPtr �� WeakPtr.

public:
    SharedPtr(); // ����������� �� ������������.
    SharedPtr(T* data); // �����������, ����� ������������ SharedPtr � �������� ��� �����.

    SharedPtr(const SharedPtr<T>& other); // ����������� �� ��������.
    SharedPtr& operator=(const SharedPtr<T>& other); // �������� �� ����������� �� SharedPtr.

    SharedPtr(SharedPtr<T>&& other); // ����������� �� �����������.
    SharedPtr& operator=(SharedPtr<T>&& other); // �������� �� ����������� ���� �����������.

    const T& operator*() const; // ���������� �������� �� dereference.
    T& operator*(); // �������� �� dereference.
    const T* operator->() const; // ���������� �������� �� ������ �� ����� �� ������.
    T* operator->(); // �������� �� ������ �� ����� �� ������.

    bool isInitlized() const; // ��������� ���� ���������� � �������������.

    ~SharedPtr(); 
};

template<class T>
inline SharedPtr<T>::SharedPtr(WeakPtr<T>& ptr)
{
    data = ptr.data;
    counter = ptr.counter;
    if (counter)
    {
        counter->addSharedPtr(); // ����������� �� ���� �� shared ���������.
    }
}

template <typename T>
void SharedPtr<T>::free()
{
    if (data == nullptr && counter == nullptr)
        return;

    counter->removeSharedPtr(); // ���������� �� ���� �� shared ���������.

    if (counter->useCount == 0)
        delete data; // ��������� �� �������, ��� ���� shared ���������.

    if (counter->weakCount == 0)
        delete counter; // ��������� �� ��������, ��� ���� weak ���������.
}

template <typename T>
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other)
{
    data = other.data;
    counter = other.counter;
    if (counter)
        counter->addSharedPtr(); // ����������� �� ���� �� shared ���������.
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
        counter = new Counter(); // ��������� �� ���� ������.
        counter->addSharedPtr(); // ����������� �� ���� �� shared ���������.
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
    return *data; // ����� ���������� �� ������.
}

template <typename T>
T& SharedPtr<T>::operator*()
{
    if (data == nullptr)
    {
        throw std::runtime_error("Pointer not set"); 
    }
    return *data; // ����� ���������� �� ������.
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    free(); 
}

template<typename T>
T* SharedPtr<T>::operator->() {
    return data; // ����� ��������� ��� �������.
}

template<typename T>
const T* SharedPtr<T>::operator->() const {
    return data; // ����� ��������� ��� ������� (����������).
}

template<typename T>
bool SharedPtr<T>::isInitlized() const
{
    return data != nullptr; // ��������� ���� ���������� � �������������.
}

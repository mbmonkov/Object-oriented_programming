#include <iostream>

// Декларация на шаблонен клас UniquePointer
template <typename T>
class UniquePointer
{
    T* ptr; // Вътрешен указател към управляемия ресурс

public:
    // Конструктор, който приема указател към ресурс
    UniquePointer(T* ptr);

    // Забранява копирането на уникалния указател
    UniquePointer(const UniquePointer&) = delete;
    UniquePointer& operator=(const UniquePointer&) = delete;

    // Разрешава прехвърляне на собствеността чрез "move semantics"
    UniquePointer(UniquePointer&&) noexcept;
    UniquePointer& operator=(UniquePointer&&) noexcept;

    // оператори
    T& operator*();
    const T& operator*() const;

    T* operator->();
    const T* operator->() const;

    // Деструктор
    ~UniquePointer();
};

// Определение на конструктора, който инициализира указателя
template <typename T>
UniquePointer<T>::UniquePointer(T* ptr) : ptr(ptr)
{}

// Определение на конструктора за прехвърляне на собственост (move constructor)
template <typename T>
UniquePointer<T>::UniquePointer(UniquePointer<T>&& other) noexcept
{
    ptr = other.ptr; 
    other.ptr = nullptr; 
}

// Определение на оператора за прехвърляне на собственост (move assignment operator)
template <typename T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer<T>&& other) noexcept
{
    if (this != &other)
    {
        delete ptr; // Освобождава текущия ресурс, ако има такъв
        ptr = other.ptr; // Прехвърля указателя от другия обект
        other.ptr = nullptr; // Нулира указателя на другия обект
    }
    return *this;
}

// Определение на оператора * (dereference operator) за достъп до управляемия ресурс
template <typename T>
T& UniquePointer<T>::operator*()
{
    return *ptr;
}

// Определение на константната версия на оператора * (dereference operator) за достъп до управляемия ресурс
template <typename T>
const T& UniquePointer<T>::operator*() const
{
    return *ptr;
}

// Определение на оператора -> (member access operator) за достъп до членове на управляемия ресурс
template <typename T>
T* UniquePointer<T>::operator->()
{
    return ptr; // Връща указателя, а не разменната стойност
}

// Определение на константната версия на оператора -> (member access operator) за достъп до членове на управляемия ресурс
template <typename T>
const T* UniquePointer<T>::operator->() const
{
    return ptr; // Връща указателя, а не разменната стойност
}

// Определение на деструктора, който освобождава управляемия ресурс
template <typename T>
UniquePointer<T>::~UniquePointer()
{
    delete ptr; // Освобождава управляемия ресурс, ако има такъв
}

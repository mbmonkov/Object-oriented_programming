#include <iostream>
#include <memory>

template <typename T, const unsigned S>
class MyStack
{
private:
    T arr[S];
    size_t size = 0;
public:

    void push(const T& obj)
    {
        if (size >= S)
            return;
        arr[size++] = obj;
    }
    void push(T&& obj)
    {
        if (size >= S)
            return;
        arr[size++] = std::move(obj);
    }

    const T& peek() const
    {
        if (isEmpty())
            throw std::out_of_range("Error!");

        return arr[size - 1];
    }
    void pop()
    {
        if (isEmpty())
            throw std::out_of_range("Error!");
        size--;
    }

    bool isEmpty() const
    {
        return size == 0;
    }
};

// Шаблонен клас (подобен на std::optional)
template <typename T>
class Optional
{
private:
    T* data = nullptr; // Указател към данните

    // Копиране на данните от друг Optional обект
    void copyFrom(const Optional<T>& other)
    {
        if (other.data)
            data = new T(*other.data); // Копиране на данните
        else
            data = nullptr;
    }

    // Освобождаване на паметта
    void free()
    {
        delete data;
    }

public:
    // Конструктор по подразбиране
    Optional() = default;

    // Конструктор с копиране на стойност
    Optional(const T& value)
    {
        data = new T(value); // Копиране на стойността
    }

    // Конструктор с преместена стойност
    Optional(T&& value)
    {
        data = new T(std::move(value)); // Преместване на стойността
    }

    // Оператор за присвояване (копиране)
    Optional<T>& operator=(const Optional<T>& other)
    {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
    }

    // Оператор за разрeшаване на стойността
    const T& operator*() const
    {
        if (!data)
            throw std::runtime_error("No value stored");
        return *data;
    }
    T& operator*()
    {
        if (!data)
            throw std::runtime_error("No value stored");
        return *data;
    }

    // Задаване на нова стойност (копиране)
    void setValue(const T& value)
    {
        delete data;
        data = new T(value);
    }

    // Задаване на нова стойност (преместване)
    void setValue(T&& value)
    {
        delete data;
        data = new T(std::move(value));
    }

    // Нулиране на стойността
    void reset()
    {
        delete data;
        data = nullptr;
    }

    // Оператор за проверка дали има стойност
    operator bool() const
    {
        return data != nullptr;
    }
};

// Шаблонен клас  (подобен на std::shared_ptr)
template <typename T>
class SharedPtr
{
private:
    T* data;             // Указател към данните
    unsigned* pointersCount; // Брояч на указателите

    // Освобождаване на ресурси
    void free()
    {
        if (*pointersCount == 1)
        {
            delete data;
            delete pointersCount;
        }
        else
            (*pointersCount)--;
    }

    // Копиране на ресурсите от друг SharedPtr обект
    void copyFrom(const SharedPtr<T>& other)
    {
        data = other.data;
        pointersCount = other.pointersCount;
        (*pointersCount)++;
    }

public:
    // Конструктор с данни
    SharedPtr(T* data)
    {
        this->data = data;
        pointersCount = new unsigned(1);
    }

    // Конструктор за копиране
    SharedPtr(const SharedPtr<T>& other)
    {
        copyFrom(other);
    }

    // Оператор за присвояване (копиране)
    SharedPtr& operator=(const SharedPtr<T>& other)
    {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
    }

    // Оператор за разрeшаване на данните
    const T& operator*() const
    {
        return *data;
    }

    T& operator*()
    {
        return *data;
    }

    // Деструктор
    ~SharedPtr()
    {
        free();
    }
};

// Шаблонен клас за двойка от стойности
template <class T, class D>
class Pair
{
private:
    T first;  // Първата стойност
    D second; // Втората стойност

public:
    // Конструктор с копиране на стойности
    Pair(const T& first, const D& second) : first(first), second(second)
    {}

    // Конструктор с преместени стойности
    Pair(T&& first, D&& second) : first(std::move(first)), second(std::move(second))
    {}

    // Получаване на първата стойност
    const T& getFirst() const
    {
        return first;
    }

    // Получаване на втората стойност
    const D& getSecond() const
    {
        return second;
    }

    // Задаване на първата стойност (копиране)
    void setFirst(const T& first)
    {
        this->first = first;
    }

    // Задаване на първата стойност (преместване)
    void setFirst(T&& first)
    {
        this->first = std::move(first);
    }

    // Задаване на втората стойност (копиране)
    void setSecond(const D& second)
    {
        this->second = second;
    }

    // Задаване на втората стойност (преместване)
    void setSecond(D&& second)
    {
        this->second = std::move(second);
    }
};

// Шаблонен клас 
template <typename T, typename D, typename K>
class Tripple
{
private:
    Pair<Pair<T, D>, K> data; // Тройка, състояща се от двойка и допълнителна стойност
};

int main()
{
    // Пример за използване на Pair
    Pair<int, char> qq(3, 'D');
    std::cout << "First: " << qq.getFirst() << ", Second: " << qq.getSecond() << std::endl;
}

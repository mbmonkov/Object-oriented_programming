#include <iostream>
#include <exception>

template <typename T>
class MyQueue
{
private:
    T* data;                // Динамичен масив за съхранение на елементите на опашката
    size_t capacity;        // Капацитет на масива
    size_t size;            // Текущ размер на опашката

    size_t get;             // Индекс за четене от опашката
    size_t put;             // Индекс за добавяне в опашката

    void resize();          // Метод за разширяване на капацитета на опашката

    void moveFrom(MyQueue<T>&& other);  // Метод за прехвърляне на ресурси от друг обект (RVO)
    void copyFrom(const MyQueue<T>& other);  // Метод за копиране на ресурси от друг обект
    void free();           // Метод за освобождаване на динамичната памет
public:
    MyQueue();             // Конструктор по подразбиране

    MyQueue(const MyQueue<T>& other);   // Конструктор за копиране
    MyQueue<T>& operator=(const MyQueue<T>& other);  // Оператор за присвояване на копие

    MyQueue(MyQueue<T>&& other);  // Конструктор за прехвърляне
    MyQueue<T>& operator=(MyQueue<T>&& other);  // Оператор за присвояване на прехвърляне

    void push(const T& obj);  // Метод за добавяне на елемент в опашката
    void push(T&& obj);       // Метод за добавяне на елемент в опашката (преместване)

    void pop();               // Метод за премахване на елемент от опашката

    const T& peek() const;    // Метод за получаване на елемента на върха на опашката (без да го премахва)
    bool isEmpty() const;     // Метод за проверка дали опашката е празна

    ~MyQueue();               // Деструктор
};

// Конструктор по подразбиране
template <typename T>
MyQueue<T>::MyQueue() : capacity(4), size(0), get(0), put(0)
{
    data = new T[capacity];  // Инициализиране на динамичния масив с капацитет 4
}

// Метод за добавяне на елемент в опашката (копиране)
template <typename T>
void MyQueue<T>::push(const T& obj)
{
    if (size == capacity)
        resize();  // Увеличаване на капацитета, ако опашката е пълна

    data[put] = obj;  // Копиране на обекта в опашката
    (++put) %= capacity;  // Цикличен индекс за добавяне
    size++;  // Увеличаване на размера
}

// Метод за добавяне на елемент в опашката (преместване)
template <typename T>
void MyQueue<T>::push(T&& obj)
{
    if (size == capacity)
        resize();  // Увеличаване на капацитета, ако опашката е пълна

    data[put] = std::move(obj);  // Преместване на обекта в опашката
    (++put) %= capacity;  // Цикличен индекс за добавяне
    size++;  // Увеличаване на размера
}

// Метод за проверка дали опашката е празна
template <typename T>
bool MyQueue<T>::isEmpty() const
{
    return size == 0;
}

// Метод за получаване на елемента на върха на опашката
template <typename T>
const T& MyQueue<T>::peek() const
{
    if (isEmpty())
        throw std::logic_error("Empty queue!");  // Хвърля изключение ако опашката е празна

    return data[get];  // Връща елемента на върха на опашката
}

// Метод за премахване на елемент от опашката
template <typename T>
void MyQueue<T>::pop()
{
    if (isEmpty())
        throw std::logic_error("Empty queue!");  // Хвърля изключение ако опашката е празна

    (++get) %= capacity;  // Цикличен индекс за премахване
    size--;  // Намалява размера
}

// Метод за разширяване на капацитета на опашката
template <typename T>
void MyQueue<T>::resize()
{
    T* resizedData = new T[capacity * 2];  // Създаване на нов масив с два пъти по-голям капацитет
    for (size_t i = 0; i < size; i++)
    {
        resizedData[i] = std::move(data[get]);  // Преместване на елементите в новия масив
        (++get) %= capacity;  // Цикличен индекс за четене
    }
    capacity *= 2;  // Увеличаване на капацитета
    delete[] data;  // Освобождаване на стария масив
    data = resizedData;  // Присвояване на новия масив
    get = 0;  // Нулиране на индекса за четене
    put = size;  // Присвояване на индекса за добавяне
}

// Метод за копиране на ресурсите от друг обект
template <typename T>
void MyQueue<T>::copyFrom(const MyQueue<T>& other)
{
    data = new T[other.capacity];  // Създаване на нов масив с капацитета на другия обект
    for (size_t i = 0; i < other.size; i++)
        data[i] = other.data[(other.get + i) % other.capacity];  // Копиране на елементите
    get = 0;  // Нулиране на индекса за четене
    put = other.size;  // Присвояване на индекса за добавяне

    size = other.size;  // Копиране на размера
    capacity = other.capacity;  // Копиране на капацитета
}

// Метод за прехвърляне на ресурсите от друг обект
template <typename T>
void MyQueue<T>::moveFrom(MyQueue<T>&& other)
{
    get = other.get;  // Присвояване на индекса за четене
    put = other.put;  // Присвояване на индекса за добавяне

    size = other.size;  // Присвояване на размера
    capacity = other.capacity;  // Присвояване на капацитета

    data = other.data;  // Присвояване на указателя за данни
    other.data = nullptr;  // Избягване на двойно освобождаване на памет
    other.size = other.capacity = 0;  // Нулиране на данните на другия обект
}

// Метод за освобождаване на динамичната памет
template <typename T>
void MyQueue<T>::free()
{
    delete[] data;
}

// Конструктор за копиране
template <typename T>
MyQueue<T>::MyQueue(const MyQueue<T>& other)
{
    copyFrom(other);  // Копиране на ресурсите
}

// Оператор за присвояване на копие
template <typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue<T>& other)
{
    if (this != &other)
    {
        free();  // Освобождаване на старите ресурси
        copyFrom(other);  // Копиране на новите ресурси
    }
    return *this;
}

// Конструктор за прехвърляне
template <typename T>
MyQueue<T>::MyQueue(MyQueue<T>&& other)
{
    moveFrom(std::move(other));  // Прехвърляне на ресурсите
}

// Оператор за присвояване на прехвърляне
template <typename T>
MyQueue<T>& MyQueue<T>::operator=(MyQueue<T>&& other)
{
    if (this != &other)
    {
        free();  // Освобождаване на старите ресурси
        moveFrom(std::move(other));  // Прехвърляне на новите ресурси
    }
    return *this;
}

// Деструктор
template <typename T>
MyQueue<T>::~MyQueue()
{
    free();  // Освобождаване на динамичната памет
}

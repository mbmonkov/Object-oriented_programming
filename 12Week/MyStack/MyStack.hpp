#include <iostream>
#include <stdexcept>  // За std::out_of_range
#include <utility>    // За std::move

// Шаблонен клас MyStack
template <typename T, const unsigned S>
class MyStack
{
private:
    T arr[S];          // Масив с фиксиран размер S, в който се съхраняват елементите на стека
    size_t size = 0;   // Текущ размер на стека (брой елементи)

public:
    // Метод за добавяне на елемент в стека (копираща версия)
    void push(const T& obj);

    // Метод за добавяне на елемент в стека (версия с прехвърляне)
    void push(T&& obj);

    // Метод за връщане на елемента на върха на стека (без да го премахва)
    const T& peek() const;

    // Метод за премахване на елемента от върха на стека
    void pop();

    // Метод за проверка дали стекът е празен
    bool isEmpty() const;
};


template <typename T, const unsigned S>
void MyStack<T, S>::push(const T& obj)
{
	if (size >= S)
		return;
	arr[size++] = obj;
}

template <typename T, const unsigned S>
void MyStack<T, S>::push(T&& obj)
{
	if (size >= S)
		return;
	arr[size++] = std::move(obj);
}

template <typename T, const unsigned S>
const T& MyStack<T, S>::peek() const
{
	if (isEmpty())
		throw std::out_of_range("Error!");

	return arr[size - 1];
}

template <typename T, const unsigned S>
void MyStack<T, S>::pop()
{
	if (isEmpty())
		throw std::out_of_range("Error!");
	size--;
}

template <typename T, const unsigned S>
bool MyStack<T, S>::isEmpty() const
{
	return size == 0;
}
using namespace std;  
#include <iostream>  

#include "Rectangle.h"
#include "Circle.h"  
#include "Triangle.h" 

void printAreas(const Shape* const* shapes, size_t shapesCount)
{
	for (int i = 0; i < shapesCount; i++) 
		cout << shapes[i]->getArea() << endl;  // Извиква метода getArea() на всяка фигура и отпечатва резултата
}

void printPers(const Shape* const* shapes, size_t shapesCount)
{
	for (int i = 0; i < shapesCount; i++)  
		cout << shapes[i]->getPer() << endl;  // Извиква метода getPer() на всяка фигура и отпечатва резултата
}

void checkPointIn(const Shape* const* shapes, size_t shapesCount, int x, int y)
{
	for (int i = 0; i < shapesCount; i++) 
		cout << shapes[i]->isPointIn(x, y) << endl;  // Извиква метода isPointIn() на всяка фигура с координатите на точката и отпечатва резултата
}

void freeCollection(Shape** shapes, size_t shapesCount)
{
	for (int i = 0; i < shapesCount; i++)  // Итерация през всички фигури
		delete shapes[i];  // Изтрива всяка фигура
	delete[] shapes;  // Изтрива масива от указатели
}

int main()
{
	Shape** arr = new Shape * [4];  // Създава масив от указатели към Shape с размер 4

	// FACTORY
	//
	arr[0] = new Rectangle(3, 4, 6, 8);  // Създава нов Rectangle и го добавя в масива
	arr[1] = new Circle(3, 3, 4);  // Създава нов Circle и го добавя в масива
	arr[2] = new Circle(1, 4, 5);  // Създава нов Circle и го добавя в масива
	arr[3] = new Triangle(1, 1, 2, 2, 3, 3);  // Създава нов Triangle и го добавя в масива
	//
	// 

	printAreas(arr, 4);
	std::cout << endl;

	printPers(arr, 4);
	std::cout << endl;  

	// Проверява дали точка с координати (3, 3) е вътре в някоя от фигурите и отпечатва резултата
	checkPointIn(arr, 4, 3, 3);

	//
}
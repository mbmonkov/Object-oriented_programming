#include "Circle.h"
#include "ColouredCircle.h"
#include "Rectangle.h"

#include <iostream>

void addNewShape(const Shape* shape, Shape* shapes[], size_t& count)
{
	shapes[count++] = shape->clone();
}

void testVirtualFunctions()
{
	Circle c(0, 0, 3);
	Shape* sptr = &c;
	// динамично свързване
	std::cout << sptr->getArea() << "\n";
	// статично свързване
	sptr->print();

	Circle* cptr = &c;
	std::cout << cptr->getArea() << "\n";

	// обръщение с псевдоним
	Shape& sref = c;
	std::cout << sref.getArea() << "\n";

	Circle& cref = c;
	std::cout << cref.getArea() << "\n";

	// абстрактен клас
	// не можем да създадем обекти от този клас
	//Shape shape = c;
	//std::cout << shape.getArea() << "\n";

	ColouredCircle cc(1, 1, 2, "red");
	
	ColouredCircle* ptrCC = &cc;
	// статично свързване на виртуална функция
	std::cout << ptrCC->Circle::getArea() << "\n";

	Shape& refCC = cc;
	// динамично свързване
	std::cout << refCC.getArea() << "\n";
}

void testVirtualDestructor()
{
	Circle* coloredCircle = new ColouredCircle(1, 1, 2, "blue");
	coloredCircle->print();
	delete coloredCircle;
}

void testPolymorphicArray()
{
	// полиморфен контейнер
	Shape* abstractPainting[10];
	size_t count = 0;

	Circle c(0, 0, 3);
	ColouredCircle cc(1, 1, 2, "red");
	Rectangle rect(Point(1, 1), 2, 3);

	addNewShape(&c, abstractPainting, count);
	addNewShape(&cc, abstractPainting, count);
	addNewShape(&rect, abstractPainting, count);

	for (size_t i = 0; i < count; ++i)
	{
		std::cout << "--- Shape[" << i << "] ---\n";
		abstractPainting[i]->print();
	}

	for (size_t i = 0; i < count; ++i)
	{
		delete abstractPainting[i];
	}
}

int main()
{
	//testVirtualFunctions();
	//testVirtualDestructor();
	testPolymorphicArray();

	return 0;
}



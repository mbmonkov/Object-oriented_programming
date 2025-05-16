#include "Rectangle.h"

Rectangle::Rectangle(const Point& topLeft, unsigned width, unsigned height)
	: topLeft(topLeft), width(width), height(height)
{
}

double Rectangle::getArea() const
{
	return width * height;
}

Shape::Type Rectangle::getType() const
{
	return Shape::RECTANGLE;
}

Rectangle* Rectangle::clone() const
{
	return new Rectangle(*this);
}

void Rectangle::printOwn() const
{
	std::cout << "Top left: "; topLeft.print();
	std::cout << "width = " << width << ", height = " << height << "\n";
}

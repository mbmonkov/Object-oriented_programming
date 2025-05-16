#pragma once

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(const Point& topLeft, unsigned width, unsigned height);

	virtual double getArea() const override;
	virtual Shape::Type getType() const override;
	virtual Rectangle* clone() const override;

protected:
	virtual void printOwn() const;

private:
	Point topLeft;
	unsigned width;
	unsigned height;
};

#endif // !RECTANGLE_H

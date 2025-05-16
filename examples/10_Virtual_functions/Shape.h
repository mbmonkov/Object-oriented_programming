#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>

class Shape
{
public:
	enum Type
	{
		CIRCLE,
		COLOUR_CIRCLE, 
		RECTANGLE
	};

public:
	void print() const
	{
		static const char* types[] = { "circle", "coloured circle", "rectangle" };

		std::cout
			<< "Type: " << types[this->getType()]
			<< ", Area: " << this->getArea()
			<< std::endl;

		printOwn();
	}

public:
	virtual ~Shape() = default;

	virtual Shape* clone() const = 0;
	virtual double getArea() const = 0;
	virtual Type getType() const = 0;

protected:
	virtual void printOwn() const = 0;
};

#endif // !SHAPE_H

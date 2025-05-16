#include <iostream>

#include "Object.h"

int Object::liveObjCount = 0;
int Object::nextID = 1;

Object::Object(int val)
	: value(val), id(Object::getNextID())
{
	++liveObjCount;
}

Object::Object(const Object& o)
	: value(o.value), id(Object::getNextID())
{
	++liveObjCount;
}

Object& Object::operator=(const Object& o)
{
	if (this != &o)
	{
		this->value = o.value;
	}

	return *this;
}

Object::~Object()
{
	--liveObjCount;
}

int Object::getNextID()
{
	int id = nextID;
	nextID += step;
	return id;
}

void printID(const Object& o)
{
	std::cout << "ID: " << o.id << std::endl;
}

// всички член-функции на класа FileWriter имат достъп
// до private компонентите на класа Object
void FileWriter::printToFile(const Object& obj, std::ostream& out)
{
	out << obj.id << '\t' << obj.value << '\n';
}

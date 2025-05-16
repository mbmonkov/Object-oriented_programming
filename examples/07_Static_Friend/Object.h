#pragma once

#ifndef OBJECT_H
#define OBJECT_H

// forward декларация, необхофима за printToFile
class Object;

class FileWriter
{
public:
	void printToFile(const Object&, std::ostream& out = std::cout);
};

class Object
{
	// приятелска функция
	friend void printID(const Object&);
	
	// приятелски клас
	// friend class FileWriter;

	// приятелска член-функция на клас
	friend void FileWriter::printToFile(const Object&, std::ostream& out);

public:
	Object(int val);
	Object(const Object& o);
	Object& operator=(const Object& o);
	~Object();

	int getValue() const { return value; }
	void setValue(int newVal) { value = newVal; }

public:
	static int getLiveObjects() { return liveObjCount; }
	static int getNextID();

private:
	static int liveObjCount;
	static int nextID;
	static const int step = 3;

private:
	int value;
	const int id;
};

#endif // !OBJECT_H
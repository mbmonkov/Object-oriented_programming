#ifndef PERSON_H
#define PERSON_H

#include <iostream>

using std::cout;
using std::endl;

#include <string>

class Person
{
public:
    Person(const char* name) : name(name)
    {}

    virtual ~Person()
    {}

    const char* getName() const
    {
        return name.c_str();
    }

    void setName(const char* name)
    {
		if(name)
			this->name = name;
    }

    virtual void info() const
    {
        cout << name << endl;
    }
	
private:
    std::string name;
};

#endif // PERSON_H

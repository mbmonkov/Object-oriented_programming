#ifndef STUDENT_H
#define STUDENT_H

#include "Person.hpp"

class Student : virtual public Person
{
public:
    Student(int fn, const char* name) : Person(name)
    {
        this->fn = fn;
    }

    virtual void info() const
    {
        cout << "FN: " << getFn() << " name: " << getName() << endl;
    }

    int getFn() const
    {
        return fn;
    }

protected:
    int fn;
};

#endif // STUDENT_H

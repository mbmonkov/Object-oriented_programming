#ifndef MASTER_H
#define MASTER_H

#include "Student.hpp"
#include "Employee.hpp"

class Master : public Student
{
public:
    Master(const char* spec, const char* name, int fn)
        : Person(name)
        , Student(fn, name)
        , spec(spec)
    {
    }

    virtual void info()const
    {
        cout << "Master at: " << spec << endl;
        Student::info();
    }
protected:
    std::string spec;
};

#endif // MASTER_H

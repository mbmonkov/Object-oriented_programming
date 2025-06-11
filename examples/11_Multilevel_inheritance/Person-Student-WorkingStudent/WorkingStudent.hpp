#ifndef WORKING_STUDENT_H
#define WORKING_STUDENT_H

#include "Student.hpp"
#include "Employee.hpp"

class WorkingStudent : public Employee, public Student
{
public:
    WorkingStudent(const char* name, int fn, double sal)
        : Person(name)
        , Employee(sal, name)
        , Student(fn, name)
    {
    }

    virtual void info()const
    {
        cout << "-- Working student: " << endl;
        Student::info();
        Employee::info();
    }
};

#endif // WORKING_STUDENT_H

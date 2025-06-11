#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.hpp"

#include <cmath>

class Employee : virtual public Person
{
public:
    Employee(double salary, const char* name) : Person(name)
    {
        setSalary(salary);
    }

    void setSalary(double sal)
    {
        salary = fabs(sal);
    }

    double getSalary() const
    {
        return salary;
    }

    virtual void info() const
    {
        cout << "I'm " << getName() << " and my salary is " << getSalary() << endl;
    }

protected:
    double salary;
};

#endif // EMPLOYEE_H

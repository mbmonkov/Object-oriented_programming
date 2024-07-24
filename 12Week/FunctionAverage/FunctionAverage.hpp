#pragma once

// Декларация на шаблонен клас IntFunctionAverage, който приема два типа функции
template<class FunctionOne, class FunctionTwo>
class IntFunctionAverage
{
private:
    FunctionOne first;  // Член-променлива за първата функция или функционален обект от тип FunctionOne
    FunctionTwo second; // Член-променлива за втората функция или функционален обект от тип FunctionTwo

public:
    // Конструктор на класа, инициализира първата и втората функция
    IntFunctionAverage(const FunctionOne& fOne, const FunctionTwo& fTwo) : first(fOne),  second(fTwo) {}

    // Метод за изчисляване на средната стойност на резултатите от двете функции
    double average(int x) const
    {
        return (first(x) + second(x)) / 2.0; // Изчислява средната стойност от резултатите на first и second
    }
};

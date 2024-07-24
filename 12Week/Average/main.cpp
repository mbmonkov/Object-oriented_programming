#include <iostream> 

// Шаблонен клас FuncAverage, който комбинира две функции и изчислява средната стойност от тях
template <class Func1Type, class Func2Type>
class FuncAverage
{
    Func1Type f1; // Първата функция (или функционален обект)
    Func2Type f2; // Втората функция (или функционален обект)

public:
    // Конструктор, който приема две функции и ги инициализира
    FuncAverage(const Func1Type& f1, const Func2Type& f2) : f1(f1), f2(f2) {}

    // Оператор () за изчисляване на средната стойност от резултатите на двете функции
    double operator()(int x)
    {
        return (f1(x) + f2(x)) / 2.0;
    }
};

// Клас, който дефинира функционален обект
class FuncWithContext
{
    int a;
    int b;
    int c;
public:
    // Оператор () на класа FuncWithContext, който връща самия входен параметър
    int operator()(int x)
    {
        return x;
    }
};

int main()
{
    FuncWithContext myFunc; // Създава обект на FuncWithContext

    // Създава обект на шаблонен клас FuncAverage, като първият аргумент е ламбда функция, а вторият е myFunc
    FuncAverage<int(*)(int), FuncWithContext> f([](int x) {return x; }, myFunc);

    // Извиква FuncAverage с аргумент 10 и извежда резултата
    std::cout << f(10);
}

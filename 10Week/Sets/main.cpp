#include <iostream>
#include "SetByCriteria.h"
#include "SetByString.h"

int main()
{
    // Създаване на SetByString с максимален брой елементи 1000 и начален низ "1 5 9"
    SetByString s(1000, "1 5 9");

    s.print();
    s.setAt(1, '0');
    s.print();

    // Създаване на SetByCriteria с максимален брой елементи 11 и критерий за включване на четни числа
    SetByCriteria s2(11, [](unsigned i) { return i % 2 == 0; });

    s2.print();
}

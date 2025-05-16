#include "Circle.h"
#include "ColouredCircle.h"

#include <iostream>

int main()
{
    ColouredCircle cc(0, 0, 3, "blue");

    std::cout << "============" << std::endl;
    cc.print();

    /// извежда само наследените компоненти
    Circle* pc = &cc;
    pc->print();

    std::cout << "============" << std::endl;

    return 0;
}

int test()
{
    Circle* coloredCircle = new ColouredCircle(1, 1, 2, "blue");
    // кой метод ще се извика тук?
    coloredCircle->print();
    delete coloredCircle;

    return 0;
}

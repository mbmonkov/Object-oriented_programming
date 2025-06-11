#include <iostream>

// проста йерархия с множествено наследяване,
// която има за цел да илюстрира един от възможните проблеми,
// които възникват при МН: наследяване на компоненти с еднакви имена

class Base1
{
    public:
        Base1()
        {
            std::cout << "Base1()" << std::endl;
        }

        void doSmth() const
        {
            std::cout << "Base1::doSmth()" << std::endl;
        }

        ~Base1()
        {
            std::cout << "~Base1()" << std::endl;
        }
};

class Base2
{
    public:
        Base2()
        {
            std::cout << "Base2()" << std::endl;
        }

        int doSmth() const
        {
            std::cout << "Base2::doSmth()" << std::endl;
            return 0;
        }

        ~Base2()
        {
            std::cout << "~Base2()" << std::endl;
        }
};

// производният клас
class Derived: public Base1, private Base2
{
    public:
        // редът на извикване на конструкторите на базовите класове
        // зависи от реда, в който са изброени при декларирането на
        // производния клас, а не от реда в инициализиращия списък
        // на конструктора на производния клас
        Derived(): Base2(), Base1()
        {
            std::cout << "Derived()" << std::endl;
        }

        ~Derived()
        {
            std::cout << "~Derived()" << std::endl;
        }
};

int main()
{
    Derived d;

    // въпреки че класът Base2 е наследен като private
    // и функцията Base2::doSmth() става част от private секцията на Derived
    // и до нея няма достъп, подобно обръщение не може да се изпълни (ambiguous)
    // причината това да не се допуска, че ако се промени нивото на достъп на някоя от функциите
    // смисълът на кода ще се промени
    //d.doSmth();

    d.Base1::doSmth();

    // външният достъп до функцията в класа Base2 не е възможен,
    // защото класът е наследен с атрибут private
    //d.Base2::doSmth();

    return 0;
}

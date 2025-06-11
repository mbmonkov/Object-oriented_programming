#include <iostream>

class A
{
    protected:
        int a;

    public:
        A(int newA): a(newA)
        {}

        void print() const
        {
            std::cout << "&a = " << &a << std::endl;
            std::cout << "A::a = " << a << std::endl;
        }

        ~A()
        {
            std::cout << "~A" << std::endl;
        }
};

class B: virtual public A
{
    protected:
        int b;

		void printOwn() const
		{
            std::cout << "&b = " << &b << std::endl;
            std::cout << "B::b = " << b << std::endl;
		}

    public:
        B(int newA, int newB): A(newA), b(newB)
        {}

        void print() const
        {
            std::cout << "--- B::print() ---" << std::endl;
            A::print();
			printOwn();
            std::cout << "------------------" << std::endl;
        }

        ~B()
        {
            std::cout << "~B" << std::endl;
        }
};

class C: virtual public A
{
    protected:
        int c;

		void printOwn() const
		{
            std::cout << "&c = " << &c << std::endl;
            std::cout << "C::c = " << c << std::endl;
		}

    public:
        C(int newA, int newC): A(newA), c(newC)
        {}

        void print() const
        {
            std::cout << "--- C::print() ---" << std::endl;
            A::print();
			printOwn();
            std::cout << "------------------" << std::endl;
        }

        ~C()
        {
            std::cout << "~C" << std::endl;
        }
};

class D: public B, public C
{
    private:
        // няма собствени член-данни

    public:
        // конструкторът на виртуалния базов клас се извиква в конструкторите 
        // на всички наследници, независимо от кое ниво са

        // обръщение към констукторите на базовите класове
        D(int newA, int newB, int newC): A(newA), B(newA, newB), C(newA, newC)
        {
            // празно тяло, няма собствени член-данни,
            // трябва единствено да извика базовите конструктори
        }

        void print() const
        {
            std::cout << "--- D::print() ---" << std::endl;
			
            // при виртуално наследяване, копието на виртуалния базов клас е само едно
            A::print();
            B::printOwn();
            C::printOwn();

            std::cout << "------------------" << std::endl;
        }

        ~D()
        {
            std::cout << "~D" << std::endl;
        }

};

int main()
{
    D d(1, 2, 3);

    d.print();

    std::cout << "Calling the print function..." << std::endl;
    A* ptrA = &d;
    ptrA->print();

    B* ptrB = &d;
    ptrB->print();

    C* ptrC = &d;
    ptrC->print();

    return 0;
}

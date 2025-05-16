#include "Doctor.h"
#include "String.h"
#include "Patient.h"
#include "PatientS.h"

#include <iostream>
#include <utility>

//
//class A
//{
//	int a;
//
//public:
//	A(int varA)
//		: a(varA)
//	{}
//
//};

//class A
//{
//	int a;
//
//public:
//	A(int varA)
//		: a(varA)
//	{
//	}
//};
//
//class B
//{
//	A a;
//public:
//	
//};

String makeCopy(const char* str)
{
	String copy(str);
	return copy;
}

void f(String s)
{

}

//void f(int& a)
//{
//
//}

//void f(int&& a)
//{
//
//}

void f(const int& a)
{

}

int main()
{
	try
	{
		String s{ "abc" };

		String s1 = s;
		s1 = s;

		// move ctor
		String s2 = std::move(s1);
		
		// след move над s1 можем да приложим само
		// операция за присвояване, move assignment
		s1 = String("BCD");

		String s3 = makeCopy("ABC");
	}
	catch (const char* ex)
	{
		std::cerr << "Error: " << ex;
	}
	catch (const std::bad_alloc& ex)
	{
		std::cerr << "Error: " << ex.what();
	}
	
	return 0;
}

Patient f()
{
	return Patient{ "SB", "1" };
}

int main_()
{
	try
	{
		PatientS so{ "SO", "1234567890" };
		Doctor gp{ "DR" };

		std::cout << "Max patients count: " << Doctor::getMaxPatientsCount() << std::endl;

		if (so.registerTo(gp))
		{
			std::cout << "Doctor ";
			gp.getName().print();
			std::cout << " has a new patient!\n";
		}
		else
		{
			std::cout << "The patient was not registered!\n";
		}

		if (gp.registerNewPatient(so))
		{
			std::cout << "Doctor ";
			gp.getName().print();
			std::cout << " has a new patient!\n";
		}
		else
		{
			std::cout << "The patient was not registered!\n";
		}

		if (so.unregisterFromGP())
		{
			std::cout << "The patient has no GP!\n";
		}
	}
	catch (...)
	{
		std::cerr << "Exception has occurred!";
	}
	
	return 0;

}
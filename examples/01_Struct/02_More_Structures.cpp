#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

struct Address
{
	char city[24];
	char street[20];
	unsigned number;
};

struct Student
{
	char fn[11];
	char name[30];
	int course;
	double grades;

	Address address;
	// Student* mentor;
};

void read(Address& a);
void print(const Address& a);

void read(Student& s);
void print(const Student& s);

struct Array
{
	int arr[10];
};

void f(int a[])
{
	// нямаме копиране на масива, 
	// директно достъпваме елементите му
}

void f(Array a)
{
	// функцията получава копие на масива в структурната променлива а
}

Array f()
{
	Array a = { {0, } };
	// масив, който връщаме като резултат от функция
	return a;
}

Student read()
{
	Student s;
	s.address.city;

	read(s);

	return s;
}

int main()
{
	std::cout << "sizeof(Address): " << sizeof(Address) << std::endl;
	std::cout << "sizeof(Student): " << sizeof(Student) << std::endl;

	Student me;
	read(me);
	print(me);
	
	Student inf[10] = { 
		{"1", "me", 2, 4.50},
		// оценката е 0
		{"2", "you", 2}
		// всички останали елементи на масива са нули
	};

	strcpy(inf[2].address.city, "Sofia");
	std::cout << "\nStudent[2]:\n";
	print(inf[2]);

	return 0;
}

void read(Address& a)
{
	std::cin.getline(a.city, sizeof(a.city));
	std::cin.getline(a.street, sizeof(a.street));
	std::cin >> a.number;
	std::cin.ignore();
}

void print(const Address& a)
{
	std::cout << "\nAddress:\n";
	std::cout << "city: " << a.city << std::endl;
	std::cout << "street: " << a.street << std::endl;
	std::cout << "number: " << a.number << std::endl;
}

void read(Student& s)
{
	std::cin >> s.fn;
	// за да изчисти новия ред
	std::cin.ignore();

	std::cin.getline(s.name, sizeof(s.name));
	std::cin >> s.course;
	std::cin >> s.grades;
	std::cin.ignore();

	read(s.address);
}

void print(const Student& s)
{
	std::cout << "FN: " << s.fn << std::endl;
	std::cout << "Name: " << s.name << std::endl;
	std::cout << "Course: " << s.course << std::endl;
	std::cout << "Grades: " << s.grades << std::endl;

	print(s.address);
}
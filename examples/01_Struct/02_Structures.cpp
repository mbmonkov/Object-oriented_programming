#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

struct Student
{
	// полета, които описват характеристиките на реалния обект
	char fn[11];
	char name[30];
	int course;
	double grades;
};

// 
void read(Student& s);

// параметърът е с псевдоним, директен достъп до структурната променлива
// само за четене обаче
void print(const Student& s);

Student read();

int main()
{
	Student student;
	std::cout << "sizeof(Student): " << sizeof(Student) << std::endl;
	
	// четенето от стандартния вход и извеждането на стандартния изход не са дефинирани
	//std::cin >> me;
	//std::cout << me << std::endl;

	// ние трябва да определим поведението
	read(student);
	print(student);

	// директна инициализация
	Student me = {"42901", "me", 4, 5.78};

	// полетата на структурната променлива се достъпват с оператора .
	std::cout << me.name << std::endl;
	me.grades = 3.40;

	strcpy(me.name, "You");
	std::cout << me.name << std::endl;

	// ако подадем по-малко данни отколкото са полетата на структурата,
	// останалото се инициализира с нули
	Student gosho = { "12345", "Gosho", 1 };
	print(gosho);

	// операция за присвояване, побитово копиране
	me = gosho;
	std::cout << "\n me has been chaged:\n";
	print(me);

	// указател кум структурна променлива
	Student* ptr = &me;
	(*ptr).course = 2;
	// -> за достъп до полетата на структурната променлива през указател
	ptr->course = 3;
	std::cout << "\nPrint through the pointer:\n";
	print(*ptr);

	Student& ref = me;
	ref.grades = 5.75;
	std::cout << "\nPrint through the reference:\n";
	print(ref);

	return 0;
}

void read(Student& s)
{
	std::cin >> s.fn;
	std::cin.ignore();

	std::cin.getline(s.name, 30);
	std::cin >> s.course;
	std::cin >> s.grades;
}

// параметърът е с псевдоним, директен достъп до структурната променлива
// само за четене обаче
void print(const Student& s)
{
	std::cout << "fn: " << s.fn << std::endl;
	std::cout << "name: " << s.name << std::endl;
	std::cout << "course: " << s.course << std::endl;
	std::cout << "grades: " << s.grades << std::endl;
}

Student read()
{
	// структурната променлива е създадена върху стековата рамка на функцията
	Student s;
	read(s);

	// може да се върне само по стойност
	return s;
}
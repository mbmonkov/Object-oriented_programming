#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

int main_writeToFile()
{
	double array[] = { 11.2345, -2.345, 45, 3.456, 5.5, -0.66, 1.77 };
	const size_t count = sizeof(array) / sizeof(array[0]);

	std::ofstream file("numbers.txt", std::ios::out);

	if (!file.is_open())
	{
		std::cerr << "Missing file or no access to the file!";
		return 1;
	}

	for (size_t i = 0; i < count; ++i)
	{
		// форматираме извеждането
		// два символа след десетичния разделител,
		// на поле с дължина 10
		file
			<< std::setiosflags(std::ios::fixed)
			<< std::setprecision(2)
			<< std::setw(10)
			<< array[i];
	}

	file.close();

	return 0;
}

int main_forwardInputOutput()
{
	int arr[] = { 201, 23, 4, 5, 6, 7 };
	const size_t count = sizeof(arr) / sizeof(arr[0]);

	for (size_t i = 0; i < count; ++i)
	{
		std::cout << arr[i] << '\t';
	}

	// не се буферира, извежда се веднага
	std::cerr << "Error has occurred!\n";
	// буферира съдържание
	std::clog << "Log the error!";

	// ако възникне проблем, съръжанието на буфера
	// може да не се изведе
	int five = 5;
	int res = five / (five - 5);

	return 0;
}

void printState(std::ifstream& file)
{
	std::cout
		<< "State: "	<<	file.rdstate()
		<< "\neof: "	<< (file.rdstate() & std::ios::eofbit)
		<< "\nfail: "	<< (file.rdstate() & std::ios::failbit)
		<< "\nbad: "	<< (file.rdstate() & std::ios::badbit)
		<< "\ngood: "	<< (file.rdstate() & std::ios::goodbit)
		<< std::endl;
}

int main_readErrors()
{
	std::ifstream file("numbers-errors.txt");
	if (!file.is_open())
	{
		std::cerr << "Cannot open the file!\n";
		return 1;
	}

	double number = 0;
	while (file)
	{
		file >> number;

		if (file) // file.good()
		{
			std::cout << number << '\t';
		}
		else if (file.eof())
		{
			if (!file.fail())
			{
				// последният запис е прочен,
				// с него е вдигнат флагът за край на файл
				std::cout << number << '\t';
			}

			// вдигнат е и флагът за грешка
			std::cout << "\nDone!\n";
		}
		else if (file.fail())
		{
			std::cout << "Invalid data: removing it...\n";
			file.clear();

			// разделителят между записите е интервал
			char c;
			while (file.get(c) && c != ' ');

			if (!file)
			{
				std::cout << "\nEOF reached while skipping the invalid data!\n";
			}
		}
	}

	std::cout << "\n--- Before closing the file ---\n";
	printState(file);

	// file.clear();
	file.close();

	file.open("numbers-errors.txt");

	std::cout << "\n--- After opening the file again ---\n";
	printState(file);

	return 0;
}

struct Student
{
	char name[28];
	unsigned facNumber;
	double grades;
};

bool read(std::ifstream& file, Student& student);
bool print(std::ostream& file, const Student& student);

int main()//_filter()
{
	std::ifstream source("Students.txt", std::ios::in);
	if (!source.is_open())
	{
		std::cerr << "The input file cannot be opened!\n";
		return -1;
	}

	std::ofstream output("scholarships.txt", std::ios::out);
	if (!output)
	{
		std::cerr << "The output file cannot be opened!\n";
		return -1;
	}

	Student st = {"", };
	while (source)
	{
		if (read(source, st))
		{
			if (st.grades >= 5.50)
			{
				print(output, st);
			}

			print(std::cout, st);
		}
	}

	source.close();
	output.close();

	if (!output)
	{
		std::cerr << "Error while closing the output file!\n";
	}

	return 0;
}

void clearLine(std::ifstream& file)
{
	char c;
	while (file.get(c) && c != '\n');
}

bool isValidGrade(double grade)
{
	return grade >= 2.00 && grade <= 6.00;
}

bool read(std::ifstream& file, Student& student)
{
	char name[28];
	file.getline(name, sizeof(name), '\t');

	if (!file)
	{
		if (file.eof())
			return false;

		// прочетени са sizeof(name) - 1 символа
		file.clear();

		if (file.peek() != '\t')
		{
			std::cerr << "Invalid name!\n";
			clearLine(file);

			return false;
		}

	}

	unsigned number;
	file >> number;

	if (!file)
	{
		std::cerr << "Invalid faculty number!\n";

		file.clear();
		clearLine(file);

		return false;
	}

	double grades;
	file >> grades;

	if (!file || !isValidGrade(grades))
	{
		std::cerr << "Invalid grades!\n";

		file.clear();
		clearLine(file);

		return false;
	}

	// новият ред в края на записа
	file.ignore();

	strcpy(student.name, name);
	student.facNumber = number;
	student.grades = grades;

	return true;
}

bool print(std::ostream& file, const Student& student)
{
	file
		<< student.name << '\t'
		<< student.facNumber << '\t'
		<< student.grades << '\n';

	return file.good();
}


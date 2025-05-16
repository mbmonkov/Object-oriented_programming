#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>

bool fillBinFile(std::fstream& file, const double* array, size_t count);
size_t getFileSize(std::fstream& file);
size_t countElements(std::fstream& file);

void showContent(std::fstream& file);

bool changeElemAt(std::fstream& file, size_t pos, double newValue);

bool changeOnCond(std::fstream& file, bool (*cond)(double), double (*f)(double));

bool validGrade(double grade)
{
	return grade >= 2.00 && grade <= 6.00;
}

double negate(double number)
{
	return -number;
}

int main_numbers()
{
	double arr[] = { 1.23, 2.34, 4.56, 5.67 };
	size_t count = sizeof(arr) / sizeof(arr[0]);

	std::fstream file("numbers.bin",
						std::ios::in | std::ios::out | std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "Cannot open the file!\n";
		return 1;
	}

	bool filled = fillBinFile(file, arr, count);
	if (!filled)
	{
		std::cerr << "Error while writing in the file!\n";
		return 1;
	}

	std::size_t stored = countElements(file);
	if (stored != count)
	{
		std::cout << "Different number of elements is stored!\n";
	}
	else
	{
		std::cout << "All numbers are stored!\n";
		showContent(file);

		if (changeElemAt(file, 3, 7.00))
		{
			std::cout << "\nElement at position 3 has been changed!\n";
			showContent(file);

			bool res = changeOnCond(file, validGrade, negate);
			if (res)
			{
				std::cout << "\nElements have been changed!\n";
				showContent(file);
			}
		}
	}

	file.close();

	if (!file)
	{
		std::cerr << "Error while closing the file!\n";
		return 1;
	}

	return 0;
}

bool fillBinFile(std::fstream& file, const double* array, size_t count)
{
	assert(array);
	assert(file.is_open());

	//for (std::size_t i = 0; i < count; ++i)
	//{
	//	file.write(reinterpret_cast<const char*>(array + i), sizeof(array[i]));
	//}

	file.write(reinterpret_cast<const char*>(array), sizeof(array[0]) * count);

	return file.good();
}

std::size_t getFileSize(std::fstream& file)
{
	assert(file.is_open());

	file.seekp(0, std::ios::end);

	std::streampos pos = file.tellp();
	if (!file || pos == std::streampos(-1))
		return 0;

	return (std::size_t)pos;
}

std::size_t countElements(std::fstream& file)
{
	assert(file.is_open());

	std::size_t fileSize = getFileSize(file);

	assert(fileSize % sizeof(double) == 0);
	return fileSize / sizeof(double);
}

void rewind(std::fstream& file)
{
	file.clear();
	file.seekg(0, std::ios::beg);
}

void showContent(std::fstream& file)
{
	assert(file.is_open());

	rewind(file);

	while (file.good())
	{
		double number;
		file.read(reinterpret_cast<char*>(&number), sizeof(number));

		if (file && file.gcount() == sizeof(number))
		{
			std::cout << number << '\t';
		}
		else if (file) //  file.gcount != sizeof(number)
        {
            std::cerr << "A number was partially read - skip it\n";
            size_t left = sizeof(number) - file.gcount();
            while(file && left > 0) // skip what was not read from number
            {
                file.read(reinterpret_cast<char*>(&number), left);
                left -= file.gcount();
            }
        }
	}
}

bool changeElemAt(std::fstream& file, std::size_t pos, double newValue)
{
	assert(file.is_open());

	if (!file)
		file.clear();

	file.seekp(pos * sizeof(newValue), std::ios::beg);
	if (!file)
		return false;

	file.write(reinterpret_cast<const char*>(&newValue), sizeof(newValue));
	return file.good();
}

bool changeOnCond(std::fstream& file, bool (*cond)(double), double (*f)(double))
{
	assert(file.is_open());

	rewind(file);

	std::streampos readingPos = 0;
	while (file.good())
	{
		double number;

		file.seekg(readingPos, std::ios::beg);
		file.read(reinterpret_cast<char*>(&number), sizeof(number));

		if (file.eof())
		{
			std::cout << "All records have been processed!\n";
			return true;
		}

		if (!file || file.gcount() != sizeof(number))
		{
			std::cerr << "Error ocurred while reading the file!\n";
			return false;
		}

		if (cond(number))
		{
			number = f(number);

			file.seekp((-1) * sizeof(number), std::ios::cur);
			file.write(reinterpret_cast<const char*>(&number), sizeof(number));

			if (!file)
			{
				std::cerr << "Error ocurred while writing in the file!\n";
				return false;
			}
		}

		readingPos = file.tellg();
	}

	return true;
}

// Паметта за името е фиксирана като размер! Предполага се разположение без подравняване!
struct FStudent
{
	char name[28];
	unsigned facNumber;
	double grades;
};

int main_structures()
{
	std::fstream file("Students.bin", std::ios::in | std::ios::out | std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "Cannot open the file!\n";
		return 1;
	}

	// записване на цяла структурна променлива
	FStudent me = { "Me", 123, 4.50 };
	file.write(reinterpret_cast<const char*>(&me), sizeof(me));
	if (file)
	{
		std::cout << "The data have been stored!\n";
	}

	file.seekg(0, std::ios::beg);

	FStudent inFileStudent = { "", };

	// изчитане на информацията от файла
	file.read(reinterpret_cast<char*>(&inFileStudent), sizeof(FStudent));
	if (file && file.gcount() == sizeof(FStudent))
	{
		std::cout
			<< "The stored student was: "
			<< inFileStudent.name << '\t'
			<< inFileStudent.facNumber << '\t'
			<< inFileStudent.grades << '\n';
	}

	file.close();

	return 0;
}

// ако в структурата има указател?
struct Student
{
	char* name;
	unsigned fn;
	double grades;
};

bool store(std::fstream& file, const Student& st)
{
	size_t	len = strlen(st.name);
	file.write(reinterpret_cast<const char*> (&len), sizeof(len));
	file.write(st.name, len);

	file.write(reinterpret_cast<const char*>(&st.fn), sizeof(st.fn));
	file.write(reinterpret_cast<const char*>(&st.grades), sizeof(st.grades));

	return file.good();
}

bool read(std::fstream& file, Student& st)
{
	size_t len;
	file.read(reinterpret_cast<char*>(&len), sizeof(len));
	if (!file || file.gcount() != sizeof(len))
	{
		std::cerr << "Error reading: Invalid size of name!\n";
		return false;
	}

	char* name = new (std::nothrow) char[len + 1];
	if (!name)
		return false;

	file.read(name, len);
	if (!file || file.gcount() != len)
	{
		std::cerr << "Error reading: Invalid name!\n";
		delete[] name;
		return false;
	}
	name[len] = '\0';

	unsigned fn;
	file.read(reinterpret_cast<char*>(&fn), sizeof(fn));
	if (!file || file.gcount() != sizeof(fn))
	{
		std::cerr << "Error reading: Invalid fn!\n";
		delete[] name;
		return false;
	}

	double grades;
	file.read(reinterpret_cast<char*>(&grades), sizeof(grades));
	if (!file || file.gcount() != sizeof(grades))
	{
		std::cerr << "Error reading: Invalid fn!\n";
		delete[] name;
		return false;
	}

	st.name = name;
	st.fn = fn;
	st.grades = grades;

	return true;
}

int main()
{
	std::fstream file("Students-pointer.bin", std::ios::out | std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Cannot open the file!\n";
		return 1;
	}

	const char* name = "Me";
	Student st = { nullptr,  };

	st.name = new (std::nothrow) char[strlen(name) + 1];
	if (st.name)
	{
		strcpy(st.name, name);
		st.fn = 123;
		st.grades = 5.78;

		// НЕ записваме указатели в двоичен файл!
		// file.write(reinterpret_cast<const char*>(&st), sizeof(st));

		// сериализиране на полетата на структурната променлива
		if (store(file, st))
		{
			std::cout << "All good! Data have been stored!\n";
		}

		delete[] st.name;
	}

	Student inFileStudent = { nullptr, };

	file.seekg(0, std::ios::beg);
	if (read(file, inFileStudent))
	{
		std::cout
			<< "The stored student was: "
			<< inFileStudent.name << '\t'
			<< inFileStudent.fn << '\t'
			<< inFileStudent.grades << '\n';
        delete[] inFileStudent.name;
	}

	file.close();
	return 0;
}

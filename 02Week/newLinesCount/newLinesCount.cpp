#include <iostream>
#include <fstream>
#include <assert.h>

const char NEW_LINE_CHAR = '\n';

// Функция за броене на появяванията на даден символ в даден входен файл
int getCharCount(std::ifstream& ifs, char ch)
{

	if (!ifs.is_open())
		return -1;

	int count = 0;
	while (true)// Безкраен цикъл за четене на символи
	{
		char current = ifs.get();// Чете един символ от файла

		if (ifs.eof()) 
			return count;

		if (current == ch) 
			count++;
	}
}

// Функция за броене на редовете в даден файл
int getLinesCount(const char* fileName) 
{
	if (!fileName) // Проверява дали името на файла е валидно (не е nullptr)
		return -1;

	std::ifstream ifs(fileName);
	if (!ifs.is_open()) 
		return -1;

	return getCharCount(ifs, NEW_LINE_CHAR) + 1;// Брои броя на редовете в файла и връща резултата
}

int main()
{
	std::cout << getLinesCount("file.txt");
}
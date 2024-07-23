#include <iostream>
#include <fstream>

bool copyTo(const char* fileNameSource, const char* fileNameDest)
{
	std::ifstream inFile(fileNameSource);
	if (!inFile.is_open())
		return false;

	std::ofstream outFile(fileNameDest);
	if (!outFile.is_open())
		return false;

	while (!inFile.eof())
	{
		char buff[1024];
		inFile.getline(buff, 1024);// Чете 1 ред от изходния файл в буфера
		outFile << buff << std::endl;// Записва съдържанието на буфера във файла, след което добавя нов ред
	}
}
int main()
{
	std::cout << copyTo("file1.txt", "file2.txt");
}
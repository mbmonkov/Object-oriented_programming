#include <iostream>
#include <fstream>
using namespace std;

// Функция за замяна на всички срещания на символ 'ch' с 'ch2' в отворен файл
void replaceInFile(char ch, char ch2, fstream& file)
{
    while (!file.eof())  // Докато не достигне края на файла
    {
        char currentSybmol = file.get();  // Чете текущия символ от файла

        if (currentSybmol != ch)  // Ако текущият символ не е 'ch'
            continue;  // Продължава към следващия символ

        file.seekp(-1, ios::cur);  // Премества позицията на писане назад с 1 байт (т.е. позицията на текущия символ)
        file.put(ch2);  // Замества текущия символ с 'ch2'
        file.flush();   // Изпразва буфера, за да гарантира, че промените са записани във файла
    }
}

int main()
{
	fstream file("treasureTrail.txt", ios::in | ios::out);


	if (!file.is_open())
	{
		std::cout << "Error while opening the file!" << std::endl;
		return -1;
	}

	replaceInFile('a', 'X', file);
	return 0;
}
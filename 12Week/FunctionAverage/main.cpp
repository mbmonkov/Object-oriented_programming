#include <iostream>
#include <fstream>
#include "FunctionAverage.hpp"

// Клас, който управлява числа, заредени от файл
class NumberInFile
{
private:
    int* data = nullptr;  // указател към масив от числа
    size_t size = 0;      // брой на елементите в масива
    bool loaded = false;  // флаг, показващ дали данните са заредени успешно

    // Статичен метод за получаване на размера на файла
    static unsigned getFileSize(std::ifstream& ifs)
    {
        size_t currentPos = ifs.tellg();   // Запазва текущата позиция в потока
        ifs.seekg(0, std::ios::end);       // Премества позицията в края на файла
        size_t fileSize = ifs.tellg();     // Получава размера на файла
        ifs.seekg(currentPos);             // Връща позицията обратно
        return fileSize;
    }

    // Метод за зареждане на данни от файл
    void load(const char* filePath)
    {
        std::ifstream ifs(filePath);  // Отваря файла
        if (!ifs.is_open())          // Проверява дали файлът е отворен успешно
            return;

        size = getFileSize(ifs) / sizeof(int);  // Изчислява броя на числата в файла
        data = new int[size] {};  // Създава нов масив за числата
        ifs.read((char*)data, size * sizeof(int));  // Чете данните от файла в масива
        loaded = true;  // Обновява флага, че данните са заредени
    }

    void copyFrom(const NumberInFile& other)
    {
        size = other.size;  
        data = new int[size] {};  
        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    void free()
    {
        delete[] data;  
    }

public:
    // Конструктор, който зарежда данни от файл
    NumberInFile(const char* filePath)
    {
        load(filePath);
    }

    // Оператор () - Функционален обект, търси число x в заредените данни
    int operator()(int x) const
    {
        for (size_t i = 0; i < size; i++)
        {
            if (x == data[i])
            {
                return x;  
            }
        }
        return 0;
    }

    bool good() const
    {
        return loaded;
    }

    
    NumberInFile(const NumberInFile& other)
    {
        copyFrom(other);
    }

    
    NumberInFile& operator=(const NumberInFile& other)
    {
        if (this != &other)  
        {
            free();  
            copyFrom(other);  
        }
        return *this;
    }

    ~NumberInFile()
    {
        free(); 
    }
};

int main()
{
    char filePath[1024]{}; 
    std::cin.getline(filePath, 1024);  // Чете пътя на файла от входа

    NumberInFile func(filePath);  // Създава обект NumberInFile и зарежда данни от файл
    if (func.good())  // Проверява дали данните са заредени успешно
    {
        std::cout << "Loaded!" << std::endl;
    }
    else
    {
        std::cout << "Invalid file path";
        return 1;  // Завършва програмата с код 1 за грешка
    }

    // Създава IntFunctionAverage с NumberInFile и lambda функция
    IntFunctionAverage<NumberInFile, int (*)(int)> f(func, [](int x) -> int { return x; });

    // Безкраен цикъл, който изчислява средната стойност от резултатите на функциите
    while (true)
    {
        int num = 0;
        std::cin >> num;  // Чете число от входа
        std::cout << "Average: " << f.average(num) << std::endl;  // Изчислява и извежда средната стойност
    }
}

// IntFunctionAverage е шаблонен клас с два параметъра :
// NumberInFile: вероятно е някакъв клас или структура.
// int (*)(int) : указател към функция, която приема int като аргумент и връща int.
// 
// f е обект от тип IntFunctionAverage<NumberInFile, int (*)(int)>.
// 
// func : Това е първият аргумент на конструктора на IntFunctionAverage.Вероятно func е указател към функция или друг подходящ тип, който отговаря на първия шаблонен параметър(NumberInFile).
//    
// [](int x) -> int { return x; } : Това е ламбда функция, която приема int аргумент(x) и връща int.В този случай тя просто връща своя аргумент без промяна.
// 
// Целият ред може да бъде разтълкуван като създаване на обект f от тип IntFunctionAverage, като се използва func като първи аргумент и ламбда функцията като втори аргумент.

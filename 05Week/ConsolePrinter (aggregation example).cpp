#include <iostream> 
#include <fstream>   
#include <string>    
#include <iomanip> 
#pragma warning (disable:4996)  

class ConsolePrinter  
{
    bool (*shouldCensore)(char ch);  // Указател към функция, която определя дали символ трябва да бъде цензуриран
public:
    ConsolePrinter();  // Конструктор по подразбиране
    ConsolePrinter(bool (*pred)(char ch));  // Конструктор с параметър указател към функция
    void print(const char* str) const;  // Метод за печатане на низ
};

ConsolePrinter::ConsolePrinter() : shouldCensore([](char ch) { return false; }) 
// Инициализиране на shouldCensore с ламбда функция, която винаги връща false
{
}

ConsolePrinter::ConsolePrinter(bool (*pred)(char ch)) : shouldCensore(pred))
{
}

void ConsolePrinter::print(const char* str) const
{
    while (*str) 
    {
        if (shouldCensore(*str)) 
            std::cout << "*"; 
        else
            std::cout << *str; 
        str++;  
    }
    std::cout << std::endl; 
}

class NumberWrapper 
{
private:
    int n;  
    const ConsolePrinter& consolePrinter; 

public:
    NumberWrapper(int n, const ConsolePrinter& cp);  // Конструктор с параметри за число и ConsolePrinter
    int getNumber() const; 
    void print() const;  
};

NumberWrapper::NumberWrapper(int n, const ConsolePrinter& cp) : n(n), consolePrinter(cp) 
{
}

int NumberWrapper::getNumber() const
{
    return n; 
}

void NumberWrapper::print() const
{
    consolePrinter.print(std::to_string(n).c_str());  
}

class StringWrapper
{
    const char* str;  // Указател към низ
    const ConsolePrinter& cp;  
public:
    StringWrapper(const char* str, const ConsolePrinter& cp);  
    void print() const;  а
};

StringWrapper::StringWrapper(const char* str, const ConsolePrinter& cp) : str(str), cp(cp) 
{
}

void StringWrapper::print() const
{
    cp.print(str);  // Печата низа str чрез ConsolePrinter
}

bool isDigit(char ch)  
{
    return ch >= '0' && ch <= '9';  
}

int main()  
{
    {
        ConsolePrinter noNumbers([](char ch) { return ch >= '0' && ch <= '9'; });

        StringWrapper sr("Test3432wrwe", noNumbers);  

        NumberWrapper nw(12345, noNumbers);  

        sr.print();  
        nw.print();
    }
    {
        ConsolePrinter censoreEverything([](char ch) { return true; });
	    
        StringWrapper sr("Test3432wrwe", censoreEverything);  

        NumberWrapper nw(12345, censoreEverything);  

        sr.print(); 
        nw.print();  
    }
}

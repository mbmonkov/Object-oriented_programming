#include <iostream>  


bool isLittleEndian()
{
    // Създаване на обединение за тест на байт ред
    union endiannessTest
    {
        uint32_t n = 1;         // Променлива от 4 байта, инициализирана със стойност 1
        unsigned char bytes[4]; // Массив от байтове
    } myTest;

    // Проверка на първия байт от променливата n
    return myTest.bytes[0]; // Връща true (1), ако първият байт е 1, което означава, че сме в little-endian
}

int main()
{
    std::cout << isLittleEndian();  
}

#include <iostream>  
#include <fstream>   


unsigned getCharCountFromFile(std::ifstream& ifs, char ch)
{
    size_t currentPosition = ifs.tellg(); // Запазва текущата позиция на указателя
    ifs.seekg(0, std::ios::beg); // Премества позицията на указателя в началото

    if (!ifs.is_open()) 
        return 0; 

    unsigned int count = 0;

    while (true) // Безкраен цикъл за четене на символи
    {
        char current = ifs.get(); // Чете един символ от файла
        if (ifs.eof()) // Проверява дали е достигнат края на файла
            break; 

        if (current == ch) // Проверява дали текущият символ е равен на 'ch'
            count++; 
    }

    ifs.clear(); // Изчиства флаговете на потока, ако са били задействани от EOF
    ifs.seekg(currentPosition); // Възстановява позицията на указателя 
    return count; 
}

// Функция за извличане на масив от числа от файл
int* getArrayFromFile(const char* fileName, size_t& arraySize)
{
    std::ifstream stream(fileName); // Отваря файл за четене
    if (!stream.is_open())
        return nullptr;

    arraySize = getCharCountFromFile(stream, ' ') + 1; // Определя размера на масива на базата на броя на празните места
    int* result = new int[arraySize]; // Създава динамичен масив с необходимия размер

    for (int i = 0; i < arraySize; i++) // Цикъл за четене на числа от файла и записването им в масива
    {
        stream >> result[i]; // Чете едно число и го записва в масива
    }

    stream.close(); // Затваря файла
    return result; // Връща указателя на масива с числата
}

// Функция за сливане на два сортирани масива
int* merge(const int* first, size_t firstSize, const int* second, size_t secondSize)
{
    size_t iterFirst = 0; // Инициализира брояча за първия масив
    size_t iterSecond = 0; // Инициализира брояча за втория масив

    int* merged = new int[firstSize + secondSize]; // Създава нов масив с размер, равен на сумата от размерите на двата масива
    size_t mergedIter = 0; // Инициализира брояча за слетия масив

    while (iterFirst < firstSize && iterSecond < secondSize) // Цикъл за сливане на масивите
    {
        if (first[iterFirst] <= second[iterSecond]) // Проверява кой елемент е по-малък или равен
            merged[mergedIter++] = first[iterFirst++]; // Добавя елемента от първия масив в слетия масив
        else
            merged[mergedIter++] = second[iterSecond++]; // Добавя елемента от втория масив в слетия масив
    }

    while (iterFirst < firstSize) // Добавя останалите елементи от първия масив
        merged[mergedIter++] = first[iterFirst++];

    while (iterSecond < secondSize) // Добавя останалите елементи от втория масив
        merged[mergedIter++] = second[iterSecond++];

    return merged; // Връща указателя на слетия масив
}

// Функция за сливане на данни от два файла и записването на резултата в нов файл
void mergeFromFiles(const char* firstFileName, const char* secondFileName, const char* mergedFileName)
{
    size_t firstArraySize, secondArraySize; // Променливи за размерите на масивите
    int* firstArray = getArrayFromFile(firstFileName, firstArraySize); // Чете масива от първия файл
    if (!firstArray) // Проверява дали масивът е успешно създаден
        return; // Прекратява функцията, ако не е успешно създаден

    int* secondArray = getArrayFromFile(secondFileName, secondArraySize); // Чете масива от втория файл

    if (!secondArray) // Проверява дали масивът е успешно създаден
    {
        delete[] firstArray; // Освобождава паметта, заделена за първия масив
        return; // Прекратява функцията, ако не е успешно създаден
    }

    int* result = merge(firstArray, firstArraySize, secondArray, secondArraySize); // Слива двата масива

    std::ofstream output(mergedFileName); // Отваря файл за запис на слетия резултат

    if (!output.is_open()) // Проверява дали файлът е успешно отворен за запис
    {
        delete[] firstArray; 
        delete[] secondArray; 
        delete[] result; 
        return; // Прекратява функцията, ако файлът не може да бъде отворен
    }
    for (int i = 0; i < firstArraySize + secondArraySize; i++) // Цикъл за запис на елементите на слетия масив в изходния файл
        output << result[i] << " "; // Записва всеки елемент последван от интервал

    delete[] firstArray; 
    delete[] secondArray;
    delete[] result; 

    output.close(); // Затваря изходния файл
}


int main()
{
    mergeFromFiles("file1.txt", "file2.txt", "merged.txt"); 
}

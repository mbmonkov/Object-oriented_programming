#include <iostream> 
#include <sstream>   
#include <fstream>   
#include <assert.h>  

namespace GlobalConstants
{
    // Деклариране на константи за максимални размери и разделители
    constexpr int FIELD_MAX_SIZE = 30; // Максимален размер на поле (30 символа)
    constexpr int MAX_FIELDS_ROW = 10; // Максимален брой полета на ред (10)
    constexpr int ROWS_MAX_SIZE = 300; // Максимален брой редове (300)
    constexpr int BUFFER_SIZE = 1024; // Размер на буфера (1024 байта)
    constexpr char SEP = ';'; // Символ за разделител (точка и запетая)
}

typedef char Field[GlobalConstants::FIELD_MAX_SIZE]; // Дефинира тип за поле с фиксиран размер
typedef Field Row[GlobalConstants::MAX_FIELDS_ROW];  // Дефинира тип за ред от полета с фиксиран брой полета

// Структура за представяне на CSV таблица
struct CsvTable
{
    Row rows[GlobalConstants::ROWS_MAX_SIZE]; // Массив от редове с фиксиран размер
    size_t rowsCount = 0; // Брой на редовете
    size_t collsCount = 0; // Брой на полетата в текущия ред
};

// Функция за парсиране на ред от CSV формат
size_t parseRow(const char* row, Row& toReturn)
{
    std::stringstream ss(row); // Създава низов поток от входния ред

    size_t currentColumnCount = 0; // Брояч на текущите колони
    while (!ss.eof()) // Цикъл, който продължава докато не достигне края на потока
    {
        ss.getline(toReturn[currentColumnCount++], GlobalConstants::FIELD_MAX_SIZE, GlobalConstants::SEP); // Чете поле до разделителя и го записва в реда
    }
    return currentColumnCount; // Връща броя на колоните
}

// Функция за парсиране на CSV файл от поток
CsvTable parseFromFile(std::istream& ifs)
{
    CsvTable result; // Създава празна таблица
    char rowStr[GlobalConstants::BUFFER_SIZE]; // Буфер за четене на редове
    while (!ifs.eof()) // Цикъл, който продължава докато не достигне края на файла
    {
        ifs.getline(rowStr, GlobalConstants::BUFFER_SIZE, '\n'); // Чете ред от входния поток
        result.collsCount = parseRow(rowStr, result.rows[result.rowsCount++]); // Парсира реда и увеличава броя на редовете
    }
    return result; // Връща попълнената таблица
}

// Функция за парсиране на CSV файл по име на файл
CsvTable parseFromFile(const char* fileName)
{
    std::ifstream ifs(fileName); // Отваря файл за четене
    if (!ifs.is_open()) // Проверява дали файлът е успешно отворен
    {
        return {}; // Връща празна таблица, ако файлът не може да бъде отворен
    }

    return parseFromFile(ifs); // Извиква функцията за парсиране с отворения поток
}

// Функция за печат на съдържанието на CSV таблица
void printTable(const CsvTable& table)
{
    for (int i = 0; i < table.rowsCount; i++) // Цикъл за преминаване през всички редове
    {
        for (int j = 0; j < table.collsCount; j++) // Цикъл за преминаване през всички колони в текущия ред
        {
            std::cout << table.rows[i][j] << "          "; // Извежда съдържанието на текущото поле, последвано от разстояние
        }
        std::cout << std::endl; // Преминава на нов ред след края на реда
    }
}

// Функция за запис на ред от таблица в поток
void saveRowToFile(std::ostream& ofs, const Row& row, size_t collsCount)
{
    for (int i = 0; i < collsCount; i++) // Цикъл за преминаване през всички полета в реда
    {
        ofs << row[i]; // Записва полето в изходния поток
        if (i != collsCount - 1) // Ако не е последното поле в реда
        {
            ofs << GlobalConstants::SEP; // Добавя разделител след полето
        }
    }
}

// Функция за запис на съдържанието на CSV таблица в поток
void saveToFile(std::ostream& ofs, const CsvTable& table)
{
    for (int i = 0; i < table.rowsCount; i++) // Цикъл за преминаване през всички редове
    {
        saveRowToFile(ofs, table.rows[i], table.collsCount); // Записва текущия ред в потока
        if (i != table.rowsCount - 1) // Ако не е последният ред
        {
            ofs << std::endl; // Добавя нов ред след реда
        }
    }
}

// Функция за запис на съдържанието на CSV таблица в файл
void saveToFile(const char* fileName, const CsvTable& table)
{
    std::ofstream ofs(fileName); // Отваря файл за запис
    saveToFile(ofs, table); // Записва таблицата в файла
    ofs.close(); // Затваря файла
}

// Функция за намиране на индекс на колона по име на колона
int getColumnIndex(const CsvTable& csvTable, const char* columnName)
{
    assert(csvTable.rowsCount >= 1); // Проверява дали има поне един ред в таблицата
    if (!columnName) // Проверява дали името на колоната е валидно
        return -1; // Връща -1, ако името на колоната е невалидно

    for (int i = 0; i < csvTable.collsCount; i++) // Цикъл за преминаване през всички колони на първия ред
    {
        if (strcmp(csvTable.rows[0][i], columnName) == 0) // Проверява дали текущото поле съвпада с името на колоната
            return i; // Връща индекса на колоната
    }
    return -1; // Връща -1, ако името на колоната не е намерено
}

// Функция за модификация на стойностите в колона
bool modify(CsvTable& csv, const char* columnName, const char* newValues, char sep)
{
    int columnIndex = getColumnIndex(csv, columnName); // Намира индекс на колоната
    if (columnIndex < 0) // Проверява дали индексът е валиден
        return false; // Връща false, ако колоната не е намерена

    std::stringstream ss(newValues); // Създава низов поток от новите стойности
    int rowIndex = 1; // Започва от втория ред (0 е заглавния ред)
    while (!ss.eof()) // Цикъл, който продължава докато не достигне края на потока
    {
        if (rowIndex >= csv.rowsCount) // Проверява дали индексът на реда е извън допустимите граници
            break; // Прекратява цикъла, ако няма достатъчно редове
        ss.getline(csv.rows[rowIndex++][columnIndex], GlobalConstants::FIELD_MAX_SIZE, sep); // Чете новата стойност и я записва в таблицата
    }
    return true; // Връща true, ако модификацията е успешна
}


int main()
{
    CsvTable myFile = parseFromFile("students.csv"); 

    printTable(myFile); 

    
    modify(myFile, "Ime", "Katerina|Petya", '|'); // Променя стойностите в колоната "Ime" с нови стойности, разделени със символ '|'

    saveToFile("students_new.csv", myFile); 
}

#include <iostream>
#include <cstddef>
#include <cassert>

enum Program
{
    PROGRAM_UNKNOWN, 

    INFORMATICS,
    COMPUTER_SCIENCE,
    SOFTWARE_ENGINEERING,
    INFORMATION_SYSTEMS,

    PROGRAM_COUNT          
};

// как да намалим размера на структурата?
struct Student
{
    char name[24];

    Program program;

    unsigned int facNumber;
    unsigned char year;
    unsigned char stream;
    unsigned char group;

    bool interrupted;
    bool stateTuition;
};

// Битови полета
struct OMStudent
{
    char name[24];                  
 
    Program program;             

    unsigned int facNumber      : 22;   // [0..2^22 - 1]
    unsigned int year           : 3;    // [0..7]
    unsigned int group          : 3;    // [0..7]
    unsigned int interrupted    : 1;    // 0 или 1
    unsigned int stateTuition   : 1;    // 0 или 1
    unsigned int                : 2;    // за подравняване...
    unsigned int stream         : 12;
};

int main_testBitFields()
{
    std::cout << "sizeof(Student): " << sizeof(OMStudent) << std::endl;

    Student s = { "Me", INFORMATICS, 12345, 4, 1, 0, };
    // указател и псевдоним към полета на структурната променлива
    unsigned char& year = s.year;
    unsigned int* fn = &s.facNumber;


    OMStudent s1 = { "You", INFORMATION_SYSTEMS, 90123, 4, 1, 0, };
    std::cout << s1.group << std::endl;

    // ако запишем по-голяма стойност?
    s1.group = 11;
    std::cout << s1.group << std::endl;

    // не можем да създадем указател към битово поле
    //unsigned int* stream = &s1.stream;

    return 0;
}

union Data
{
    char mChar;
    int mInt;
    double mDouble;
};

void printUnion(Data data)
{
    std::cout << "as char: "    << data.mChar   << std::endl;
    std::cout << "as int: "     << data.mInt    << std::endl;
    std::cout << "as double: "  << data.mDouble << std::endl;
}

int main() //_testUnion()
{
    std::cout << "sizeof(Data): " << sizeof(Data) << std::endl;

    Data data = { 'A' }; // инициализира само първото поле
    printUnion(data);

    data.mDouble = 1023.50;
    std::cout << "\n--- change (as double) ---\n" << std::endl;
    printUnion(data);

    data.mInt = 1000000;
    std::cout << "\n--- change (as int) ---\n" << std::endl;
    printUnion(data);

    return 0;
}

enum DataType
{
    TYPE_UNKNOWN = -1,
    CHAR,
    INT,
    DOUBLE,
    TYPE_COUNT
};

struct Elem
{
    DataType type;
    union
    {
        char mChar;
        int mInt;
        double mDouble;
    } data;
};

void printElem(const Elem& elem)
{
    switch (elem.type)
    {
    case INT:   
        std::cout 
            << "int: "    
            << elem.data.mInt   
            << std::endl; 
        break;
    
    case CHAR: 
        std::cout 
            << "char: "   
            << elem.data.mChar  
            << std::endl; 
        break;
    
    case DOUBLE: 
        std::cout 
            << "double: " 
            << elem.data.mDouble 
            << std::endl; 
        break;

    default:
        assert("Invalid data type!" && false);
        break;
    }
}

int main_testArray()
{
    std::cout << "sizeof(Elem): " << sizeof(Elem) << std::endl;

    Elem ed;
    ed.type = DOUBLE;
    ed.data.mDouble = 1023.25;

    Elem ei;
    ei.type = INT;
    ei.data.mInt = 4;

    Elem ec;
    ec.type = CHAR;
    ec.data.mChar = 'B';

    Elem elems[3] = { ed, ei, ec };

    // скоби и за обединението!
    // 42, 'а' и 10.25 
    // ще инициализират първият елемент на обединението
    // 
    //Elem elems[3] = {
    //    {INT,       {42}},    // int се преобразува се до char
    //    {CHAR,      {'a'}},
    //    {DOUBLE,    {10.25}}  // int се преобразува се до char
    //};

    for (int i = 0; i < 3; ++i)
        printElem(elems[i]);

    return 0;
}



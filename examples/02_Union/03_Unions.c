#include <stdio.h>

union Data
{
    char mChar;
    int mInt;
    double mDouble;
};

void printUnion(union Data data)
{
    printf("as char: %c\n", data.mChar);
    printf("as int: %d\n", data.mInt);
    printf("as double: %lf\n", data.mDouble);
}

int main_()
{
    printf("sizeof(Data): %llu\n", sizeof(union Data));

    // designated initializer, C (since C99), C++ (C++20)
    union Data data = { .mDouble = 100.25 };
    printUnion(data);

    data.mChar = 'A';
    printUnion(data);

    data.mInt = 1000000;
    printUnion(data);

    return 0;
}

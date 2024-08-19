#include <iostream>
#include <fstream>
#include "Factory.h"
#include "ExampleCriteria.h"

void readFileToArr(const char* fileName, int* arr, size_t& size, size_t maxSize) {
    std::ifstream ifs(fileName);
    if (!ifs)
        return;
    size = 0;
    while (size < maxSize && ifs >> arr[size]) {
        size++;
    }
}

void printSetInInterval(const Set& set, unsigned begin, unsigned end) {
    for (unsigned i = begin; i < end; i++) {
        if (set.accepts(i))
            std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    ExampleCriteria include;
    include.include = true;
    readFileToArr("include.txt", include.arr, include.size, 32);

    ExampleCriteria exclude;
    exclude.include = false;
    readFileToArr("exclude.txt", exclude.arr, exclude.size, 32);

    // Използваме фабриката за създаване на Set обекти
    Set* s1 = SetFactory::createSetByCriteria(include);
    Set* s2 = SetFactory::createSetByCriteria(exclude);
    Set* s3 = SetFactory::createSetByCriteria([](unsigned x) { return x % 2 == 0; });

    const Set* sets[] = { s1, s2, s3 };
    Set* s4 = SetFactory::createIntersectionOfSets(sets, 3);

    printSetInInterval(*s1, 0, 10);
    printSetInInterval(*s2, 0, 10);
    printSetInInterval(*s3, 0, 10);
    printSetInInterval(*s4, 0, 10);

    // Освобождаване на паметта
    delete s1;
    delete s2;
    delete s3;
    delete s4;

    return 0;
}

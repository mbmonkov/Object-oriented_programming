#include "Factory.h"

Set* SetFactory::createSetByCriteria(const ExampleCriteria& criteria) {
    return new SetByCriteria<ExampleCriteria>(criteria);
}

Set* SetFactory::createSetByCriteria(ExampleCriteria&& criteria) {
    return new SetByCriteria<ExampleCriteria>(std::move(criteria));
}

Set* SetFactory::createSetByCriteria(bool(*criteriaFunc)(unsigned)) {
    return new SetByCriteria<bool(*)(unsigned)>(criteriaFunc);
}

Set* SetFactory::createUnionOfSets(const Set** sets, size_t count) {
    return new Union(sets, count);
}

Set* SetFactory::createUnionOfSets(Set**&& sets, size_t count) {
    return new Union(std::move(sets), count);
}

Set* SetFactory::createIntersectionOfSets(const Set** sets, size_t count) {
    return new Intersection(sets, count);
}

Set* SetFactory::createIntersectionOfSets(Set**&& sets, size_t count) {
    return new Intersection(std::move(sets), count);
}

Set** SetFactory::createSetArray(std::istream& file, uint16_t size) {
    Set** sets = new Set * [size];
    // Пример за четене и създаване на Set обекти (може да се адаптира спрямо специфичния формат на файла)
    for (uint16_t i = 0; i < size; ++i) {
        // Тук може да се имплементира логика за създаване на различни типове Set обекти на база данните във файла
    }
    return sets;
}

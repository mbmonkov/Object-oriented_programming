#pragma once
#include "Set.h"
#include "SetByCriteria.hpp"
#include "SetOperation.h"
#include "UnionOfSet.h"
#include "Intersection.h"
#include "ExampleCriteria.h"
#include <istream>

class SetFactory
{
public:
    static Set* createSetByCriteria(const ExampleCriteria& criteria);
    static Set* createSetByCriteria(ExampleCriteria&& criteria);
    static Set* createSetByCriteria(bool(*criteriaFunc)(unsigned));

    static Set* createUnionOfSets(const Set** sets, size_t count);
    static Set* createUnionOfSets(Set**&& sets, size_t count);

    static Set* createIntersectionOfSets(const Set** sets, size_t count);
    static Set* createIntersectionOfSets(Set**&& sets, size_t count);

    static Set** createSetArray(std::istream& file, uint16_t size);
};

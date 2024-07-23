#pragma once
#include "DynamicSet.h"

// Клас за работа с множество от числа, базирано на критерий
class SetByCriteria : private DynamicSet
{
public:
    // Конструктор, който инициализира множество от числа в зависимост от критериен метод
    SetByCriteria(unsigned n, bool (*incl)(unsigned n));

    // Метод за задаване на нов критериен метод
    void setInclude(bool (*incl)(unsigned n));

    // Декларира публично достъпни методи от базовия клас DynamicSet
    using DynamicSet::print;
    using DynamicSet::contains;

private:
    // Метод за попълване на множеството в зависимост от зададения критерий
    void fillSet(bool (*criteria)(unsigned n));
};

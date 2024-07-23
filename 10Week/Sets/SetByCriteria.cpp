#include "SetByCriteria.h"

// Конструктор на SetByCriteria
SetByCriteria::SetByCriteria(unsigned n, bool (*incl)(unsigned n)) : DynamicSet(n)
{
    fillSet(incl); // Запълва множеството с числа в зависимост от критериите
}

// Метод за попълване на множеството въз основа на предоставената функция за критерии
void SetByCriteria::fillSet(bool (*criteria)(unsigned n))
{
    for (unsigned i = 0; i < getN(); i++)
    {
        if (criteria(i))
            add(i);  
        else
            remove(i); 
    }
}

// Метод за смяна на критериите за включване на числа в множеството
void SetByCriteria::setInclude(bool (*incl)(unsigned n))
{
    fillSet(incl); // Пренастройва множеството въз основа на новите критерии
}

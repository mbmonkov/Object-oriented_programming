#pragma once

struct ExampleCriteria
{
    bool include = false;  // Определя дали числото трябва да бъде включено или изключено.
    size_t size = 0;       // Размер на масива от числа.
    int arr[32] = { 0 };   // Масив от числа, които определят критерия.

    bool operator()(unsigned n) const
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == n)
            {
                return include;
            }
        }
        return !include;
    }
};

#include "Sorts.h"
#include <algorithm>

// Предварително декларация на структура A
struct A;

// Шаблонна функция за SelectionSort на масив
template <class T>
void SelectionSort(T* pArr, size_t Size)
{
    // Проверява дали указателят към масива е валиден и размерът на масива е ненулев
    if (!pArr || Size == 0)
        return;

    // Процедурата за SelectionSort 
    for (size_t i = 0; i < Size - 1; i++)
    {
        size_t min = i;

        for (size_t j = i + 1; j < Size; j++)
        {
            if (pArr[j] < pArr[min])
                min = j;
        }

        if (pArr[min] < pArr[i])
            std::swap(pArr[i], pArr[min]);
    }
}

// Шаблонна функция за BubbleSort на масив
template <class T>
void BubbleSort(T* pArr, size_t Size)
{
    // Проверява дали указателят към масива е валиден и размерът на масива е ненулев
    if (!pArr || Size == 0)
        return;

    // Процедурата за BubbleSort 
    for (size_t i = 0; i < Size - 1; i++)
    {
        for (size_t j = Size - 1; j > i; j--)
        {
            if (pArr[j] < pArr[j - 1])
                std::swap(pArr[j], pArr[j - 1]);
        }
    }
}

// Специализация на шаблонната функция SelectionSort за тип double
template void SelectionSort<double>(double* pArr, size_t Size);

// Специализация на шаблонната функция BubbleSort за тип double
template void BubbleSort<double>(double* pArr, size_t Size);

// Специализация на шаблонната функция BubbleSort за тип A
// Тук типът A трябва да бъде дефиниран по някакъв начин,
// защото без това, компилаторът не би знаел какво е A.
template void BubbleSort<A>(A* pArr, size_t Size);

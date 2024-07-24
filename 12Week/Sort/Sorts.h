#pragma once

// Функция за сортиране на масив с помощта на SelectionSort 
// Шаблонна функция, която работи с различни типове данни
// pArr: указател към началото на масива
// Size: броя на елементите в масива
template <class T>
void SelectionSort(T* pArr, size_t Size);

// Функция за сортиране на масив с помощта на BubbleSort 
// Шаблонна функция, която работи с различни типове данни
// pArr: указател към началото на масива
// Size: броя на елементите в масива
template <class T>
void BubbleSort(T* pArr, size_t Size);

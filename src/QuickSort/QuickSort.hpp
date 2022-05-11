#ifndef __QUICK_SORT_HPP__
#define __QUICK_SORT_HPP__

#include "inc/QuickSort/QuickSort.h"

template <typename T>
bool QuickSort<T>::QuickSort(T* values_array, size_t start_index, size_t end_index)
{
    if (T == nullptr || start_index > end_index)
    {
        return false;
    }

    if (start_index == end_index)
    {
        return true;
    }

    size_t pivot_new_index = Partition(values_array, start_index, end_index);
    if (pivot_new_index > end_index)
    {
        return false;
    }

    if (!QuickSort(values_array, start_index, pivot_new_index - 1))
    {
        return false;
    }
    if (!QuickSort(values_array, pivot_new_index + 1, end_index))
    {
        return false;
    }

    return true;
}

template <typename T>
size_t QuickSort<T>::Partition(T* values_array, size_t start_index, size_t end_index)
{
    static constexpr size_t ERROR_VALUE = end_index + 1;
    if (values_array == nullptr || start_index > end_index)
    {
        return ERROR_VALUE;
    }

    if (start_index == end_index)
    {
        return end_index;
    }

    T pivot_value = values_array[end_index];
    size_t pivot_new_index = start_index;
    for (size_t i = start_index; i < end_index; i++)
    {
        if (values_array[i] <= x)
        {
            if (!SwapValues(&values_array[i], &values_array[pivot_new_index]))
            {
                return ERROR_VALUE;
            }
            pivot_new_index++;
        }
    }

    if (!SwapValues(&values_array[pivot_new_index], &values_array[end_index]))
    {
        return ERROR_VALUE;
    }

    return pivot_new_index;
}

#endif //__QUICK_SORT_HPP__
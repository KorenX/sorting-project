#ifndef __QUICK_SORT_HPP__
#define __QUICK_SORT_HPP__

#include "inc/QuickSort/QuickSort.h"
#include "inc/SortUtils.h"

template <typename T>
bool QuickSort::QuickSort(T* values_array, size_t start_index, size_t end_index)
{
    if (values_array == nullptr || start_index > end_index)
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

    if (pivot_new_index != start_index) 
    {
        if (!QuickSort(values_array, start_index, pivot_new_index - 1))
        {
            return false;
        }
    }
    if (pivot_new_index != end_index)
    {
        if (!QuickSort(values_array, pivot_new_index + 1, end_index))
        {
            return false;    
        }
    }

    return true;
}

template <typename T>
bool QuickSort::RandomizedSelect(T* values_array, size_t start_index, size_t end_index, size_t index_to_find)
{
    if (values_array == nullptr || start_index > end_index || index_to_find > end_index)
    {
        return false;
    }

    if (start_index == end_index)
    {
        if (index_to_find == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    size_t pivot_new_index = RandomizedPartition(values_array, start_index, end_index);
    if (pivot_new_index > end_index)
    {
        return false;
    }

    size_t smaller_values_amount = pivot_new_index - start_index;
    if (smaller_values_amount == index_to_find)
    {
        return true;
    }
    else if (smaller_values_amount > index_to_find)
    {
        return RandomizedSelect(values_array, start_index, pivot_new_index - 1, index_to_find);
    }
    else
    {
        return RandomizedSelect(values_array, pivot_new_index + 1, end_index, index_to_find - smaller_values_amount - 1);
    }

    // Should never get here
    return false;
}

template <typename T>
size_t QuickSort::Partition(T* values_array, size_t start_index, size_t end_index)
{
    const size_t ERROR_VALUE = end_index + 1;
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
        if (values_array[i] <= pivot_value)
        {
            if (!SortUtils::SwapValues(&values_array[i], &values_array[pivot_new_index]))
            {
                return ERROR_VALUE;
            }
            pivot_new_index++;
        }

        comparison_counter++;
    }

    if (!SortUtils::SwapValues(&values_array[pivot_new_index], &values_array[end_index]))
    {
        return ERROR_VALUE;
    }

    return pivot_new_index;
}

template <typename T>
size_t QuickSort::RandomizedPartition(T* values_array, size_t start_index, size_t end_index)
{
    const size_t ERROR_VALUE = end_index + 1;
    if (values_array == nullptr || start_index > end_index)
    {
        return ERROR_VALUE;
    }

    size_t random_range = end_index - start_index + 1;
    size_t random_pivot = (rand() % random_range) + start_index;

    if (!SortUtils::SwapValues(&values_array[random_pivot], &values_array[end_index]))
    {
        return ERROR_VALUE;
    }

    // Now the randomly selected pivot is in the last index, so we can just call Partition.
    return Partition(values_array, start_index, end_index);
}

size_t QuickSort::GetComparisonCounter()
{
    return comparison_counter;
}

void QuickSort::ResetComparisonCounter()
{
    comparison_counter = 0;
}

#endif //__QUICK_SORT_HPP__
#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include <stddef.h>
#include <stdlib.h>

namespace QuickSort
{
    /**
     * This function is the main function for QuickSort. It will also be used recursively
     * as a part of the implementation.
     *
     * @param values_array - the array of values to be sorted. The sorting will take place inplace.
     * @param start_index - the index inside of the array to start counting from. the indices before that index will not be changed.
     * @param end_index - the index inside of the array to finish counting at. the values after that will not be changed.
     *
     * @return true if the function was successful, false otherwise.
     */
    template <typename T>
    bool QuickSort(T* values_array, size_t start_index, size_t end_index);

    /**
     * This function finds the n-th smallest number in the values array, using partition which means that it will be as if it were
     * the pivot in a Partition function
     *
     * @param values_array - the array of values to be sorted. The sorting will take place inplace.
     * @param start_index - the index inside of the array to start counting from. the indices before that index will not be changed.
     * @param end_index - the index inside of the array to finish counting at. the values after that will not be changed.
     * @param index_to_find - the n-th smallest number requested.
     *
     * @return true if the function was successful, false otherwise.
     */
    template <typename T>
    bool RandomizedSelect(T* values_array, size_t start_index, size_t end_index, size_t index_to_find);

    /**
     * This function takes an unsorted array, and reorganizes it such that the last value will
     * be in the place it would be in had the array been sorted, and all the values before it
     * will be smaller or equal to it, and all the values after it will be larger than it.
     *
     * @param values_array - the array of values to be partitioned. The partitioning will take place inplace.
     * @param start_index - the index inside of the array to start counting from. the indices before that index will not be changed.
     * @param end_index - the index inside of the array to finish counting at. the indices after that will not be changed.
     *
     * @return the new location of the last value of the array, in case of error return end_index + 1
     */
    template <typename T>
    size_t Partition(T* values_array, size_t start_index, size_t end_index);

    /**
     * Same as partition, but chooses a random index as pivot. assumes srand is already set.
     *
     * @param values_array - the array of values to be partitioned. The partitioning will take place inplace.
     * @param start_index - the index inside of the array to start counting from. the indices before that index will not be changed.
     * @param end_index - the index inside of the array to finish counting at. the indices after that will not be changed.
     *
     * @return the new location of the pivot, in case of error return end_index + 1
     */
    template <typename T>
    size_t RandomizedPartition(T* values_array, size_t start_index, size_t end_index);
    
    /**
     * Returns the amount of value comparisons made since last reset
     *
     * @returns the amount of value comparisons
     */
    size_t GetComparisonCounter();

    /**
     * Resets the amount of value comparisons made to 0
     */
    void ResetComparisonCounter();
    
    static size_t comparison_counter = 0;
}

#include "src/QuickSort/QuickSort.hpp"

#endif //__QUICK_SORT_H__
#ifndef __MIN_HEAP_H__
#define __MIN_HEAP_H__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/*
    An implementation of MinHeap for this project's use.
    typename T - the values held in the inner array. must have compare functions implemented
    size_t max_size - the maximum number of values in the stack

    In theory, all of the MinHeap functions can work inplace on a given array,
    but in practice it would make the functions be written as if we were using C,
    and I would like to use C++ for this excercise, so please ignore the additional
    used in this implementation.

    Notice I don't like to work with Exceptions (something I carry from my personal job experience),
    So my code may be a bit unconventional.
*/

template <typename T, size_t max_size>
class MinHeap
{
public:
    MinHeap() : m_values_amount(0), m_initialized(false) {}

    /**
     * This function initializes the class from an array of T values
     * 
     * @param unsorted_array - the array of values the MinHeap will be initialized from
     * @param values_count - the amount of values in the unsorted array
     * 
     * @returns true if the function was successful, false otherwise.
     */
    bool BuildMinHeap(T* unsorted_array, size_t values_count);

    /**
     * This function extracts the head of the heap and reorganizes it
     * 
     * @param o_min [OUT] - a reference to the out param from the function, will hold the minimum value of the heap.
     * 
     * @returns true if the function was successful, false otherwise.
     */
    bool ExtractMin(T& o_min);

private:
    /**
     * This function reorganizes the heap downwards, assuming that the trees beneath the head are organized
     * 
     * @param uneven_head - the head which may be uneven and in that case, reordered.
     * 
     * @returns true if the function was successful, false otherwise.
     */
    bool MinHeapify(size_t uneven_head);

    /**
     * This function swaps two of the array values with each other
     *
     * @param index1 - the first index, will be swapped with index2
     * @param index2 - the second index, will be swapped with index1
     *
     * @returns true if the function was successful, false otherwise.
     */
    bool SwapValues(size_t index1, size_t index2);

    T m_values[max_size];
    size_t m_values_amount;
    bool m_initialized;
};


template <typename T, size_t max_size>
bool MinHeap<T, max_size>::BuildMinHeap(T* unsorted_array, size_t values_count)
{
    m_initialized = false;

    if (unsorted_array == nullptr || values_count > max_size)
    {
        printf("a\n");
        return false;
    }

    for (size_t i = 0; i < values_count; i++)
    {
        m_values[i] = unsorted_array[i];
    }

    m_values_amount = values_count;
    
    // run for each node except for the last to avoid underflow
    for (size_t i = m_values_amount/2; i > 0; i--)
    {
        if (!MinHeapify(i))
        {
            printf("b 0x%x\n", i);
            return false;
        }
    }

    if (!MinHeapify(0))
    {
        printf("c 0x%x\n", 0);
        return false;
    }

    m_initialized = true;
    return true;
}

template <typename T, size_t max_size>
bool MinHeap<T, max_size>::ExtractMin(T& o_min)
{
    if (!m_initialized)
    {
        return false;
    }

    // Check if the heap is empty
    if (m_values_amount == 0)
    {
        return false;
    }

    o_min = m_values[0];
    // Take the last value out, and put it as the first value
    m_values[0] = m_values[m_values_amount - 1];
    m_values_amount--;

    // Fix the heap
    return MinHeapify(0);
}

template <typename T, size_t max_size>
bool MinHeap<T, max_size>::MinHeapify(size_t uneven_head)
{
    size_t smallest_index = uneven_head;
    size_t left_child_index = uneven_head * 2;
    size_t right_child_index = left_child_index + 1;

    // Check integer overflow
    if (left_child_index < uneven_head || right_child_index < uneven_head)
    {
        return false;
    }

    if (left_child_index < m_values_amount && m_values[left_child_index] < m_values[smallest_index])
    {
        smallest_index = left_child_index;
    }

    if (right_child_index < m_values_amount && m_values[right_child_index] < m_values[smallest_index])
    {
        smallest_index = right_child_index;
    }

    if (smallest_index != uneven_head)
    {
        if (!SwapValues(smallest_index, uneven_head))
        {
            return false;
        }

        return MinHeapify(smallest_index);
    }

    return true;
}

template <typename T, size_t max_size>
bool MinHeap<T, max_size>::SwapValues(size_t index1, size_t index2)
{
    if (index1 >= m_values_amount || index2 >= m_values_amount)
    {
        return false;
    }

    T swap_temp = m_values[index1];
    m_values[index1] = m_values[index2];
    m_values[index2] = swap_temp;

    return true;
}

#endif //__MIN_HEAP_H__
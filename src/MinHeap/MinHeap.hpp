#ifndef __MIN_HEAP_HPP__
#define __MIN_HEAP_HPP__

#include "inc/MinHeap/MinHeap.h"

template <typename T, size_t max_size>
bool MinHeap::MinHeap<T, max_size>::BuildMinHeap(T* unsorted_array, size_t values_count)
{
    if (unsorted_array == nullptr || values_count > max_size)
    {
        return false;
    }

    for (size_t i = 0; i < values_count; i++)
    {
        // We don't use memcpy here becasue we want to call copy constructor
        m_values[i] = unsorted_array[i];
    }

    m_values_amount = values_count;
    
    // Run for each node except for the last to avoid underflow
    for (size_t i = m_values_amount/2; i > 0; i--)
    {
        if (!MinHeapify(i))
        {
            return false;
        }
    }

    if (!MinHeapify(0))
    {
        return false;
    }

    return true;
}

template <typename T, size_t max_size>
bool MinHeap::MinHeap<T, max_size>::ExtractMin(T& o_min)
{
    if (IsEmpty())
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
bool MinHeap::MinHeap<T, max_size>::IsEmpty()
{
    return m_values_amount == 0;
}

template <typename T, size_t max_size>
bool MinHeap::MinHeap<T, max_size>::IsFull()
{
    return m_values_amount == max_size;
}

template <typename T, size_t max_size>
bool MinHeap::MinHeap<T, max_size>::MinHeapify(size_t uneven_head)
{
    size_t smallest_index = uneven_head;
    size_t left_child_index = LEFT_CHILD(uneven_head);
    size_t right_child_index = RIGHT_CHILD(uneven_head);

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
bool MinHeap::MinHeap<T, max_size>::SwapValues(size_t index1, size_t index2)
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

#endif //__MIN_HEAP_HPP__
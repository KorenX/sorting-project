#include "inc/MinHeap/MinHeap.h"

template <typename T, size_t max_size>
bool MinHeap<T, max_size>::BuildMinHeap(T* unsorted_array, size_t values_count)
{
    m_initialized = false;

    if (unsorted_array == nullptr || values_count > max_size)
    {
        return false;
    }

    for (size_t i = 0; i < values_count; i++)
    {
        m_values[i] = unsorted_array[i];
    }

    m_values_amount = values_count;
    
    for (size_t i = m_values_amount/2; i >= 0; i--)
    {
        if (!MinHeapify(i))
        {
            return false;
        }
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
    if (!m_initialized)
    {
        return false;
    }

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
        T swap_temp = m_values[uneven_head];
        m_values[uneven_head] = m_values[smallest_index];
        m_values[smallest_index] = swap_temp;
        return MinHeapify(smallest_index);
    }

    return true;
}

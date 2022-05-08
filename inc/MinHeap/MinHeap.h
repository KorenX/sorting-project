#ifndef __MIN_HEAP_H__
#define __MIN_HEAP_H__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#define LEFT_CHILD(head) (head<<1)
#define RIGHT_CHILD(head) ((head<<1)+1)

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

#ifdef TESTING_BUILD
public:
#else
private:
#endif

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

#include "src/MinHeap/MinHeap.hpp"

#endif //__MIN_HEAP_H__
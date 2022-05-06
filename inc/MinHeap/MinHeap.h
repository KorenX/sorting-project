#include <stdint.h>

/*
    An implementation of MinHeap for this project's use.
    typename T - the values held in the inner array
    size_t max_size - the max number of values in the stack

    In theory, all of the MinHeap functions can work inplace on a given array,
    but in practice it would make the functions be written as if we were using C,
    and I would like to use C++ for this excercise, so please ignore the additional
    used in this implementation.
*/

template <typename T, size_t max_size>
namespace MinHeap
{
public:
    bool BuildMinHeap(T* unsorted_array, size_t values_count);

    bool ExtractMin(T& o_min);
private:
    bool MaxHeapify(size_t uneven_head);

    T m_values[max_size];
    size_t m_values_amount;
};
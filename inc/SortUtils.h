#ifndef __SORT_UTILS_H__
#define __SORT_UTILS_H__

namespace SortUtils
{
    /**
     * This function swaps two values inplace
     *
     * @param p_value1 - the first value, will be swapped with p_value2
     * @param p_value2 - the second value, will be swapped with p_value1
     *
     * @returns true if the function was successful, false otherwise.
     */
    template <typename T>
    bool SwapValues(T* p_value1, T* p_value2);
}

#include "src/SortUtils.hpp"

#endif //__SORT_UTILS_H__
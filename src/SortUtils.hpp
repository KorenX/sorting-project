#ifndef __SORT_UTILS_HPP__
#define __SORT_UTILS_HPP__

#include "inc/SortUtils.h"

template <typename T>
bool SortUtils::SwapValues(T* p_value1, T* p_value2)
{
    if (p_value1 == nullptr || p_value2 == nullptr)
    {
        return false;
    }

    if (p_value1 == p_value2)
    {
        return true;
    }

    T swap_temp = *p_value1;
    *p_value1 = *p_value2;
    *p_value2 = swap_temp;

    return true;
}

#endif //__SORT_UTILS_HPP__
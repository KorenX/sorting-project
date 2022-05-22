#include "inc/MinHeap/MinHeap.h"
#include "tests/TestsUtils.h"
#include <stdlib.h>

template <typename T>
size_t GetMinimumIndex(T* array, size_t count)
{
    T min = array[0];
    size_t min_index = 0;
    for (size_t i = 1; i < count; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
            min_index = i;
        }
    }

    return min_index;
}

void MinHeapTests();
bool MinHeapTest_IsEmptyBasicUse();
bool MinHeapTest_IsFullBasicUse();
bool MinHeapTest_InitialHeadIsSmallest();
bool MinHeapTest_ValuesFitMinHeapStruct();
bool MinHeapTest_ExtractMinAlwaysRemovesMin();
bool MinHeapTest_GetComparisonCounterBasicUse();
bool MinHeapTest_ResetComparisonCounterBasicUse();

void MinHeapTests()
{
    RUN_TEST(MinHeapTest_IsEmptyBasicUse);
    RUN_TEST(MinHeapTest_IsFullBasicUse);
    RUN_RANDOM_TEST(MinHeapTest_InitialHeadIsSmallest, RANDOM_TESTS_AMOUNT);
    RUN_RANDOM_TEST(MinHeapTest_ValuesFitMinHeapStruct, RANDOM_TESTS_AMOUNT);
    RUN_RANDOM_TEST(MinHeapTest_ExtractMinAlwaysRemovesMin, RANDOM_TESTS_AMOUNT);
    RUN_RANDOM_TEST(MinHeapTest_GetComparisonCounterBasicUse, RANDOM_TESTS_AMOUNT);
    RUN_RANDOM_TEST(MinHeapTest_ResetComparisonCounterBasicUse, RANDOM_TESTS_AMOUNT);
    FINISH_RUNNING_TESTS(MinHeapTests);
}

bool MinHeapTest_IsEmptyBasicUse()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 1000;

    MinHeap::MinHeap<int, ARRAY_SIZE> mheap;

    bool res = mheap.IsEmpty();
    ASSERT_TRUE(res);
    TEST_END;
}

bool MinHeapTest_IsFullBasicUse()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 1000;

    int arr[ARRAY_SIZE] = {};
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = rand() % VALUES_CAP;
    }

    MinHeap::MinHeap<int, ARRAY_SIZE> mheap;
    bool res = mheap.BuildMinHeap(arr, ARRAY_SIZE);
    ASSERT_TRUE(res);
    res = mheap.IsFull();
    ASSERT_TRUE(res);
    TEST_END;
}

bool MinHeapTest_InitialHeadIsSmallest()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 1000;

    int arr[ARRAY_SIZE] = {};
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = rand() % VALUES_CAP;
    }

    MinHeap::MinHeap<int, ARRAY_SIZE> mheap;
    bool res = mheap.BuildMinHeap(arr, ARRAY_SIZE);
    ASSERT_TRUE(res);
    int min = 0;
    res = mheap.ExtractMin(min);
    ASSERT_TRUE(res);
    
    ASSERT_EQ(min, arr[GetMinimumIndex(arr, ARRAY_SIZE)]);
    TEST_END;
}

bool MinHeapTest_ValuesFitMinHeapStruct()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 1000;

    int arr[ARRAY_SIZE] = {};
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = rand() % VALUES_CAP;
    }

    MinHeap::MinHeap<int, ARRAY_SIZE> mheap;
    bool res = mheap.BuildMinHeap(arr, ARRAY_SIZE);
    ASSERT_TRUE(res);
    for (size_t i = 0; i < ARRAY_SIZE/2; i++)
    {
        if (LEFT_CHILD(i) < ARRAY_SIZE)
        {
            ASSERT_LE(mheap.m_values[i], mheap.m_values[LEFT_CHILD(i)]);
        }

        if (RIGHT_CHILD(i) < ARRAY_SIZE)
        {
            ASSERT_LE(mheap.m_values[i], mheap.m_values[RIGHT_CHILD(i)]);
        }
    }

    TEST_END;
}

bool MinHeapTest_ExtractMinAlwaysRemovesMin()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 1000;

    int arr[ARRAY_SIZE] = {};
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = rand() % VALUES_CAP;
    }

    MinHeap::MinHeap<int, ARRAY_SIZE> mheap;
    bool res = mheap.BuildMinHeap(arr, ARRAY_SIZE);
    ASSERT_TRUE(res);
    
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        int min = 0;
        res = mheap.ExtractMin(min);
        ASSERT_TRUE(res);
        
        size_t min_index = GetMinimumIndex(arr, ARRAY_SIZE);
        ASSERT_EQ(min, arr[min_index]);
        // This makes sure the values will not be the minimum value again
        arr[min_index] = VALUES_CAP;
    }

    res = mheap.IsEmpty();
    ASSERT_TRUE(res);

    TEST_END;
}

bool MinHeapTest_GetComparisonCounterBasicUse()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 100000;
    
    MinHeap::MinHeap<int, ARRAY_SIZE> mheap;
    size_t random_value = rand() % VALUES_CAP;
    mheap.m_comparison_counter = random_value;
    size_t actual_value = mheap.GetComparisonCounter();
    ASSERT_EQ(actual_value, random_value);
    TEST_END;
}

bool MinHeapTest_ResetComparisonCounterBasicUse()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 100000;
    
    MinHeap::MinHeap<int, ARRAY_SIZE> mheap;
    size_t random_value = rand() % VALUES_CAP;
    mheap.m_comparison_counter = random_value;
    mheap.ResetComparisonCounter();
    size_t actual_value = mheap.GetComparisonCounter();
    ASSERT_EQ(actual_value, 0);
    TEST_END;
}

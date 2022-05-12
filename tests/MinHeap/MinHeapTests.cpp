#include "inc/MinHeap/MinHeap.h"
#include <stdlib.h>
#include <time.h>
#include "tests/TestsUtils.h"

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

void MinHeapTests()
{
    srand(time(0));
    RUN_TEST(MinHeapTest_IsEmptyBasicUse);
    RUN_TEST(MinHeapTest_IsFullBasicUse);
    RUN_RANDOM_TEST(MinHeapTest_InitialHeadIsSmallest, RANDOM_TESTS_AMOUNT);
    RUN_RANDOM_TEST(MinHeapTest_ValuesFitMinHeapStruct, RANDOM_TESTS_AMOUNT);
    RUN_RANDOM_TEST(MinHeapTest_ExtractMinAlwaysRemovesMin, RANDOM_TESTS_AMOUNT);
    FINISH_RUNNING_TESTS(MinHeapTests);
}

bool MinHeapTest_IsEmptyBasicUse()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 1000;

    MinHeap::MinHeap<int, ARRAY_SIZE> mheap;

    ASSERT_TRUE(mheap.IsEmpty());
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
    ASSERT_TRUE(mheap.BuildMinHeap(arr, ARRAY_SIZE));
    ASSERT_TRUE(mheap.IsFull());
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
    ASSERT_TRUE(mheap.BuildMinHeap(arr, ARRAY_SIZE));
    int min = 0;
    ASSERT_TRUE(mheap.ExtractMin(min));
    
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
    ASSERT_TRUE(mheap.BuildMinHeap(arr, ARRAY_SIZE));
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
    ASSERT_TRUE(mheap.BuildMinHeap(arr, ARRAY_SIZE));
    
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        int min = 0;
        ASSERT_TRUE(mheap.ExtractMin(min));
        
        size_t min_index = GetMinimumIndex(arr, ARRAY_SIZE);
        ASSERT_EQ(min, arr[min_index]);
        // This makes sure the values will not be the minimum value again
        arr[min_index] = VALUES_CAP;
    }

    ASSERT_TRUE(mheap.IsEmpty());

    TEST_END;
}

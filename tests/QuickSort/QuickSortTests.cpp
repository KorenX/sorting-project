#include "inc/QuickSort/QuickSort.h"
#include "tests/TestsUtils.h"
#include <stdlib.h>

bool QuickSortTests_ArrayIsSorted();
bool QuickSortTests_PartitionGeneralUse();
bool QuickSortTests_RandomizedPartitionGeneralUse();
bool QuickSortTests_RandomizedSelectGeneralUse();
bool QuickSortTest_GetComparisonCounterBasicUse();
bool QuickSortTest_ResetComparisonCounterBasicUse();

void QuickSortTests()
{
    RUN_RANDOM_TEST(QuickSortTests_ArrayIsSorted, RANDOM_TESTS_AMOUNT)
    RUN_RANDOM_TEST(QuickSortTests_PartitionGeneralUse, RANDOM_TESTS_AMOUNT)
    RUN_RANDOM_TEST(QuickSortTests_RandomizedPartitionGeneralUse, RANDOM_TESTS_AMOUNT)
    RUN_RANDOM_TEST(QuickSortTests_RandomizedSelectGeneralUse, RANDOM_TESTS_AMOUNT)
    RUN_RANDOM_TEST(QuickSortTest_GetComparisonCounterBasicUse, RANDOM_TESTS_AMOUNT)
    RUN_RANDOM_TEST(QuickSortTest_ResetComparisonCounterBasicUse, RANDOM_TESTS_AMOUNT)
    FINISH_RUNNING_TESTS(QuickSortTests);
}

bool QuickSortTests_ArrayIsSorted()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 1000;

    int arr[ARRAY_SIZE] = {};
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = rand() % VALUES_CAP;
    }

    bool res = QuickSort::QuickSort(arr, 0, ARRAY_SIZE - 1);
    ASSERT_TRUE(res);
    for (size_t i = 0; i < ARRAY_SIZE/2; i++)
    {
        if (i + 1 < ARRAY_SIZE)
        {
            ASSERT_LE(arr[i], arr[i + 1]);
        }
    }

    TEST_END;
}

bool QuickSortTests_PartitionGeneralUse()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 1000;

    int arr[ARRAY_SIZE] = {};
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = rand() % VALUES_CAP;
    }

    int original_pivot = arr[ARRAY_SIZE - 1];
    size_t pivot_new_index = QuickSort::Partition(arr, 0, ARRAY_SIZE - 1);
    ASSERT_EQ(original_pivot, arr[pivot_new_index]);
    for (size_t i = 0; i < pivot_new_index; i++)
    {
        ASSERT_LE(arr[i], original_pivot);
    }

    for (size_t i = pivot_new_index + 1; i < ARRAY_SIZE; i++)
    {
        ASSERT_GT(arr[i], original_pivot);
    }

    TEST_END;
}

bool QuickSortTests_RandomizedPartitionGeneralUse()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 1000;

    int arr[ARRAY_SIZE] = {};
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = rand() % VALUES_CAP;
    }

    size_t pivot_new_index = QuickSort::RandomizedPartition(arr, 0, ARRAY_SIZE - 1);
    int pivot_value = arr[pivot_new_index];
    for (size_t i = 0; i < pivot_new_index; i++)
    {
        ASSERT_LE(arr[i], pivot_value);
    }

    for (size_t i = pivot_new_index + 1; i < ARRAY_SIZE; i++)
    {
        ASSERT_GT(arr[i], pivot_value);
    }

    TEST_END;
}

bool QuickSortTests_RandomizedSelectGeneralUse()
{
    static constexpr size_t ARRAY_SIZE = 10;
    static constexpr size_t VALUES_CAP = 1000;

    int arr[ARRAY_SIZE] = {};
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = rand() % VALUES_CAP;
    }

    size_t look_up_index = rand() % ARRAY_SIZE;

    bool res = QuickSort::RandomizedSelect(arr, 0, ARRAY_SIZE - 1, look_up_index);
    ASSERT_TRUE(res);

    int pivot_value = arr[look_up_index];
    for (size_t i = 0; i < look_up_index; i++)
    {
        ASSERT_LE(arr[i], pivot_value);
    }

    for (size_t i = look_up_index + 1; i < ARRAY_SIZE; i++)
    {
        ASSERT_GE(arr[i], pivot_value);
    }

    TEST_END;
}

bool QuickSortTest_GetComparisonCounterBasicUse()
{
    static constexpr size_t VALUES_CAP = 100000;
    
    size_t random_value = rand() % VALUES_CAP;
    QuickSort::comparison_counter = random_value;
    size_t actual_value = QuickSort::GetComparisonCounter();
    ASSERT_EQ(actual_value, random_value);
    TEST_END;
}

bool QuickSortTest_ResetComparisonCounterBasicUse()
{
    static constexpr size_t VALUES_CAP = 100000;
    
    size_t random_value = rand() % VALUES_CAP;
    QuickSort::comparison_counter = random_value;
    QuickSort::ResetComparisonCounter();
    size_t actual_value = QuickSort::GetComparisonCounter();
    ASSERT_EQ(actual_value, 0);
    TEST_END;
}

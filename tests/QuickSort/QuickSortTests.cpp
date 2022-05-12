#include "inc/QuickSort/QuickSort.h"
#include "tests/TestsUtils.h"
#include <stdlib.h>

bool QuickSortTests_ArrayIsSorted();
bool QuickSortTests_PartitionGeneralUse();

void QuickSortTests()
{
    RUN_RANDOM_TEST(QuickSortTests_ArrayIsSorted, RANDOM_TESTS_AMOUNT)
    RUN_RANDOM_TEST(QuickSortTests_PartitionGeneralUse, RANDOM_TESTS_AMOUNT)
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

    ASSERT_TRUE(QuickSort::QuickSort(arr, 0, ARRAY_SIZE - 1));
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

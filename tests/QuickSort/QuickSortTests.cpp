#include "inc/QuickSort/QuickSort.h"
#include <stdlib.h>
#include <time.h>
#include "tests/TestsUtils.h"

bool QuickSortTests_ArrayIsSorted();

void QuickSortTests()
{
    srand(time(0));
    RUN_RANDOM_TEST(QuickSortTests_ArrayIsSorted, RANDOM_TESTS_AMOUNT)
    FINISH_RUNNING_TESTS(QuickSortTests);
}

bool QuickSortTests_ArrayIsSorted()
{
    static constexpr size_t ARRAY_SIZE = 4;
    static constexpr size_t VALUES_CAP = 1000;

    int arr[ARRAY_SIZE] = {1, 3, 4, 2};
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

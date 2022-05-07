#include "inc/MinHeap/MinHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ASSERT_EQ(a, b) if(a!=b) {printf("expected value " # a " which is %x to be equal to " # b " which is %x\n",a,b);return false;}
#define ASSERT_NE(a, b) if(a==b) return false;
#define ASSERT_GE(a, b) if(a<b) return false;
#define ASSERT_LE(a, b) if(a>b) return false;
#define ASSERT_GT(a, b) if(a<=b) return false;
#define ASSERT_LT(a, b) if(a>=b) return false;
#define ASSERT_TRUE(a) ASSERT_EQ(a, true)
#define TEST_END return true

#define TEST_FAILED(test_function) printf("test named " # test_function  " failed\n")
#define RUN_TEST(test_function) if(!test_function()) TEST_FAILED(test_function)
#define FINISH_RUNNING_TESTS printf("finished running tests\n")

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

void RunMinHeapTests();
bool MinHeapTest_InitialHeadIsSmallest();

int main()
{
    RunMinHeapTests();
    return 0;
}

void RunMinHeapTests()
{
    srand(time(0));
    RUN_TEST(MinHeapTest_InitialHeadIsSmallest);
    FINISH_RUNNING_TESTS;
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

    MinHeap<int, ARRAY_SIZE> mheap;
    ASSERT_TRUE(mheap.BuildMinHeap(arr, ARRAY_SIZE));
    int min = 0;
    ASSERT_TRUE(mheap.ExtractMin(min));
    
    ASSERT_EQ(min, arr[GetMinimumIndex(arr, ARRAY_SIZE)]);
    TEST_END;
}
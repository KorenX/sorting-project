#include "inc/MinHeap/MinHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#define ASSERT_EQ(a, b) if(a!=b) {printf("expected value " # a " which is %x to be equal to " # b " which is %x\n",a,b);return false;}
#define ASSERT_NE(a, b) if(a==b) {printf("expected value " # a " which is %x to be different than " # b " which is %x\n",a,b);return false;}
#define ASSERT_GE(a, b) if(a<b) {printf("expected value " # a " which is %x to be greater or equal to " # b " which is %x\n",a,b);return false;}
#define ASSERT_LE(a, b) if(a>b) {printf("expected value " # a " which is %x to be smaller or equal to " # b " which is %x\n",a,b);return false;}
#define ASSERT_GT(a, b) if(a<=b) {printf("expected value " # a " which is %x to be greater than " # b " which is %x\n",a,b);return false;}
#define ASSERT_LT(a, b) if(a>=b) {printf("expected value " # a " which is %x to be smaller than " # b " which is %x\n",a,b);return false;}
#define ASSERT_TRUE(a) ASSERT_EQ(a, true)
#define TEST_END return true

#define TEST_FAILED(test_function) printf("test named " # test_function  RED " failed\n" RESET)
#define TEST_SUCCEEDED(test_function) printf("test named " # test_function  GREEN " succeeded\n" RESET)
#define RUN_TEST(test_function) if(!test_function()) TEST_FAILED(test_function); else TEST_SUCCEEDED(test_function);
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
bool MinHeapTest_ValuesFitMinHeapStruct();
bool MinHeapTest_ExtractMinAlwaysRemovesMin();

int main()
{
    RunMinHeapTests();
    return 0;
}

void RunMinHeapTests()
{
    srand(time(0));
    RUN_TEST(MinHeapTest_InitialHeadIsSmallest);
    RUN_TEST(MinHeapTest_ValuesFitMinHeapStruct);
    RUN_TEST(MinHeapTest_ExtractMinAlwaysRemovesMin);
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
        arr[min_index] = VALUES_CAP;
    }

    TEST_END;
}

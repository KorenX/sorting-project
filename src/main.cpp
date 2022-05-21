#include <stdio.h>
#include "inc/MinHeap/MinHeap.h"
#include "inc/QuickSort/QuickSort.h"
#include <stdlib.h>
#include <time.h>

static constexpr size_t MAX_ARRAY_SIZE = 5000;
static constexpr char ARRAY_SIZE_INPUT_MESSAGE_FORMAT[] = "please input the amount of values you want to be in the array (Maximum %lu): ";
static constexpr char SUBARRAY_SIZE_INPUT_MESSAGE_FORMAT[] = "please input the amount of values you want sorted from the array (Maximum %lu): ";
static constexpr size_t MAX_SIZE_T_CHARS = 10;

static constexpr char USER_ENTER_OWN_ARRAY_VALUES[] = "Would you like to enter your own values?\n";

size_t GetSmallerValue(size_t value, const char* request_message);
bool GetYesNoValue(const char* request_message);
void GetArrayValues(int* array, size_t values_amount);
void GetRandomArrayValues(int* array, size_t values_amount);

void PerformMinHeapMethodSorting(int* array, size_t array_size, size_t to_sort_amount);
void PerformSelectQuickSortMethodSorting(int* array, size_t array_size, size_t to_sort_amount);
void PrintArray(int* array, size_t array_size);

int main(int argc, const char* argv[])
{
    srand(time(0));
    int values_array[MAX_ARRAY_SIZE] = {};

    // Get the n in the question
    char request_array_message[sizeof(ARRAY_SIZE_INPUT_MESSAGE_FORMAT) + MAX_SIZE_T_CHARS];
    snprintf(request_array_message, sizeof(request_array_message), ARRAY_SIZE_INPUT_MESSAGE_FORMAT, MAX_ARRAY_SIZE);
    size_t array_size = GetSmallerValue(MAX_ARRAY_SIZE, request_array_message);
    
    // Get in k in the question
    char request_subarray_message[sizeof(SUBARRAY_SIZE_INPUT_MESSAGE_FORMAT) + MAX_SIZE_T_CHARS];
    snprintf(request_subarray_message, sizeof(request_subarray_message), SUBARRAY_SIZE_INPUT_MESSAGE_FORMAT, array_size);
    size_t sorted_subarray_size = GetSmallerValue(array_size, request_subarray_message);

    bool enter_own_values = GetYesNoValue(USER_ENTER_OWN_ARRAY_VALUES);

    if (enter_own_values)
    {
        GetArrayValues(values_array, array_size);
    }
    else
    {
        GetRandomArrayValues(values_array, array_size);
    }

    printf("values array size: %lu\namount of values to sort: %lu\n%s values \n", array_size, sorted_subarray_size, enter_own_values?"own inserted":"random");

    PerformMinHeapMethodSorting(values_array, array_size, sorted_subarray_size);
    // Since MinHeap doesn't perform the sorting inplace, we don't need to reorder the array
    PerformSelectQuickSortMethodSorting(values_array, array_size, sorted_subarray_size);
    // Since QuickSort performs the sorting inplace, now the first K values are sorted and ready to print
    PrintArray(values_array, sorted_subarray_size);
}

size_t GetSmallerValue(size_t value, const char* request_message)
{
    size_t array_size = value + 1;
    while (array_size > value)
    {
        printf(request_message);
        fflush(stdout);
        scanf("%lu", &array_size);
    }

    return array_size;
}

bool GetYesNoValue(const char* request_message)
{
    static constexpr char YES = 'y';
    static constexpr char NO = 'n';
    char answer = '\0';
    while (answer != YES && answer != NO)
    {
        printf(request_message);
        printf("enter %c for yes or %c for no: ", YES, NO);
        fflush(stdout);
        fflush(stdin);
        scanf("%c", &answer);
    }

    return answer == YES;
}

void GetArrayValues(int* array, size_t values_amount)
{
    for (size_t i = 0; i < values_amount; i++)
    {
        printf("please enter value for array index %lu: ", i);
        fflush(stdout);
        scanf("%d", &(array[i]));
    }
}

void GetRandomArrayValues(int* array, size_t values_amount)
{
    static constexpr size_t RANDOM_VALUES_CAP = 1000;
    for (size_t i = 0; i < values_amount; i++)
    {
        array[i] = rand() % RANDOM_VALUES_CAP;
    }
}

void PerformMinHeapMethodSorting(int* array, size_t array_size, size_t to_sort_amount)
{
    MinHeap::MinHeap<int, MAX_ARRAY_SIZE> mheap;
    // Make sure comparison counter is at 0
    mheap.ResetComparisonCounter();
    if (!mheap.BuildMinHeap(array, array_size))
    {
        printf("MinHeap building failed!\n");
        return;
    }

    for (size_t i = 0; i < to_sort_amount; i++)
    {
        int min;
        if (!mheap.ExtractMin(min))
        {
            printf("MinHeap extract min %lu failed!\n", i);
            return;
        }
    }

    printf("MinHeap Method required %lu value comparisons!\n", mheap.GetComparisonCounter());
}

void PerformSelectQuickSortMethodSorting(int* array, size_t array_size, size_t to_sort_amount)
{
    // Make sure comparison counter is at 0
    QuickSort::ResetComparisonCounter();
    if (!QuickSort::RandomizedSelect(array, 0, array_size - 1, to_sort_amount - 1))
    {
        printf("QuickSort Selection failed!\n");
        return;
    }

    if (!QuickSort::QuickSort(array, 0, to_sort_amount - 1))
    {
        printf("QuickSort Subarray Sorting failed!\n");
        return;
    }

    printf("QuickSort Method required %lu value comparisons!\n", QuickSort::GetComparisonCounter());
}

void PrintArray(int* array, size_t array_size)
{
    static constexpr size_t NEW_LINE_VALUES_AMOUNT = 16;
    for (size_t i = 0; i < array_size; i++)
    {
        printf("%04d, ", array[i]);
        if (i % NEW_LINE_VALUES_AMOUNT == NEW_LINE_VALUES_AMOUNT - 1)
        {
            printf("\n");
        }
    }

    printf("\nFinished printing array values\n");
}

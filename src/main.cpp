#include <stdio.h>
#include "inc/MinHeap/MinHeap.h"
#include "inc/QuickSort/QuickSort.h"
#include <stdlib.h>
#include <time.h>

static constexpr size_t MAX_ARRAY_SIZE = 5000;
static constexpr char ARRAY_SIZE_INPUT_MESSAGE_FORMAT[] = "please input the amount of values you want to be in the array (Maximum %lu): ";
static constexpr char SUBARRAY_SIZE_INPUT_MESSAGE_FORMAT[] = "please input the amount of values you want sorted from the array (Maximum %lu): ";
static constexpr size_t MAX_SIZE_T_CHARS = 10;

static constexpr char AUTO_OR_MANUAL_MODE[] = "Would you like to run the auto mode?\n";
static constexpr char USER_ENTER_OWN_ARRAY_VALUES[] = "Would you like to enter your own values?\n";

/**
 * Get an input from the user which is a smaller integer than the value param.
 * 
 * @param value the value the input has to be larger than
 * @param request_message the message to print to the user before getting user input
 * @return size_t the value from the user
 */
size_t GetSmallerValue(size_t value, const char *request_message);

/**
 * Get an input from the user which is an answer to a yes/no question
 * 
 * @param request_message the yes/no question
 * @return true if the user said yes
 * @return false if the user said no
 */
bool GetYesNoValue(const char *request_message);

/**
 * Fills an array with values from the user
 * 
 * @param array the array to fill
 * @param values_amount the amount of values to get as inputs
 */
void GetArrayValues(int *array, size_t values_amount);

/**
 * Fills an array with randomly generated values
 * 
 * @param array the array to fill
 * @param values_amount the amount of values to randomly get
 */
void GetRandomArrayValues(int *array, size_t values_amount);

/**
 * Runs the code as requested in the question, with predetermined n and k values 
 */
void RunAutoSetup();

/**
 * Runs the code with user input, for one single use of the comparison module 
 */
void RunManualSetup();

/**
 * Runs a single use of the comparison modules with the passed arguments
 * 
 * @param array_size the amount of values to use (n in the question)
 * @param to_sort_amount the amount of values to sort (k in the question)
 * @param own_values should we get user inputs or random values (true for user input)
 * @param verbose [DEFAULT-TRUE] should we print the sorted array in the end of the function
 */
void RunSingleSetup(size_t array_size, size_t to_sort_amount, bool own_values, bool verbose=true);

/**
 * Takes the given array, puts it into a temporary array, makes that array into a minimum heap,
 * and extracts the head an amount of time equal to to_sort_amount
 * 
 * @param array the array to build the minheap from 
 * @param array_size the amount of values in the array
 * @param to_sort_amount the amount of values to extract from the head
 * @return size_t the amount of value comparisons done through the whole run of the function
 */
size_t PerformMinHeapMethodSorting(int *array, size_t array_size, size_t to_sort_amount);

/**
 * Takes the given array, uses partition functions to get a subarray the size of to_sort_amount of
 * the smallest numbers, and uses quicksort to sort that subarray
 * 
 * @param array the array to partition and sort
 * @param array_size the amount of values in the array
 * @param to_sort_amount the amount of values that needs to be partitioned and sorted
 * @return size_t the amount of value comparisons done through the whole run of the function
 */
size_t PerformSelectQuickSortMethodSorting(int *array, size_t array_size, size_t to_sort_amount);

/**
 * Prints array values in order 
 * 
 * @param array the array to print
 * @param array_size the amount of values in the array
 */
void PrintArray(int *array, size_t array_size);

int main(int argc, const char *argv[])
{
    srand(time(0));
    bool auto_mode = GetYesNoValue(AUTO_OR_MANUAL_MODE);
    if (auto_mode)
    {
        RunAutoSetup();
    }
    else
    {
        RunManualSetup();
    }

    return 0;
}

void RunAutoSetup()
{
    //fill in array setup
    static constexpr size_t AMOUNT_OF_N_VALUES = 4;
    static constexpr size_t AMOUNT_OF_K_VALUES = 3;
    size_t n_values[AMOUNT_OF_N_VALUES] = {100, 200, 500, 1000};
    size_t k_values[AMOUNT_OF_K_VALUES] = {8, 50, 100};
    for (size_t i = 0; i < AMOUNT_OF_N_VALUES; i++)
    {
        for (size_t j = 0; j < AMOUNT_OF_K_VALUES; j++)
        {
            RunSingleSetup(n_values[i], k_values[j], false, false);
        }
    }

    printf("\nfinished running auto setup\n");
}

void RunManualSetup()
{
    // Get the n in the question
    char request_array_message[sizeof(ARRAY_SIZE_INPUT_MESSAGE_FORMAT) + MAX_SIZE_T_CHARS];
    snprintf(request_array_message, sizeof(request_array_message), ARRAY_SIZE_INPUT_MESSAGE_FORMAT, MAX_ARRAY_SIZE);
    size_t array_size = GetSmallerValue(MAX_ARRAY_SIZE, request_array_message);

    // Get in k in the question
    char request_subarray_message[sizeof(SUBARRAY_SIZE_INPUT_MESSAGE_FORMAT) + MAX_SIZE_T_CHARS];
    snprintf(request_subarray_message, sizeof(request_subarray_message), SUBARRAY_SIZE_INPUT_MESSAGE_FORMAT, array_size);
    size_t sorted_subarray_size = GetSmallerValue(array_size, request_subarray_message);

    bool enter_own_values = GetYesNoValue(USER_ENTER_OWN_ARRAY_VALUES);

    RunSingleSetup(array_size, sorted_subarray_size, enter_own_values);
}

void RunSingleSetup(size_t array_size, size_t to_sort_amount, bool own_values, bool verbose)
{
    int values_array[MAX_ARRAY_SIZE] = {};
    
    if (own_values)
    {
        GetArrayValues(values_array, array_size);
    }
    else
    {
        GetRandomArrayValues(values_array, array_size);
    }

    printf("values array size: %lu\namount of values to sort: %lu\n%s values \n", array_size, to_sort_amount, own_values ? "own inserted" : "random");

    size_t mheap_counter = PerformMinHeapMethodSorting(values_array, array_size, to_sort_amount);
    // Since MinHeap doesn't perform the sorting inplace, we don't need to reorder the array
    size_t qsort_counter = PerformSelectQuickSortMethodSorting(values_array, array_size, to_sort_amount);
    
    printf("comparisons in minheap method: %lu\ncomparisons in quicksort method: %lu\n", mheap_counter, qsort_counter);
    
    // Since QuickSort performs the sorting inplace, now the first K values are sorted and ready to print
    if (verbose)
    {
        PrintArray(values_array, to_sort_amount);
    }
}

size_t GetSmallerValue(size_t value, const char *request_message)
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

bool GetYesNoValue(const char *request_message)
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

void GetArrayValues(int *array, size_t values_amount)
{
    for (size_t i = 0; i < values_amount; i++)
    {
        printf("please enter value for array index %lu: ", i);
        fflush(stdout);
        scanf("%d", &(array[i]));
    }
}

void GetRandomArrayValues(int *array, size_t values_amount)
{
    static constexpr size_t RANDOM_VALUES_CAP = 1000;
    for (size_t i = 0; i < values_amount; i++)
    {
        array[i] = rand() % RANDOM_VALUES_CAP;
    }
}

size_t PerformMinHeapMethodSorting(int *array, size_t array_size, size_t to_sort_amount)
{
    MinHeap::MinHeap<int, MAX_ARRAY_SIZE> mheap;
    // Make sure comparison counter is at 0
    mheap.ResetComparisonCounter();
    if (!mheap.BuildMinHeap(array, array_size))
    {
        printf("MinHeap building failed!\n");
        return 0;
    }

    for (size_t i = 0; i < to_sort_amount; i++)
    {
        int min;
        if (!mheap.ExtractMin(min))
        {
            printf("MinHeap extract min %lu failed!\n", i);
            return 0;
        }
    }

    return mheap.GetComparisonCounter();
}

size_t PerformSelectQuickSortMethodSorting(int *array, size_t array_size, size_t to_sort_amount)
{
    // Make sure comparison counter is at 0
    QuickSort::ResetComparisonCounter();
    if (!QuickSort::RandomizedSelect(array, 0, array_size - 1, to_sort_amount - 1))
    {
        printf("QuickSort Selection failed!\n");
        return 0;
    }

    if (!QuickSort::QuickSort(array, 0, to_sort_amount - 1))
    {
        printf("QuickSort Subarray Sorting failed!\n");
        return 0;
    }

    return QuickSort::GetComparisonCounter();
}

void PrintArray(int *array, size_t array_size)
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

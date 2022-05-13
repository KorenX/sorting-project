#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "tests/TestsUtils.h"

extern void MinHeapTests();
extern void QuickSortTests();

int main()
{
    srand(time(0));
    MinHeapTests();
    QuickSortTests();
    printf("%u tests have failed \n", tests_failed);
    return 0;
}
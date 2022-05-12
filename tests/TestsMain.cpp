#include <stdlib.h>
#include <time.h>

extern void MinHeapTests();
extern void QuickSortTests();

int main()
{
    srand(time(0));
    MinHeapTests();
    QuickSortTests();
    return 0;
}
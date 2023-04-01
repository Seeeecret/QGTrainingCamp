
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SortSystem.h"


int arr[200000];
int main() {
    int RANDMAX = 0x7fff;
    int *a = createTinyArray();
    //insetSort(a, 100);
    //mergeSort(a, 0, 99);
    //quickSort(a, 100);
    //countSort(a, 100);
    radixCountSort(a, 100);
    printArray(a, 100);
    return 0;
}

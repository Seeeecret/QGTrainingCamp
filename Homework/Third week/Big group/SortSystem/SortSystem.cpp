
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SortSystem.h"


int arr[100];
int main() {
    int RANDMAX = 0x7fff;
    //int* arr = createColorSortArray(10);
    int *a = createTinyArray();
    //insetSort(a, 100);
    //mergeSort(a, 0, 99);
    //printf("%d\n\n", findKthLargest(a, 100, 100));
    //quickSort(a, 100);
    //quickSort2(a, 100);
    bubbleSort(a, 100);
    //countSort(a, 100);
    //radixCountSort(arr, 100);
    //colorSort(arr,10);
    
    printArray(a, 100);
    //writeArrayToFile(a, 100);
    return 0;
}

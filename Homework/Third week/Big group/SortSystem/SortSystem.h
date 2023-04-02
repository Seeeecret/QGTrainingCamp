#define _CRT_SECURE_NO_WARNINGS 1
#define BASE 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <queue>
void printArray(int* arr, int length);
void CountSort(int* arr, int length);
void mergeSort(int* array, int left, int right);
void merge(int* array, int left, int mid, int right);
void writeArrayToFile(int* arr, int length);
int* readArrayFromFile(int length);
/*
	本系统集成插入排序、归并排序、快速排序、计数排序、计数排序的排序算法并且能输出各种数据量大小及各种次数下的排序用时
	也支持生成测试数据到.txt和从.txt中读取数据的功能
*/

void printArray(int* arr,int length) {
	int i;
	for (i = 0; i < length; i++) {
		printf("%d  ", arr[i]);
	}
}

int* createBigArray() {// 创建一个长度为200000并填充有随机非负整数的数组
	int i;
	int* arr = (int*)malloc(sizeof(int) * 200000);
	// 设置随机数种子
	srand(time(NULL));
	// 填充数组
	for (i = 0; i < 200000; i++) {
		arr[i] = rand();
	}
	// 输出数组
	return arr;
}
int* createMediumArray() {// 创建一个长度为50000并填充有随机非负整数的数组
	int i;
	int* arr = (int*)malloc(sizeof(int) * 50000);
	// 设置随机数种子
	srand(time(NULL));
	// 填充数组
	for (i = 0; i < 50000; i++) {
		arr[i] = rand();
	}
	// 输出数组
	return arr;

}
int* createSmallArray() {// 创建一个长度为10000并填充有随机非负整数的数组
	int i;
	int* arr = (int*)malloc(sizeof(int) * 10000);
	// 设置随机数种子
	srand(time(NULL));
	// 填充数组
	for (i = 0; i < 10000; i++) {
		arr[i] = rand();
	}
	// 输出数组
	return arr;

}

int* createTinyArray() {// 创建一个大小为100并填充有随机非负整数的数组

	int i;
	int* arr = (int*)malloc(sizeof(int) * 100);
	// 设置随机数种子
	srand(time(NULL));
	// 填充数组
	for (i = 0; i < 100; i++) {
		arr[i] = rand();
	}
	// 输出数组
	return arr;

}
int* createColorSortArray(int length) {
	int* arr = (int*)malloc(sizeof(int) * length);
	// 设置随机数种子
	srand(time(NULL));
	// 填充数组
	for (int i = 0; i < length; i++) {
		arr[i] = rand() % 3;
	}
	return arr;

}



void colorSort(int* arr,int length) {
		int p0 = 0; 
		int p2 = length -1; 
		int i = 0;
		while ( i <= p2) {
			if (arr[i] == 0) {
				arr[i] = arr[p0];
				arr[p0] = 0;
				p0++;
				i++;
			}
			else if (arr[i] == 1) { 
				i++;
			}
			else { 
				arr[i] = arr[p2];
				arr[p2] = 2;
				p2--;
			}
		}

}

int* readArrayFromFile(int length) {
	int* arr = (int*)malloc(sizeof(int) * length);
	FILE* fp = fopen("sort.txt", "r");
	if (fp == NULL) {
		printf("File can't be opend");
		return NULL;
	}
	for (int i = 0; i < length; i++) {
		fscanf(fp, "%d", &arr[i]);
	}
	fclose(fp);
	return arr;
}
void writeArrayToFile(int* arr, int length) {
	FILE* fp = fopen("sort.txt", "w");
	if (fp == NULL) {
		printf("File can't be opend");
		return;
	}
	for (int i = 0; i < length; i++) {
		fprintf(fp, "%d ", arr[i]);
	}
	fclose(fp);
}





void radixCountSort(int* arr, int length) {
	int divisor = 1;
	int max = arr[0];
	int* tempArray = (int*)malloc(sizeof(int)*(length));
	for (int i = 0; i < length; i++) {
		max = max > arr[i] ? max : arr[i];
	}
	while (max / divisor > 0) {
		int bucket[10];
		int sumbucket[10];
		memset(bucket, 0, sizeof(int)*10);// 此数组用来记录每个位数有多少个数字
		memset(sumbucket, 0, sizeof(int)*10);// 前缀和数组，用来记录原数组数字在新数组的位置的末尾!!!(重点，这是下面--的原因)
		for (int i = 0; i < length; i++) {
			bucket[(arr[i] / divisor) % 10]++;
		}
		sumbucket[0] = bucket[0];
		for (int i = 1; i <= 9; i++) {
			sumbucket[i] = bucket[i] + sumbucket[i - 1];
		}
		for (int i = length - 1; i >=0 ; i--) {// 从后往前遍历原数组，根据每个元素所在的桶将其放入临时数组中。模拟队列的先进先出，后进后出，但是是逆过程
			int arrRemainder = (arr[i] / divisor) % 10;
			int arrPosition = --sumbucket[arrRemainder];// 数组后面位置的数据，是放在桶的上层的，取出的时候是晚取出的,取出后也是排在tempArray的后面位置
			tempArray[arrPosition] = arr[i];
		}
		for (int i = 0; i < length; i++) {
			arr[i] = tempArray[i];
		}
		divisor *= 10;
	}
	free(tempArray);
}


void countSort(int* arr,int length) {
	int max = arr[0], min = arr[0];
	for (int i = 0; i < length; i++) {
		max = max > arr[i] ? max : arr[i];
		min = min < arr[i] ? min : arr[i];
	}
	int tempArrayLength = max - min + 1;
	int* tempArray = (int*)malloc(sizeof(int) * tempArrayLength);
	if (tempArray == NULL)return;
	memset(tempArray, 0, sizeof(int) * tempArrayLength);

	for (int i = 0; i < length; i++) {
		tempArray[arr[i] - min]++;
	}
	int j = 0;
	for (int i = 0; i < tempArrayLength; i++) {
		while (tempArray[i] > 0) {
			arr[j++] = i + min;
			tempArray[i]--;
		}

	}
}


void insetSort(int* array, int length) {// 插入排序
	for (int i = 1; i < length; i++) {// 未排序区的第一个指针
		int  k=i;// 记录i的指针
		int temp = array[i];
		while (temp < array[i-1]&& i>0) {
			
			array[i] = array[i-1];
			i--;
		}
		array[i] = temp;
		i = k;
	}

}


void bubbleSort(int arr[], int length) {
	int low = 0; 
	int high = length - 1;
	int last = low;
	while (low < high) {
		int flag = 1; // 设置flag
		
		for (int i = low; i < high; i++) { // 从前往后冒泡
			if (arr[i] > arr[i + 1]) { 
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				flag = 0; 
				last = i; // 记录最后一次交换的位置
			}
		}
		high = last; // 更新从后往前遍历的终点
		if (flag) { 
			break; 
		}
		for (int i = high; i > low; i--) { // 从后往前冒泡
			if (arr[i] < arr[i - 1]) {
				int temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
				last = i; // 记录最后一次交换的位置
			}
		}
		low = last;
	}
}
clock_t startClock() {
	return clock();
}

void endClock(clock_t startTime) {
	clock_t diff = startTime - clock();
	printf("The algorithm cost %d ms\n", diff);
	return;
}


void mergeSort(int* array, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;
	mergeSort(array, left, mid);
	mergeSort(array, mid + 1, right);
	merge(array, left, mid, right);
}
void merge(int* array, int left, int mid, int right)
{
	int s1 = left;
	int s2 = mid + 1;
	int* temp = (int*)malloc(sizeof(int) * (right - left + 1));
	int i = 0;
	while (s1 <= mid && s2 <= right)
	{
		if (array[s1] <= array[s2])// 修改升序逆序仅需修改这里
		{
			temp[i++] = array[s1++];
		}
		else
		{
			temp[i++] = array[s2++];
		}
	}
	while (s1 <= mid)
	{
		temp[i++] = array[s1++];
	}
	while (s2 <= right)
	{
		temp[i++] = array[s2++];
	}
	for (int j = 0; j < (right - left + 1); j++)
	{
		array[j + left] = temp[j];
	}
	free(temp);
}
int partition(int* arr, int low, int high) {
	int pivot;
	int a = 0;
	pivot = rand() % (high - low + 1) + low;
	int i = low, j = high;
	a = arr[low];
	arr[low] = arr[pivot];
	arr[pivot] = a;
	int index = arr[low];
	while (i < j)
	{
		while (i < j && arr[j] > index)
		{
			j--;
		}
		if (i < j)
		{
			arr[i++] = arr[j];
		}
		while (i < j && arr[i] < index)
		{
			i++;
		}
		if (i < j)
		{
			arr[j--] = arr[i];
		}
	}
	arr[i] = index;
	return i;
}

int partitionMoT(int* arr, int low, int high) {
	int mid = low + (high - low) / 2;
	if (arr[low] > arr[high]) {// low最小,high最大，保证high比low大
		int temp = arr[low];
		arr[low] = arr[high];
		arr[high] = temp;
	}
	if (arr[mid] > arr[high]) {// mid中间,high最大,保证high比mid大
		int temp = arr[mid];
		arr[mid] = arr[high];
		arr[high] = temp;

	}
	if (arr[mid] > arr[low]) {// 如果mid比low大，那mid就是中间值，交换。否则low是中间值，不做处理
		int temp = arr[mid];
		arr[mid] = arr[low];
		arr[low] = temp;
	}
	int pivot = arr[low];
	int i = low, j = high;
	int index = arr[low];
	while (i < j)
	{
		while (i < j && arr[j] > index)
		{
			j--;
		}
		if (i < j)
		{
			arr[i++] = arr[j];
		}
		while (i < j && arr[i] < index)
		{
			i++;
		}
		if (i < j)
		{
			arr[j--] = arr[i];
		}
	}
	arr[i] = index;
	return i;
}

int findKthLargest(int* arr, int length, int k) {
	int low = 0, high = length - 1;
	while (low <= high) {
		int pos = partition(arr, low, high);
		if (pos == k - 1) {
			return arr[pos];
		}
		else if (pos > k - 1) {
			high = pos - 1;
		}
		else {
			low = pos + 1;
		}
	}
	return -1; // 若找不到第K大的数，返回-1
}

int* quickMoT(int arr[], int low, int high)
{
	if (low >= high)
	{
		return arr;
	}
	int i = partitionMoT(arr, low, high);
	quickMoT(arr, low, i - 1);
	quickMoT(arr, i + 1, high);
}
int* quickSortMoT(int arr[], int N)// 递归版
{
	if (arr == NULL)
	{
		return arr;
	}
	else
	{
		quickMoT(arr, 0, N - 1);
	}
}
int* quick(int arr[], int low, int high)
{
	if (low >= high)
	{
		return arr;
	}
	int i = partition(arr, low, high);
	quick(arr, low, i - 1);
	quick(arr, i + 1, high);
}
int* quickSort(int arr[], int N)// 递归版
{
	if (arr == NULL)
	{
		return arr;
	}
	else
	{
		quick(arr, 0, N - 1);
	}
}

void quickSort2(int arr[], int length) {// 非递归版
	int low = 0, high = length - 1;
	int* stack = (int*)malloc(sizeof(int) * (high - low + 1));
	int top = -1;
	stack[++top] = low;
	stack[++top] = high;
	while (top >= 0) {
		high = stack[top--];
		low = stack[top--];
		int pivotIndex = partition(arr, low, high);
		if (pivotIndex - 1 > low) {
			stack[++top] = low;
			stack[++top] = pivotIndex - 1;
		}
		if (pivotIndex + 1 < high) {
			stack[++top] = pivotIndex + 1;
			stack[++top] = high;
		}
	}
}
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
	��ϵͳ���ɲ������򡢹鲢���򡢿������򡢼������򡢼�������������㷨���������������������С�����ִ����µ�������ʱ
	Ҳ֧�����ɲ������ݵ�.txt�ʹ�.txt�ж�ȡ���ݵĹ���
*/

void printArray(int* arr,int length) {
	int i;
	for (i = 0; i < length; i++) {
		printf("%d  ", arr[i]);
	}
}

int* createBigArray() {// ����һ������Ϊ200000�����������Ǹ�����������
	int i;
	int* arr = (int*)malloc(sizeof(int) * 200000);
	// �������������
	srand(time(NULL));
	// �������
	for (i = 0; i < 200000; i++) {
		arr[i] = rand();
	}
	// �������
	return arr;
}
int* createMediumArray() {// ����һ������Ϊ50000�����������Ǹ�����������
	int i;
	int* arr = (int*)malloc(sizeof(int) * 50000);
	// �������������
	srand(time(NULL));
	// �������
	for (i = 0; i < 50000; i++) {
		arr[i] = rand();
	}
	// �������
	return arr;

}
int* createSmallArray() {// ����һ������Ϊ10000�����������Ǹ�����������
	int i;
	int* arr = (int*)malloc(sizeof(int) * 10000);
	// �������������
	srand(time(NULL));
	// �������
	for (i = 0; i < 10000; i++) {
		arr[i] = rand();
	}
	// �������
	return arr;

}

int* createTinyArray() {// ����һ����СΪ100�����������Ǹ�����������

	int i;
	int* arr = (int*)malloc(sizeof(int) * 100);
	// �������������
	srand(time(NULL));
	// �������
	for (i = 0; i < 100; i++) {
		arr[i] = rand();
	}
	// �������
	return arr;

}
int* createColorSortArray(int length) {
	int* arr = (int*)malloc(sizeof(int) * length);
	// �������������
	srand(time(NULL));
	// �������
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
		memset(bucket, 0, sizeof(int)*10);// ������������¼ÿ��λ���ж��ٸ�����
		memset(sumbucket, 0, sizeof(int)*10);// ǰ׺�����飬������¼ԭ�����������������λ�õ�ĩβ!!!(�ص㣬��������--��ԭ��)
		for (int i = 0; i < length; i++) {
			bucket[(arr[i] / divisor) % 10]++;
		}
		sumbucket[0] = bucket[0];
		for (int i = 1; i <= 9; i++) {
			sumbucket[i] = bucket[i] + sumbucket[i - 1];
		}
		for (int i = length - 1; i >=0 ; i--) {// �Ӻ���ǰ����ԭ���飬����ÿ��Ԫ�����ڵ�Ͱ���������ʱ�����С�ģ����е��Ƚ��ȳ����������������������
			int arrRemainder = (arr[i] / divisor) % 10;
			int arrPosition = --sumbucket[arrRemainder];// �������λ�õ����ݣ��Ƿ���Ͱ���ϲ�ģ�ȡ����ʱ������ȡ����,ȡ����Ҳ������tempArray�ĺ���λ��
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


void insetSort(int* array, int length) {// ��������
	for (int i = 1; i < length; i++) {// δ�������ĵ�һ��ָ��
		int  k=i;// ��¼i��ָ��
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
		int flag = 1; // ����flag
		
		for (int i = low; i < high; i++) { // ��ǰ����ð��
			if (arr[i] > arr[i + 1]) { 
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				flag = 0; 
				last = i; // ��¼���һ�ν�����λ��
			}
		}
		high = last; // ���´Ӻ���ǰ�������յ�
		if (flag) { 
			break; 
		}
		for (int i = high; i > low; i--) { // �Ӻ���ǰð��
			if (arr[i] < arr[i - 1]) {
				int temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
				last = i; // ��¼���һ�ν�����λ��
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
		if (array[s1] <= array[s2])// �޸�������������޸�����
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
	if (arr[low] > arr[high]) {// low��С,high��󣬱�֤high��low��
		int temp = arr[low];
		arr[low] = arr[high];
		arr[high] = temp;
	}
	if (arr[mid] > arr[high]) {// mid�м�,high���,��֤high��mid��
		int temp = arr[mid];
		arr[mid] = arr[high];
		arr[high] = temp;

	}
	if (arr[mid] > arr[low]) {// ���mid��low����mid�����м�ֵ������������low���м�ֵ����������
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
	return -1; // ���Ҳ�����K�����������-1
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
int* quickSortMoT(int arr[], int N)// �ݹ��
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
int* quickSort(int arr[], int N)// �ݹ��
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

void quickSort2(int arr[], int length) {// �ǵݹ��
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
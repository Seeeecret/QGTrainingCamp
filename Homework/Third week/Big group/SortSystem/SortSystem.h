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

int* readArrayFromFile(int length) {
	int* arr = (int*)malloc(sizeof(int) * length);
	FILE* fp = fopen("D:\\sort.txt", "r");
	if (fp == NULL) {
		printf("file can't be opend");
		return NULL;
	}
	for (int i = 0; i < length; i++) {
		fscanf(fp, "%d", &arr[i]);
	}
	fclose(fp);
	return arr;
}
void writeArrayToFile(int* arr, int length) {
	FILE* fp = fopen("D:\\sort.txt", "w");
	if (fp == NULL) {
		printf("file can't be opend");
		return;
	}
	for (int i = 0; i < length; i++) {
		fprintf(fp, "%d", arr[i]);
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
		for (int i = length; i >=0 ; i--) {// �Ӻ���ǰ����ԭ���飬����ÿ��Ԫ�����ڵ�Ͱ���������ʱ�����С�ģ����е��Ƚ��ȳ����������������������
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

int* quick(int array[], int low, int high)
{
	if (low >= high)
	{
		return array;
	}
	int pivot;
	int a = 0;
	pivot = rand() % (high - low + 1) + low;
	int i = low, j = high;
	a = array[low];
	array[low] = array[pivot];
	array[pivot] = a;
	int index = array[low];
	while (i < j)
	{
		while (i < j && array[j] > index)
		{
			j--;
		}
		if (i < j)
		{
			array[i++] = array[j];
		}
		while (i < j && array[i] < index)
		{
			i++;
		}
		if (i < j)
		{
			array[j--] = array[i];
		}
	}
	array[i] = index;
	quick(array, low, i - 1);
	quick(array, i + 1, high);
}
int* quickSort(int array[], int N)// �ݹ��
{
	if (array == NULL)
	{
		return array;
	}
	else
	{
		quick(array, 0, N - 1);
	}
}
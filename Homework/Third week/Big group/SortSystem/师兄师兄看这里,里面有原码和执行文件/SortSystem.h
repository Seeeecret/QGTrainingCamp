#define _CRT_SECURE_NO_WARNINGS 1
#define BASE 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <queue>

void printArray(int* arr,int length) {// ��ӡ����
	int i;
	length = 50;
	for (i = 0; i < length; i++) {
		printf("%d  ", arr[i]);
	}
	puts("");
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
int* createColorSortArray(int length) {// ����������ɫ������������
	int* arr = (int*)malloc(sizeof(int) * length);
	// �������������
	srand(time(NULL));
	// �������
	for (int i = 0; i < length; i++) {
		arr[i] = rand() % 3;
	}
	return arr;

}



int* colorSort(int* array,int length) {// ��ɫ����
	int* arr = (int*)malloc(sizeof(int) * (length));
	memcpy(arr, array, sizeof(int) * length);
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
		return arr;
}

int* readArrayFromFile(int length) {// ��input.txt�ж�������
	int* arr = (int*)malloc(sizeof(int) * length);
	int i;
	memset(arr, 0, sizeof(int) * length);
	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("File can't be opend\n");
		return NULL;
	}
	for (i = 0; i < length; i++) {
		if (fscanf(fp, "%d", &arr[i]) == EOF)
			break;
	}
	fclose(fp);
	if (i < length) {
		printf("The array in txt is shorter than current array format.\nPlease select Option 0 or change the arraylength in txt to %d\n", length);
	}
	else
	printf("Successfully write in from input.txt!\n");
	return arr;
}
void writeArrayToFile(int* arr, int length) {// ������д�뵽output.txt��
	FILE* fp = fopen("output.txt", "w");
	if (fp == NULL) {
		printf("File can't be opend\n");
		return;
	}
	for (int i = 0; i < length; i++) {
		fprintf(fp, "%d ", arr[i]);
	}
	printf("Successfully output output.txt !\n");
	fclose(fp);
}





int* radixCountSort(int* array, int length) {// �ɵ���һ������Ļ�����������
	int* arr = (int*)malloc(sizeof(int)*(length));
	memcpy(arr, array, sizeof(int) * length);
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
	return arr;
}


int* countSort(int* array,int length) {// ��������
	int* arr = (int*)malloc(sizeof(int) * (length));
	memcpy(arr, array, sizeof(int) * length);
	int max = arr[0], min = arr[0];
	for (int i = 0; i < length; i++) {
		max = max > arr[i] ? max : arr[i];
		min = min < arr[i] ? min : arr[i];
	}
	int tempArrayLength = max - min + 1;
	int* tempArray = (int*)malloc(sizeof(int) * tempArrayLength);
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
	return arr;
}


int* insertSort(int* array, int length) {// ��������
	int* arr = (int*)malloc(sizeof(int) * (length));
	memcpy(arr, array, sizeof(int) * length);
	for (int i = 1; i < length; i++) {
		int  k=i;
		int temp = arr[i];
		while (temp < arr[i-1]&& i>0) {
			
			arr[i] = arr[i-1];
			i--;
		}
		arr[i] = temp;
		i = k;
	}
	return arr;
}


int* bubbleSort(int* array, int length) {// �����Ż���ð������
	int* arr = (int*)malloc(sizeof(int) * (length));
	memcpy(arr, array, sizeof(int) * length);
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
	return arr;
}
clock_t startClock() {
	return clock();
}

clock_t endClock() {
	return clock();
}
void costTime(clock_t startTime,clock_t endTime) {// �����㷨����ʱ��
	clock_t diff = endTime - startTime;
	printf("The algorithm cost %ld ms\n", diff);
	return;
}


void merge(int* arr, int left, int mid, int right)// �鲢���������Ԫ
{
	int s1 = left;
	int s2 = mid + 1;
	int* temp = (int*)malloc(sizeof(int) * (right - left + 1));
	int i = 0;
	while (s1 <= mid && s2 <= right)
	{
		if (arr[s1] <= arr[s2])// �޸�������������޸�����
		{
			temp[i++] = arr[s1++];
		}
		else
		{
			temp[i++] = arr[s2++];
		}
	}
	while (s1 <= mid)
	{
		temp[i++] = arr[s1++];
	}
	while (s2 <= right)
	{
		temp[i++] = arr[s2++];
	}
	for (int j = 0; j < (right - left + 1); j++)
	{
		arr[j + left] = temp[j];
	}
	free(temp);
}

void mergeInto(int* array, int left, int right)// �鲢����ĵݹ鵥Ԫ
{

	if (left >= right)
	{
		return;
	}

	int mid = (left + right) / 2;
	mergeInto(array, left, mid);
	mergeInto(array, mid + 1, right);
	merge(array, left, mid, right);

}
int* mergeSort(int* array, int length) {// �鲢�����������װ
	int* arr = (int*)malloc(sizeof(int) * (length));
	memcpy(arr, array, sizeof(int) * (length));
	mergeInto(arr, 0, length - 1);
	return arr;
}
int partition(int* arr, int low, int high) {// ���ŵ�����Ԫ
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

int partitionMoT(int* arr, int low, int high) {// ���ŵ�����Ԫ
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

int findKthSmallest(int* array,int k,int length) {// �ҵ���KС��Ԫ��
	if (k<1 || k>length) {
		return -1;
	}
	int* arr = (int*)malloc(sizeof(int) * (length));
	memcpy(arr, array, sizeof(int) * length);
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

int* quickMoT(int* arr, int low, int high){

	if (low >= high)
	{
		return arr;
	}
	int i = partitionMoT(arr, low, high);
	quickMoT(arr, low, i - 1);
	quickMoT(arr, i + 1, high);
}
int* quickSortMoT(int* array, int length){// MoT�Ż��ݹ�����
	int* arr = (int*)malloc(sizeof(int) * (length));
	memcpy(arr, array, sizeof(int) * length);
	if (arr == NULL)
	{
		return arr;
	}
	else
	{
		quickMoT(arr, 0, length - 1);
	}
	return arr;
}
int* quick(int* arr, int low, int high)
{
	if (low >= high)
	{
		return arr;
	}
	int i = partition(arr, low, high);
	quick(arr, low, i - 1);
	quick(arr, i + 1, high);
}
int* quickSort(int* array, int length)// �ݹ�����
{
	int* arr = (int*)malloc(sizeof(int) * (length));
	memcpy(arr, array, sizeof(int) * length);
	if (arr == NULL)
	{
		return arr;
	}
	else
	{
		quick(arr, 0, length - 1);
	}
	return arr;
}

int* quickSort2(int* array, int length) {// �ǵݹ�����
	int* arr = (int*)malloc(sizeof(int) * (length));
	memcpy(arr, array, sizeof(int) * length);
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
	return arr;
}
void sortCell(int* arr,int*(*func)(int*,int),int flag) {// ��Operation()���õķ�װ�ø������ܵ�����Ԫ
	int* temparr=NULL;
	if (flag == 100) {
		puts("The origin array:");
		printArray(arr, flag);
		clock_t start = startClock();
		for (int i = 0; i < flag; i++) {
			temparr = func(arr, flag);
		}
		clock_t end = endClock();
		puts("The sorted array:");
		printArray(temparr, flag);
		costTime(start, end);
	}
	else
	{
		puts("The origin array:");
		printArray(arr, flag);
		clock_t start = startClock();
		temparr = func(arr, flag);
		clock_t end = endClock();
		puts("The sorted array:");
		printArray(temparr, flag);
		costTime(start, end);
	}
}
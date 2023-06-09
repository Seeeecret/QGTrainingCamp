#define _CRT_SECURE_NO_WARNINGS 1
#define BASE 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <queue>

void printArray(int* arr,int length) {// 打印数组
	int i;
	length = 50;
	for (i = 0; i < length; i++) {
		printf("%d  ", arr[i]);
	}
	puts("");
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
int* createColorSortArray(int length) {// 创建符合颜色排序规则的数组
	int* arr = (int*)malloc(sizeof(int) * length);
	// 设置随机数种子
	srand(time(NULL));
	// 填充数组
	for (int i = 0; i < length; i++) {
		arr[i] = rand() % 3;
	}
	return arr;

}



int* colorSort(int* array,int length) {// 颜色排序
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

int* readArrayFromFile(int length) {// 从input.txt中读入数组
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
void writeArrayToFile(int* arr, int length) {// 将数组写入到output.txt中
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





int* radixCountSort(int* array, int length) {// 干掉我一个下午的基数计数排序
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
	return arr;
}


int* countSort(int* array,int length) {// 计数排序
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


int* insertSort(int* array, int length) {// 插入排序
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


int* bubbleSort(int* array, int length) {// 三重优化版冒泡排序
	int* arr = (int*)malloc(sizeof(int) * (length));
	memcpy(arr, array, sizeof(int) * length);
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
	return arr;
}
clock_t startClock() {
	return clock();
}

clock_t endClock() {
	return clock();
}
void costTime(clock_t startTime,clock_t endTime) {// 计算算法消耗时间
	clock_t diff = endTime - startTime;
	printf("The algorithm cost %ld ms\n", diff);
	return;
}


void merge(int* arr, int left, int mid, int right)// 归并排序的排序单元
{
	int s1 = left;
	int s2 = mid + 1;
	int* temp = (int*)malloc(sizeof(int) * (right - left + 1));
	int i = 0;
	while (s1 <= mid && s2 <= right)
	{
		if (arr[s1] <= arr[s2])// 修改升序逆序仅需修改这里
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

void mergeInto(int* array, int left, int right)// 归并排序的递归单元
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
int* mergeSort(int* array, int length) {// 归并排序的最外层封装
	int* arr = (int*)malloc(sizeof(int) * (length));
	memcpy(arr, array, sizeof(int) * (length));
	mergeInto(arr, 0, length - 1);
	return arr;
}
int partition(int* arr, int low, int high) {// 快排的排序单元
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

int partitionMoT(int* arr, int low, int high) {// 快排的排序单元
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

int findKthSmallest(int* array,int k,int length) {// 找到第K小的元素
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
	return -1; // 若找不到第K大的数，返回-1
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
int* quickSortMoT(int* array, int length){// MoT优化递归版快排
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
int* quickSort(int* array, int length)// 递归版快排
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

int* quickSort2(int* array, int length) {// 非递归版快排
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
void sortCell(int* arr,int*(*func)(int*,int),int flag) {// 供Operation()调用的封装好附属功能的排序单元
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
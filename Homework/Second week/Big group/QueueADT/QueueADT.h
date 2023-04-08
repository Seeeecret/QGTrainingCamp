#pragma once
struct node {
    void* data;             // 数据指针
    struct node* next;      // 下一个节点的指针
};
typedef struct node Node;

// 定义队列
struct queueHead {
    Node* front;          // 队头指针
    Node* rear;           // 队尾指针
    int size;               // 队列大小
};
typedef struct queueHead Queue;
#include <stdio.h>
#include <stdlib.h>
extern int typeFlag;
// 定义队列节点



void initializeQueue(Queue** queue) {// 初始化队列
    if (*queue == NULL) {
        (*queue) = (Queue*)malloc(sizeof(Queue));
		(*queue)->front = (*queue)->rear = NULL;
		(*queue)->size = 0;
        fprintf(stdout, "A new queue created!\n");
    }
    else fprintf(stderr, "A queue has already created before.\n");
}

void destroyQueue(Queue* queue) {// 销毁队列
    if (queue == NULL) {
        fprintf(stderr, "NullPointerException! Please try again.\n");
        return;
    }
    Node* current = queue->front;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    queue->front = queue->rear = NULL;
    queue->size = 0;
    free(queue);
    puts("Queue is deleted!");
    //queue = NULL;
}

// 队列是否为空
int isEmpty(Queue* queue) {
    return queue->size == 0;
}

bool enQueue(Queue* queue, void* data) {// 入队函数，返回值为bool，表示是否入队成功
    if (queue == NULL) {
        fprintf(stderr, "NullPointerException! Please try again.\n");
        return false;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        Node* tempNode = queue->rear;
        queue->rear = newNode;
        tempNode->next = newNode;
    }
    queue->size++;
    data == NULL;
    return true;
}

void* deQueue(Queue* queue) {// 出队函数，返回值为void*，需要强制类型转换
    if (queue == NULL) {
        fprintf(stderr, "NullPointerException! Please try again.\n");
        return NULL;
    }
    if (isEmpty(queue)) {// 判断队列是否为空
        fprintf(stderr,"EmptyQueueException! Please try again.\n");
        return NULL;
    }
    Node* frontNode = queue->front;
    void* dedata = frontNode->data;
    queue->front = queue->front->next;
    free(frontNode);
    queue->size--;
    if (queue->size == 0) {
        queue->rear = NULL;
    }
    return dedata;
}

void* deQueueForTraverse(Queue* queue) {// 出队函数，返回值为void*，需要强制类型转换
    if (queue == NULL) {
        fprintf(stderr, "NullPointerException! Please try again.\n");
        return NULL;
    }
    if (isEmpty(queue)) {
        return NULL;
    }
    Node* frontNode = queue->front;
    void* dedata = frontNode->data;
    queue->front = queue->front->next;
    free(frontNode);
    queue->size--;
    if (queue->size == 0) {
        queue->rear = NULL;
    }
    return dedata;
}

/*void deQueue2(Queue* queue, void* value) {// 原先设计的出队函数，已弃用
    if (isEmpty(queue)) {
        printf("EmptyQueueException! Please try again.\n");
        return;
    }
    else {
        Node* frontnode = queue->front;
        memcpy(value, frontnode->data, sizeof(frontnode->data)); //将数据域中的值复制到传入的参数中
        queue->front = frontnode->next; //队头指针指向下一个节点
        free(frontnode->data); //释放数据域的内存
        free(frontnode); //释放节点的内存
        queue->size--; //队列大小减一
        if (queue->size == 0) {
			queue->rear = NULL;
		}
    }
}*/

void* getFront(Queue* queue) {// 获取队头元素
    if (queue == NULL) {
        fprintf(stderr, "NullPointerException! Please try again.\n");
        return NULL;
    }
    if (isEmpty(queue)) {
		return NULL;
	}
	return queue->front->data;
}
void TraverseQueue(Queue* queue) {// 遍历队列并打印
    if (queue == NULL) {
		fprintf(stderr, "NullPointerException! Please try again.\n");
		return;
	}
    if (isEmpty(queue)) {
        printf("EmptyQueueException! Please try again.\n");
        return;
    }
    if (typeFlag == 0) {
        int* data1;
        while ((data1 = (int*)deQueueForTraverse(queue)) != NULL) {
            printf("Data is: %d\n", *data1);
        }
    }
    else {
        double* data2;
        while ((data2 = (double*)deQueueForTraverse(queue)) != NULL) {
            printf("Data is: %lf\n", *data2);
        }
    }
}


int getLength(Queue* queue) {// 获取队列大小
    if (queue == NULL) {
        fprintf(stderr, "NullPointerException! Please try again.\n");
        return -1;
    }
    return queue->size;
}



#pragma once
struct node {
    void* data;             // ����ָ��
    struct node* next;      // ��һ���ڵ��ָ��
};
typedef struct node Node;

// �������
struct queueHead {
    Node* front;          // ��ͷָ��
    Node* rear;           // ��βָ��
    int size;               // ���д�С
};
typedef struct queueHead Queue;
#include <stdio.h>
#include <stdlib.h>
extern int typeFlag;
// ������нڵ�



void initializeQueue(Queue** queue) {// ��ʼ������
    if (*queue == NULL) {
        (*queue) = (Queue*)malloc(sizeof(Queue));
		(*queue)->front = (*queue)->rear = NULL;
		(*queue)->size = 0;
        fprintf(stdout, "A new queue created!\n");
    }
    else fprintf(stderr, "A queue has already created before.\n");
}

void destroyQueue(Queue* queue) {// ���ٶ���
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

// �����Ƿ�Ϊ��
int isEmpty(Queue* queue) {
    return queue->size == 0;
}

bool enQueue(Queue* queue, void* data) {// ��Ӻ���������ֵΪbool����ʾ�Ƿ���ӳɹ�
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

void* deQueue(Queue* queue) {// ���Ӻ���������ֵΪvoid*����Ҫǿ������ת��
    if (queue == NULL) {
        fprintf(stderr, "NullPointerException! Please try again.\n");
        return NULL;
    }
    if (isEmpty(queue)) {// �ж϶����Ƿ�Ϊ��
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

void* deQueueForTraverse(Queue* queue) {// ���Ӻ���������ֵΪvoid*����Ҫǿ������ת��
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

/*void deQueue2(Queue* queue, void* value) {// ԭ����Ƶĳ��Ӻ�����������
    if (isEmpty(queue)) {
        printf("EmptyQueueException! Please try again.\n");
        return;
    }
    else {
        Node* frontnode = queue->front;
        memcpy(value, frontnode->data, sizeof(frontnode->data)); //���������е�ֵ���Ƶ�����Ĳ�����
        queue->front = frontnode->next; //��ͷָ��ָ����һ���ڵ�
        free(frontnode->data); //�ͷ���������ڴ�
        free(frontnode); //�ͷŽڵ���ڴ�
        queue->size--; //���д�С��һ
        if (queue->size == 0) {
			queue->rear = NULL;
		}
    }
}*/

void* getFront(Queue* queue) {// ��ȡ��ͷԪ��
    if (queue == NULL) {
        fprintf(stderr, "NullPointerException! Please try again.\n");
        return NULL;
    }
    if (isEmpty(queue)) {
		return NULL;
	}
	return queue->front->data;
}
void TraverseQueue(Queue* queue) {// �������в���ӡ
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


int getLength(Queue* queue) {// ��ȡ���д�С
    if (queue == NULL) {
        fprintf(stderr, "NullPointerException! Please try again.\n");
        return -1;
    }
    return queue->size;
}



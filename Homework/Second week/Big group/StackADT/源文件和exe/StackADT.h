struct item {
    double data;
    item(double newData) {
        data = newData;
    }
};


typedef struct item Item;


struct node // 栈结点
{
    Item item; // 数据域
    struct node* next; // 指针域
};

typedef struct node Node;

typedef struct node* Stack; // 栈类型

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h>




Stack createStack() {// 创建一个空栈
    Stack s = (Stack)malloc(sizeof(Node)); // 分配内存空间
    if (s==NULL) // 内存分配失败
    {
        printf("MemoryAllocationException!Please try again!\n");
        free(s);
        return NULL;
    }
    s->next = NULL; // 栈顶指针指向NULL
    s->item.data = NAN;
    return s;

}

int isEmpty(Stack* s) { // 判断栈是否为空
    if ((*s) == NULL) {
        printf("NullPointerException! Please try again!\n");
        return -1;
    }
    return isnan((*s)->item.data);
}// 判断栈是否为空

int countStack(Stack* s) { // 计算栈中元素个数
    if ((*s) == NULL) {
        printf("NullPointerException! Please try again!\n");
        return -1;
    }
    else if (isEmpty(s)) {
        printf("EmptyStackException! Please try again!\n");
        return -1;
    }
    else {
        int cnt = 1;
        Node* temp = (*s);
        while (temp->next != NULL) {
            cnt++;
            temp = temp->next;
        }
        return cnt;
    }
}

void deleteStack(Stack* s) { // 删除栈
    if ((*s) == NULL) {
        printf("NullPointerException! Please try again!\n");
        return;
    }
    Node* temp = NULL;
    while ((*s)->next != NULL) // 遍历链表，释放每个结点的空间
    {
        temp = (*s)->next;
        (*s)->next = temp->next;
        free(temp);
    }
    free(*s); // 释放头结点的空间
    *s = NULL;
    printf("Done!\n");
}

void pushStack(Stack* s, Item newItem) { // 入栈
    if((*s)==NULL){
        printf("NullPointerException! Please enter Q to quit and create a stack!\n");
        return;
    }
    else if (isEmpty(s)) {
        (*s)->item = newItem;
        puts("New data pushed in!");
        return;
    }
    else {
        Node* p = (Node*)malloc(sizeof(Node)); // 分配内存空间
        if (!p) // 内存分配失败
        {
            printf("MemoryAllocationException! Please try again!\n");
            return;
        }
        p->item = newItem; // 指定数据域数值
        p->next = (*s); // 将新结点插入到头结点上面
        (*s) = p; // 更新头节点
        puts("New data pushed in!");
    }
}

Item popStack(Stack* s) { // 出栈
    if ((*s) == NULL) {
        printf("NullPointerException! Please try again!\n");
        return Item(NAN);
    }
    else if (isEmpty(s)) {
        printf("EmptyStackException! Please try again!\n");
        return Item(NAN);
    }
    else if ((*s)->next == NULL) {
        Item popItem1 = (*s)->item;
        (*s)->item.data = NAN;
        return popItem1;
    }
    else {
        Node* temp = (*s);
        Item popItem2 = (*s)->item;
        (*s) = (*s)->next;
        (*s)->next = temp->next->next;
        free(temp);
        return popItem2;
    }
}


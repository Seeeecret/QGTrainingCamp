
#define UPKEY 72//�����ϼ��ĵڶ���ֵ
#define DOWNKEY 80//�����¼��ĵڶ���ֵ, ���ߵ�һ��ֵ����ͬ��
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "QueueADT.h"
int typeFlag;
#define IN_CYAN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                        BACKGROUND_GREEN |               \
                                            BACKGROUND_BLUE |            \
                                            BACKGROUND_INTENSITY)//��������˵����ݱ�����ɫ�ĺ궨��: ����ɫ
#define IN_DEFAULT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                           FOREGROUND_RED |                 \
                                               FOREGROUND_GREEN |           \
                                               FOREGROUND_BLUE)//��������˵����ݱ�����ɫ�ĺ궨��: Ĭ��
void Menu();//�˵�����
void cursorUpdate1(int x);//������ʾ���ֵĴ�ӡ����
int cursorOperate(int line, int deta, int lower, int upper, void (*p)(int));//�����������¼��ĺ���
void Gotoxy(int x, int y);//�ƶ����ĺ���
void Operation();

void Menu()
{
    printf("                                ��ӭʦ���������Ͷ��в���ϵͳ                               \n");
    printf("*******************************************************************************************\n");
    if (typeFlag == 0)
        printf("*                0) �л����е�������������: int                                           *\n");
    else
        printf("*                0) �л����е�������������: double                                        *\n");
    printf("*                1) �½�һ���յ��������Ͷ���                                              *\n");
    printf("*                2) ����һ����Ԫ�أ�����Ԫ������                                          *\n");
    printf("*                3) �ö���Ԫ�س��в���ӡ��Ӧ��ֵ                                          *\n");
    printf("*                4) �ö���������Ԫ�س��в���ӡ                                            *\n");
    printf("*                5) ��ղ���ȫɾ������                                                    *\n");
    printf("*                6) ��ӡ����Ԫ�ص�ֵ(������)                                              *\n");
    printf("*                7) ��ӡ���г���                                                          *\n");
    printf("*                8) �˳�����                                                              *\n");
    printf("*******************************************************************************************\n");
    printf("    ��ʹ�á�������enter��ʵ��ѡ���ִ�������������ÿ������ǰ��Ĵ�����ִ������<0 - 8>   \n");
    printf("                     �ڲ˵���ҳ����δ�����˵�ʱ����'q'��'Q'�˳�����\n");
    printf("                ��ϵͳ���Ͷ������ͽ����ڶ���ʱ�������л����ӵڶ����ڵ㿪ʼ�洢����         \n");
    return;
}

void cursorUpdate1(int x)
{
    switch (x)
    {
    case 0:
        if (typeFlag == 0)
            printf("*                0) �л����е�������������: int                                           *\n");
        else
            printf("*                0) �л����е�������������: double                                        *\n");
        break;
    case 1:
        printf("*                1) �½�һ���յ��������Ͷ���                                              *\n");
        break;
    case 2:
        printf("*                2) ����һ����Ԫ�أ�����Ԫ������                                          *\n");
        break;
    case 3:
        printf("*                3) �ö���Ԫ�س��в���ӡ��Ӧ��ֵ                                          *\n");
        break;
    case 4:
        printf("*                4) �ö���������Ԫ�س��в���ӡ                                            *\n");
        break;
    case 5:
        printf("*                5) ��ղ���ȫɾ������                                                    *\n");
        break;
    case 6:
        printf("*                6) ��ӡ����Ԫ�ص�ֵ(������)                                              *\n");
        break;
    case 7:
        printf("*                7) ��ӡ���г���                                                          *\n");
        break;
    case 8:
        printf("*                8) �˳�����                                                              *\n");
        break;
    }
    return;
}
void Gotoxy(int x, int y)
{
    COORD pos = { x, y };
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, pos);
    return;
}

int cursorOperate(int line, int deta, int lower, int upper, void (*p)(int))
{
    /*
    line����ǰ�����������
    deta��������˵�ѡ��Ĳ�ֵ��������main�˵���ѡ��(0)�ڵ�2��(������0��ʼ����)������deta����2����2 - 0
    upper, lower��ѡ������½�
    (*P)(int)������ָ�룬ѡ���ĸ����ǲ˵���ֻʵ����cursorUpdate1һ��
    */
    char c1, c2;
    Gotoxy(0, line);
    do
    {
        c2 = _getch();
        if (c2 == DOWNKEY)
        {
            Gotoxy(0, line);
            IN_DEFAULT; //ѡ��Ĭ��ɫ
            (*p)(line - deta); //���ǣ�ʵ����ѡ(ʵ���Ͼ��Ǵ�ӡ)
            if (line == upper) //����Ѿ������Ͻ磬�򷵻��½磬ʵ�ֹ�������
                line = lower;
            else
                ++line; //
            Gotoxy(0, line);
            IN_CYAN; // ѡ����ɫ
            (*p)(line - deta);
        }
        if (c2 == UPKEY)
        {
            Gotoxy(0, line);
            IN_DEFAULT;
            (*p)(line - deta);
            if (line == lower)
                line = upper;
            else
                --line;
            Gotoxy(0, line);
            IN_CYAN;
            (*p)(line - deta);
        }
    } while ((c1 = _getch()) != '\r');
    Gotoxy(0, line);
    (*p)(line - deta);
    IN_DEFAULT;
    return line - deta;
}

void Operation() {
    Queue* originQueue = NULL;
    int n = 0, line = 2; // ��Ӧmenu()��0)
    char c1;
    IN_DEFAULT;
    while (1) {
        system("cls");
        Menu();
        Gotoxy(0, 15);
        if ((c1 = _getch()) == -32) {//��VS����������Ҫ�������е�_getch�ĳ�getch

            n = cursorOperate(line, 2, 2, 10, cursorUpdate1);//���¼�����
        }
        else if (c1 == '\0')continue;
        else if (c1 >= '0' && c1 <= '9') {//�������ֱ�Ų���
            char tmp = c1;
            putchar(tmp);
            puts("");
            n = tmp - '0';
        }
        else if (c1 == 'q' || c1 == 'Q') {//�����������
            Gotoxy(0, 16);//�ù�굽���ʵĵط����
            putchar(c1);
            puts("");
            printf("ʦ���ټ�\n");
            system("pause");
            exit(0);
        }
        else {//�����������
            puts("�������");
            system("pause");
            continue;
        }
        switch (n) {
        case 0: {
            Gotoxy(0, 16);
            if (typeFlag == 0 && originQueue == NULL) typeFlag = 1;
            else if (typeFlag == 1 && originQueue == NULL)typeFlag = 0;
            else {
                puts("You can't change the type of queue when the queue exist.");
                system("pause");
            }
   
            break;
        }
        case 1: {
            Gotoxy(0, 16);
            initializeQueue(&originQueue);//��ʼ������
            system("pause");
            break;
        }
        case 2: {
            Gotoxy(0, 16);
            if (typeFlag == 0) {
				int* data = (int*)malloc(sizeof(int));
				puts("Please enter a integer, unless you want to quit: ");
				if (scanf("%9d", data) == 1 && enQueue(originQueue, data)) puts("Successfully enqueue");
				else puts("Failing to enqueue");                
            }
            else {
                double* data = (double*)malloc(sizeof(double));
                puts("Please enter a double, unless you want to quit: ");
                if (scanf("%9lf", data) == 1 && enQueue(originQueue, data)) puts("Successfully enqueue");
                else puts("Failing to enqueue");
            }
            fflush(stdin);
            rewind(stdin);
            system("pause");
            break;
        }
        case 3: {
            Gotoxy(0, 16);
            if (typeFlag == 0) {
                int* data;
                if ((data = (int*)deQueue(originQueue)) != NULL) {
                    puts("Successfully dequeue");
                    printf("Data is %d\n", *data);
                }
                else puts("Failing to dequeue");
            }
            else {
                double* data;
                if ((data = (double*)deQueue(originQueue)) != NULL) {
                    puts("Successfully dequeue");
                    printf("Data is %lf\n", *data);
                }
                else puts("Failing to dequeue");
            }
            system("pause");
            break;
        }
        case 4: {
            Gotoxy(0, 16);
            TraverseQueue(originQueue);
            system("pause");
            break;
        }
        case 5: {
            Gotoxy(0, 16);
            destroyQueue(originQueue);
            originQueue = NULL;
            system("pause");
            break;
        }
        case 6: {
            Gotoxy(0, 16);
            if (typeFlag == 0) {
                int* data;
                if ((data = (int*)getFront(originQueue)) != NULL) {
                    puts("Successfully get front data");
                    printf("Data is %d\n", *data);
                }
                else
                {
                    puts("Failing to get front data");
                }
            }
            else
            {
                double* data;
                if ((data = (double*)getFront(originQueue)) != NULL) {
                    puts("Successfully get front data");
                    printf("Data is %lf\n", *data);
                }
                else
                {
                    puts("Failing to get front data");
                }
            }
            system("pause");
            break;
        }
        case 7: {
            Gotoxy(0, 16);
            int cnt = getLength(originQueue);
            if (cnt == -1) puts("Failing to get the length.");
            else printf("Queue length is %d\n", cnt);
            system("pause");
            break;

        }
        case 8: {
            Gotoxy(0, 16);//�ù�굽���ʵĵط����
            puts("ʦ���ټ����´�����");
            system("pause");
            exit(0);
        }
              system("pause");
        }
    }
}
#define UPKEY 72//�����ϼ��ĵڶ���ֵ
#define DOWNKEY 80//�����¼��ĵڶ���ֵ, ���ߵ�һ��ֵ����ͬ��
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "StackADT.h"
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

void Menu()//�˵�����
{
    printf("                                  ��ӭʦ��������ջ����ϵͳ                                 \n");
    printf("*******************************************************************************************\n");
    printf("*                0) �½�һ���յ���ջ                                                      *\n");
    printf("*                1) ��ջ��ѹ��Ԫ��                                                        *\n");
    printf("*                2) ����ջ��Ԫ�ز���ӡ                                                    *\n");
    printf("*                3) ��鵱ǰջ�Ƿ�Ϊ��                                                    *\n");
    printf("*                4) ��鵱ǰջ�Ƿ����                                                    *\n");
    printf("*                5) ��ջ������Ԫ�ص�����ȫ����ӡ                                          *\n");
    printf("*                6) ���ջ��Ԫ�ز���ȫɾ��ջ                                              *\n");
    printf("*                7) ��ӡĿǰջ��Ԫ������                                                  *\n");
    printf("*                8) �˳�����                                                              *\n");
    printf("*******************************************************************************************\n");
    printf("��ʹ�á�������enter��ʵ��ѡ���ִ�������������ÿ������ǰ��Ĵ�����ִ������<0 - 7>       \n");
    printf("                     �ڲ˵���ҳ����δ�����˵�ʱ����'q'��'Q'�˳�����\n");
    printf("              ��ϵͳ��ջ����Ԫ��Ҳ�洢���ݣ�������ѹ��ʱ�ı䶥��Ԫ�ص�ָ��\n");
    return;
}

void cursorUpdate1(int x)
{
    switch (x)
    {
    case 0:
        printf("*                0) �½�һ���յ���ջ                                                      *\n");
        break;
    case 1:
        printf("*                1) ��ջ��ѹ��Ԫ��                                                        *\n");
        break;
    case 2:
        printf("*                2) ����ջ��Ԫ�ز���ӡ                                                    *\n");
        break;
    case 3:
        printf("*                3) ��鵱ǰջ�Ƿ�Ϊ��                                                    *\n");
        break;
    case 4:
        printf("*                4) ��鵱ǰջ�Ƿ����                                                    *\n");
        break;
    case 5:
        printf("*                5) ��ջ������Ԫ�ص�����ȫ����ӡ                                          *\n");
        break;
    case 6:
        printf("*                6) ���ջ��Ԫ�ز���ȫɾ��ջ                                              *\n");
    case 7:
        printf("*                7) ��ӡĿǰջ��Ԫ������                                                  *\n");
        break;
    case 8:
        printf("*                7) �˳�����                                                              *\n");
        break;
    }
    return;
}
void Gotoxy(int x, int y)// �ƶ���굽ָ��λ��
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
    Stack originStack = NULL;
    int n = 0, line = 2; // ��Ӧmenu()��0)
    char c1;
    IN_DEFAULT;
    while (1)
    {
        system("cls");
        Menu();
        Gotoxy(0, 15);
        if ((c1 = _getch()) == -32) {//��VS����������Ҫ�������е�_getch�ĳ�getch

            n = cursorOperate(line, 2, 2, 9, cursorUpdate1);//���¼�����
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
            system("pause");
            printf("Here is end of run.\n");
        
        }
        else {//�����������
            puts("�������");
            system("pause");
            continue;
        }
        switch (n) {
        case 0: {// �½�һ���յ���ջ
            Gotoxy(0, 16);
            if (originStack == NULL) {
                originStack = createStack();
                puts("New Stack!");
            }
            else puts("You have already created a stack.");
            system("pause");
            break;
        }
        case 1: {// ѹ��ջ��Ԫ��
            Gotoxy(0, 16);
            Item enterData = 0;//�����Ľڵ�
            puts("Please enter a float,otherwise function will quit:");
            while (scanf("%16lf", &enterData.data))
            {
                
                pushStack(&originStack, enterData);
            }
            fflush(stdin);
            rewind(stdin);
            system("pause");
            break;
        }
        case 2: {// ����ջ��Ԫ��
            Gotoxy(0, 16);
            Item enterData2 = popStack(&originStack);
            if(isnan(enterData2.data))puts("Failing to pop.");
			else
            printf("The pop out data is %.9e\n", enterData2.data);
            system("pause");
            break;
        }
        case 3: { // �ж�ջ�Ƿ�Ϊ��
            Gotoxy(0, 16);
            int flag = isEmpty(&originStack);
            if( flag==1 )puts("Yes, The stack is empty. Please push some new item.");
			else if(flag == 0)
                puts("No, The stack is not empty.");
            system("pause");
            break;
        }
        case 4: {// �ж�ջ�Ƿ����
            Gotoxy(0, 16);
            if (originStack == NULL) puts("The stack is not exist, Please new a stack.");
            else puts("The stack is already exist.");
            system("pause");
            fflush(stdin);
            rewind(stdin);
            break;
        }
        case 5: {// ����ջ
            Gotoxy(0, 16);
            Item popItem = 0;
            while (!isEmpty(&originStack)) {
                popItem = popStack(&originStack);
                printf("The pop item: %.9e\n", popItem.data);
            }
            system("pause");
            break;
        }
        case 6: {// ɾ��ջ
            Gotoxy(0, 16);
            deleteStack(&originStack);
            system("pause");
            break;
        }
        case 7: {
            Gotoxy(0, 16);//�ù�굽���ʵĵط����
            int cnt = countStack(&originStack);
            if (cnt == -1) printf("Failing to count.\n");
            else printf("The stack has %d items.\n", cnt);
            system("pause");
            break;
        }
        case 8: {
            Gotoxy(0, 16);//�ù�굽���ʵĵط����
            puts("ʦ���ټ����´�����");
            system("pause");
            exit(0);
        }
        }
    }
    system("pause");
}
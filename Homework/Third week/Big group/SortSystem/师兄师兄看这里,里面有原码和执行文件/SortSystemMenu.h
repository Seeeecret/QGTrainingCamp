#define UPKEY 72//�����ϼ��ĵڶ���ֵ
#define DOWNKEY 80//�����¼��ĵڶ���ֵ, ���ߵ�һ��ֵ����ͬ��
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "SortSystem.h"
int flag = 10000;
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
    printf("                                 ��ӭʦ�������ۺ��������ϵͳ                              \n");
    printf("*******************************************************************************************\n");
    if (flag == 10000)
    printf("*                0) �л������������������������ģʽ: 1�� 10000������                     *\n");
    else if(flag==50000)
    printf("*                0) �л������������������������ģʽ: 1�� 50000������                     *\n");
    else if(flag==200000)
    printf("*                0) �л������������������������ģʽ: 1�� 200000������                    *\n");
    else if(flag==100)
    printf("*                0) �л������������������������ģʽ: 10^5�� 100������                    *\n");
    printf("*                1) ���������顢���������������������ʱ                              *\n");
    printf("*                2) ���������顢�鲢�����������������ʱ                              *\n");
    printf("*                3) ���������顢�ݹ���������������������ʱ                          *\n");
    printf("*                4) ���������顢���������������������ʱ                              *\n");
    printf("*                5) ���������顢�������������������������ʱ                          *\n");
    printf("*                6) ���������顢�������������������������ʱ                          *\n");
    printf("*                7) ���������顢���Ż�ð�������������������ʱ                        *\n");
    printf("*                8) ���������顢˫�Ż����������������������ʱ                        *\n");
    printf("*                9) �����ǰ��������������Ŀ¼��output.txt�ļ�                          *\n");
    printf("*                A) �ӳ����Ŀ¼��input.txt�ļ���¼������                                 *\n");
    printf("*                B) Ӧ����һ: ����������n,չʾ��ǰ����������n�����                     *\n");
    printf("*                C) Ӧ�����: ����һ������Ϊ50�ķ�����ĿҪ������飬����ǰ��ֱ��ӡ      *\n");
    printf("*                D) �˳�����                                                              *\n");
    printf("*******************************************************************************************\n");
    printf("��ʹ�á�������enter��ʵ��ѡ���ִ�������������ÿ������ǰ��Ĵ�����ִ������<0 - 9><A - D>\n");
    printf("     �ڲ˵���ҳ����δ�����˵�ʱ����'q'��'Q'�˳�����,��ϵͳ��ӡ����ʱ�����ӡǰ50��Ԫ��     \n");
    printf("    �ļ�����ʱ������ϵͳ�������ļ����鳤�Ȳ�ƥ�䣬��ᵼ�¶���ʧ�ܻ��ļ����鲻��ȫ���롣   \n");
    return;
}
void cursorUpdate1(int x){
    switch (x)
    {
    case 0:
        if (flag == 10000)
            printf("*                0) �л������������������������ģʽ: 1�� 10000������                     *\n");
        else if (flag == 50000)
            printf("*                0) �л������������������������ģʽ: 1�� 50000������                     *\n");
        else if (flag == 200000)
            printf("*                0) �л������������������������ģʽ: 1�� 200000������                    *\n");
        else if (flag == 100)
            printf("*                0) �л������������������������ģʽ: 10^5�� 100������                    *\n");
        break;
    case 1:
        printf("*                1) ���������顢���������������������ʱ                              *\n");
        break;
    case 2:
        printf("*                2) ���������顢�鲢�����������������ʱ                              *\n");
        break;
    case 3:
        printf("*                3) ���������顢�ݹ���������������������ʱ                          *\n");
        break;
    case 4:
        printf("*                4) ���������顢���������������������ʱ                              *\n");
        break;
    case 5:
        printf("*                5) ���������顢�������������������������ʱ                          *\n");
        break;
    case 6:
        printf("*                6) ���������顢�������������������������ʱ                          *\n");
        break;
    case 7:
        printf("*                7) ���������顢���Ż�ð�������������������ʱ                        *\n");
        break;
    case 8:
        printf("*                8) ���������顢˫�Ż����������������������ʱ                        *\n");
        break;
    case 9:
        printf("*                9) �����ǰ��������������Ŀ¼��output.txt�ļ�                          *\n");
        break;
    case 10:
        printf("*                A) �ӳ����Ŀ¼��input.txt�ļ���¼������                                 *\n");
        break;
    case 11:
        printf("*                B) Ӧ����һ: ����������n,չʾ��ǰ����������n�����                     *\n");
        break;
    case 12:
        printf("*                C) Ӧ�����: ����һ������Ϊ50�ķ�����ĿҪ������飬����ǰ��ֱ��ӡ      *\n");
        break;
    case 13:
        printf("*                D) �˳�����                                                              *\n");
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
    int n = 0, line = 2; // ��Ӧmenu()��0)
    char c1;
    IN_DEFAULT;
    int *arr = createSmallArray();
    while (1) {
        system("cls");
        Menu();
        Gotoxy(0, 20);
        if ((c1 = _getch()) == -32) {//��VS����������Ҫ�������е�_getch�ĳ�getch

            n = cursorOperate(line, 2, 2, 15, cursorUpdate1);//���¼�����
        }
        else if (c1 == '\0')continue;
        else if (c1 >= '0' && c1 <= '9') {//�������ֱ�Ų���
            char tmp = c1;
            putchar(tmp);
            puts("");
            n = tmp - '0';
        }
        else if (c1 == 'q' || c1 == 'Q') {//�����������
            Gotoxy(0, 21);//�ù�굽���ʵĵط����
            putchar(c1);
            puts("");
            printf("ʦ���ټ�\n");
            system("pause");
            exit(0);
        }
        else if (c1 == 'a' || c1 == 'A') {//�������
            Gotoxy(0, 21);
            putchar(c1);
            puts("");
            int* temparr = readArrayFromFile(flag);
            if (temparr != NULL)arr = temparr;
            system("pause");
            continue;
        }
        else if (c1 == 'b' || c1 == 'B') {
            Gotoxy(0, 21);
            putchar(c1);
            puts("");
            int index = 0;
            printf("Please enter an integer <=%d and >0 :\n", flag);

            if (scanf("%d", &index) == 1 && findKthSmallest(arr, index, flag) != -1)
                printf("The %dth smallest element is %d\n", index, findKthSmallest(arr, index, flag));
            else
                printf("Wrong enter context!Please try again.\n");
            system("pause");
            continue;
        }
        else if (c1 == 'c' || c1 == 'C') {
            Gotoxy(0, 21);
            putchar(c1);
            puts("");
            int* tempTinyArray = createColorSortArray(100);
            sortCell(tempTinyArray, colorSort, 50);
            system("pause");
            continue;
        }
        else if (c1 == 'd' || c1 == 'D') {//�˳�
            Gotoxy(0, 21);
            putchar(c1);
            puts("");
            puts("ʦ���ټ����´�����");
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
            Gotoxy(0, 21);
            if (flag == 10000) {
                flag = 50000;
                arr = createMediumArray();
            }
            else if (flag == 50000) {
                flag = 200000;
                arr = createBigArray();
            }
            else if (flag == 200000) {
				flag = 100;
				arr = createTinyArray();
			}
            else if(flag==100){
                flag = 10000;
                arr = createSmallArray();
			}
            break;
        }
        case 1: {
            Gotoxy(0, 21);
            sortCell(arr, insertSort, flag);       
            system("pause");
            break;
        }
        case 2: {
            Gotoxy(0, 21);
            sortCell(arr, mergeSort, flag);
            system("pause");
            break;
        }
        case 3: {
            Gotoxy(0, 21);
            sortCell(arr, quickSort, flag);
            system("pause");
            break;
        }
        case 4: {
            Gotoxy(0, 21);
            sortCell(arr, countSort, flag);
            system("pause");
            break;
        }
        case 5: {
            Gotoxy(0, 21);
            sortCell(arr, radixCountSort, flag);
            system("pause");
            break;
        }
        case 6: {
            Gotoxy(0, 21);
            sortCell(arr, quickSort2, flag);
            system("pause");
            break;
        }
        case 7: {
            Gotoxy(0, 21);
            sortCell(arr, bubbleSort, flag);
            system("pause");
            break;

        }
        case 8: {
            Gotoxy(0, 21);
            sortCell(arr, quickSortMoT, flag);
            system("pause");
            break;

        }
        case 9: {
            Gotoxy(0, 21);
            writeArrayToFile(arr, flag);
            system("pause");
            break;

        }
        case 10: {
            Gotoxy(0, 21);
            int* temparr = readArrayFromFile(flag);
            if (temparr != NULL)arr = temparr;
            system("pause");
            break;

        }
        case 11: {
            Gotoxy(0, 21);
            int index = 0;
            printf("Please enter an integer <=%d and >0 :\n", flag);
            
            if (scanf("%d", &index) == 1 && findKthSmallest(arr, index, flag) != -1)
                printf("The %dth smallest element is %d\n", index, findKthSmallest(arr, index, flag));
            else 
                printf("Wrong enter context!Please try again.\n");
			system("pause");
			break;
        }
        case 12: {
            Gotoxy(0, 21);
            int* tempTinyArray = createColorSortArray(100);
            sortCell(tempTinyArray, colorSort, 50);
            system("pause");
            break;
        }
        case 13: {
            Gotoxy(0, 21);
            puts("ʦ���ټ����´�����");
            system("pause");
            exit(0);
        }
        }
    }
}
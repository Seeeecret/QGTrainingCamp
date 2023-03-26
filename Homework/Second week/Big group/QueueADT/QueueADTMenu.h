
#define UPKEY 72//键入上键的第二个值
#define DOWNKEY 80//键入下键的第二个值, 二者第一个值是相同的
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
                                            BACKGROUND_INTENSITY)//更改输出菜单内容背景颜色的宏定义: 天蓝色
#define IN_DEFAULT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                           FOREGROUND_RED |                 \
                                               FOREGROUND_GREEN |           \
                                               FOREGROUND_BLUE)//更改输出菜单内容背景颜色的宏定义: 默认
void Menu();//菜单函数
void cursorUpdate1(int x);//高亮显示部分的打印函数
int cursorOperate(int line, int deta, int lower, int upper, void (*p)(int));//处理键入的上下键的函数
void Gotoxy(int x, int y);//移动光标的函数
void Operation();

void Menu()
{
    printf("                                欢迎师兄来到泛型队列测试系统                               \n");
    printf("*******************************************************************************************\n");
    if (typeFlag == 0)
        printf("*                0) 切换队列的样例泛型类型: int                                           *\n");
    else
        printf("*                0) 切换队列的样例泛型类型: double                                        *\n");
    printf("*                1) 新建一个空的样例泛型队列                                              *\n");
    printf("*                2) 输入一个新元素，将新元素入列                                          *\n");
    printf("*                3) 让队首元素出列并打印相应的值                                          *\n");
    printf("*                4) 让队列中所有元素出列并打印                                            *\n");
    printf("*                5) 清空并完全删除队列                                                    *\n");
    printf("*                6) 打印队首元素的值(不出列)                                              *\n");
    printf("*                7) 打印队列长度                                                          *\n");
    printf("*                8) 退出程序                                                              *\n");
    printf("*******************************************************************************************\n");
    printf("    请使用↑、↓和enter来实现选择和执行命令，或者输入每个命令前面的代号来执行命令<0 - 8>   \n");
    printf("                     在菜单主页面且未操作菜单时键入'q'或'Q'退出程序\n");
    printf("                本系统泛型队列类型仅能在队列时不存在切换，从第二个节点开始存储数据         \n");
    return;
}

void cursorUpdate1(int x)
{
    switch (x)
    {
    case 0:
        if (typeFlag == 0)
            printf("*                0) 切换队列的样例泛型类型: int                                           *\n");
        else
            printf("*                0) 切换队列的样例泛型类型: double                                        *\n");
        break;
    case 1:
        printf("*                1) 新建一个空的样例泛型队列                                              *\n");
        break;
    case 2:
        printf("*                2) 输入一个新元素，将新元素入列                                          *\n");
        break;
    case 3:
        printf("*                3) 让队首元素出列并打印相应的值                                          *\n");
        break;
    case 4:
        printf("*                4) 让队列中所有元素出列并打印                                            *\n");
        break;
    case 5:
        printf("*                5) 清空并完全删除队列                                                    *\n");
        break;
    case 6:
        printf("*                6) 打印队首元素的值(不出列)                                              *\n");
        break;
    case 7:
        printf("*                7) 打印队列长度                                                          *\n");
        break;
    case 8:
        printf("*                8) 退出程序                                                              *\n");
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
    line：当前光标所在行数
    deta：行数与菜单选项的差值。比如在main菜单中选项(0)在第2行(行数从0开始计算)，所以deta等于2，即2 - 0
    upper, lower：选项的上下界
    (*P)(int)：函数指针，选择哪个覆盖菜单。只实现了cursorUpdate1一种
    */
    char c1, c2;
    Gotoxy(0, line);
    do
    {
        c2 = _getch();
        if (c2 == DOWNKEY)
        {
            Gotoxy(0, line);
            IN_DEFAULT; //选择默认色
            (*p)(line - deta); //覆盖，实现退选(实际上就是打印)
            if (line == upper) //如果已经到了上界，则返回下界，实现滚动高亮
                line = lower;
            else
                ++line; //
            Gotoxy(0, line);
            IN_CYAN; // 选择青色
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
    int n = 0, line = 2; // 对应menu()的0)
    char c1;
    IN_DEFAULT;
    while (1) {
        system("cls");
        Menu();
        Gotoxy(0, 15);
        if ((c1 = _getch()) == -32) {//非VS环境运行需要将代码中的_getch改成getch

            n = cursorOperate(line, 2, 2, 10, cursorUpdate1);//上下键操作
        }
        else if (c1 == '\0')continue;
        else if (c1 >= '0' && c1 <= '9') {//输入数字编号操作
            char tmp = c1;
            putchar(tmp);
            puts("");
            n = tmp - '0';
        }
        else if (c1 == 'q' || c1 == 'Q') {//处理键入数据
            Gotoxy(0, 16);//让光标到合适的地方输出
            putchar(c1);
            puts("");
            printf("师兄再见\n");
            system("pause");
            exit(0);
        }
        else {//处理键入数据
            puts("输入错误");
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
            initializeQueue(&originQueue);//初始化队列
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
            Gotoxy(0, 16);//让光标到合适的地方输出
            puts("师兄再见，下次再来");
            system("pause");
            exit(0);
        }
              system("pause");
        }
    }
}
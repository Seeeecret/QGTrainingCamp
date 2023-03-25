#define UPKEY 72//键入上键的第二个值
#define DOWNKEY 80//键入下键的第二个值, 二者第一个值是相同的
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
                                            BACKGROUND_INTENSITY)//更改输出菜单内容背景颜色的宏定义: 天蓝色
#define IN_DEFAULT SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                           FOREGROUND_RED |                 \
                                               FOREGROUND_GREEN |           \
                                               FOREGROUND_BLUE)//更改输出菜单内容背景颜色的宏定义: 默认
void Menu();//菜单函数
void cursorUpdate1(int x);//高亮显示部分的打印函数
int cursorOperate(int line, int deta, int lower, int upper, void (*p)(int));//处理键入的上下键的函数
void Gotoxy(int x, int y);//移动光标的函数

void Menu()//菜单函数
{
    printf("                                  欢迎师兄来到链栈测试系统                                 \n");
    printf("*******************************************************************************************\n");
    printf("*                0) 新建一个空的链栈                                                      *\n");
    printf("*                1) 往栈中压入元素                                                        *\n");
    printf("*                2) 弹出栈顶元素并打印                                                    *\n");
    printf("*                3) 检查当前栈是否为空                                                    *\n");
    printf("*                4) 检查当前栈是否存在                                                    *\n");
    printf("*                5) 将栈中所有元素弹出并全部打印                                          *\n");
    printf("*                6) 清空栈中元素并完全删除栈                                              *\n");
    printf("*                7) 打印目前栈中元素数量                                                  *\n");
    printf("*                8) 退出程序                                                              *\n");
    printf("*******************************************************************************************\n");
    printf("请使用↑、↓和enter来实现选择和执行命令，或者输入每个命令前面的代号来执行命令<0 - 7>       \n");
    printf("                     在菜单主页面且未操作菜单时键入'q'或'Q'退出程序\n");
    printf("              本系统链栈顶部元素也存储数据，弹出和压入时改变顶部元素的指针\n");
    return;
}

void cursorUpdate1(int x)
{
    switch (x)
    {
    case 0:
        printf("*                0) 新建一个空的链栈                                                      *\n");
        break;
    case 1:
        printf("*                1) 往栈中压入元素                                                        *\n");
        break;
    case 2:
        printf("*                2) 弹出栈顶元素并打印                                                    *\n");
        break;
    case 3:
        printf("*                3) 检查当前栈是否为空                                                    *\n");
        break;
    case 4:
        printf("*                4) 检查当前栈是否存在                                                    *\n");
        break;
    case 5:
        printf("*                5) 将栈中所有元素弹出并全部打印                                          *\n");
        break;
    case 6:
        printf("*                6) 清空栈中元素并完全删除栈                                              *\n");
    case 7:
        printf("*                7) 打印目前栈中元素数量                                                  *\n");
        break;
    case 8:
        printf("*                7) 退出程序                                                              *\n");
        break;
    }
    return;
}
void Gotoxy(int x, int y)// 移动光标到指定位置
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
    Stack originStack = NULL;
    int n = 0, line = 2; // 对应menu()的0)
    char c1;
    IN_DEFAULT;
    while (1)
    {
        system("cls");
        Menu();
        Gotoxy(0, 15);
        if ((c1 = _getch()) == -32) {//非VS环境运行需要将代码中的_getch改成getch

            n = cursorOperate(line, 2, 2, 9, cursorUpdate1);//上下键操作
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
            system("pause");
            printf("Here is end of run.\n");
        
        }
        else {//处理键入数据
            puts("输入错误");
            system("pause");
            continue;
        }
        switch (n) {
        case 0: {// 新建一个空的链栈
            Gotoxy(0, 16);
            if (originStack == NULL) {
                originStack = createStack();
                puts("New Stack!");
            }
            else puts("You have already created a stack.");
            system("pause");
            break;
        }
        case 1: {// 压入栈顶元素
            Gotoxy(0, 16);
            Item enterData = 0;//新增的节点
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
        case 2: {// 弹出栈顶元素
            Gotoxy(0, 16);
            Item enterData2 = popStack(&originStack);
            if(isnan(enterData2.data))puts("Failing to pop.");
			else
            printf("The pop out data is %.9e\n", enterData2.data);
            system("pause");
            break;
        }
        case 3: { // 判断栈是否为空
            Gotoxy(0, 16);
            int flag = isEmpty(&originStack);
            if( flag==1 )puts("Yes, The stack is empty. Please push some new item.");
			else if(flag == 0)
                puts("No, The stack is not empty.");
            system("pause");
            break;
        }
        case 4: {// 判断栈是否存在
            Gotoxy(0, 16);
            if (originStack == NULL) puts("The stack is not exist, Please new a stack.");
            else puts("The stack is already exist.");
            system("pause");
            fflush(stdin);
            rewind(stdin);
            break;
        }
        case 5: {// 遍历栈
            Gotoxy(0, 16);
            Item popItem = 0;
            while (!isEmpty(&originStack)) {
                popItem = popStack(&originStack);
                printf("The pop item: %.9e\n", popItem.data);
            }
            system("pause");
            break;
        }
        case 6: {// 删除栈
            Gotoxy(0, 16);
            deleteStack(&originStack);
            system("pause");
            break;
        }
        case 7: {
            Gotoxy(0, 16);//让光标到合适的地方输出
            int cnt = countStack(&originStack);
            if (cnt == -1) printf("Failing to count.\n");
            else printf("The stack has %d items.\n", cnt);
            system("pause");
            break;
        }
        case 8: {
            Gotoxy(0, 16);//让光标到合适的地方输出
            puts("师兄再见，下次再来");
            system("pause");
            exit(0);
        }
        }
    }
    system("pause");
}
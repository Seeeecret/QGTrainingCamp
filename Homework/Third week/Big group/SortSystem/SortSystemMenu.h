#define UPKEY 72//键入上键的第二个值
#define DOWNKEY 80//键入下键的第二个值, 二者第一个值是相同的
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
    printf("                                 欢迎师兄来到综合排序测试系统                              \n");
    printf("*******************************************************************************************\n");
    if (flag == 10000)
    printf("*                0) 切换并随机生成排序数组与排序模式: 1次 10000个数据                     *\n");
    else if(flag==50000)
    printf("*                0) 切换并随机生成排序数组与排序模式: 1次 50000个数据                     *\n");
    else if(flag==200000)
    printf("*                0) 切换并随机生成排序数组与排序模式: 1次 200000个数据                    *\n");
    else if(flag==100)
    printf("*                0) 切换并随机生成排序数组与排序模式: 10^5次 100个数据                    *\n");
    printf("*                1) 输出随机数组、插入排序后的数组和排序用时                              *\n");
    printf("*                2) 输出随机数组、归并排序后的数组和排序用时                              *\n");
    printf("*                3) 输出随机数组、递归快速排序后的数组和排序用时                          *\n");
    printf("*                4) 输出随机数组、计数排序后的数组和排序用时                              *\n");
    printf("*                5) 输出随机数组、基数计数排序后的数组和排序用时                          *\n");
    printf("*                6) 输出随机数组、迭代快速排序后的数组和排序用时                          *\n");
    printf("*                7) 输出随机数组、三优化冒泡排序后的数组和排序用时                        *\n");
    printf("*                8) 输出随机数组、双优化快速排序后的数组和排序用时                        *\n");
    printf("*                9) 输出当前随机数组至程序根目录的output.txt文件                          *\n");
    printf("*                A) 从程序根目录的input.txt文件中录入数组                                 *\n");
    printf("*                B) 应用题一: 输入正整数n,展示当前随机数组里第n大的数                     *\n");
    printf("*                C) 应用题二: 生成一个长度为50的符合题目要求的数组，排序前后分别打印      *\n");
    printf("*                D) 退出程序                                                              *\n");
    printf("*******************************************************************************************\n");
    printf("请使用↑、↓和enter来实现选择和执行命令，或者输入每个命令前面的代号来执行命令<0 - 9><A - D>\n");
    printf("     在菜单主页面且未操作菜单时键入'q'或'Q'退出程序,本系统打印数组时仅会打印前50个元素     \n");
    printf("    文件读入时若存在系统数组与文件数组长度不匹配，则会导致读入失败或文件数组不完全读入。   \n");
    return;
}
void cursorUpdate1(int x){
    switch (x)
    {
    case 0:
        if (flag == 10000)
            printf("*                0) 切换并随机生成排序数组与排序模式: 1次 10000个数据                     *\n");
        else if (flag == 50000)
            printf("*                0) 切换并随机生成排序数组与排序模式: 1次 50000个数据                     *\n");
        else if (flag == 200000)
            printf("*                0) 切换并随机生成排序数组与排序模式: 1次 200000个数据                    *\n");
        else if (flag == 100)
            printf("*                0) 切换并随机生成排序数组与排序模式: 10^5次 100个数据                    *\n");
        break;
    case 1:
        printf("*                1) 输出随机数组、插入排序后的数组和排序用时                              *\n");
        break;
    case 2:
        printf("*                2) 输出随机数组、归并排序后的数组和排序用时                              *\n");
        break;
    case 3:
        printf("*                3) 输出随机数组、递归快速排序后的数组和排序用时                          *\n");
        break;
    case 4:
        printf("*                4) 输出随机数组、计数排序后的数组和排序用时                              *\n");
        break;
    case 5:
        printf("*                5) 输出随机数组、基数计数排序后的数组和排序用时                          *\n");
        break;
    case 6:
        printf("*                6) 输出随机数组、迭代快速排序后的数组和排序用时                          *\n");
        break;
    case 7:
        printf("*                7) 输出随机数组、三优化冒泡排序后的数组和排序用时                        *\n");
        break;
    case 8:
        printf("*                8) 输出随机数组、双优化快速排序后的数组和排序用时                        *\n");
        break;
    case 9:
        printf("*                9) 输出当前随机数组至程序根目录的output.txt文件                          *\n");
        break;
    case 10:
        printf("*                A) 从程序根目录的input.txt文件中录入数组                                 *\n");
        break;
    case 11:
        printf("*                B) 应用题一: 输入正整数n,展示当前随机数组里第n大的数                     *\n");
        break;
    case 12:
        printf("*                C) 应用题二: 生成一个长度为50的符合题目要求的数组，排序前后分别打印      *\n");
        break;
    case 13:
        printf("*                D) 退出程序                                                              *\n");
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
    int n = 0, line = 2; // 对应menu()的0)
    char c1;
    IN_DEFAULT;
    int *arr = createSmallArray();
    while (1) {
        system("cls");
        Menu();
        Gotoxy(0, 20);
        if ((c1 = _getch()) == -32) {//非VS环境运行需要将代码中的_getch改成getch

            n = cursorOperate(line, 2, 2, 15, cursorUpdate1);//上下键操作
        }
        else if (c1 == '\0')continue;
        else if (c1 >= '0' && c1 <= '9') {//输入数字编号操作
            char tmp = c1;
            putchar(tmp);
            puts("");
            n = tmp - '0';
        }
        else if (c1 == 'q' || c1 == 'Q') {//处理键入数据
            Gotoxy(0, 21);//让光标到合适的地方输出
            putchar(c1);
            puts("");
            printf("师兄再见\n");
            system("pause");
            exit(0);
        }
        else if (c1 == 'a' || c1 == 'A') {//清空链表
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
        else if (c1 == 'd' || c1 == 'D') {//退出
            Gotoxy(0, 21);
            putchar(c1);
            puts("");
            puts("师兄再见，下次再来");
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
            puts("师兄再见，下次再来");
            system("pause");
            exit(0);
        }
        }
    }
}
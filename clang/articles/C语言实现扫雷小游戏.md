## C语言实现扫雷小游戏

来源：[http://blog.csdn.net/windyj809/article/details/79951220](http://blog.csdn.net/windyj809/article/details/79951220)

时间 2018-04-15 17:44:16




* 我们首先说一下基本思路：首先我们需要两个面板，一个显示面板，一个雷面板，这两个面板需要用二维数组来实现。其次，要在雷面板中布置雷，然后需要输入坐标，排查雷，继而判断是否踩到雷，如果踩到雷，那么玩家死翘翘，游戏结束，如果没有踩到雷，需要判断此坐标周围雷的个数。如果最后设置雷的总个数全部被排查出来，那么玩家赢，游戏结束。
* 我们需要创建一个头文件lei.h来存放需要用到的函数。创建一个源文件lei.c来实现各个是函数。创建一个源文件main.c来测试各个函数。头文件lei.h中，需要有初始化雷函数，即布置雷、显示面板函数、判断周围雷的个数函数、玩游戏函数。源文件lei.c里面就是实现头文件lei.c里面的函数。源文件main.c里面需要有一个菜单函数，一个玩游戏函数，玩游戏函数里面，首先需要定义两个二维数组，用于创建雷面板和显示面板，接着初始化这两个二维数组，然后布置雷函数，接着显示两个面板函数，然后测试判断周围雷的个数函数，最后测试玩游戏函数。
* 具体实现代码如下，里面也有比较详细的注释，供大家参考：

头文件lei.h

    
  

```c
#ifndef __LEI_H_
#define __LEI_H_

#define ROW 10
#define COL 10

#define MINE_COUNT 20  //设置雷的个数

//初始雷 设置雷函数
void set_mine(char mine[ROW + 2][COL + 2], int row, int col);//ROW+2 COL+2是因为为了查看附近的雷方便，给数组的外围又加了一层

//显示雷和面板
void display(char board[ROW][COL], int row, int col);//ROW+2 COL+2是因为输入显示时方便从1开始而不是数组下标的从0开始

//查看附近的雷数
int mine_count(char mine[ROW + 2][COL + 2], int x, int y);

//玩游戏
void play_game(char mine[ROW + 2][COL + 2], char board[ROW + 2][COL + 2]);
#endif
```

源文件main.c

```c
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "lei.h"

//菜单函数
void menu()
{
    printf("***************************\n");
    printf("******  1.play game  ******\n");
    printf("******  0.exit game  ******\n");
    printf("***************************\n");
}

//定义游戏函数
void game()
{
    //定义雷数组和显示面板数组
    char mine[ROW + 2][COL + 2];
    char board[ROW + 2][COL + 2];
    srand((unsigned)time(NULL));

    //初始化雷数组和显示面板数组  将雷数组初始值设置为'0',有雷的值设置为'1'
    memset(mine, '0', sizeof(mine));//将从当前位置到sizeof(mine)的值全部换成'0'并返回给数组mine
    memset(board, '*', sizeof(board));

    //设置雷
    set_mine(mine, ROW + 2, COL + 2);

    //显示初始化数组
    display(board, ROW + 2, COL + 2);//将ROW+2 COL+2传递入函数

    //查看附近还有几个雷
    mine_count(mine, ROW+2, COL+2);

    //玩游戏
    play_game(mine, board);
}

int main()
{
    int choose = 0;
    do
    {
        menu();
        printf("请选择:>");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            game();
            break;
        case 0:
            printf("exit game\n");
            break;
        default:
            printf("输入错误，请重新输入\n");
            break;
        }
    } while (choose);
    system("pause");
    return 0;
}
```

源文件lei.c

```c
#include "lei.h"

//初始化雷 设置雷函数
void set_mine(char mine[ROW + 2][COL + 2], int row, int col)//ROW+2 COL+2是因为为了查看附近的雷方便,给数组的外围又加了一层
{
    int count = MINE_COUNT;
    int i = 0;
    for (i = 0; i < count; i++)
    {
        int x = rand() % (row - 2) + 1;//传递过来的实参是ROW+2,rand()%(row-2)+1,就是1-10
        int y = rand() % (col - 2) + 1;
        if (mine[x][y] == '0')//如果将要放入坐标的位置是‘0’，就说明可以放入雷
        {
            mine[x][y] = '1';
        }
        else//如果将要放入坐标的位置不是‘0’，就说明不能放雷，此时将i--，恢复到原来的数值
        {
            i--;
        }
    }
}


//显示雷和面板
void display(char board[ROW+2][COL+2], int row, int col)//ROW+2 COL+2是因为输入显示时方便从1开始而不是数组下标的从0开始
{
    int i = 0;
    int j = 0;
    printf("    1 2 3 4 5 6 7 8 9 10\n");
    printf("    --------------------\n");
    for (i = 1; i <= ROW; i++)
    {
        printf("%2d |",i);
        for (j = 1; j <= COL; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("    --------------------\n");
}

//查看附近的雷数
int mine_count(char mine[ROW + 2][COL + 2], int x, int y)
{   //雷周围一共8个坐标 int型变量-‘0’就会变为该值的ASCII值，若有雷，返回1，无雷返回0，所以该函数返回的是雷的个数
    return mine[x - 1][y - 1] - '0' + mine[x - 1][y] - '0' + mine[x - 1][y + 1] - '0'
        + mine[x][y + 1] - '0' + mine[x + 1][y + 1] - '0' + mine[x + 1][y] - '0' +
        mine[x + 1][y - 1] - '0' + mine[x][y - 1] - '0';
}

//玩游戏 先输入坐标判断坐标是否合理，再判断是否有雷
void play_game(char mine[ROW + 2][COL + 2], char board[ROW + 2][COL + 2])
{
    int count = 0;//计数器，判断消灭雷的个数
    while (1)
    {
        //输入坐标
        int x = 0;
        int y = 0;
        printf("请输入坐标:");
        scanf("%d%d", &x,&y);
        //判断坐标是否在范围内
        if (((1 <= x) && (x <= ROW)) && ((1 <= y) && (y <= COL)))
        {
            //判断该位置有没有雷
            if (mine[x][y] == '1')
            {
                printf("有雷！你死翘翘啦！\n");
                display(mine, ROW + 2, COL + 2);//显示雷面板，让玩家死的明白
                break;
            }
            else
            {
                int ret = mine_count(mine, x, y);//判断周围雷的个数
                board[x][y] = ret + '0';//ret是int型变量，加‘0’后会转变为相应的ASCII值
                count++;
                display(board, ROW + 2, COL + 2);
                if (count == MINE_COUNT)
                {
                    printf("雷已全部排完，你赢了！\n");
                    break;
                }

            }
        }
        else
        {
            printf("瞎跑，请重新输入\n");
        }

    }
}
```



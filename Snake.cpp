// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
#include <string.h>
#include <windows.h>
using namespace std;









/*
*  if (Time == 1) {
                a++;
                if (a % 15 == 0)
                    Time_count++;
                if(Time_count%61==0)
                    PlaySound(TEXT("Monkeys-Spinning-Monkeys"), NULL, SND_ASYNC);
            gotoRowCol(7, 100);
            cout << "Time passed = " << Time_count;
        }
*/


#define     BLACK        0
#define     BLUE         1
#define    GREEN         2
#define    CYAN          3   
#define    RED           4
#define   MAGENTA        5
#define    BROWN         6 
#define   LIGHTGRAY      7 
#define   DARKGRAY       8 
#define   LIGHTBLUE      9
#define  LIGHTGREEN     10
#define   LIGHTCYAN     11
#define   LIGHTRED      12
#define   LIGHTMAGENTA  13
#define  YELLOW         14
#define    WHITE        15
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define rows 87
#define cols 168
struct point
{
    int ri, ci;
};
struct snake {
    point* Positions = new point[1000];
    int size;
    int Direction;
    char sym;
    int clr;
    int score;
    bool alive;
};
struct food
{
    point Pos;
    int clr;
    char sym;
    bool Alive;
};
void SetClr(int clr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
void SetClr2(int tcl, int bcl)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}
void eraseSnake(snake s)
{
    for (int i = 0; i < s.size; i++)
    {
        gotoRowCol(s.Positions[i].ri, s.Positions[i].ci);
        cout << " ";
    }
}
void eraseSnake_H(snake s)
{
    for (int i = 1; i < s.size; i++)
    {
        gotoRowCol(s.Positions[i].ri, s.Positions[i].ci);
        cout << " ";
    }
}
void moveEat_Grow(snake& snake1, int rl, int cl, food& _food, point* obs, int obsSize, int stage)
{

    int size = snake1.size;
    int last_row = snake1.Positions[size - 1].ri;
    int last_col = snake1.Positions[size - 1].ci;
    for (int i = size - 1; i > 0; i--)
    {
        snake1.Positions[i].ci = snake1.Positions[i - 1].ci;
        snake1.Positions[i].ri = snake1.Positions[i - 1].ri;
    }
    snake1.Positions[0].ci = snake1.Positions[1].ci;
    snake1.Positions[0].ri = snake1.Positions[1].ri;
    if (snake1.Direction == UP)
    {
        snake1.Positions[0].ri++;
    }
    if (snake1.Direction == DOWN)
    {
        snake1.Positions[0].ri--;
    }
    if (snake1.Direction == RIGHT)
    {
        snake1.Positions[0].ci++;
    }
    if (snake1.Direction == LEFT)
    {
        snake1.Positions[0].ci--;
    }
    if (stage == 3)
    {
        if (snake1.Positions[0].ri == rl || snake1.Positions[0].ri == 0 || snake1.Positions[0].ci == 0 || snake1.Positions[0].ci == cl)
        {
            snake1.alive = false;
            eraseSnake(snake1);
            SetClr(BLACK); system("cls"); SetClr(6);
            gotoRowCol(12, 60); cout << " Player got OUT HIT BY OBSTACLE BORDER"; _getch(); exit(1);
        }
    }
    else if (snake1.Positions[0].ri == rl || snake1.Positions[0].ri == 0 || snake1.Positions[0].ci == 0 || snake1.Positions[0].ci == cl)
    {
        if (snake1.Positions[0].ri == 0)
        {
            snake1.Positions[0].ri = rl - 1;

        }
        if (snake1.Positions[0].ci == 0)
        {
            snake1.Positions[0].ci = cl - 1;

        }
        if (snake1.Positions[0].ri == rl)
        {
            snake1.Positions[0].ri = 1;

        }
        if (snake1.Positions[0].ci == cl)
        {
            snake1.Positions[0].ci = 1;


        }
    }
    if (snake1.Positions[0].ri == _food.Pos.ri && snake1.Positions[0].ci == _food.Pos.ci)
    {
        _food.Alive = false;
        snake s2; s2.Positions = new point[snake1.size + 1];
        s2.size = snake1.size;
        for (int i = 0; i < snake1.size; i++)
        {
            s2.Positions[i].ci = snake1.Positions[i].ci;
            s2.Positions[i].ri = snake1.Positions[i].ri;
        }
        s2.Positions[s2.size - 1].ci = last_row;
        s2.Positions[s2.size - 1].ri = last_col;
        delete[]snake1.Positions;
        snake1.Positions = s2.Positions;
        snake1.size++;


    }
    for (int i = 1; i < snake1.size; i++)
    {
        if (snake1.Positions[0].ri == snake1.Positions[i].ri && snake1.Positions[0].ci == snake1.Positions[i].ci)
        {
            SetClr(BLACK);
            system("cls");
            gotoRowCol(rows / 2 - 30, cols / 2 - 30);
            SetClr(6);
            cout << "SNAKE TOCHED HIS BODY AND  GOT OUT       ";
            _getche();
            exit(1);
        }
    }
    for (int i = 1; i < obsSize; i++)
    {
        if (snake1.Positions[0].ri == obs[i].ri && snake1.Positions[0].ci == obs[i].ci)
        {
            SetClr(BLACK);
            system("cls");
            gotoRowCol(rows / 2 - 30, cols / 2 - 30);
            SetClr(6);
            cout << "      SNAKE TOCHED HIS OBSTACLES AND  GOT OUT       ";
            _getch();
            exit(1);
        }
    }

}
bool IsValidDir(snake snake, char Dir)
{
    int I;
    int newDir = Dir;
    if(!(newDir==72|| newDir == 75|| newDir == 80|| newDir == 77))
        return false;       
    if (newDir == 72)
        I = UP;
    if (newDir == 80)
        I = DOWN;
    if (newDir == 77)
        I = LEFT;
    if (newDir == 75)
        I = RIGHT;
    if (snake.Direction == I)
        return false;
    return true;
}
bool IsValidDir3_done(snake *& snake,char Dir,int player,int &snake1)
{
    int I=0; int i=0;
    int newDir = Dir;
    if (newDir == 72 || newDir == 119|| newDir == 116|| newDir == 105)
        I = DOWN;
    if (newDir == 80 || newDir == 115|| newDir == 107 || newDir == 103)
        I = UP;
    if (newDir == 77 || newDir == 102 || newDir == 106 || newDir == 97)
        I = LEFT;
    if (newDir == 75 || newDir == 100 || newDir == 108 || newDir == 104)
        I = RIGHT;

    if (snake1 == 1)
    if (newDir == 72 || newDir == 75 || newDir == 80 || newDir == 77)
        i=1;
    if (newDir == 119 || newDir == 115 || newDir == 97 || newDir == 100)
        i = 2;
    if (newDir == 116 || newDir == 103 || newDir == 104 || newDir == 102)
        i = 3;
    if (newDir == 105 || newDir == 106|| newDir == 107 || newDir == 108)
        i = 4;
    if (player < i &&i<=0)
        return false;
    if (snake[i - 1].Direction == UP && I == DOWN)
        return false;
    if (snake[i - 1].Direction == DOWN && I == UP)
        return false;
    if (snake[i - 1].Direction == RIGHT && I == LEFT)
        return false;
    if (snake[i - 1].Direction == LEFT && I == RIGHT)
        return false;
    snake[i-1].Direction = I;
    return true;
}


int  Direction_(char k)
{
    int a=k;
    if (a == 72)
      return DOWN;
    if (a == 80)
        return UP;
    if (a == 77)
        return RIGHT;
    if (a == 75)
        return LEFT;
}
void init(snake &s) 
{

    s.Direction = RIGHT;
    s.size = 3;
    s.clr = 9;
    s.score = 0;
    int hr =5;
    int hc = cols / 3;
    for (int i = 0;s.size>i; i++)                 
    {                                                
        s.Positions[i].ri = hr;
        s.Positions[i].ci = hc-i;
    }

} 
void printSnake(snake s,char sym,char h)
{
    SetClr(s.clr);
    for (int i = 0; s.size > i; i++)
    {
        gotoRowCol(s.Positions[i].ri, s.Positions[i].ci);
         cout << sym;
    }
}

void Boundry(int ro,int co)
{
    char sym = -37;
    for (int i = 0; ro > i; i++)
    {
        for (int j = 0; co > j; j++)
        {
            if (i == 0 || j == 0 || j == co - 1 || i == ro - 1)
            {
                gotoRowCol(i, j);
                SetClr(9);
                cout << sym;
            }
        }
    }
    Sleep(30);
    for (int i = 0; ro > i; i++)
    {
        Sleep(15);
        for (int j = 0; co > j; j++)
        {
            if (i == 0 || j == 0 || j == co - 1 || i == ro - 1)
            {
                gotoRowCol(i,j);
                SetClr(5);
                cout << sym;
            }
        }
    }
}
void food_Gen(int ro, int co, snake snake_, food & A, point* Obs, int size_ob,snake *S_array,int player)
{
    int obstical_point;
    do {
        obstical_point = 0;
        A.Pos.ri = (rand() % ro) + 1;int & a =  A.Pos.ri;
        A.Pos.ci = (rand() % co) + 1;int& b = A.Pos.ci;
        for (int i = 0; size_ob > i; i++)
        {
            if (Obs[i].ci == A.Pos.ci && Obs[i].ri == A.Pos.ri)
                obstical_point = 1;
        }
        if (player == 1)
        {
            for (int i = 0; snake_.size > i; i++)
            {
                if (snake_.Positions[i].ci == A.Pos.ci && A.Pos.ri == snake_.Positions[i].ri)
                    obstical_point = 1;
            }
        }
        else
        {
            for (int j = 0; player > j; j++) {
                for (int i = 0; S_array[j].size > i; i++)
                {
                    if (S_array[j].Positions[i].ci == A.Pos.ci && S_array[j].Positions[i].ri == snake_.Positions[i].ri)
                        obstical_point = 1;
                }
            }
        }
    } while (obstical_point == 1||A.Pos.ri==0||A.Pos.ci==0|| A.Pos.ci >=co|| A.Pos.ri >= ro);
    gotoRowCol(A.Pos.ri, A.Pos.ci);
    SetClr(A.clr);
    cout <<A.sym;
    SetClr(snake_.clr);
    A.Alive = true;
}
void eraseFood(food food_)
{
    gotoRowCol(food_.Pos.ri,food_.Pos.ci);
    SetClr(BLACK);
    cout << food_.sym;
}
void display_apple(food A)
{
    gotoRowCol(A.Pos.ri, A.Pos.ci);
    SetClr(A.clr);
    cout << A.sym;
} 
void initMultiplayer(int players,snake * &Snake,int r,int c)
{
    for (int i = 0; i < players; i++)
    {
        Snake[i].Positions = new point[100];
        Snake[i].sym = -37;
        Snake[i].size = 3;
        Snake[i].score = 0;
        Snake[i].clr = i + 1;
        Snake[i].Direction = RIGHT;
        Snake[i].alive = 1;

    }
    if (players == 2)
    {
        Snake[0].Positions[0].ri = rows / 3 - 10;
        Snake[0].Positions[0].ci = cols / 3 + 10;
        Snake[0].Positions[1].ri = rows / 3 - 10;
        Snake[0].Positions[1].ci = cols / 3 + 10-1;
        Snake[0].Positions[2].ri = rows / 3 - 10;
        Snake[0].Positions[2].ci = cols / 3 + 10-2;


        Snake[1].Positions[0].ri = rows / 3 +20;
        Snake[1].Positions[0].ci = cols / 3 + 10;
        Snake[1].Positions[1].ri = rows / 3 + 20;
        Snake[1].Positions[1].ci = cols / 3 + 10 - 1;
        Snake[1].Positions[2].ri = rows / 3 + 20;
        Snake[1].Positions[2].ci = cols / 3 + 10 - 2;


    }
    if (players == 3 ||players==4)
    {
        for (int i = 0; i < players; i++)
        {
            Snake[i].Positions[0].ri = rows /(players+i)+(rows/players)*i;
            Snake[i].Positions[0].ci = cols / 3 + 10;
            Snake[i].Positions[1].ri = rows/(players + i) + (rows / players) * i;
            Snake[i].Positions[1].ci = cols / 3 + 10 - 1;
            Snake[i].Positions[2].ri = rows/(players + i) + (rows / players) * i;
            Snake[i].Positions[2].ci = cols / 3 + 10 - 2;
        }
    }
}
void move_eat_grow2(snake*& snakess, int rl, int cl, food& _food, int player,int obsSize,point* obs,int stage)
{
    for (int j = 0; j < player; j++) {
        if (snakess[j].alive == 0)
            continue;
        int last_row = snakess[j].Positions[snakess[j].size - 1].ri;
        int last_col = snakess[j].Positions[snakess[j].size - 1].ci;
        for (int i = snakess[j].size; i > 0; i--)
        {
            snakess[j].Positions[i].ci = snakess[j].Positions[i - 1].ci;
            snakess[j].Positions[i].ri = snakess[j].Positions[i - 1].ri;
        }
        snakess[j].Positions[0].ci = snakess[j].Positions[1].ci;
        snakess[j].Positions[0].ri = snakess[j].Positions[1].ri;

        if (snakess[j].Direction == UP)
        {
            snakess[j].Positions[0].ri++;
        }
        if (snakess[j].Direction == DOWN)
        {
            snakess[j].Positions[0].ri--;
        }
        if (snakess[j].Direction == RIGHT)
        {
            snakess[j].Positions[0].ci++;
        }
        if (snakess[j].Direction == LEFT)
        {
            snakess[j].Positions[0].ci--;
        }

        if (stage == 3)
        {
            if (snakess[j].Positions[0].ri == rl || snakess[j].Positions[0].ri == 0 || snakess[j].Positions[0].ci == 0 || snakess[j].Positions[0].ci == cl)
            {
                snakess[j].alive = false;
                eraseSnake_H(snakess[j]); SetClr(7); int o = rand() % 4;
                gotoRowCol(15+o,cols-30); cout <<"No. " << j + 1 << " Player got OUT";
            }
        }
        else if (snakess[j].Positions[0].ri == rl || snakess[j].Positions[0].ri == 0 || snakess[j].Positions[0].ci == 0 || snakess[j].Positions[0].ci == cl)
        {
            if (snakess[j].Positions[0].ri == 0)
            {
                snakess[j].Positions[0].ri = rl - 1;

            }
            if (snakess[j].Positions[0].ci == 0)
            {
                snakess[j].Positions[0].ci = cl - 1;

            }
            if (snakess[j].Positions[0].ri == rl)
            {
                snakess[j].Positions[0].ri = 1;

            }
            if (snakess[j].Positions[0].ci == cl)
            {
                snakess[j].Positions[0].ci = 1;


            }
        }
        if (snakess[j].Positions[0].ri == _food.Pos.ri && snakess[j].Positions[0].ci == _food.Pos.ci)
        {
            _food.Alive = false;
            snake s2; s2.Positions = new point[1000];
            s2.size = snakess[j].size;
            for (int i = 0; i < snakess[j].size; i++)
            {
                s2.Positions[i].ci = snakess[j].Positions[i].ci;
                s2.Positions[i].ri = snakess[j].Positions[i].ri;
            }
            s2.Positions[s2.size - 1].ci = last_col;
            s2.Positions[s2.size - 1].ri = last_row;
            delete[]snakess[j].Positions;
            snakess[j].Positions = s2.Positions;
            snakess[j].size++;
            snakess[j].score++;
        }
        for (int i = 0; i < player; i++)
        {    
            if (snakess[i].alive == 0)
                continue;
            for (int k = 0; k < snakess[i].size; k++)
            {
                if (i == j &&k==0)
                    continue;
                if (snakess[j].Positions[0].ri == snakess[i].Positions[k].ri && snakess[j].Positions[0].ci == snakess[i].Positions[k].ci)
                {
                    snakess[j].alive = false;
                    for (int m = 0; m < snakess[j].size; m++)
                    {
                        gotoRowCol(snakess[j].Positions[m].ri, snakess[j].Positions[m].ci);
                        cout << " ";
                    }

                }
            }
        }
        for (int i = 0; i < obsSize; i++)
        {
            if (snakess[j].Positions[0].ri == obs[i].ri && snakess[j].Positions[0].ci == obs[i].ci)
            {
                snakess[j].alive = false;
                gotoRowCol(12, cols - 30); cout << j + 1 << " Player got OUT";
                eraseSnake_H(snakess[j]);
            }
        }
    }
}
void printSnake1(snake s, char sym, char h,int &scores)
{
    SetClr(s.clr);
    for (int i = 0; s.size > i; i++)
    {
        gotoRowCol(s.Positions[i].ri, s.Positions[i].ci);
        cout << sym;
    }
   // gotoRowCol(s.Positions[s.size].ri, s.Positions[s.size].ci);
   // cout << " ";
    /*if (scores != s.score)
    {
        gotoRowCol(s.Positions[s.size].ri, s.Positions[s.size].ri);
        cout << ' ';
        gotoRowCol(s.Positions[s.size - 1].ri, s.Positions[s.size - 1].ri);
        cout << ' ';
        gotoRowCol(s.Positions[s.size - 2].ri, s.Positions[s.size - 2].ri);
        cout << ' ';
    }
    scores = s.score;*/
}
point mouse(int len)
{
    point A;
    getRowColbyLeftClick(A.ri, A.ci);
    A.ri /= len;
    A.ci /= len;
    return A;

}
void box(int r, int c, const char* A, int len, int clr, int clr2)
{
    char a = -37;
    for (int ri = r; ri < r + len; ri++)
    {
        for (int ci = c; ci < c + len; ci++)
        {
            if (ci == c || ci == c + len - 1 || r == ri || ri == r + len - 1)
                SetClr(6);

            else
                SetClr(clr);
            gotoRowCol(ri, ci);
            cout << a;
        }
        cout << endl;
    }
    SetClr2(clr2,clr);
    gotoRowCol((r)+(len / 2) - 1, c + (len / 2) - 4);
    cout << A;

}


void box2(int r, int c, const char* A, int len, int clr, int clr2)
{
    char a = -37;
    for (int ri = r; ri < r + len; ri++)
    {
        for (int ci = c; ci < c + len; ci++)
        {
            if (ci == c || ci == c + len - 1 || r == ri || ri == r + len - 1)
                SetClr(6);

            else
                SetClr(clr);
            gotoRowCol(ri, ci);
            cout << a;
        }
        cout << endl;
    }
    SetClr(clr2);
    gotoRowCol((r)+(len / 2) - 1, c + (len / 2) - 4);
    cout << A;

}

void makeobs(int stage, int players, point*& obs, int& obsSize)
{
    obsSize = 0;
    if (players == 1)
    {
        if (stage == 1 || stage == 3)
        {
            for (int i = 30; i <= 50; i++)
            {
                obs[obsSize].ri = 30;
                obs[obsSize].ci = i;
                obsSize++;
            }
            for (int i = 30; i <= 50; i++)
            {
                obs[obsSize].ri = 51;
                obs[obsSize].ci = i;
                obsSize++;
            }
            for (int i = 30; i <= 35; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 30;
                obsSize++;
            }
            for (int i = 30; i <= 35; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 50;
                obsSize++;
            }
            for (int i = 45; i <= 50; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 30;
                obsSize++;
            }
            for (int i = 45; i <= 50; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 50;
                obsSize++;
            }
        }
        if (stage == 2)
        {
            for (int i = 15; i <= 30; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 22;
                obsSize++;
            }
            for (int i = 15; i <= 30; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 61;
                obsSize++;
            }
            for (int i = 60; i <= 75; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 22;
                obsSize++;
            }
            for (int i = 60; i <= 75; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 61;
                obsSize++;
            }
        }
    }
    if (players > 1)
    {
        if (stage == 1 || stage == 3)
        {
            for (int i = 30; i <= 90; i++)
            {
                obs[obsSize].ri = 8;
                obs[obsSize].ci = i;
                obsSize++;
            }
            for (int i = 30; i <= 90; i++)
            {
                obs[obsSize].ri = 67;
                obs[obsSize].ci = i;
                obsSize++;
            }

            for (int i = 8; i <= 15; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 30;
                obsSize++;
            }
            for (int i = 8; i <= 15; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 90;
                obsSize++;
            }

            for (int i = 59; i <= 67; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 30;
                obsSize++;
            }
            for (int i = 59; i <= 67; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = 90;
                obsSize++;
            }
        }
        if (stage == 2)
        {
            int r = 13;
            for (int i = 1; 127 > i; i++)
            {
                obs[obsSize].ri = r;
                obs[obsSize].ci = i;
                obsSize++;
            }
            r = 106;
            for (int i = 1; rows - 3 > i; i++)
            {
                obs[obsSize].ri = i;
                obs[obsSize].ci = r;
                obsSize++;
            }
        }
    }
}
void AnyAlive(snake*snake,int players)
{
    int var=0;
    for (int i = 0; i < players; i++)
    {
        if (snake[i].alive == true)
        {
            var++;
        }
    }
    if (var == 0)
    {
        SetClr(BLACK);
        system("cls"); SetClr(6);
        gotoRowCol(12, 60); cout << " All Player got OUT"; _getch();
        exit(1);
    }
}
void IsWin(snake* s, int players, snake sa, int w)
{
    if (players == 1)
    {
        if (w == sa.score)
        {
            SetClr(3);
            system("cls");
            SetClr(6);
            gotoRowCol(10, 70);
            cout << "PLAYER WON";
            _getche(); exit(1);
        }
    }
    else {
        for (int i = 0; i < players; i++)
            if (w == s[i].score)
            {
                SetClr(0);
                system("cls");
                SetClr(6);
                gotoRowCol(10, 70);
                cout << i + 1 << "PLAYER WON";
                _getch(); exit(1);
            }
    }
}
int main()
{
    bool play = PlaySound(TEXT("Monkeys-Spinning-Monkeys"), NULL, SND_ASYNC);
    const char* A =  " PLAYER 1";
    const char* S1 = " STAGE 0 ";
    const char* S2 = " STAGE 1 ";
    const char* S3 = " STAGE 2 ";
    const char* S4 = " STAGE 3 ";
    const char* B =  " PLAYER 2 ";
    const char* C =  " PLAYER 3 ";
    const char* D = " PLAYER 4 ";
    const char* Y = "   Yes    ";
    const char* N = "   NO     ";
    const char* E = "          ";
    srand(time(0));
    int WinCount=0;
    bool Timemode=0;
    bool TimeFood=0;
    int zero = 0;
    point p; int player; int stage;
        for (int i = 0; i < 4; i++)
        {
            if (i == 0)
                box(30, 30 + (i * 30), A, 15, 2 + i, 15);
            if (i == 1)
                box(30, 30 + (i * 30), B, 15, 2 + i, 15);
            if (i == 2)
                box(30, 30 + (i * 30), C, 15, 2 + i, 15);
            if (i == 3)
                box(30, 30 + (i * 30), D, 15, 2 + i, 15);

        }
        do {
            p = mouse(15);
        } while (!((p.ri == 2 && p.ci == 2) || (p.ri == 2 && p.ci == 4) || (p.ri == 2 && p.ci == 6) || (p.ri == 2 && p.ci == 8)));
        player = p.ci / 2;
        for (int i = 0; i < 4; i++)
        {
            if (i == 0)
                box(30, 30 + (i * 30), S1, 15, 2 +i+ i, 15);
            if (i == 1)
                box(30, 30 + (i * 30), S2, 15, 2 +i+ i, 15);
            if (i == 2)
                box(30, 30 + (i * 30), S3, 15, 2 +i+2+ i, 15);
            if (i == 3)
                box(30, 30 + (i * 30), S4, 15, 2 +i+3+ i, 15);

        }
        do {
            p = mouse(15);
        } while (!((p.ri == 2 && p.ci == 2) || (p.ri == 2 && p.ci == 4) || (p.ri == 2 && p.ci == 6) || (p.ri == 2 && p.ci == 8)));
        stage = p.ci / 2 -1;
        SetClr(BLACK);
        system("cls");
        SetClr(15);
        gotoRowCol(10, 70); cout << "  TIME BASE MODE ";
        box(30, 30 + (1 * 30), Y, 15, 2 + 1, 15);
        box(30, 30 + (2 * 30), N, 15, 2 + 2, 15);
        do {
            p = mouse(15);
        } while (!((p.ri == 2 && p.ci == 4) || (p.ri == 2 && p.ci == 6)));
        if (p.ci == 4)
            Timemode = true;
        if (p.ci == 6)
            Timemode = false;
        if (Timemode == true)
        {
            SetClr(15);
            gotoRowCol(10, 70);
            cout << "  TIME BASE FOOD ALSO ";
            do {
                p = mouse(15);
            } while (!((p.ri == 2 && p.ci == 4) || (p.ri == 2 && p.ci == 6)));
            if (p.ci == 4) {
                TimeFood = true;
                system("cls");
                cout << "\n\n\n\nAfter every 10 sec food will reappear on anonher spot ";
                Sleep(1000);
            }
            if (p.ci == 6)
                TimeFood = false;
        }
        SetClr(BLACK);
        system("cls");
        SetClr(15);
        gotoRowCol(10, 70); cout << "  ENTER WIN POINT  ";
        box2(20, (2 * 30) + 10, E, 15, 2 + 2, 8);
        do
        {
            gotoRowCol(26, 73);
            cin >> WinCount;
        } while (WinCount<=0 || WinCount >110);
    snake* snakess = new snake[player]{};
    snake snake{};
    point* obs = new point[1000]{}; int obs_size = 0;
    int Time_count = 0; int a = 1;
    SetClr(BLACK);
    if (player==1)
    {
        system("cls");
        if (stage == 3)
        {
            SetClr(7);
            gotoRowCol(60, cols - 30);
            cout << "BOUNDRIES ARE DEADLY";
        }
        char f, s;
        food _food;
        char sym = -37;
        init(snake);
        Boundry(rows, cols / 2+1);
        makeobs(stage,player,obs,obs_size);
        for (int i = 0; i < obs_size; i++)
        {
            gotoRowCol(obs[i].ri, obs[i].ci);
            cout << sym;
        }
        printSnake(snake, sym, ':');
        food_Gen(rows-1,cols/2-1,snake,_food,obs,obs_size,snakess,player);
        gotoRowCol(5, 100);
        SetClr(5);
        cout << " Score of Player is  " << snake.score;
        if (TimeFood == 0) {
            while (1)
            {
                if (Timemode == 1) {
                    a++;
                    if (a % 15 == 0)
                        Time_count++;
                    if (Time_count % 59 == 0)
                        PlaySound(TEXT("Monkeys-Spinning-Monkeys"), NULL, SND_ASYNC);
                    gotoRowCol(7, 100);
                    cout << "Time passed = " << Time_count;
                }
                int score = 0;
                Sleep(60);
                int size2 = snake.size - 1;
                if (!((snake.Positions[size2].ri == _food.Pos.ri && snake.Positions[size2].ci == _food.Pos.ci) && (snake.Positions[snake.size].ri == _food.Pos.ri && snake.Positions[snake.size].ci == _food.Pos.ci)))
                {
                  
                    {
                        gotoRowCol(snake.Positions[size2 - 1].ri, snake.Positions[size2 - 1].ci);
                        cout << " ";
                        score = snake.score;
                    }
                    gotoRowCol(snake.Positions[size2].ri, snake.Positions[size2].ci);
                    cout << " ";
                    
                }
                display_apple(_food);
                moveEat_Grow(snake, rows - 1, cols / 2, _food,obs,obs_size,stage);
                if (_food.Alive == false)
                {
                    snake.score += 1;
                    gotoRowCol(5, 100);
                    SetClr(1);
                    cout << "Score of Player is   " << snake.score;
                    eraseFood(_food);
                    food_Gen(rows - 1, cols / 2 - 1, snake, _food, obs, obs_size, snakess, player);
                }
                printSnake(snake, sym, ':');
                 IsWin(snakess, player, snake, WinCount);
                if (_kbhit())
                {
                    char f = _getch();
                    if ((int)f == -32)
                    {
                        if (_kbhit())
                        {
                            char s = _getch();
                            if (IsValidDir(snake, s))
                            {
                                snake.Direction = Direction_(s);
                            }
                        }
                    }
                }
            }
        }
        if (TimeFood == 1)
        {
            int ktime = 0;
            while (1)
            {
                if (Timemode == 1) {
                    a++;
                    if (a % 15 == 0) {
                        Time_count++;
                        ktime++;
                    }
                    if (Time_count % 59 == 0)
                        PlaySound(TEXT("Monkeys-Spinning-Monkeys"), NULL, SND_ASYNC);//GUL
                    gotoRowCol(7, 100);
                    cout << "Count  of 10 = " << ktime<<"  ";
                }
                
                if (ktime%10==0)
                {
                    ktime = 1;
                    _food.Alive = false;
                }
                int score = 0;
                Sleep(60);
                int size2 = snake.size - 1;
                if (!((snake.Positions[size2].ri == _food.Pos.ri && snake.Positions[size2].ci == _food.Pos.ci) && (snake.Positions[snake.size].ri == _food.Pos.ri && snake.Positions[snake.size].ci == _food.Pos.ci)))
                {
                    {
                        gotoRowCol(snake.Positions[size2 - 1].ri, snake.Positions[size2 - 1].ci);
                        cout << " ";
                        score = snake.score;
                    }
                    gotoRowCol(snake.Positions[size2].ri, snake.Positions[size2].ci);
                    cout << " ";
                }
                display_apple(_food);
                moveEat_Grow(snake, rows - 1, cols / 2 - 1, _food,obs,obs_size,stage);
                if (_food.Alive == false)
                {
                    if(ktime!=1)
                    {
                     snake.score += 1;
                     gotoRowCol(5, 100);
                     SetClr(1);
                     cout << "Score of Player is   " << snake.score;
                    }
                    ktime = 1;
                    eraseFood(_food);
                    food_Gen(rows - 1, cols / 2 - 1, snake, _food, obs, obs_size, snakess, player);
                }
                printSnake(snake, sym, ':');
                IsWin(snakess, player, snake, WinCount);

                if (_kbhit())
                {
                    char f = _getch();
                    if ((int)f == -32)
                    {
                        if (_kbhit())
                        {
                            char s = _getch();
                            if (IsValidDir(snake, s))
                            {
                                snake.Direction = Direction_(s);
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
       /* cout << "Do you want to play time mode?...............0 for no 1 for yes";
        cin >> Timemode;
        if (Timemode != 0)
        {
            cout << "Do you want to play time base food mode...............0 for no 1 for yes";
            cin >> TimeFood;
            cout << " Enter Win Count ="; do { cin >> WinCount; } while (!(WinCount > 0 && WinCount < 1000));
            Sleep(100);
            cout << "\n\n\n\nAfter every 10 sec food will reappear on anonher spot ";
        }*/
        system("cls");
        SetClr(3);
        cout << "SNAKE 1 ARROW KEYS\n\n\n";
        cout << "SNAKE 2   W == UP...   D == RIGHT....   A == LEFT....  S == DOWN  \n\n\n";
        cout << "SNAKE 3  W == UP...   D == RIGHT....   A == LEFT....  S == DOWN  \n\n\n";
        cout << " I == UP...   L == RIGHT....   J == LEFT....  K == DOWN  \n\n\n";
        cout << "                                        PRESS ANY KEY\n\n\n"; _getch();
        SetClr(0);

        system("cls");
        if (stage == 3)
        {
            SetClr(7);
            gotoRowCol(60, cols - 30);
            cout << "BOUNDRIES ARE DEADLY";
        }
        int* scores = new int [player] {};
        food khana;
        Boundry(rows-2,cols-39);
        makeobs(stage, player, obs, obs_size);
        for (int i = 0; i < obs_size; i++)
        {
            char a = -37;
            gotoRowCol(obs[i].ri, obs[i].ci);
            cout << a;
        }
        initMultiplayer(player,snakess, rows - 3, cols - 40);
        for (int i = 0; player > i; i++)
        {
            printSnake(snakess[i],-37,')');
        }
        food_Gen(rows - 3, cols - 50,snake,khana,obs,obs_size,snakess,player);
        int ktime = 0;
        while (1)
        {
            if (Timemode == 1) {
                a++;
                if (a % 22 == 0) {

                    Time_count++;
                    if(TimeFood)
                    ktime++;
                }
                if (Time_count % 59 == 0)
                    PlaySound(TEXT("Monkeys-Spinning-Monkeys"), NULL, SND_ASYNC);//GULMonkeys-Spinning-Monkeys
                if (TimeFood == 1)
                {
                    
                    gotoRowCol(7, cols - 30);
                    cout << "Count of 10 = " << ktime<<"  ";
                }
                else
                {
                    gotoRowCol(7, cols - 30);
                    cout << "Time passed = " << Time_count;
                }
            }
            if (ktime == 10)
            {
                ktime = 1;
                eraseFood(khana);
                khana.Alive = false;
            }
            Sleep(30);
            for (int i = 0; player > i; i++)
            {
                SetClr(7);
                gotoRowCol(10 + i, cols - 30);
                cout << " Score of player " << i + 1 << " is " << snakess[i].score;
            }
            if (khana.Alive == false)
            {
                eraseFood(khana);
                food_Gen(rows - 1, cols / 2 - 1, snake, khana, obs, obs_size, snakess, player);
            }
            for (int i = 0; player > i; i++)
            {
                if (snakess[i].alive == 0)
                    continue;
                {
                    gotoRowCol(snakess[i].Positions[snakess[i].size - 1].ri, snakess[i].Positions[snakess[i].size - 1].ci);
                    cout << " ";
                    gotoRowCol(snakess[i].Positions[snakess[i].size - 2].ri, snakess[i].Positions[snakess[i].size - 2].ci);
                    cout << " ";
                    gotoRowCol(snakess[i].Positions[snakess[i].size ].ri, snakess[i].Positions[snakess[i].size ].ci);
                    cout << " ";
                }
            }
            move_eat_grow2(snakess, rows - 3, cols - 40, khana, player,obs_size,obs,stage);
            if (khana.Alive == false)
            food_Gen(rows - 30, cols - 50, snake, khana, obs, obs_size, snakess, player);
            if (_kbhit())
            {
                char f = _getch();
                if ((int)f == -32)
                {
                    if (_kbhit())
                    {
                        char s = _getch();
                        if (IsValidDir(snakess[0], s))
                        {
                            snakess[0].Direction = Direction_(s);
                        }
                    }
                }
                else
                {
                    if (IsValidDir3_done(snakess, f, player, zero))
                        int jjjj = 9;
                }
            }
            for (int i = 0; player > i; i++)
            {
                if (snakess[i].alive == 0)
                    continue;
                printSnake1(snakess[i], -37, ')', scores[i]);
                if(TimeFood)
                if (snakess[i].score == WinCount)
                {
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n"<<" PLAYER"<< i+1<<" WON ";
                    exit(1);
                }
            }
            AnyAlive(snakess,player);
            IsWin(snakess, player, snake, WinCount);
        }
    }
}















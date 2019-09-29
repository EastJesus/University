/* 
    Игра "Лабиринт".Нужно персонажем дойти до выхода, можно двигать ящики, 
    управление на wasd.При нахождении выхода игра успешно завершается, но параллельно 
    идет таймер, если он доходит до нуля, то вы проигрываете. Как составлялся уровень : 
    я сделал массив из символов, в начале игры он проходит цикл, и каждый символ 
    заменяется символом из ascii таблицы.Управление героем выполняется функцией Switch, 
    считывается пространство перед героем и перемещает героя.Есть два логических типа, 
    один отвечает за то, может ли герой двигаться вперед, а второй за то, должна ли 
    игра продолжаться.Все это описано в отдельных функциях, которые выполяются вместе 
    в функции main, основная часть игры выполянется в цикле.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <unistd.h>

const int rows = 10;
const int columns = 15;
const unsigned char Hero = 2;
const unsigned char Wall = 177;
const unsigned char Box = 254;
const unsigned char Exit = 176;
const unsigned char Surprise = 3;

const unsigned char level0[rows][columns + 1] =
    {"#####2#########",
     "# X    X  X # #",
     "########   X  #",
     "#   X  #  X # #",
     "# X  ###X  X  #",
     "# # X    X #X #",
     "# X  ## X   X #",
     "#   X#   # X  #",
     "# 1 X###  X  3#",
     "###############"};

bool gamego = true;
unsigned char level2[rows][columns];
int herorow = 0;
int herocolumn = 0;
HANDLE console = 0;

void settings()
{
    srand(time(0));
    console = GetStdHandle(STD_OUTPUT_HANDLE);
}

void startsettings()
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            unsigned char symbol = level0[r][c]; /// symbol - ñèìâîë õ,#, 1, 2
            switch (symbol)
            {
            case '#':
            {
                level2[r][c] = Wall;
                break;
            }
            case '1':
            {
                level2[r][c] = Hero;
                herorow = r;
                herocolumn = c;
                break;
            }
            case '2':
            {
                level2[r][c] = Exit;
                break;
            }
            case 'X':
            {
                level2[r][c] = Box;
                break;
            }
            case '3':
            {
                level2[r][c] = Surprise;
                break;
            }
            default:
            {
                level2[r][c] = symbol;
                break;
            }
            }
        }
    }
}

void graphics()
{
    COORD cursor;
    cursor.X = 0;
    cursor.Y = 0;
    SetConsoleCursorPosition(console, cursor);

    printf("\n\n\t");
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            unsigned char symbol = level2[r][c];

            switch (symbol)
            {
            case Wall:
            {
                SetConsoleTextAttribute(console, 15);
                break;
            }
            case Hero:
            {
                SetConsoleTextAttribute(console, 14);
                break;
            }
            case Box:
            {
                SetConsoleTextAttribute(console, 10);
                break;
            }
            case Exit:
            {
                SetConsoleTextAttribute(console, 12);
                break;
            }
            case Surprise:
            {
                SetConsoleTextAttribute(console, 4);
                break;
            }
            }
            printf("%c", symbol);
        }
        printf("\n\t");
    }
}

void MoveHero(int row, int column)
{
    unsigned char moveTo = level2[row][column];
    bool canMove = false;

    switch (moveTo)
    {
    case ' ':
    {
        canMove = true;
        break;
    }
    case Exit:
    {
        gamego = false;
        break;
    }
    case Box:
    {
        int HeroDirectionR = row - herorow;
        int HeroDirectionC = column - herocolumn;
        if (level2[row + HeroDirectionR][column + HeroDirectionC] == ' ')
        {
            canMove = true;
            level2[row][column] = ' ';
            level2[row + HeroDirectionR][HeroDirectionC + column] = Box;
        }
        break;
    }
    case Surprise:
    {
        system("cls");
        printf("\n\t Hello, mister Pugachev!");
        _getch();
        gamego = false;
    }
    }
    if (canMove)
    {
        level2[herorow][herocolumn] = ' ';
        herorow = row;
        herocolumn = column;
        level2[herorow][herocolumn] = Hero;
    }
}

void game()
{

    unsigned char input;
    while (kbhit())
    {
        input = _getch();
    }

    switch (input)
    {
    case 'w':
    {
        MoveHero(herorow - 1, herocolumn);
        break;
    }
    case 's':
    {
        MoveHero(herorow + 1, herocolumn);
        break;
    }
    case 'a':
    {
        MoveHero(herorow, herocolumn - 1);
        break;
    }
    case 'd':
    {
        MoveHero(herorow, herocolumn + 1);
        break;
    }
    case 'r':
    {
        startsettings();
        break;
    }
    }
}

void theend()
{
    system("cls");
    printf("\n\t The end");
    _getch;
}

void badend()
{
    system("cls");
    printf("\n\t Game over, username");
    _getch();
}

DWORD WINAPI taimer(LPVOID lpParam)
{
    clock_t start, stop;
    float b;
    float a = 20;
    start = clock();
    printf("You have %f seconds.\n\t", b = (a - (((double)(stop + start)) / CLOCKS_PER_SEC)));
    if (b <= 0)
    {
        gamego = false;
    }
    stop = clock();
}

int main()
{
    printf("\n\t Use AWSD to play, you need find exit. Good luck. Press any key.");
    _getch();
    system("cls");
    settings();
    startsettings();
    do
    {
        HANDLE hThread;
        hThread = CreateThread(NULL, 0, taimer, 0, 0, NULL);
        graphics();
        game();
    } while (gamego);
    theend();
    return 0;
}
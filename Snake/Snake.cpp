#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;


enum KeyCodes {ESCAPE = 27, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80};
enum Colors { DARKGREEN = 2, RED = 12, YELLOW = 14};
enum Objects {WALL, HALL, APPLE};
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

const int hight = 20;
const int wight = 40;
int location[hight][wight] = {};

void dvishok();
void ganerLocation();
void ganerApple();



int main()
{   
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100;
    SetConsoleCursorInfo(h, &info);

    srand(time(0));

	ganerLocation();
    dvishok();
    ganerApple();
}

void ganerApple()
{
    int i = 0;
    int y = 0;
    do
    {
        i = rand() % (hight - 2) + 1;
        y = rand() % (wight - 2) + 1;
    } while (location[i][y] != HALL);

    location[i][y] = APPLE;
              
}

void ganerLocation()
{

    for (int i = 0; i < hight; ++i)
    {
        for (int y = 0;y < wight; ++y)
        {
            if (i == 0 || y == 0 || i == hight - 1 || y == wight - 1)
            {
                location[i][y] = WALL;
            }
            else
            {
                location[i][y] = HALL;
            }
        }
    }

    for (int i = 0; i < hight; ++i)
    {
        for (int y = 0; y < wight; ++y)
        {
            switch (location[i][y])
            {
            case WALL:
                SetConsoleTextAttribute(h, DARKGREEN);
                cout << (char)177;
                break;
            case HALL:
                cout << " ";
                break;
            case APPLE:
                SetConsoleTextAttribute(h, RED);
                cout << (char)15;
                break;
            default:
                cout << location[i][y];
                break;
            }
        }
        cout << "\n";
    }
}

void dvishok()
{
	COORD position;
	position.X = 1;
	position.Y = 2;

	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, YELLOW);
	cout << 0;

    while (true) {
        int code = _getch();
        if (code == 224)
            code = _getch();

        SetConsoleCursorPosition(h, position);
        SetConsoleTextAttribute(h, YELLOW);
        cout << " ";

        switch (code) {
        case ESCAPE:
            // cout << "ESCAPE\n";
            break;
        case RIGHT:
            position.X++;
            break;
        case LEFT:
            position.X--;
            break;
        case UP:
            position.Y--;
            break;
        case DOWN:
            position.Y++;
            break;
        default:
            cout << code << "\n";
            break;
        }

        SetConsoleCursorPosition(h, position);
        SetConsoleTextAttribute(h, YELLOW);
        cout << 0;

        if (location[position.Y][position.X] == WALL)
        {
            SetConsoleTextAttribute(h, RED);
            cout << "Game over!";
            break;
        }
        else if(location[position.Y][position.X] == APPLE)
        {
            ganerApple();
            location[position.Y][position.X] = HALL;
            break;
        }


    }
}
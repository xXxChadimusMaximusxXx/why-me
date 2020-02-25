
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool gameOver;
const int height = 20;
const int width = 30;
int x, y, fruitX, fruitY,score = 0;
int tailX[height * width], tailY[height*width];
int tailN = 0;
enum eDirections { STOP = 0,UP,DOWN,RIGHT,LEFT };
eDirections dir;

void startUp() {

    gameOver = false;
    dir = STOP;
    x = height / 2;
    y = width / 2;
    fruitX = rand() % height;
    fruitY = rand() % width;
}

void draw() {

    system("cls");
    
    for (int i = 0; i < width+1; i++)
        cout << "#";

    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) 
                cout << "#";
            
            bool print = false;
            
            if (i == x && j == y) {

                cout << "O";
                

            }
            else 
                if (i == fruitX && j == fruitY){

                    cout << "F";
                    
            }else {
                for (int k = 0; k < tailN; k++) {
                    
                    if (tailX[k] == i && tailY[k] == j) {
                        cout << "o";
                        print = true;
                    }

                }
                if (!print)
                    cout << " ";
            }
            
        }
        cout << endl;
    }

    for (int i = 0; i < width+1; i++)
        cout << "#";

    cout << endl;
    
}

void input() {
    
    if (_kbhit) {
        switch (_getch()) {
            case 'w':
                dir = UP;
               break;
            case 's':
                dir = DOWN;
               break;
            case 'a': 
                dir = LEFT;
               break;
            case 'd': 
                dir = RIGHT;
               break;
            case 'x':
                gameOver = true;
               break;
        }
    }

}

void logic() {
    
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X;
    int prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailN;i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case UP:
            x--;
           break;
        case DOWN:
            x++;
           break;
        case LEFT:
             y--;
            break;
        case RIGHT:
            y++;
           break;
    }

    if (x > height || x<0 || y>width-2 || y < 0)
        gameOver = true;

    for (int i = 0; i < tailN; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % height;
        fruitY = rand() % width;
        tailN++;
    }

}

int main()
{
    startUp();
    
    while (!gameOver) {
        draw();
        input();
        logic();
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

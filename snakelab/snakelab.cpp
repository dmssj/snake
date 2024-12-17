#include <iostream> //змейка
#include <conio.h>  //консольные функц
#include <thread> 
#include <chrono>
using namespace std;

const int width = 20, height = 20;
int x, y, fruitx, fruity, score, tailx[100], taily[100], n_tail;
bool gameOver;
enum eDirection { Stop = 0, Left, Right, Up, Down } dir;

int main() {
    setlocale(LC_ALL, "RU");
    gameOver = false;
    dir = Stop;
    x = width / 2; y = height / 2;
    fruitx = rand() % width; fruity = rand() % height;
    score = n_tail = 0;

    while (!gameOver) {
        system("cls");
        for (int i = 0; i < width + 2; i++) cout << "_"; cout << endl; //верх
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) { //лево
                if (j == 0) cout << "|";
                if (i == y && j == x) cout << "o";
                else if (i == fruity && j == fruitx) cout << "$";
                else {
                    bool print = false;
                    for (int k = 0; k < n_tail; k++)
                        if (tailx[k] == j && taily[k] == i) { cout << "o"; print = true; }
                    if (!print) cout << " ";
                }
                if (j == width - 1) cout << "|"; //право
            }
            cout << endl;
        }
        for (int i = 0; i < width + 2; i++) cout << "_"; cout << "\nСчет: " << score << endl; //низ

        if (_kbhit()) { //управ змейкой
            switch (_getch()) {
            case 'a': dir = Left; break;
            case 'd': dir = Right; break;
            case 'w': dir = Up; break;
            case 's': dir = Down; break;
            case 'x': gameOver = true; break;
            }
        }

        int prevX = tailx[0], prevY = taily[0], prev2X, prev2Y; //движ змейки
        tailx[0] = x; taily[0] = y;
        for (int i = 1; i < n_tail; i++) {
            prev2X = tailx[i]; prev2Y = taily[i];
            tailx[i] = prevX; taily[i] = prevY;
            prevX = prev2X; prevY = prev2Y;
        }
        switch (dir) {
        case Left: x--; break;
        case Right: x++; break;
        case Up: y--; break;
        case Down: y++; break;
        }
        if (x < 0 || x >= width || y < 0 || y >= height) gameOver = true; //столкновение
        for (int i = 0; i < n_tail; i++) if (tailx[i] == x && taily[i] == y) gameOver = true;
        if (x == fruitx && y == fruity) { //еда
            score += 10; 
            fruitx = rand() % width; 
            fruity = rand() % height; 
            n_tail++;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <conio.h>
using namespace std;
bool gameOver;
int width = 20;
int height = 20;
int x, y, fruitX, fruitY, score;
vector<pair<int, int>> tail;
size_t tailLength;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    tail.clear();
    tailLength = 0;
}
void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";
            if (i == y && j == x) cout << "O";
            else if (i == fruitY && j == fruitX) cout << "F";
            else {
                bool print = false;
                for (auto segment : tail) {
                    if (segment.first == j && segment.second == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }
            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': dir = LEFT; break;
        case 'd': dir = RIGHT; break;
        case 'w': dir = UP; break;
        case 's': dir = DOWN; break;
        case 'x': gameOver = true; break;
        }
    }
}
void Logic() {
    pair<int, int> prev = {x, y};
    tail.insert(tail.begin(), prev);
    if (tail.size() > tailLength)
        tail.pop_back();
    switch (dir) {
    case LEFT: x--; break;
    case RIGHT: x++; break;
    case UP: y--; break;
    case DOWN: y++; break;
    case STOP: break;
    }
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
    for (auto segment : tail)
        if (segment.first == x && segment.second == y)
            gameOver = true;
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailLength++;
    }
}
int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    return 0;
}
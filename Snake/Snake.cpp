#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
using namespace std;

struct Point {
    int x;
    int y;
};

enum class Direction { Right, Down, Left, Up };

// Hop dong toa do chung cho ca nhom.
const int BOARD_LEFT = 2;
const int BOARD_TOP = 2;
const int BOARD_RIGHT = 45;
const int BOARD_BOTTOM = 20;

void gotoxy(int x, int y) {
    COORD pos;
    pos.X = static_cast<SHORT>(x);
    pos.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Snake {
private:
    vector<Point> body;

public:
    Snake() {
        body.push_back({ 12, 10 }); // dau
        body.push_back({ 11, 10 });
        body.push_back({ 10, 10 });
    }

    void draw() const {
        for (size_t i = 0; i < body.size(); ++i) {
            gotoxy(body[i].x, body[i].y);
            cout << (i == 0 ? 'O' : 'o');
        }
    }

    void move(Direction direction) {
        for (int i = static_cast<int>(body.size()) - 1; i > 0; --i) {
            body[i] = body[i - 1];
        }

        if (direction == Direction::Right) body[0].x++;
        if (direction == Direction::Down)  body[0].y++;
        if (direction == Direction::Left)  body[0].x--;
        if (direction == Direction::Up)    body[0].y--;
    }

    Point head() const {
        return body.front();
    }

    bool occupies(int x, int y) const {
        for (const Point& p : body) {
            if (p.x == x && p.y == y) return true;
        }
        return false;
    }
};

bool isOpposite(Direction current, Direction next) {
    return (current == Direction::Right && next == Direction::Left) ||
        (current == Direction::Left && next == Direction::Right) ||
        (current == Direction::Up && next == Direction::Down) ||
        (current == Direction::Down && next == Direction::Up);
}

int main() {
    Snake snake;
    Direction direction = Direction::Right;

    while (true) {
        if (_kbhit()) {
            char key = static_cast<char>(_getch());
            Direction next = direction;

            if (key == 'd' || key == 'D') next = Direction::Right;
            if (key == 's' || key == 'S') next = Direction::Down;
            if (key == 'a' || key == 'A') next = Direction::Left;
            if (key == 'w' || key == 'W') next = Direction::Up;

            if (!isOpposite(direction, next)) {
                direction = next;
            }
        }

        system("cls");
        snake.draw();
        snake.move(direction);
        Sleep(150);
    }
    return 0;
}
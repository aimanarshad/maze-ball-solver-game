#include <iostream>
#include <stack>

using namespace std;

const int ROWS = 7;
const int COLS = 7;

int maze[ROWS][COLS] = {
    {0, 1, 0, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1},
    {0, 0, 1, 0, 1, 0, 1},
    {0, 1, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 1, 0, 0},
    {1, 1, 1, 1, 0, 0, 0}
};

struct Point {
    int x, y;
    Point* parent;
};

void printMaze(int maze[ROWS][COLS], Point* start) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (start->x == i && start->y == j) {
                cout << "P ";
            } else if (maze[i][j] == 1) {
                cout << "# ";
            } else if (maze[i][j] == 2) {
                cout << "* ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

bool isValidMove(int x, int y, int maze[ROWS][COLS]) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] == 0);
}

void DFS(int maze[ROWS][COLS], Point* start, Point* end) {
    stack<Point*> s;
    bool visited[ROWS][COLS] = {false};

    s.push(start);
    start->parent = nullptr;
    visited[start->x][start->y] = true;

    while (!s.empty()) {
        Point* current = s.top();
        s.pop();

        if (current->x == end->x && current->y == end->y) {
            cout << "Path found!" << endl;
            while (current != nullptr) {
                maze[current->x][current->y] = 2; // Mark path cells
                current = current->parent;
            }
            printMaze(maze, start);
            return;
        }

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++) {
            int newX = current->x + dx[i];
            int newY = current->y + dy[i];
            if (isValidMove(newX, newY, maze) && !visited[newX][newY]) {
                Point* next = new Point{newX, newY, current};
                s.push(next);
                visited[newX][newY] = true;
            }
        }
    }

    cout << "No path found!" << endl;
}

int main() {
    Point start = {0, 0, nullptr};
    Point end = {ROWS - 1, COLS - 1, nullptr};

    cout << "Maze Solver Game" << endl;
    cout << "Maze Legend: P - Player, # - Wall, * - Path" << endl;
    cout << "Commands: u (up), d (down), l (left), r (right), q (quit)" << endl;

    char move;
    bool gameOver = false;

    while (!gameOver) {
        printMaze(maze, &start);

        cout << "Enter move: ";
        cin >> move;

        int newX = start.x;
        int newY = start.y;

        switch (move) {
            case 'u':
                newX--;
                break;
            case 'd':
                newX++;
                break;
            case 'l':
                newY--;
                break;
            case 'r':
                newY++;
                break;
            case 'q':
                gameOver = true;
                break;
            default:
                cout << "Invalid command!" << endl;
                continue;
        }

        if (isValidMove(newX, newY, maze)) {
            start.x = newX;
            start.y = newY;
        } else {
            cout << "Invalid move!" << endl;
        }

        if (start.x == end.x && start.y == end.y) {
            cout << "Congratulations! You've reached the end of the maze." << endl;
            gameOver = true;
        }
    }

    return 0;
}


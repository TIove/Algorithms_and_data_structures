#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Point {
    int x;
    int y;
    Point() = default;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

vector<char> bfs(vector<vector<char>>& maze, Point start, Point end) {
    vector<vector<vector<char>>> path(maze.size(), vector<vector<char>>(maze[0].size(), vector<char>()));
    queue<Point> queue;
    queue.push(start);
    while (!queue.empty()) {
        Point cur = queue.front();
        queue.pop();

        if (cur.x == end.x && cur.y == end.y) {
            return path[cur.y][cur.x];
        }

        if (cur.y - 1 >= 0 && maze[cur.y - 1][cur.x] != '#' &&
            path[cur.y - 1][cur.x].empty() &&
            !(cur.x == start.x && cur.y - 1 == start.y)) {
            path[cur.y - 1][cur.x] = path[cur.y][cur.x];
            path[cur.y - 1][cur.x].push_back('U');
            queue.push(Point(cur.x, cur.y - 1));
        }
        if (cur.y + 1 < maze.size() && maze[cur.y + 1][cur.x] != '#' &&
            path[cur.y + 1][cur.x].empty() &&
            !(cur.x == start.x && cur.y + 1 == start.y)) {
            path[cur.y + 1][cur.x] = path[cur.y][cur.x];
            path[cur.y + 1][cur.x].push_back('D');
            queue.push(Point(cur.x, cur.y + 1));
        }
        if (cur.x - 1 >= 0 && maze[cur.y][cur.x - 1] != '#' &&
            path[cur.y][cur.x - 1].empty() &&
            !(cur.x - 1 == start.x && cur.y == start.y)) {
            path[cur.y][cur.x - 1] = path[cur.y][cur.x];
            path[cur.y][cur.x - 1].push_back('L');
            queue.push(Point(cur.x - 1, cur.y));
        }
        if (cur.x + 1 < maze[cur.y].size() && maze[cur.y][cur.x + 1] != '#' &&
            path[cur.y][cur.x + 1].empty() &&
            !(cur.x + 1 == start.x && cur.y == start.y)) {
            path[cur.y][cur.x + 1] = path[cur.y][cur.x];
            path[cur.y][cur.x + 1].push_back('R');
            queue.push(Point(cur.x + 1, cur.y));
        }
    }
    return vector<char>();
}

int main() {
    ifstream in("in.txt");
    int n, m;
    in >> n >> m;

    vector<vector<char>> maze(n, vector<char>(m));

    Point start, end;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            in >> maze[i][j];
            if (maze[i][j] == 'S') {
                start.y = i;
                start.x = j;
            }
            else if (maze[i][j] == 'T') {
                end.y = i;
                end.x = j;
            }
        }
    }
    in.close();

    vector<char> path = bfs(maze, start, end);

    ofstream out("out.txt");

    if (!path.empty()) {
        out << path.size() << endl;
        for (char c : path) {
            out << c;
        }
        out << endl;
    }
    else {
        out << -1 << endl;
    }
    out.close();
    return 0;
}
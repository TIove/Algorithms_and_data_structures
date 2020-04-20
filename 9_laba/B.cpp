#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    int x;
    int y;
};

int dist(Point A, Point B) {
    return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);
}

double Prim(const vector<Point>& points) {
    int n = points.size();
    vector<bool> used(n, false);
    vector<int> min_cost_edge(n, 2147483647);
    min_cost_edge[0] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int w = 0; w < n; w++) {
            if (!used[w] && (v == -1 || min_cost_edge[w] < min_cost_edge[v]))
                v = w;
        }
        used[v] = true;
        for (int to = 0; to < n; to++) {
            if (!used[to] && to != v && dist(points[v], points[to]) < min_cost_edge[to])
                min_cost_edge[to] = dist(points[v], points[to]);
        }
    }
    double totalCost = 0;
    for (int dist2 : min_cost_edge)
        totalCost += sqrt(dist2);
    return totalCost;
}

int main() {
    ifstream in("spantree.in");
    int n;
    in >> n;
    vector<Point> points(n);
    int x, y;
    for (int i = 0; i < n; i++) {
        in >> x >> y;
        points[i] = {x, y};
    }
    in.close();
    ofstream out("spantree.out");
    out.precision(10);
    out << Prim(points) << endl;
    out.close();
    return 0;
}
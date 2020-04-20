#include <fstream>
#include <vector>

using namespace std;

void floyd(vector <vector <int>>& graph, int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

int main() {
    ifstream in("pathsg.in");
    ofstream out("pathsg.out");

    int n, m;

    in >> n >> m;

    vector<vector <int>> graph(n, vector <int>(n, 10001));
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        in >> from >> to >> weight;
        graph[from - 1][to - 1] = weight;
    }
    floyd(graph, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                graph[i][j] = 0;
            out << graph[i][j] << ' ';
        }
        out << '\n';
    }
    return 0;
}
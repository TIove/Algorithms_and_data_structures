#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum color {
    white,
    grey,
    black
};

bool DFS(const vector<vector<int>>& G, vector<color>& colors, vector<int>& answer, int v) {
    colors[v] = grey;
    for (int u : G[v]) {
        if (colors[u] == white) {
            if (!DFS(G, colors, answer, u))
                return false;
        }
        else if (colors[u] == grey)
            return false;
    }
    colors[v] = black;
    answer.push_back(v);
    return true;
}

vector<int> topSort(const vector<vector<int>>& G) {
    vector<int> result;
    vector<color> colors(G.size(), white);
    for (int i = 0; i < G.size(); i++) {
        if (colors[i] == white) {
            if (!DFS(G, colors, result, i))
                return vector<int>(0);
        }
    }
    return result;
}

int main() {
    ifstream fin("topsort.in");

    int n, m;
    fin >> n >> m;
    vector<vector<int>> G(n, vector<int>(0));

    int v, u;
    for (int i = 0; i < m; ++i) {
        fin >> v >> u;
        v--, u--;
        G[v].push_back(u);
    }
    fin.close();

    vector<int> answer = topSort(G);

    ofstream fout("topsort.out");
    if (answer.empty())
        fout << -1 << endl;
    else {
        for (int i = answer.size() - 1; i >= 0; --i)
            fout << answer[i] + 1 << " ";
    }
    fout.close();
}
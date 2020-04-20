#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

enum color {
    white,
    color1,
    color2
};

color getInverseColor(color c) {
    if (c == color1)
        return color2;
    else if (c == color2)
        return color1;
    else
        return white;
}

bool DFS(const vector<list<int>>& G, vector<color>& colors, color c, int v) {
    colors[v] = c;
    for (int u : G[v]) {
        if (colors[u] == white) {
            if (!DFS(G, colors, getInverseColor(c), u))
                return false;
        }
        else if (colors[u] == c)
            return false;
    }
    return true;
}

bool isTwoParts(const vector<list<int>>& G) {
    vector<color> colors(G.size(), white);
    for (int i = 0; i < G.size(); i++) {
        if (colors[i] == white) {
            if (!DFS(G, colors, color1, i))
                return false;
        }
    }
    return true;
}

int main() {
    ifstream fin("bipartite.in");

    int n, m;
    fin >> n >> m;
    vector<list<int>> G(n, list<int>(0));

    int v, u;
    for (int i = 0; i < m; i++) {
        fin >> v >> u;
        v--, u--;
        G[v].push_back(u);
        G[u].push_back(v);
    }
    fin.close();

    ofstream fout("bipartite.out");
    if (isTwoParts(G))
        fout << "YES" << endl;
    else
        fout << "NO" << endl;
    fout.close();
}
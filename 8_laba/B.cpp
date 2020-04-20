#include <fstream>
#include <vector>
#include <list>

using namespace std;

enum color {
    white,
    grey,
    black
};

bool isCycle(const vector<list<int>>& G, vector<color>& colors, list<int>& cycle, int v) {
    colors[v] = grey;
    for (int u : G[v]) {
        if (colors[u] == white) {
            if (isCycle(G, colors, cycle, u)) {
                colors[v] = black;
                cycle.push_back(v);
                return true;
            }
        }
        else if (colors[u] == grey) {
            colors[v] = black;
            cycle.push_back(u);
            cycle.push_back(v);
            return true;
        }
    }
    colors[v] = black;
    cycle.clear();
    return false;
}

list<int> getCycle(const vector<list<int>>& G) {
    vector<color> colors(G.size(), white);
    for (int i = 0; i < G.size(); i++) {
        if (colors[i] == white) {
            list<int> cycle;
            if (isCycle(G, colors, cycle, i)) {
                cycle.reverse();
                while (cycle.front() != cycle.back())
                    cycle.pop_front();
                cycle.pop_back();
                return cycle;
            }
        }
    }
    return list<int>(0);
}

int main() {
    ifstream fin("cycle.in");

    int n, m;
    fin >> n >> m;
    vector<list<int>> G(n, list<int>(0));

    int v, u;
    for (int i = 0; i < m; i++) {
        fin >> v >> u;
        v--, u--;
        G[v].push_back(u);
    }
    fin.close();

    list<int> cycle = getCycle(G);

    ofstream fout("cycle.out");
    if (cycle.empty())
        fout << "NO" << endl;
    else {
        fout << "YES" << endl;
        for (int i : cycle)
            fout << i + 1 << " ";
    }
    fout.close();
}
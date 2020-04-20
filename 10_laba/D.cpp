#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = 8e18;

struct Edge {
    int from;
    int to;
    ll weight;
    Edge(int from, int to, ll weight) : from(from), to(to), weight(weight) {}
    Edge() {}
};

void Dfs(int from, const vector<vector<int>>& graph, vector<bool>& used)
{
    used[from] = true;
    for (auto to : graph[from])
    {
        if (!used[to])
            Dfs(to, graph, used);
    }
}

vector<ll> Ford(int v, const vector<Edge>& edges, const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<ll> dist(n, INF);
    vector<int> parents(n, -1);
    int lastChanged = -1;
    dist[v] = 0;
    for (int i = 0; i < n; ++i) {
        lastChanged = -1;
        for (auto edge : edges) {
            if (dist[edge.from] < INF) {
                if (dist[edge.to] > dist[edge.from] + edge.weight) {
                    dist[edge.to] = max(-INF, dist[edge.from] + edge.weight);
                    parents[edge.to] = edge.from;
                    lastChanged = edge.to;
                }
            }
        }
    }

    if (lastChanged != -1) {
        for (int i = 0; i < n; ++i)
            lastChanged = parents[lastChanged];

        vector<bool> used(n);
        Dfs(lastChanged, graph, used);

        for (int i = 0; i < n; ++i) {
            if (used[i])
                dist[i] = -INF;
        }
    }

    return dist;
}


int main(){
    ifstream fin("path.in");
    ofstream fout("path.out");
    int n, m, s;
    fin >> n >> m >> s;
    s--;

    ll from, to, weight;
    vector<Edge> edges;
    vector<vector<int>> graph(n);

    for (int i = 0; i < m; ++i) {
        fin >> from >> to >> weight;
        edges.emplace_back(from - 1, to - 1, weight);
        graph[from - 1].push_back(to - 1);
    }

    for (auto dist : Ford(s, edges, graph)) {
        switch (dist)
        {
            case INF:
                fout << "*";
                break;
            case -INF:
                fout << "-";
                break;
            default:
                fout << dist;
        }
        fout << "\n";
    }

    fout << '\n';

    return 0;
}
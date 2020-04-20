#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct edge {
    int from, to, weight;
};

void ford(vector<int>& dist, vector<int>& parent, vector<edge> graph, int& n, int& negCycleStart) {
    dist[0] = 0;
    for (int i = 0; i < n; i++) {
        negCycleStart = -1;
        for (edge edge : graph) {
            if (dist[edge.to] > dist[edge.from] + edge.weight) {
                dist[edge.to] = dist[edge.from] + edge.weight;
                parent[edge.to] = edge.from;
                negCycleStart = edge.to;
            }
        }
    }
}

int main() {
    ifstream in("negcycle.in");
    ofstream out("negcycle.out");
    
    int n;
    int negCycleStart = -1;
    vector<edge> graph;
    
    vector<int> parent;
    in >> n;
    vector<int> dist(n, 10001);
    graph.resize(n);
    parent.resize(n);
    for (int from = 0; from < n; from++) {
        for (int to = 0; to < n; to++) {
            int weight;
            in >> weight;
            graph.push_back({ from, to, weight });
        }
    }
    ford(dist, parent, graph, n, negCycleStart);
    if (negCycleStart != -1) {
        vector<int> way;
        int negCycleEnd = negCycleStart;

        for (int i = 0; i < n; i++)
            negCycleEnd = parent[negCycleEnd];

        for (int negCycleNow = negCycleEnd; negCycleNow != negCycleEnd || way.empty(); negCycleNow = parent[negCycleNow])
            way.push_back(negCycleNow);

        way.push_back(negCycleEnd);
        reverse(way.begin(), way.end());

         out << "YES\n";
         out << way.size() << endl;

        for (int cur_v : way)
             out << cur_v + 1 << ' ';
    }
    else
         out << "NO";


    return 0;
}
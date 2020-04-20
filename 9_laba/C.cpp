#include <fstream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

ll Prim(vector <bool> isPath, vector <pair <ll, ll>> graph[1000000]) {
    ll result = 0;
    priority_queue< pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>> > pQueue;

    pQueue.push({0, 0});

    while (!pQueue.empty()) {
        pair<ll, ll> costOfVertex = pQueue.top();
        pQueue.pop();
        if (isPath[costOfVertex.second])
            continue;
        isPath[costOfVertex.second] = true;
        
        result += costOfVertex.first;

        for (auto & i : graph[costOfVertex.second]) {
            if (!isPath[i.first])
                pQueue.push(make_pair(i.second, i.first));
        }
    }
    return result;
}

int main() {
    ifstream in("spantree3.in");
    ofstream out("spantree3.out");
    ll n, m;
    in >> n >> m;
    vector <pair <ll, ll>> graph[1000000];
    vector <bool> isPath(n, false);
    
    for (ll i = 0; i < m; i++) {
        ll from, to, weight;
        in >> from >> to >> weight;
        from--;
        to--;
        graph[from].emplace_back(to, weight);
        graph[to].emplace_back(from, weight);
    }
    out << Prim(isPath, graph);
    return 0;
}
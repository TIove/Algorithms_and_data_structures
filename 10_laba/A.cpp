#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <limits>

using namespace std;

typedef long long ll;

const ll INF = numeric_limits<ll>::max();

struct Edge {
    ll to;
    ll weight;

    Edge() = default;

    Edge(ll to, ll weight)
            : to(to)
            , weight(weight) {}

    bool operator < (const Edge& other) const {
        return weight < other.weight;
    }

};

ll dijkstra(const vector<list<Edge>>& G, ll from, ll to) {
    ll n = G.size();
    vector<ll> distances(n, INF);
    set<pair<ll, ll>> queue;

    distances[from] = 0;
    queue.insert({0, from});

    while(!queue.empty()) {
        auto cur = *queue.begin();
        queue.erase(queue.begin());

        for (Edge e : G[cur.second]) {
            if (distances[e.to] > cur.first + e.weight) {
                queue.erase({distances[e.to], e.to});
                queue.insert({cur.first + e.weight, e.to});
                distances[e.to] = cur.first + e.weight;
            }
        }
    }

    return distances[to] != INF ? distances[to] : -1;
}
int main() {
    ifstream in("pathmgep.in");
    ll n, s, f;
    in >> n >> s >> f;
    s--, f--;

    vector<list<Edge>> G(n);
    ll weight;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            in >> weight;
            if (weight != -1 && i != j)
                G[i].push_back({j, weight});
        }
    }
    in.close();

    ofstream out("pathmgep.out");
    out << dijkstra(G, s, f) << endl;
    out.close();

    return 0;
}

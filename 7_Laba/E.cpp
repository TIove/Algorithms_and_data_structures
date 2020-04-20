#include <fstream>
#include <vector>
#include <queue>

using namespace std;

vector<int> bfs(vector<vector<int>>& nodes, int source) {
    vector<int> dest(nodes.size(), -1);
    dest[0] = 0;
    queue<int> queue;
    queue.push(0);
    
    while (!queue.empty()) {
        int cur = queue.front();
        queue.pop();
        for (int v : nodes[cur]) {
            if (dest[v] == -1) {
                dest[v] = dest[cur] + 1;
                queue.push(v);
            }
        }
    }
    return dest;
}

int main() {
    ifstream input("pathbge1.in");
    int n, m;
    input >> n >> m;

    vector<vector<int>> nodes(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int a, b;
        input >> a >> b;
        a--;
        b--;
        nodes[a].push_back(b);
        nodes[b].push_back(a);
    }
    input.close();

    vector<int> ans = bfs(nodes, 0);

    ofstream output("pathbge1.out");
    for (int i : ans)
        output << i << ' ';
    output << '\n';
    output.close();

    return 0;
}
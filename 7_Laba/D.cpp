#include <fstream>
#include <vector>

using namespace std;

void dfs(
        vector<vector<int>>& nodes, int nodeNumber, vector<int>& nodesComponents, int componentNumber) {
    
    nodesComponents[nodeNumber] = componentNumber;
    for (int i = 0; i < nodes[nodeNumber].size(); i++) {
        if (nodesComponents[nodes[nodeNumber][i]] == 0) {
            dfs(nodes, nodes[nodeNumber][i], nodesComponents, componentNumber);
        }
    }
}

int main() {
    ifstream in("components.in");
    ofstream output("components.out");

    int n, m;
    in >> n >> m;

    vector<vector<int>> nodes(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int a, b;
        in >> a >> b;
        a--;
        b--;
        nodes[a].push_back(b);
        nodes[b].push_back(a);
    }

    vector<int> nodesComponents(n, 0);
    int componentNumber = 0;
    for (int i = 0; i < n; i++) {
        if (nodesComponents[i] == 0) {
            dfs(nodes, i, nodesComponents, ++componentNumber);
        }
    }

    output << componentNumber << '\n';
    for (int i = 0; i < n; i++) {
        output << nodesComponents[i] << ' ';
    }

    in.close();
    output.close();

    return 0;
}
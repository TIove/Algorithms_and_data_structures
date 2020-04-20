#include <fstream>
#include <vector>

using namespace std;
bool cyclic (int n, int &cycle_st, vector <int> *graph, vector <int> &color ) {
    for (int j = 0; j < ; ++j) {
        color[j] = 1;
        for (size_t i = 0; i < graph[j].size(); ++i) {
            int to = graph[j][i];
            if (color[to] == 0) {
                if (cyclic (to, cycle_st, graph,  color))  return true;
            }
            else if (color[to] == 1) {
                cycle_st = to;
                return true;
            }
        }
        color[v] = 2;
        return false;
    }
}
void dfs (int v, vector <int> *graph, vector<bool> &used, vector <int> &answer) {
    used[v] = true;
    for (int i = 0; i < graph[v].size(); i++) {
        int to = graph[v][i];
        if (!used[to])
            dfs (to, graph, used, answer);
    }
    answer.push_back (v+1);
}

void topological_sort(int n, vector <int> *graph, vector<bool> &used, vector <int> &answer) {
    for (int i = 0; i < n; i++)
        used[i] = false;
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs (i, graph, used, answer);
    reverse (answer.begin(), answer.end());
}

int main() {
    ifstream in("topsort.in");
    ofstream out("topsort.out");
    int n, m;
    in >> n >> m;

    vector <int> graph[100001];
    vector <bool> used (n);
    vector<int> answer;
    vector<int> color (n,0);

    int cycle_st = -1;
    for (int i = 0; i < m; i++){
        int a, b;
        in >> a >> b;
        graph[a-1].push_back(b-1);
    }
    in.close();
/*
    for (int i = 0; i < n; i++){
        if (cyclic(i, cycle_st, graph, color))
            break;
    }
*/
    if (cyclic()){
        out << "-1";
    }
    else{
        topological_sort(n, graph, used, answer);
        for (int i : answer)
        {
            out << i << " ";
        }
        out << endl;
    }
    out.close();
    return 0;
}
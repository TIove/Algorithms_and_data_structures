#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void DFS(int start,const vector<vector<int>>& matrix,vector<short>& used,vector<int>& ans,bool& cycle){
    for(const int& i: matrix[start]){
        if (used[i] == 1){
            cycle = true;
        }
        if (used[i] == 0){
            used[i] = 1;
            DFS(i,matrix,used,ans,cycle);
        }
    }
    used[start] = 2;
    ans.push_back(start);
}

int main() {
    int n,m, start, end;
    bool cycle = false;

    ifstream fin("hamiltonian.in");
    ofstream fou2t("hamiltonian.out");

    fin >> n >> m;
    vector<vector<int>> matrix(n,(vector<int>()));
    vector<short> used(n,0);
    vector<int> ans(0);

    for (int i = 0; i < m; ++i) {
        fin >> start >> end;
        matrix[start - 1].push_back(end - 1);
    }
    for (int j = 0; j < n; ++j) {
        used[j] = 1;
        DFS(j,matrix,used,ans,cycle);
        while (j + 1 < n) {
            if (used[j + 1] == 0) {
                break;
            } else {
                j++;
            }
        }
    }

    bool trouble = true;
    bool error = false;

    for (int i = n - 1; i > 0; --i) {
        trouble = true;
        for (const int& j: matrix[ans[i]]) {
            if (j == ans[i - 1]) {
                trouble = false;
            }
        }
        if (trouble) {
            error = true;
            break;
        }
    }

    if (error) {
        fout << "NO";
    } else {
        fout << "YES";
    }
    fin.close();
    fout.close();
    return 0;
}
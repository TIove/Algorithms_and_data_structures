#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m;
    in >> n >> m;

    vector<int> ans(n, 0);

    for (int i = 0; i < m; ++i) {
        int j, k;
        in >> j >> k;
        ans[j - 1]++;
        ans[k - 1]++;
    }

    for (int l = 0; l < n; ++l) {
        out << ans[l] << " ";
    }

    in.close();
    out.close();
    return 0;
}
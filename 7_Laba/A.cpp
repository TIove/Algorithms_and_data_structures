#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    short n, m;
    in >> n >> m;

    vector<vector<int>> matrix(n, vector<int> (n, 0));

    for (int i = 0; i < m; ++i) {
        short j, k;
        in >> j >> k;
        matrix [j - 1][k - 1] = 1;
    }

    for (short l = 0; l < n; ++l) {
        for (short i = 0; i < n; ++i) {
            out << matrix[l][i] << ' ';
        }
        out << '\n';
    }

    in.close();
    out.close();
    return 0;
}
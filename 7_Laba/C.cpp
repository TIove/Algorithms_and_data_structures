#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    bool f = false;
    short n, m;
    in >> n >> m;

    vector <vector<short>> matrix(n, vector<short>(n,0));

    for (short k = 0; k < m; ++k) {
        short i, j;
        in >> i >> j;
        if (matrix[i - 1][j - 1] == 1 or matrix[j - 1][i - 1] == 1){
            f = true;
        }
        matrix[i - 1][j - 1] = 1;
        matrix[j - 1][i - 1] = 1;
    }

    if (f)
        out << "YES";
    else
        out << "NO";

    in.close();
    out.close();
    return 0;
}
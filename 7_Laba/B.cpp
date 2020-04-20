#include <fstream>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    bool isNoDirection = true;
    short n;
    in >> n;

    short matrix[n][n];
    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < n; ++j) {
            in >> matrix[i][j];
        }
    }

    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < n; ++j) {
            if (!isNoDirection) {
                break;
            }
            if (i == j && matrix[i][j] == 1) {
                isNoDirection = false;
            } else
                isNoDirection = matrix[i][j] == matrix[j][i] == 1;
        }
    }

    if (isNoDirection)
        out << "YES";
    else
        out << "NO";

    in.close();
    out.close();

    return 0;
}
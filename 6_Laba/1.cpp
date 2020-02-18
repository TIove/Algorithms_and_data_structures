#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("height.in");
    ofstream out("height.out");
    int n;
    in >> n;
    vector<int> nodes(n, 1);
    for (int i = 0; i < n; i++) {
        int value, l, r;
        in >> value >> l >> r;
        if (l != 0)
            nodes[l - 1] = nodes[i] + 1;
        if (r != 0)
            nodes[r - 1] = nodes[i] + 1;
    }
    in.close();

    int height = 0;
    for (int i = 0; i < n; i++) {
        if (nodes[i] > height)
            height = nodes[i];
    }
    out << height;
    out.close();
    return 0;
}
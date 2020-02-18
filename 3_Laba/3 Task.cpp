#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("isheap.in");
    ofstream out("isheap.out");
    int n;
    in >> n;
    vector <int> list (n);

    bool key = true;
    in >> list.at(0);
    for (int i = 1; i < n; i++) {
        in >> list.at(i);
        if (list.at(i) < list.at(i / 2 - (i + 1) % 2) ) {
            key = false;
        }
    }

    if (key) {
        out << "YES";
    }
    else {
        out << "NO";
    }
    in.close();
    out.close();
}


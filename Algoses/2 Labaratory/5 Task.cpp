#include <fstream>
#include <vector>
using namespace std;

void Qsort(vector<int> &a, int left, int right, int& k) {
    if (left < right) {
        int key = a.at(left + ( rand() % (right - left) ) );

        int i = left;
        int j = right;

        while (i <= j) {
            while (a.at(i) < key) i++;
            while (a.at(j) > key) j--;
            if (i > j)
                break;
            swap(a.at(i), a.at(j));
            i++;
            j--;
        }

        if (k <= j)
            Qsort(a, left, j, k);
        else
            Qsort(a, i, right, k);
    }
}

int main() {
    ifstream in("kth.in");
    ofstream out("kth.out");
    int k, n;
    in >> n >> k;
    k--;

    int A, B, C;
    vector<int> a (n);
    in >> A >> B >> C >> a.at(0) >> a.at(1);
    in.close();

    for (int i = 2; i < n; i++) {
        a[i] = A * a[i - 2] + B * a[i - 1] + C;
    }
    Qsort(a, 0, a.size() - 1, k);

    out << a[k];
    out.close();
    return 0;
}
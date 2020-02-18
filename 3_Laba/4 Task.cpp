#include <vector>
#include <fstream>

using namespace std;

void siftDown(vector<int>& a, int n, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int max = i;
    if (l < n && a[l] > a[max])
        max = l;
    if (r < n && a[max] < a[r])
        max = r;
    if (max != i) {
        swap(a[i], a[max]);
        siftDown(a, n, max);
    }
}

void buildHeap(vector<int>& a) {
    for (int i = a.size() / 2 - 1; i >= 0; --i) {
        siftDown(a, a.size(), i);
    }
}

void heapSort(vector<int>& a) {
    buildHeap(a);
    for (int i = a.size() - 1; i >= 0 ; --i) {
        swap(a[0], a[i]);
        siftDown(a, i, 0);
    }
}

int main()
{
    ifstream in("sort.in");
    int n;
    in >> n;
    vector<int> a (n);
    for (int i = 0; i < n; i++) {
        in >> a[i];
    }
    in.close();

    heapSort(a);

    ofstream out("sort.out");
    for (int i : a) {
        out << i << " ";
    }
    out.close();
}

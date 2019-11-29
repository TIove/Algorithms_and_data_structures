#include <fstream>
#include <vector>
#include <string>

using namespace std;

void lsdsort(vector<string>& v, int m, int k) {

    for (int i = m - 1; i >= m - k; i--) {
        vector<int> counters(26);
        for (int j = 0; j < v.size(); j++) {
            counters[v[j][i] - 'a']++;
        }

        int buf, sum = 0;
        for (int j = 0; j < counters.size(); j++) {
            buf = counters[j];
            counters[j] = sum;
            sum += buf;
        }

        vector<string> result(v.size());
        for (int j = 0; j < v.size(); j++) {
            result[ counters[v[j][i] - 'a'] ] = v[j];
            counters[v[j][i] - 'a']++;
        }
        v = result;

        counters.clear();
        result.clear();
    }
}



int main() {
    ifstream in("radixsort.in");
    int n, m, k;
    in >> n >> m >> k;
    vector<string> a (n);
    for (int i = 0; i < n; i++) {
        in >> a[i];
    }
    in.close();

    lsdsort(a, m, k);

    ofstream out("radixsort.out");
    for (int i = 0; i < a.size(); i++) {
        out << a[i] << endl;
    }
    out.close();
}
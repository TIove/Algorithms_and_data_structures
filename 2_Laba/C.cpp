#include <vector>
#include <fstream>
using namespace std;

void merge(vector<int>& array, vector<int>& array_first, vector<int>& array_second) {
    array.clear();
    int index_first = 0, index_second = 0;
    while (index_first < array_first.size() && index_second < array_second.size()) {
        if ( array_first.at(index_first) <= array_second.at(index_second) ) {
            array.push_back(array_first.at(index_first));
            index_first++;
        }
        else if ( array_first.at(index_first) > array_second.at(index_second) ) {
            array.push_back(array_second.at(index_second));
            index_second++;
        }
    }

    while (index_first < array_first.size()) {
        array.push_back(array_first.at(index_first));
        index_first++;
    }

    while (index_second < array_second.size()) {
        array.push_back(array_second.at(index_second));
        index_second++;
    }
}

void merge_sort(vector<int>& array, long long& sum) {
    if (1 < array.size()) {
        vector<int> array_first (array.begin(), array.begin() + array.size() / 2);
        merge_sort(array_first, sum);

        vector<int> array_second(array.begin() + array.size() / 2, array.end());
        merge_sort(array_second, sum);

        int index_first = 0, index_second = 0;
        while (index_first < array_first.size() && index_second < array_second.size()) {
            if ( array_first.at(index_first) > array_second.at(index_second) ) {
                sum += array_first.size() - index_first;
                index_second++;
            }
            else {
                index_first++;
            }
        }

        merge(array, array_first, array_second);
    }
}

int main() {
    long long sum = 0;
    ifstream in("inversions.in");
    ofstream out("inversions.out");
    int n;
    in >> n;
    vector<int> a (n);
    for (int i = 0; i < n; i++) {
        in >> a.at(i);
    }
    in.close();

    merge_sort(a, sum);

    out << sum;
    out.close();
    return 0;
}

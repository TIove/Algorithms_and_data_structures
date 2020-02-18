#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void merge(vector< vector<string> > &vec, int left, int mid, int right){
    int it1 = 0;
    int it2 = 0;
    vector<vector<string> > result;
    while(left + it1 < mid && mid + it2 < right){
        if (vec[left + it1][0] <= vec[mid + it2][0]){
            result.push_back(vec[left + it1]);
            it1++;
        }else{
            result.push_back(vec[mid + it2]);
            it2++;
        }
    }
    while(left + it1 < mid){
        result.push_back(vec[left + it1]);
        it1++;
    }
    while(mid + it2 < right){
        result.push_back(vec[mid + it2]);
        it2++;
    }
    for(int i = 0; i < it1 + it2; i++){
        vec[left + i] = result[i];
    }
}

void mergeSort(vector< vector<string> >& p, int left, int right){
    if(left + 1 >= right){
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(p, left, mid);
    mergeSort(p, mid, right);
    merge(p, left, mid, right);
}
int main() {
    ifstream in("race.in");
    ofstream out("race.out");

    int n;
    in >> n;
    vector<vector<string> > Vec (n);
    for(int i = 0; i < n; i++){
        string buf;
        for(int j = 0; j < 2; j++){
            in >> buf;
            Vec[i].push_back(buf);
        }
    }
    mergeSort(Vec, 0, n);
    string country;

    out << "=== " << Vec[0][0] << " ===" << '\n';
    country = Vec[0][0];

    for(int j = 0; j < n; j++){
        if(country != Vec[j][0]){
            out << "=== " << Vec[j][0] << " ===" << endl;
            out << Vec[j][1] << endl;
        }else{
            out << Vec[j][1] << endl;
        }
        country = Vec[j][0];
    }


    return 0;
}
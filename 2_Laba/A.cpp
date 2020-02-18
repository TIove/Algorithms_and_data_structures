#include <iostream>
#include <fstream>
void quickSort( int left, int right,int arr[]) {

    int i = left, j = right;
    int key;
    int mid = arr[rand() % (right-left) + left ];

    while (i <= j) {
        while (arr[i] < mid)
            i++;
        while (arr[j] > mid)
            j--;
        if (i <= j) {
            key = arr[i];
            arr[i] = arr[j];
            arr[j] = key;
            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(left, j,arr);
    if (i < right)
        quickSort(i, right,arr);
}



int main() {
    using namespace std;
    int length = 0;


    ifstream ifile("sort.in");
    ifile >> length;
    int a[length];

    for (int i = 0; i < length ; ++i) {
        ifile >> a[i];
    }

    quickSort(0,length-1,a);


    ofstream ofile("sort.out");
    for (int k = 0; k < length; ++k) {
        ofile << a[k]<<" ";
    }

    return 0;
}
#include <iostream>
#include <fstream>

int main() {
    using namespace std;
    int length = 0;


    ifstream ifile("smallsort.in");
    ifile >> length;
    int a[length];


    for (int i = 0; i < length ; ++i) {
        ifile >> a[i];
    }



    int key=0, temp=0;
    for (int i=0; i<length-1; i++) {
        key=i+1;
        temp=a[key];

        for (int j=i+1; j>0; j--) {
            if (temp<a[j-1]) {
                a[j]=a[j-1];
                key=j-1;
            }
        }
        a[key]=temp;
    }

    ofstream ofile("smallsort.out");
    for (int k = 0; k < length; ++k) {
        ofile << a[k]<<" ";
    }

    return 0;
}
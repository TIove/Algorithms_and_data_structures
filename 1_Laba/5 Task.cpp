#include <iostream>
#include <fstream>

int main() {
    using namespace std;
    int length = 0;
    int min,mid,max;

    ifstream ifile("sortland.in");
    ifile >> length;
    float a[length];
    float b[length];

    for (int i = 0; i < length ; ++i) {
        ifile >> a[i];
    }
    for (int l = 0; l < length; ++l) {
        b[l]=a[l];
    }



    int key=0;
    float temp=0;
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

    for (int k = 0; k < length ; ++k) {
        if (a[0]==b[k]) {
             min = k+1;
        }
        if (a[(length-1)/2]==b[k]) {
             mid = k+1;
        }
        if (a[length-1]==b[k]) {
             max = k+1;
        }
    }


    ofstream ofile("sortland.out");
        ofile << min <<" "<< mid <<" "<< max;


    return 0;
}
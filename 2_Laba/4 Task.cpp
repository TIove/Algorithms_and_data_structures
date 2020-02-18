#include <iostream>
#include <vector>
#include <fstream>

int main(){
    using namespace std;
    int n;
    
    ifstream inp("antiqs.in");
    ofstream otp("antiqs.out");

    inp >> n;
    vector<int> arr (n);
    for (int i = 1; i < n+1; ++i) {
        arr[i-1] = i;
    }
    for (int i = 2;i < n;i++) {
        swap(arr[i],arr[i / 2]);
    }

    for (int i=0;i<n;i++)
        otp << arr[i] <<" ";

    return 0;
}
#include <iostream>
#include <fstream>
int main() {
    using namespace std;
    int h,w;
    int sumend=0;

    ifstream ifile("turtle.in");
    ifile >> h;
    ifile >> w;

    int a[h][w];

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            ifile >> a[i][j];
        }
    }




    int x = 0;
    int y = h-1;
    int locmax = 0;
    for (int k = 1; k < h+w-1; ++k) {
        int x1 = min(k, w - 1);
        int y1 = k - x1;

        while (y1 >= 0 && y >= y1 && x1>=0){
            if (x+x1-1 < 0){
                locmax = a[y-y1+1][x+x1];
            }else{
                if (y-y1+1 > h-1){
                    locmax = a[y-y1][x+x1-1];
                }else{
                    locmax = max(a[y-y1][x+x1-1],a[y-y1+1][x+x1]);
                }
            }
            a[y - y1][x + x1] += locmax;
            x1--;
            y1++;
        }
    }

    sumend = a[0][w-1];
    ofstream ofile("turtle.out");
    ofile << sumend;

    return 0;
}
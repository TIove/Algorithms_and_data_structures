#include <vector>
#include <fstream>

using namespace std;

vector<double> CreateGarland(int bulbsCount, double h1, double h2) {
    vector<double> heights(bulbsCount, 0);
    heights[0] = h1;
    heights[1] = h2;
    for (int i = 2; i < bulbsCount; i++) {
        heights[i] = 2 * heights[i - 1] - heights[i - 2] + 2;
    }
    return heights;
}

bool checkPositive(const vector<double>& heights) {
    for (double h : heights) {
        if (h < 0)
            return false;
    }
    return true;
}

double binarysearch(int count, double h1) {
    double left = 0, right = h1;
    vector<double> heights;

    while (right - left > 0.000001) {
        double mid = (right + left) / 2;
        heights = CreateGarland(count, h1, mid);
        if (checkPositive(heights))
            right = mid;
        else
            left = mid;
    }
    return heights[heights.size() - 1];
}

int main() {
    ifstream in("garland.in");
    int n;
    double A;
    in >> n >> A;
    in.close();

    ofstream out("garland.out");
    out << fixed;
    out.precision(2);
    out << binarysearch(n, A);
    out.close();
}
#include <fstream>
#include <vector>
using namespace std;

class Stack{
    vector <int> head;
public:
    void push(int value) {
        head.push_back(value);
    }
    int pop() {
        int ans = head[head.size() - 1];
        head.pop_back();
        return ans;
    }
};


int main() {
    ifstream in("stack.in");
    ofstream out("stack.out");
    int n, buf;
    char operand;
    Stack stack;

    in >> n;
    for (int i = 0; i < n; ++i) {
        in >> operand;
        if (operand == '+') {
            in >> buf;
            stack.push(buf);
        } else if (operand == '-') {
            out << stack.pop() << '\n';
        }

        operand = '0';
    }
    return 0;
}
#include <fstream>
using namespace std;

class Stack {
public:
    int arr[100] = {};
    int head = 0;

    void push(int value) {
        arr[head] = value;
        head++;
    }
    int pop() {
        head--;
        return arr[head];
    }
};

int main() {
    ifstream in("postfix.in");
    ofstream out("postfix.out");
    Stack stack;

    char ch;
    while (!in.eof()) {
        in >> ch;
        if (in.eof())
            break;

        if (isdigit(ch)) {
            stack.push(atoi(&ch));
        }
        else {
            int val2 = stack.pop();
            int val1 = stack.pop();
            switch (ch) {
                case '+':
                    stack.push(val1 + val2);
                    break;
                case '-':
                    stack.push(val1 - val2);
                    break;
                case '*':
                    stack.push(val1 * val2);
                    break;
            }
        }

    }
    out << stack.pop();


    return 0;
}
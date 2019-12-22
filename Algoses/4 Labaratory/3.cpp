#include <fstream>
using namespace std;

class Stack{
public:
    char arr[10001];
    int head = 0;

    void push(char value) {
        arr[head] = value;
        head++;
    }
    void pop() {
        head--;
    }
};
int main() {
    ifstream in("brackets.in");
    ofstream out("brackets.out");

    string str;

    while (in >> str) {
        Stack stack;
        int i = 0;
        if (str[0] == '[' || str[0] == '(')
            stack.push(str[0]);
        for (i = 1; i < str.size(); i++) {
            if (str[i] == '[' || str[i] == '(')
                stack.push(str[i]);
            else if ((str[i] == ']' && stack.arr[stack.head - 1] == '[') || (str[i] == ')' && stack.arr[stack.head - 1] == '('))
                stack.pop();
            else
                break;
        }

        if (stack.head == 0 && str[0] != ')' && str[0] != ']' && i == str.size())
            out << "YES" << '\n';
        else
            out << "NO" << '\n';
    }


    return 0;
}
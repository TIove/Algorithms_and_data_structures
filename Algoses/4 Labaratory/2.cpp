#include <fstream>
#include <vector>

using namespace std;

class Stack{
public:
    int arr[1000000];
    int head = 0;
    int tail = 0;
    void push(int value){
        arr[head] = value;
        head++;
    }
    int pop(){
        return arr[tail++];
    }
};
int main(){
    ifstream in("queue.in");
    ofstream out("queue.out");
    Stack stack;
    int counter;
    char operation;
    in >> counter;
    int value;
    for (int i = 0; i < counter; ++i) {
        in >> operation;
        if (operation == '+'){
            in >> value;
            stack.push(value);
        }else{
            out << stack.pop() << "\n";
        }
    }
    return 0;
}
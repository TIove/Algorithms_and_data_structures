#include <fstream>
#include <string>
#include <vector>

using namespace std;

class PriorityQueue {
private:
    vector<int> data;
    unsigned curSize = 0;

    void siftUp(unsigned current) {
        if (current > 0 && data[current] < data[(current - 1) / 2]) {
            swap(data[current], data[(current - 1) / 2]);
            siftUp((current - 1) / 2);
        }
    }

    void siftDown(unsigned current) {
        unsigned l = 2 * current + 1;
        unsigned r = 2 * current + 2;
        unsigned indexToSwap = current;
        if (l < curSize && data[current] > data[l])
            indexToSwap = l;
        if (r < curSize && data[indexToSwap] > data[r])
            indexToSwap = r;
        if (indexToSwap != current) {
            swap(data[current], data[indexToSwap]);
            siftDown(indexToSwap);
        }
    }

    int findByKey(int key) {
        for (int i = 0; i < curSize; i++) {
            if (data[i] == key)
                return i;
        }
        return -1;
    }

public:
    PriorityQueue() {
        data.resize(1000000);
    }

    void push(int key) {
        data[curSize] = key;
        siftUp(curSize++);
    }

    int extractMin() {
        if (curSize > 0) {
            int returnValue = data[0];
            data[0] = data[--curSize];
            siftDown(0);
            return returnValue;
        }
        else
            return -1000000001;
    }

    void decreaseKey(int oldKey, int newKey) {
        int index = findByKey(oldKey);
        data[index] = newKey;
        siftUp(index);
    }

};

int main() {
    ifstream in("priorityqueue.in");
    ofstream out("priorityqueue.out");

    PriorityQueue priority_queue;

    vector<int> keys(1000000);

    string cmd;
    int x, y;
    int counter = 0;
    while (!in.eof()) {
        cmd = "";
        in >> cmd;
        if (cmd == "push") {
            in >> x;
            priority_queue.push(x);
            keys[counter] = x;
        }
        else if (cmd == "extract-min") {
            int min = priority_queue.extractMin();
            if (min > -1000000001)
                out << min << endl;
            else
                out << '*' << endl;
        }
        else if (cmd == "decrease-key") {
            in >> x >> y;
            priority_queue.decreaseKey(keys[x - 1], y);
            keys[x - 1] = y;
        }
        counter++;
    }
    in.close();
    out.close();
    return 0;
}
#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class Map {
private:
    struct Element {
        string key;
        string value;
    };

    vector<list<Element>> hashTable;

    unsigned hash(string key) {
        unsigned hash = 0;
        int charCode;
        const int k = 223;
        for (char i : key) {
            charCode = tolower(i) - 'a';
            hash = (hash * k + charCode) % hashTable.size();
        }
        return hash;
    }

public:

    Map() : Map(100003) {}

    Map(unsigned size) {
        hashTable.resize(size);
    }

    void put(string key, string value) {
        unsigned index = hash(key);
        for (Element& i : hashTable[index]) {
            if (i.key == key) {
                i.value = value;
                return;
            }
        }
        Element newEl;
        newEl.key = key;
        newEl.value = value;
        hashTable[index].push_back(newEl);
    }

    string get(string key) {
        unsigned index = hash(key);
        for (Element i : hashTable[index]) {
            if (i.key == key) {
                return i.value;
            }
        }
        return "none";
    }

    void remove(string key) {
        unsigned index = hash(key);
        for (auto i = hashTable[index].begin(); i != hashTable[index].end(); i++) {
            if (i->key == key) {
                hashTable[index].erase(i);
                return;
            }
        }
    }

};

int main() {
    Map map(100003);
    ifstream in("map.in");
    ofstream out("map.out");
    string command, x, y;
    while (!in.eof()) {
        command = "";
        in >> command >> x;
        if (command == "put") {
            in >> y;
            map.put(x, y);
        }
        else if (command == "get") {
            out << map.get(x) << '\n';
        }
        else if (command == "delete") {
            map.remove(x);
        }
    }
    in.close();
    out.close();
}
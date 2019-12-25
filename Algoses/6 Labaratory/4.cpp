#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

class QuackVM {
private:
    vector<uint16_t> registers;
    queue<uint16_t> mainQueue;
    map<string, int> labels;
    vector<string> commands;
    int current_pos = 0;

    void updateLabels() {
        int pos = 0;
        labels.clear();
        for (string command : commands) {
            if (command[0] == ':') {
                command.erase(0, 1);
                labels.emplace(command, pos);
            }
            pos++;
        }
    }

public:
    QuackVM() {
        registers.resize(26, 0);
    }

    void add() {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        uint16_t y = mainQueue.front();
        mainQueue.pop();
        mainQueue.push((x + y) % 65536);
    }

    void sub() {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        uint16_t y = mainQueue.front();
        mainQueue.pop();
        mainQueue.push((x - y) % 65536);
    }

    void mul() {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        uint16_t y = mainQueue.front();
        mainQueue.pop();
        mainQueue.push((x * y) % 65536);
    }

    void div() {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        uint16_t y = mainQueue.front();
        mainQueue.pop();
        uint16_t result = y == 0 ? 0 : x / y;
        mainQueue.push(result);
    }

    void mod() {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        uint16_t y = mainQueue.front();
        mainQueue.pop();
        uint16_t result = y == 0 ? 0 : x % y;
        mainQueue.push(result);
    }

    void setRegister(char reg) {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        registers[reg - 'a'] = x;
    }

    void getRegister(char reg) {
        mainQueue.push(registers[reg - 'a']);
    }

    void print(ostream& output) {
        uint16_t x = mainQueue.front();
        mainQueue.pop();
        output << x << endl;
    }

    void printRegister(ostream& output, char reg) {
        output << registers[reg - 'a'] << endl;
    }

    void printChar(ostream& output) {
        output << (char) (mainQueue.front() % 256);
        mainQueue.pop();
    }

    void printRegisterChar(ostream& output, char reg) {
        output << (char) (registers[reg - 'a'] % 256);
    }

    void updateLabel(string label) {
        labels.erase(label);
        labels.insert(make_pair(label, current_pos));
    }

    void jump(string label) {
        current_pos = labels[label];
    }

    void jumpIfZero(char reg, string label) {
        if (registers[reg - 'a'] == 0)
            jump(label);
    }

    void jumpIfEquals(char reg1, char reg2, string label) {
        if (registers[reg1 - 'a'] == registers[reg2 - 'a'])
            jump(label);
    }

    void jumpIfMore(char reg1, char reg2, string label) {
        if (registers[reg1 - 'a'] > registers[reg2 - 'a'])
            jump(label);
    }

    void put(uint16_t x) {
        mainQueue.push(x);
    }

    void start(ostream& output) {
        updateLabels();
        current_pos = 0;
        while (current_pos < commands.size()) {
            string command = commands[current_pos];
            if (command.length() == 0) {
                current_pos++;
                continue;
            }
            switch (command[0]) {
                case '+':
                    this->add();
                    break;
                case '-':
                    this->sub();
                    break;
                case '*':
                    this->mul();
                    break;
                case '/':
                    this->div();
                    break;
                case '%':
                    this->mod();
                    break;
                case '>':
                    this->setRegister(command[1]);
                    break;
                case '<':
                    this->getRegister(command[1]);
                    break;
                case 'P':
                    if (command.length() == 1)
                        this->print(output);
                    else
                        this->printRegister(output, command[1]);
                    break;
                case 'C':
                    if (command.length() == 1)
                        this->printChar(output);
                    else
                        this->printRegisterChar(output, command[1]);
                    break;
                case ':': {
                    string label = command;
                    label.erase(0, 1);
                    this->updateLabel(label);
                    break;
                }
                case 'J': {
                    string label = command;
                    label.erase(0, 1);
                    this->jump(label);
                    break;
                }
                case 'Z': {
                    char reg = command[1];
                    string label = command;
                    label.erase(0, 2);
                    this->jumpIfZero(reg, label);
                    break;
                }
                case 'E': {
                    char reg1 = command[1];
                    char reg2 = command[2];
                    string label = command;
                    label.erase(0, 3);
                    this->jumpIfEquals(reg1, reg2, label);
                    break;
                }
                case 'G': {
                    char reg1 = command[1];
                    char reg2 = command[2];
                    string label = command;
                    label.erase(0, 3);
                    this->jumpIfMore(reg1, reg2, label);
                    break;
                }
                case 'Q':
                    return;
                default: {
                    if (isdigit(command[0])) {
                        this->put(stoi(command));
                    }
                }
            }
            current_pos++;
        }
    }

    void start(vector<string> commands, ostream& output) {
        this->commands = commands;
        this->start(output);
    }

};

int main() {
    ifstream in("quack.in");
    ofstream out("quack.out");
    QuackVM qvm;
    vector<string> commands;
    while (!in.eof()) {
        string line;
        in >> line;
        commands.push_back(line);
    }
    qvm.start(commands, out);
}
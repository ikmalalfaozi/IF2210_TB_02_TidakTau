#ifndef COMMAND_H
#define COMMAND_H
#include <string>

using namespace std;

class Command {
private:
    int size;
    string* command;
public:
    Command();
    Command(Command&);
    ~Command(); 
    Command& operator=(const Command&);
    void scanCommand();
    int getSize();
    string* getCommand();
};

#endif
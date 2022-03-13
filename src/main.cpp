#include <iostream>
#include <string>
#include "Command/Command.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Command c;
    do {
        c.scanCommand();

        for(int i = 0; i < c.getSize(); i++) {
            cout << c.getCommand()[i] << endl;
        }    
    } while (c.getCommand()[0] != "QUIT" && c.getCommand()[0] != "quit");

    return 0;
}

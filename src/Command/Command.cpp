#include "Command.hpp"
#include <iostream>
#include <string>

Command::Command() {
    size = 0;
    command = new std::string[10];
    for(int i = 0; i < 10; i++) {
        command[i] = "";
    }
}

Command::~Command() {
    delete[] command;
}

Command::Command(Command& c){
    this->size = c.size;
    this->command = new string[10];
    for(int i = 0; i < size; i++) {
        command[i] = c.command[i];
    }
}

Command& Command::operator=(const Command& c) {
    this->size = c.size;
    
    for(int i; i < size; i++) {
        command[i] = c.command[i];
    }

    return *this;
}

void Command::scanCommand() {
    string input;
    string word;

    getline(cin, input);

    // Mencari indeks pertama yang bukan spasi di input
    int i = 0;
    while(input[i] == ' ') {
        i++;
    } 

    size = 0;
    for(i; i < input.length(); i++) {
        if (input[i] == ' ') {
            if (input[i+1] != ' ') {
                command[size] = word;
                word = "";
                size++;
            }
        } else if (i == input.length() - 1) {
            word += input[i];
            command[size] = word;
            size++;
        } else {
            word += input[i];
        }        
    }
}

int Command::getSize() {
    return size;
}

string* Command::getCommand() {
    return command;
}
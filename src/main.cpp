// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "../config/ItemList.hpp"
#include "./Command/Command.hpp"
#include "./Crafting/crafting.hpp"
#include "./Inventory/inventory.hpp"
#include "./Item/Item.hpp"
#include "./Item/NonTool.hpp"
#include "./Item/Tool.hpp"

using namespace std;

//     Command c;
//     do {
//         c.scanCommand();

//         for(int i = 0; i < c.getSize(); i++) {
//             cout << c.getCommand()[i] << endl;
//         }    
//     } while (c.getCommand()[0] != "QUIT" && c.getCommand()[0] != "quit");

//     return 0;

int main() {
    // Inisialisasi objek
    Command cmd;
    Crafting craft;

    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";

    // read item from config file
    ifstream itemConfigFile(itemConfigPath);
    for (string line; getline(itemConfigFile, line);) {
        cout << line << endl;
        // do something
    }

    // read recipes
    for (const auto &entry :
        filesystem::directory_iterator(configPath + "/recipe")) {
        cout << entry.path() << endl;
        // read from file and do something
    }

    Command c;
     do {
        cmd.scanCommand();

        for(int i = 0; i < cmd.getSize(); i++) {
            cout << cmd.getCommand()[i] << endl;
        }

        if (cmd.getCommand()[0] == "SHOW") {
            
        } else if (cmd.getCommand()[0] == "GIVE") {

        } else if (cmd.getCommand()[0] == "DISCARD") {
            
        } else if (cmd.getCommand()[0] == "MOVE") {
            
        } else if (cmd.getCommand()[0] == "USE") {

        } else if (cmd.getCommand()[0] == "CRAFT") {

        } else if (cmd.getCommand()[0] == "EXPORT") {

        }
    } while (cmd.getCommand()[0] != "QUIT" && cmd.getCommand()[0] != "quit");

  // sample interaction
  string command;
  while (cin >> command) {
    if (command == "EXPORT") {
      string outputPath;
      cin >> outputPath;
      ofstream outputFile(outputPath);

      // hardcode for first test case
      outputFile << "21:10" << endl;
      outputFile << "6:1" << endl;
      for (int i = 2; i < 27; i++) {
        outputFile << "0:0" << endl;
      }

      cout << "Exported" << endl;
    } else if (command == "CRAFT") {
      cout << "TODO" << endl;
    } else if (command == "GIVE") {
      // inisialisasi item yang disebutkan di command
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      cout << "TODO" << endl;
    } else if (command == "MOVE") {
      string slotSrc;
      int slotQty;
      string slotDest;
      // need to handle multiple destinations
      cin >> slotSrc >> slotQty >> slotDest;
      cout << "TODO" << endl;
    } else {
      // todo
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}

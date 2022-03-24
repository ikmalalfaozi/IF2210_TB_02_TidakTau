/* 
 * File: main.cpp
 * compile test: g++ ./main.cpp ./Command/Command.cpp ./Crafting/crafting.cpp ./Crafting/craftingSlot.cpp ../config/recipe.cpp ../config/ItemList.cpp ../config/ItemElmt.cpp ./Inventory/Inventory.cpp ./Inventory/InventorySlot.cpp ./Item/Item.cpp ./Item/Tool.cpp ./Item/NonTool.cpp -o main
 */
// sample main file, replace this with your own code
#include <fstream>
#include <iostream>
#include <string>
#include <dirent.h>
#include "../config/ItemList.hpp"
#include "./Command/Command.hpp"
#include "./Crafting/crafting.hpp"
#include "./Inventory/inventory.hpp"
#include "./Item/Item.hpp"
#include "./Item/NonTool.hpp"

using namespace std;

int main() {
    // Inisialisasi objek
    Command cmd;
    Inventory* inventory = new Inventory();
    Crafting craft;
    ItemList* itemList = new ItemList();
    Recipe* recipe = new Recipe();

    string configPath = "../config";
    string itemConfigPath = configPath + "/item.txt";
    string recipePath = configPath + "/recipe";

    // read item from config file
    int itemCount = 0;
    ifstream fileIn;
    fileIn.open(itemConfigPath);
    string id, type, varian, category;
    while (fileIn) {
        itemCount++;
        fileIn >> id >> type >> varian >> category;
        int intID = stoi(id);
        itemList->addItemElmt(type, intID, category, varian);
        //cout << id << varian << type << category << endl;
    }
    
    fileIn.close();

    vector<string> filesList;
    vector<Recipe> recipeList;
    vector<Recipe>::iterator it;
    DIR* dir;
    dirent* parentDir;

    dir = opendir("../config/recipe");
    while (parentDir = readdir(dir)) {
        filesList.push_back(parentDir->d_name);
    }

    for (int i = 2; i < filesList.size(); i++) {
        ifstream recipeIn;
        recipeIn.open(recipePath + "/" + filesList[i]);
        vector<vector<string>> recipeMatrix;
        
        int rows, cols;
        string result;
        string recipeElmt;
        int resultCount;
        string line;
        
        while (recipeIn) {
            recipeIn >> rows >> cols;
            for (int j = 0; j < rows; j++) {
                vector<string> recipeRow;
                for (int k = 0; k < cols; k++) {
                    recipeIn >> recipeElmt;
                    //cout << "Elements:" << recipeElmt << endl;
                    recipeRow.push_back(recipeElmt);
                }
                recipeMatrix.push_back(recipeRow);
            }
            recipeIn >> result >> resultCount;
            break;
        } 
        recipeIn.close();

        Recipe recipe;
        recipe.setRows(rows);
        recipe.setCols(cols);
        recipe.setHasilRecipe(result);
        recipe.setJumlah(resultCount);
        
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                recipe.setElemen(j, k, recipeMatrix.at(j).at(k));
            }
        }
        recipeList.push_back(recipe);
    }
    
    do {
        /* SCAN COMMAND */
        cout << "Masukkan Command: ";
        cmd.scanCommand();
        // for(int i = 0; i < cmd.getSize(); i++) {
        //     cout << cmd.getCommand()[i] << endl;
        // }

        /* COMMAND: SHOW */
        if (cmd.getCommand()[0] == "SHOW") {
            if (cmd.getSize() == 1) {
              inventory->showInventory();
            } else {
              cout << "Command Salah" << endl;
            }
        } 
        
        /* COMMAND: GIVE */
        else if (cmd.getCommand()[0] == "GIVE") {
            if (cmd.getSize() == 3) {
                if (cmd.getCommand()[1] == "OAK_LOG"){
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        inventory->giveItem(new NonTool(1, "LOG", "OAK_LOG"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "SPRUCE_LOG") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        inventory->giveItem(new NonTool(2, "LOG", "SPRUCE_LOG"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "BIRCH_LOG") {
                    try {
                        int count = stoi(cmd.getCommand()[3]);
                        inventory->giveItem(new NonTool(3, "LOG", "BIRCH_LOG"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "OAK_PLANK") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        inventory->giveItem(new NonTool(4, "PLANK", "OAK_PLANK"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "SPRUCE_PLANK") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        inventory->giveItem(new NonTool(5, "PLANK", "SPRUCE_PLANK"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "BIRCH_PLANK") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        inventory->giveItem(new NonTool(6, "PLANK", "BIRCH_PLANK"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "STICK") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        inventory->giveItem(new NonTool(7, "STICK"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "COBBLESTONE") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        inventory->giveItem(new NonTool(8, "STONE", "COBLESTONE"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "BLACKSTONE") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        inventory->giveItem(new NonTool(9, "STONE", "BLACKSTONE"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "IRON_INGOT") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        inventory->giveItem(new NonTool(10, "IRON_INGOT"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "IRON_NUGGET") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        inventory->giveItem(new NonTool(11, "IRON_NUGGET"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "DIAMOND") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        inventory->giveItem(new NonTool(12, "DIAMOND"), count);
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "WOODEN_PICKAXE") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(13, "WOODEN_PICKAXE", "-", 10), 1);
                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "STONE_PICKAXE") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(14, "STONE_PICKAXE", "-", 10), 1);

                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "IRON_PICKAXE") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(15, "IRON_PICKAXE", "-", 10), 1);
                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "DIAMOND_PICKAXE") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(16, "DIAMOND_PICKAXE", "-", 10), 1);
                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "WOODEN_AXE") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(17, "WOODEN_AXE", "-", 10), 1);
                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "STONE_AXE") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(18, "STONE_AXE", "-", 10), 1);
                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "IRON_AXE") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(19, "IRON_AXE", "-", 10), 1);
                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "DIAMOND_AXE") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(20, "DIAMOND_AXE", "-", 10), 1);
                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "WOODEN_SWORD") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(21, "WOODEN_SWORD", "-", 10), 1);
                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "STONE_SWORD") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(22, "STONE_SWORD", "-", 10), 1);
                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "IRON_SWORD") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(23, "IRON_SWORD", "-", 10), 1);
                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else if (cmd.getCommand()[1] == "DIAMOND_SWORD") {
                    try {
                        int count = stoi(cmd.getCommand()[2]);
                        for(int i = 0; i < count; i++) {
                            inventory->giveItem(new Tool(24, "DIAMOND_SWORD", "-", 10), 1);
                        }
                    } catch (exception& e) {
                        cout << "Jumlah item harus bertipe integer" << endl;
                    }
                } else {
                    cout << "Command Salah" << endl;
                }
            } else {
                cout << "Command Salah" << endl;
            }        
        } 
        
        /* COMMAND: DISCARD */
        else if (cmd.getCommand()[0] == "DISCARD") {
            if (cmd.getSize() == 3) {
                try {
                    inventory->discardItem(cmd.getCommand()[1], std::stoi(cmd.getCommand()[2]));
                } catch (exception& e) {
                    cout << "Jumlah Item harus bertipe integer" << endl;
                }
            } else {
                cout << "Command Salah" << endl;
            }
        } 
        
        /* COMMAND: MOVE */
        else if (cmd.getCommand()[0] == "MOVE") {
            if (cmd.getSize() >= 4) {
                char srcSlotCode, destSlotCode;
                int n;
                srcSlotCode = cmd.getCommand()[1].at(0);
                n = std::stoi(cmd.getCommand()[2]);
                destSlotCode = cmd.getCommand()[3].at(0);

                /* MOVE <INVENTORY_SLOT_ID_SRC> 1 <INVENTORY_SLOT_ID_DEST> */
                if (srcSlotCode == 'I' && destSlotCode == 'I') {
                    inventory->moveStackItem(cmd.getCommand()[1], cmd.getCommand()[3]);
                }

                /* MOVE <CRAFTING_SLOT_ID> 1 <INVENTORY_SLOT_ID> */
                else if (srcSlotCode == 'C' && destSlotCode == 'I') {
                    inventory->moveCraftingToInventory(cmd.getCommand()[1], cmd.getCommand()[3]);
                }

                /* MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1> <CRAFTING_SLOT_ID_2> ... */
                else if (srcSlotCode == 'I' && destSlotCode == 'C') {
                    for (int i = 0; i < n; i++) {
                        inventory->moveInventoryToCrafting(cmd.getCommand()[1], cmd.getCommand()[3+i]);
                    }
                }
            }
        }
        
        /* COMMAND: USE */
        else if (cmd.getCommand()[0] == "USE") {
            if (cmd.getSize() == 2) {
                inventory->useItem(cmd.getCommand()[1]);
            } else {
                cout << "Command Salah" << endl;
            }
        } 
        
        /* COMMAND: CRAFT */
        else if (cmd.getCommand()[0] == "CRAFT") {
            try {
                inventory->Craft(*itemList, recipeList);
            } catch (const char* msg) {
                cout << msg << endl;
            }
        }
        
        /* COMMAND: EXPORT */
        else if (cmd.getCommand()[0] == "EXPORT") {
            // EXPORT inventory.txt
            if (cmd.getSize() == 2) {
                inventory->exportInventory(cmd.getCommand()[1]);
            } else {
                cout << "Command Salah" << endl;
            }
        } 
        
        /* COMMAND: EXIT */
        else if (cmd.getCommand()[0] == "quit" || cmd.getCommand()[0] == "QUIT") {

        }
        
        /* COMMAND UNAVAILABLE */
        else {
            cout << "Command Tidak Ada" << endl;
        }
    } while (cmd.getCommand()[0] != "QUIT" && cmd.getCommand()[0] != "quit");
    /* COMMAND QUIT */

    // // sample interaction
    // string command;
    // while (cin >> command) {
    //     if (command == "EXPORT") {
    //         string outputPath;
    //         cin >> outputPath;
    //         inventory->exportInventory(outputPath);
    //         cout << "Exported" << endl;
    //     } else if (command == "CRAFT") {
    //         cout << "TODO" << endl;
    //     } else if (command == "GIVE") {
    //         // inisialisasi item yang disebutkan di command
    //         string itemName;
    //         int itemQty;
    //         cin >> itemName >> itemQty;
    //         cout << "TODO" << endl;
    //     } else if (command == "MOVE") {
    //         string slotSrc;
    //         int slotQty;
    //         string slotDest;
    //         // need to handle multiple destinations
    //         cin >> slotSrc >> slotQty >> slotDest;
    //         cout << "TODO" << endl;
    //     } else {
    //     // todo
    //         cout << "Invalid command" << endl;
    //     }
    // }
    return 0;
}

/* 
 * File: InventoryTest.cpp
 * compile test: g++ ./Crafting/crafting.cpp ./Crafting/craftingSlot.cpp ../config/recipe.cpp ../config/ItemList.cpp ../config/ItemElmt.cpp ./Inventory/InventoryTest.cpp ./Inventory/Inventory.cpp ./Inventory/InventorySlot.cpp ./Item/Item.cpp ./Item/Tool.cpp ./Item/NonTool.cpp -o ivTest
 */

#include "Inventory.hpp"
#include <iostream>
#include <string>

int main() {
    /* Inventory */
    Inventory* inventory = new Inventory();
    inventory->showInventory();

    // GIVE OAK_PLANK 1
    cout << "GIVE OAK_PLANK 1" << endl;
    NonTool* oakplank = new NonTool(4, "PLANK", "OAK_PLANK");
    inventory->giveItem(oakplank, 1);

    // GIVE BIRCH_PLANK 3
    cout << "GIVE BIRCH_PLANK 3" << endl;
    NonTool* birchplank = new NonTool(6, "PLANK", "BIRCH_PLANK");
    inventory->giveItem(birchplank, 3);

    // GIVE STICK 1
    cout << "GIVE STICK 1" << endl;
    NonTool* stick = new NonTool(7, "-", "STICK");
    inventory->giveItem(stick, 1);

    cout << "SHOW" << endl;
    inventory->showInventory();

    // DISCARD I0 2
    cout << "DISCARD I0 2" << endl;
    inventory->discardItem("I0", 2);
    
    cout << "SHOW" << endl;
    inventory->showInventory();

    // DISCARD I0 1
    cout << "DISCARD I0 1" << endl;
    inventory->discardItem("I0", 1);

    // DISCARD I1 2
    cout << "DISCARD I1 2" << endl;
    inventory->discardItem("I1", 2);

    cout << "SHOW" << endl;
    inventory->showInventory();

    // GIVE BIRCH_PLANK 134
    cout << "GIVE BIRCH_PLANK 134" << endl;
    inventory->giveItem(birchplank, 134);

    cout << "SHOW" << endl;
    inventory->showInventory();

    // DISCARD I0 56
    cout << "DISCARD I0 56" << endl;
    inventory->discardItem("I0", 56);

    // DISCARD I1 7
    cout << "DISCARD I1 7" << endl;
    inventory->discardItem("I1", 7);

    cout << "SHOW" << endl;
    inventory->showInventory();

    // MOVE I3 1 I0
    cout << "MOVE I3 1 I0" << endl;
    inventory->moveStackItem("I3", "I0");

    cout << "SHOW" << endl;
    inventory->showInventory();

    // MOVE I0 1 I1
    cout << "MOVE I0 1 I1" << endl;
    inventory->moveStackItem("I0", "I1");

    cout << "SHOW" << endl;
    inventory->showInventory();

    // MOVE I0 1 C0
    cout << "MOVE I0 1 C0" << endl;
    inventory->moveInventoryToCrafting("I0", "C0");
    
    cout << "SHOW" << endl;
    inventory->showInventory();

    // MOVE I0 1 C0
    cout << "MOVE I2 1 C3" << endl;
    inventory->moveInventoryToCrafting("I2", "C3");
    
    cout << "SHOW" << endl;
    inventory->showInventory();

    cout << "EXPORT" << endl;
    inventory->exportInventory("ayam.txt");
}
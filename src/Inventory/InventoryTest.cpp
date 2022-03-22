/* 
 * File: InventoryTest.cpp
 * compile test: g++ ./Crafting/crafting.cpp ./Crafting/craftingSlot.cpp ../config/recipe.cpp ../config/ItemList.cpp ../config/ItemElmt.cpp ./Inventory/InventoryTest.cpp ./Inventory/Inventory.cpp ./Inventory/InventorySlot.cpp ./Item/Item.cpp ./Item/Tool.cpp ./Item/NonTool.cpp -o ivTest
 */

#include "Inventory.hpp"
#include <iostream>
#include <string>

int main() {
    /* Test Item 1 */
    Tool* item1 = new Tool(21, "-", "WOODEN_SWORD", 1);

    /* Test Item 2 */
    NonTool* item2 = new NonTool(1, "LOG", "OAK_LOG");

    /* Inventory */
    Inventory* inventory = new Inventory();
    inventory->showInventory();

    inventory->giveItem(item1, 1);
    inventory->showInventory();

    inventory->giveItem(item2, 1);
    inventory->showInventory();

    inventory->moveInvToCraft("I0", "C0");
    inventory->showInventory();

    inventory->exportInventory("ayam.txt");
}
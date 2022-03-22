/* 
 * File: craftingSlotTest.cpp
 * compile test: g++ ./Crafting/craftingSlot.cpp ./Crafting/craftingSlotTest.cpp ./Item/Item.cpp ./Item/Tool.cpp ./Item/NonTool.cpp -o cslotTest
 */

#include "craftingSlot.hpp"
#include <iostream>
#include <string>

void printCraftingSlot(CraftingSlot slot)
{
    cout << "SlotID: " << slot.getSlotID() << endl;

    cout << "Item ID : " << slot.getItem()->getId() << endl;
    cout << "Item Category: " << slot.getItem()->getCategory() << endl;
    cout << "Item Type: " << slot.getItem()->getType() << endl;
    cout << "Item Varian : " << slot.getItem()->getVarian() << endl;
    if (slot.getItem()->getCategory() == "Tool") {
        cout << "Item Durability : " << slot.getItem()->getDurability() << endl;
    }
    
    cout << "Quantity: " << slot.getQuantity() << endl;
}

int main()
{
    /* ALGORITMA */
    int testChoice;
    cout << "Test 1: Tool; 2: NonTool" << endl;
    cout << "Input test number: ";
    cin >> testChoice;

    if (testChoice == 1)
    {
        Tool* item1 = new Tool(21, "-", "WOODEN_SWORD", 1);
        CraftingSlot *slot1 = new CraftingSlot();

        slot1->setItem(item1);
        slot1->setQuantity(1);

        cout << "Slot 1 -- Item 1 (Tool)" << endl;
        printCraftingSlot(*slot1);
    } 
    else 
    {
        // KETERANGAN: 
        // NONTOOL SEHARUSNYA TIDAK MEMILIKI DURABILITY, NAMUN AKHIRNYA DISET MENJADI 0
        NonTool* item2 = new NonTool(1, "LOG", "OAK_LOG");
        CraftingSlot *slot2 = new CraftingSlot();

        slot2->setItem(item2);
        slot2->setQuantity(1);

        cout << "Slot 2 -- Item 2 (NonTool)" << endl;
        printCraftingSlot(*slot2);
    }
}
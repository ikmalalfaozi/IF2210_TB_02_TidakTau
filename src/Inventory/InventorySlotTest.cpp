/* 
 * File: InventorySlotTest.cpp
 * compile test: g++ ./Inventory/InventorySlot.cpp ./Inventory/InventorySlotTest.cpp ./Item/Item.cpp ./Item/Tool.cpp ./Item/NonTool.cpp -o ivslotTest
 */

#include "InventorySlot.hpp"
#include <iostream>
#include <string>

void printInventorySlot(InventorySlot<Item*> slot)
{
    cout << "SlotID: " << slot.get_slotID() << endl;

    cout << "Item ID : " << slot.get_item()->getId() << endl;
    cout << "Item Category: " << slot.get_item()->getCategory() << endl;
    cout << "Item Type: " << slot.get_item()->getType() << endl;
    cout << "Item Varian : " << slot.get_item()->getVarian() << endl;
    if (slot.get_item()->getCategory() == "Tool") {
        cout << "Item Durability : " << slot.get_item()->getDurability() << endl;
    }
    
    cout << "Quantity: " << slot.get_quantity() << endl;
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
        InventorySlot<Item*> *slot1 = new InventorySlot<Item*>();

        slot1->set_slotID("I1");
        slot1->set_item(item1);
        slot1->set_quantity(1);

        cout << "Slot 1 -- Item 1 (Tool)" << endl;
        printInventorySlot(*slot1);
    } 
    else if (testChoice == 2)
    {
        // KETERANGAN: 
        // NONTOOL SEHARUSNYA TIDAK MEMILIKI DURABILITY, NAMUN AKHIRNYA DISET MENJADI 0
        NonTool* item2 = new NonTool(1, "LOG", "OAK_LOG");
        InventorySlot<Item*> *slot2 = new InventorySlot<Item*>();

        slot2->set_slotID("I1");
        slot2->set_item(item2);
        slot2->set_quantity(1);

        cout << "Slot 2 -- Item 2 (NonTool)" << endl;
        printInventorySlot(*slot2);
    } else {
        InventorySlot<Item*> *slot2 = new InventorySlot<Item*>();

        slot2->set_slotID("I1");
        slot2->set_quantity(1);

        cout << "Slot 2 -- Item 2 (NonTool)" << endl;
        printInventorySlot(*slot2);
    }
}
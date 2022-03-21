/* 
 * File: InventorySlotTest.cpp
 */

#include "InventorySlot.hpp"
#include <iostream>
#include <string>

void printInventorySlot(InventorySlot slot)
{
    cout << "SlotID: " << slot.get_slotID() << endl;
    // cout << "Item ID : " << slot->get_item() << endl;
    cout << "Item Type : " << slot.get_item() << endl;
    // cout << "Item Durability : " << slot->get_item() << endl;
    cout << "SlotID: " << slot.get_quantity() << endl;
}

int main()
{
    /* ALGORITMA */
    InventorySlot *slot1 = new InventorySlot();
}
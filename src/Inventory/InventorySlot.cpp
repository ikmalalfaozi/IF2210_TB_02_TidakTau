// -----------InventorySlot implementation-------------
#include "InventorySlot.hpp"
#include <iostream>
#include <string>

using namespace std;

InventorySlot::InventorySlot(){
    this->slotID = "II";
    this->quantity = 0;
}

InventorySlot& InventorySlot::operator=(const InventorySlot& ivslot){
    this->slotID = ivslot.slotID;
    this->quantity = ivslot.quantity;
    this->item = ivslot.item;
    return *this;
}

void InventorySlot::set_slotID(string slotid){
    this->slotID = slotid;
}

void InventorySlot::set_item(Item* item){
    this->item = item;
}

void InventorySlot::set_quantity(int quantity){
    this->quantity = quantity;
}

string InventorySlot::get_slotID() const{
    return this->slotID;
}

Item* InventorySlot::get_item() const{
    return this->item;
}

int InventorySlot::get_quantity() const{
    return this->quantity;
}
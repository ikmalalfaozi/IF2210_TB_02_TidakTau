// -----------Inventory implementation-------------
#include "Inventory.hpp"
#include <iostream>
#include <string>

using namespace std;

Inventory::Inventory(){
    this->activesize = 0;
    this->itemlist = new InventorySlot[CAPACITY];
    for (int i = 0; i < CAPACITY; i++){
        string slotIDgenerate = "I" + i;
        this->itemlist[i].set_slotID(slotIDgenerate);
    }
}

Inventory::Inventory(Inventory& other){
    this->activesize = other.activesize;
    this->itemlist = new InventorySlot[CAPACITY];
    for (int i = 0; i < this->activesize; i++){
        this->itemlist[i] = other.itemlist[i];
    }
    for (int i = this->activesize; i < CAPACITY; i++){
        string slotIDgenerate = "I" + i;
        this->itemlist[i].set_slotID(slotIDgenerate);
    }
}

Inventory::~Inventory(){
    delete[] this->itemlist;
}

void Inventory::addItem(int itemID, int quantity){
    bool foundempty = false;
    int idx = 0;
    do{
        idx++;
    }while(!foundempty);
    // Belum bisa dilanjut
    // Cek jenis item melalui parameter item
    // Parameter yang diminta -> Item
}

void Inventory::deleteItem(int slotID, int quantity){
    
}

void Inventory::stackItem(int slotIDsrc, int slotIDdest){
    
}

void Inventory::useItem(int slotID){
    
}

// -----------InventorySlot implementation-------------

InventorySlot::InventorySlot(){
    this->slotID = "II";
    this->itemID = -999;
    this->quantity = 0;
}

void InventorySlot::set_slotID(string slotid){
    this->slotID = slotid;
}

void InventorySlot::set_itemID(int itemid){
    this->itemID = itemid;
}

void InventorySlot::set_quantity(int quantity){
    this->quantity = quantity;
}

string InventorySlot::get_slotID() const{
    return this->slotID;
}

int InventorySlot::get_itemID() const{
    return this->itemID;
}

int InventorySlot::get_quantity() const{
    return this->quantity;
}
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

void Inventory::addItem(Item item, int quantity){
    // Belum selesai secara sintaks
    // Asumsi bahwa seluruh item dengan jumlah quantity akan masuk
    int* alreadyAvailIdx = new int[27];
    int y = 0; // indeks untuk iterasi alreadyAvailIdx
    for (int x = 0; x < this->activesize; x++){
        Item ivItem(std::get<Item>(this->itemlist[x].get_item())); // Ambil 
        if (ivItem.getId() == item.getId()){
            alreadyAvailIdx[y] = x;
            y++;
            // Barang dengan id sama ditemukan
        }
    } // List dengan id item yang sama sudah terisi
    int j = 0;
    while (quantity != 0){
        if (j == y){ // Tidak ada slot dengan id yang sama lagi
            // Simpan sisanya ke slot yang kosong
            this->itemlist[this->activesize].set_item(item);

        }
        int idx = alreadyAvailIdx[j];
        int currentQuantity = this->itemlist[idx].get_quantity() + quantity;
        if (currentQuantity >= 64){
            this->itemlist[idx].set_quantity(63);
            quantity = currentQuantity - 63;
        }
        else{
            this->itemlist[idx].set_quantity(currentQuantity);
            quantity = 0;
        }
        j++;
    }

    // Belum Fix
}

void Inventory::deleteItem(string slotID, int quantity){
    bool found = false;
    Tool testo(std::get<Tool>(this->itemlist[0].get_item()));
    this->addItem(testo, 1);
    int idx = 0;
    while(!found && idx < 27){
        if (slotID == this->itemlist[idx].get_slotID()){
            found = true;
            int currentQuantity = this->itemlist[idx].get_quantity() - quantity;
            this->itemlist[idx].set_quantity(currentQuantity);
        }
        idx++;
    }
}

void Inventory::stackItem(string slotIDsrc, string slotIDdest){
    bool found = false;
    int src, dest = 0;
    while(!found && src < 27){
        if (slotIDsrc == this->itemlist[src].get_slotID()){
            found = true;
        }
        src++;
    }
    found = false;
    while(!found && dest < 27){
        if (slotIDsrc == this->itemlist[src].get_slotID()){
            found = true;
        }
        dest++;
    }
    src--;
    dest--;
    int stackQuantity = this->itemlist[src].get_quantity();
    stackQuantity += this->itemlist[dest].get_quantity();
    if (stackQuantity <= 64){
        this->itemlist[dest].set_quantity(stackQuantity);
        this->itemlist[src].set_quantity(0);
    }
    else{
        this->itemlist[dest].set_quantity(stackQuantity);
        this->itemlist[src].set_quantity(stackQuantity - 64);
    }
    
}

void Inventory::useItem(string slotID){
    
    bool found = false;
    int idx = 0;
    while(!found && idx < 27){
        if (slotID == this->itemlist[idx].get_slotID()){
            found = true;
            //testo = std::get<Tool>(this->itemlist[idx].get_item());
            Tool* testo = new Tool(std::get<Tool>(this->itemlist[idx].get_item()));
            testo->setDuarbility(testo->getDurability() - 1);
        }
        idx++;
    }
}

// -----------InventorySlot implementation-------------

InventorySlot::InventorySlot(){
    this->slotID = "II";
    this->item = Item();
    this->quantity = 0;
}

void InventorySlot::set_slotID(string slotid){
    this->slotID = slotid;
}

InventorySlot& InventorySlot::operator=(const InventorySlot& ivslot){
    this->slotID = ivslot.slotID;
    this->quantity = ivslot.quantity;
}

void InventorySlot::set_item(Item item){}

void InventorySlot::set_quantity(int quantity){
    this->quantity = quantity;
}

string InventorySlot::get_slotID() const{
    return this->slotID;
}

variant<Item, Tool, NonTool>& InventorySlot::get_item(){
    return this->item;
}

int InventorySlot::get_quantity() const{
    return this->quantity;
}
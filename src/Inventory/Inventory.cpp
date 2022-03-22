// -----------Inventory implementation-------------
#include "Inventory.hpp"
#include <iostream>
#include <string>
#include <fstream>

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

void Inventory::addItem(Item* item, int quantity){
    // Belum selesai secara sintaks

    // Asumsi bahwa seluruh item dengan jumlah quantity akan masuk
    int* alreadyAvailIdx = new int[27];
    int y = 0; // indeks untuk iterasi alreadyAvailIdx
    for (int x = 0; x < this->activesize; x++){
        if (this->itemlist[x].get_item()->getId() == item->getId()){
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
            this->itemlist[idx].get_item()->setDurability(this->itemlist[idx].get_item()->getDurability() - 1);
        }
        idx++;
    }
}

void Inventory::showInventory() const
{
    // Print Crafting Slots
    cout << "Crafting" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "[" << this->itemlist[i+j].get_item()->getId() << ":" << this->itemlist[i+j].get_quantity() << "]\t"; 
        }
        cout << endl;
    }
    cout << endl;

    // Print Inventory slotIDsrc
    cout << "Inventory" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 9; j++) {
            cout << "[" << this->itemlist[i+j].get_item()->getId() << ":" << this->itemlist[i+j].get_quantity() << "]\t";         }
        cout << endl;
    }
    cout << endl;
}

void Inventory::exportInventory(string filename)
{
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < CAPACITY; i++) {
            if (this->itemlist[i].get_item() != NULL)
            {
                file << this->itemlist[i].get_item()->getId() << ":" << this->itemlist[i].get_quantity() << endl; 
            }
            else
            {
                file << "0:0" << endl;
            }
        }
    }
    file.close();
}
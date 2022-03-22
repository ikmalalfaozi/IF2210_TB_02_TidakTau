// -----------Inventory implementation-------------
#include "Inventory.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Inventory::Inventory(){
    this->crafting = Crafting(3,3);
    this->itemlist = new InventorySlot[CAPACITY];
    for (int i = 0; i < CAPACITY; i++){
        string slotIDgenerate = "I" + i;
        this->itemlist[i].set_slotID(slotIDgenerate);
        NonTool* itemdefault = new NonTool(0, "-", "-");
        this->itemlist[i].set_item(itemdefault);
        this->itemlist[i].set_quantity(0);
    }
}

Crafting Inventory::getCrafting(){
    return this->crafting;
}

Inventory::Inventory(Inventory& other){
    this->crafting = other.getCrafting();
    
    this->itemlist = new InventorySlot[CAPACITY];
    for (int i = 0; i < CAPACITY; i++){
        this->itemlist[i] = other.itemlist[i];
    }
}

Inventory::~Inventory(){
    delete[] this->itemlist;
}

void Inventory::giveItem(Item* item, int quantity){
    /* GIVE ITEM */
    /* Menambahkan Item ke Inventory. Sejumlah Item dengan jenis yang sama akan ditambahkan ke slot inventory:
     * Berisi item nontool dengan jenis yang sama
     * Memiliki quantity < 64 (tidak penuh)
     * Apabila tidak ditemukan slot yang memenuhi syarat tersebut, item ditambahkan pada slot kosong. 
     * Penambahan item dilakukan dari ID inventory terkecil.
     */
    
    /* KAMUS LOKAL */
    int i = 0;
    
    /* ALGORITMA */
    
    // Looping untuk mencari slot dengan id item yang sama
    while (quantity != 0 && i < 27){
        if (this->itemlist[i].get_item()->getId() == item->getId()){
            int currentQuantity = this->itemlist[i].get_quantity();
            if (currentQuantity + quantity > 64) {
                this->itemlist[i].set_quantity(64);
                quantity -= 64 - currentQuantity;
            } else {
                this->itemlist[i].set_quantity(currentQuantity + quantity);
                quantity = 0;
            }
        }
        i++;
    }

    i = 0; // Inisialisasi ulang untuk iterasi
    while (quantity != 0 && i < 27){
        // Periksa apakah slot kosong
        if (this->itemlist[i].get_quantity() == 0){
            // Masukkan item ke slot
            this->itemlist[i].set_item(item);
            if (quantity > 64){
                this->itemlist[i].set_quantity(64);
                quantity -= 64;
            }
            else{
                this->itemlist[i].set_quantity(quantity);
                quantity = 0;
            }
        }
        i++;
    }
}

void Inventory::discardItem(string slotID, int quantity){
    /* DISCARD ITEM */
    /* 
     * Membuang item di slot inventory dengan kuantitas yang diberikan. 
     * Gagal bila kuantitas item lebih kecil dari item yang dijadikan masukan perintah.
     */

    /* KAMUS LOKAL */
    bool found = false;
    int idx = 0;
    
    /* ALGORITMA */ 
    while(!found && idx < 27){
        if (slotID == this->itemlist[idx].get_slotID()){
            found = true;
            int currentQuantity = this->itemlist[idx].get_quantity() - quantity;
            if (currentQuantity >= 0){
                this->itemlist[idx].set_quantity(currentQuantity);
            }
        } 
        else {
            idx++;
        }
    }
}

void Inventory::moveStackItem(string slotIDsrc, string slotIDdest){
    /* MENUMPUK ITEM 
     * Dua buah item non tool yang sama pada inventory dapat ditumpuk.
     * I.S :
     * Jumlah Item pada INVENTORY_SLOT_ID_SRC sebanyak Qty1.
     * Jumlah Item pada INVENTORY_SLOT_ID_DEST sebanyak Qty2.
     * F.S. :
     * Jumlah Item pada INVENTORY_SLOT_ID_SRC sebanyak 0 (item hilang / habis), jika memungkinkan.
     * Jumlah Item pada INVENTORY_SLOT_ID_DEST sebanyak Qty1 + Qty2, namun maksimal sebanyak 64.
     */

    /* KAMUS LOKAL */
    bool found;
    int stackQuantity;
    int src, dest;

    /* ALGORITMA */

    // Mencari indeks untuk source
    found = false;
    src = 0;
    while(!found && src < 27){
        if (slotIDsrc == this->itemlist[src].get_slotID()){
            found = true;
        }
        else{
            src++;
        }
    }

    // Mencari indeks untuk destination
    found = false;
    dest = 0;
    while(!found && dest < 27){
        if (slotIDsrc == this->itemlist[src].get_slotID()){
            found = true;
        }
        else{
            dest++;
        }
    }

    // Menumpuk item
    stackQuantity = this->itemlist[src].get_quantity() + this->itemlist[dest].get_quantity();
    if (stackQuantity <= 64){
        this->itemlist[dest].set_quantity(stackQuantity);
        this->itemlist[src].set_quantity(0);
    }
    else{
        this->itemlist[dest].set_quantity(64);
        this->itemlist[src].set_quantity(stackQuantity - 64);
    }
}

void Inventory::moveInvToCraft(string slotIDsrc, string slotIDdest){
    /* MEMINDAHKAN ITEM INVENTORY KE CRAFTING */
    /*
     * Satu jenis item dapat dipindahkan ke beberapa slot crafting. 
     * Jumlah item harus lebih besar atau sama dengan jumlah slot crafting.
     * I.S. : 
     * Jumlah Item pada INVENTORY_SLOT_ID sebanyak Qty, dengan Qty >= N (jumlah slot crafting).
     * F.S. :
     * Jumlah Item pada INVENTORY_SLOT_ID sebanyak Qty - N.
     * CRAFTING_SLOT_ID_1 hingga N berisi Item yang sama dengan INVENTORY_SLOT_ID dengan jumlah masing-masing 1.
     */

    /* KAMUS LOKAL */
    bool found;
    int src, dst;

    /* ALGORITMA */
    found = false;
    src = 0;
    while(!found && src < 27){
        if (slotIDsrc == this->itemlist[src].get_slotID()){
            found = true;
        }
        else{
            src++;
        }
    }
    dst = 0;
    int i = 0;
    bool finish = false;
    while (i < 3 && !finish) {
        int j = 0;
        while (j < 3 && !finish) {
            cout << this->crafting.getElmt(i, j).getSlotID() << endl;
            if (slotIDdest == this->crafting.getElmt(i, j).getSlotID()) {
                cout << "|------------- MASUK GES LESGOW -------------|" << endl;
                this->crafting.getElmt(i, j).setItem(this->itemlist[src].get_item());
                this->crafting.getElmt(i, j).setQuantity(this->crafting.getElmt(i, j).getQuantity() + 1);
                finish = true;
            }
            j++;
        }
        i++;
    }
}

void Inventory::useItem(string slotID){
    /* USE ITEM */
    /* Menggunakan Item. Item tool dapat digunakan dan durabilitasnya akan berkurang.
     * I.S. : INVENTORY_SLOT_ID berisi Item tool.
     * F.S. : 
     * Durability Item pada INVENTORY_SLOT_ID berkurang 1. 
     * Jika durabilitynya mencapai 0, maka item hilang dari inventory.
     */

    /* KAMUS LOKAL */
    bool found;
    int idx;
    
    /* ALGORITMA */
    found = false;
    idx = 0;

    while(!found && idx < 27){
        if (slotID == this->itemlist[idx].get_slotID()){
            found = true;
            if (this->itemlist[idx].get_item()->getCategory() == "Tool"){
                int currentDurability = this->itemlist[idx].get_item()->getDurability();
                if (currentDurability <= 0){
                    this->discardItem(slotID, 1);
                }
                else{
                    this->itemlist[idx].get_item()->setDurability(currentDurability - 1);
                }
            }
        }
        idx++;
    }
}

void Inventory::showInventory()
{
    // Print Crafting Slots
    cout << "|=============================INVENTORY=============================|" << endl;
    cout << "|=============================Crafting==============================|" << endl;
    this->crafting.displayCraftingGrid();

    // Print Inventory slotIDsrc
    cout << "|=============================Inventory=============================|" << endl;
    // int id = this->itemlist[0].get_item()->getId();
    // int qty = this->itemlist[0].get_quantity();
    // cout << "[" << id << ":" << qty << "]";
    for (int i = 0; i < 27; i++) {
        int id = this->itemlist[i].get_item()->getId();
        int qty = this->itemlist[i].get_quantity();
        cout << "[" << id << ":" << qty << "]";
        if ((i + 1) % 9 == 0) {
            cout << "\n";
        } else {
            cout << "\t";
        }
    }
    cout << "|===================================================================|\n" << endl;
}

void Inventory::exportInventory(string filename)
{
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < CAPACITY; i++) {
            file << this->itemlist[i].get_item()->getId() << ":" << this->itemlist[i].get_quantity() << endl; 
        }
    }
    file.close();
}
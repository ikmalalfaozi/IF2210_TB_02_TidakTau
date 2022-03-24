// -----------Inventory implementation-------------
#include "Inventory.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Inventory::Inventory() : crafting(3,3) {
    this->itemlist = new InventorySlot[CAPACITY];
    for (int i = 0; i < CAPACITY; i++){
        string slotIDgenerate = "I" + to_string(i);
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
    if (quantity >= 0) {
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
}

void Inventory::discardItem(string slotID, int quantity){
    /* DISCARD ITEM */
    /* 
     * Membuang item di slot inventory dengan kuantitas yang diberikan. 
     * Gagal bila kuantitas item lebih kecil dari item yang dijadikan masukan perintah.
     */

    /* KAMUS LOKAL */
    // bool found = false;
    // int idx = 0;
    int idx;
    int currentQuantity;
    
    /* ALGORITMA */ 
    idx = stoi(slotID.erase(0,1));
    if (quantity >= 0) {
        currentQuantity = this->itemlist[idx].get_quantity() - quantity;
        if (currentQuantity > 0){
            this->itemlist[idx].set_quantity(currentQuantity);
        } else if (currentQuantity == 0){
            this->itemlist[idx].set_quantity(0);
            NonTool* itemdefault = new NonTool(0, "-", "-");
            this->itemlist[idx].set_item(itemdefault);
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
    int srcQuantity, destQuantity, stackQuantity;
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
        if (slotIDdest == this->itemlist[dest].get_slotID()){
            found = true;
        }
        else{
            dest++;
        }
    }

    // Menumpuk item NonTool yang sama
    if ((this->itemlist[src].get_item()->getId() == this->itemlist[dest].get_item()->getId()) && (this->itemlist[src].get_item()->getCategory() == "NonTool")) {
        srcQuantity = this->itemlist[src].get_quantity();
        destQuantity = this->itemlist[dest].get_quantity();
        stackQuantity = srcQuantity + destQuantity;
        if (stackQuantity <= 64){
            this->itemlist[dest].set_quantity(stackQuantity);
            this->discardItem(slotIDsrc, srcQuantity);
        }
        else{
            this->itemlist[dest].set_quantity(64);
            this->discardItem(slotIDsrc, 64 - destQuantity);
        }
    }
}

void Inventory::moveInventoryToCrafting(string slotIDsrc, string slotIDdest){
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
        } else{
            src++;
        }
    }
    dst = 0;
    int i = 0;
    bool finish = false;
    while (i < 3 && !finish) {
        int j = 0;
        while (j < 3 && !finish) {
            if (slotIDdest == this->crafting.getElmt(i, j).getSlotID()) {
                CraftingSlot* newSlot = new CraftingSlot();
                newSlot->setSlotID(this->crafting.getElmt(i, j).getSlotID());
                newSlot->setItem(this->itemlist[src].get_item());
                newSlot->setQuantity(this->crafting.getElmt(i, j).getQuantity() + 1);
                this->crafting.setElmt(i, j, *newSlot);
                delete newSlot;

                discardItem(slotIDsrc, 1);
                finish = true;
            }
            j++;
        }
        i++;
    }
}

void Inventory::moveCraftingToInventory(string slotIDsrc, string slotIDdest) {
    /* KAMUS LOKAL */
    bool found, finish;
    int i, j;
    int dst, quantity;
    Item* item;

    /* ALGORITMA */
    found = false;
    i = 0;
    while (i < 3 && !found) {
        j = 0;
        while (j < 3 && !found) {
            if (slotIDsrc == this->crafting.getElmt(i, j).getSlotID()) {
                item = this->crafting.getElmt(i, j).getItem();
                quantity = this->crafting.getElmt(i, j).getQuantity();
                NonTool* itemdefault = new NonTool(0, "-", "-");
                CraftingSlot* newSlot = new CraftingSlot();
                newSlot->setSlotID(this->crafting.getElmt(i, j).getSlotID());
                newSlot->setItem(itemdefault);
                newSlot->setQuantity(0);
                this->crafting.setElmt(i, j, *newSlot);
                delete newSlot;
                found = true;
            } 
            j++;
        }
        i++;
    }

    dst = 0;
    i = 0;
    finish = false;
    while(!finish && dst < 27){
        if (slotIDdest == this->itemlist[dst].get_slotID()){
            finish = true;
        } else{
            dst++;
        }
    }
    
    if (this->itemlist[dst].get_item()->getId() == this->itemlist[dst].get_item()->getId()) {
        this->itemlist[dst].set_item(item);
        this->itemlist[dst].set_quantity(this->itemlist[dst].get_quantity() + quantity); 
    }
    else if (this->itemlist[dst].get_item()->getId() == 0) {
        this->itemlist[dst].set_item(item);
        this->itemlist[dst].set_quantity(quantity); 
    } else {
        cout << "Jenis item berbeda" << endl;
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

void Inventory::Craft(ItemList config, vector<Recipe> recipeList) {
    vector<Recipe> fullRecipeList;
    fullRecipeList = this->crafting.createFullRecipeList(recipeList);
    vector<Recipe>::iterator it;
    
    // Retrieve the correct recipe, if not found, throw "Invalid Recipe"
    Recipe result = this->crafting.getRecipe(fullRecipeList);
    if (result.getHasilRecipe() == "Dummy Recipe") {
        throw "Invalid Recipe";
    } else {
        bool possible = true;
        int resultQuantity = 0;
        string resultName = result.getHasilRecipe();
        int id = config.getItemElmt(resultName).getId();
        string varian = config.getItemElmt(resultName).getVarian();
        string category = config.getItemElmt(resultName).getCategory();

        // While crafting is still possible (no missing items)
        while (possible) {
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    if (category == "NONTOOL") {
                        if (this->crafting.getGrid().at(x).at(y).getQuantity() != 0) {
                            // Create newSlot to override current crafting slot
                            CraftingSlot* newSlot = new CraftingSlot();
                            newSlot->setSlotID(this->crafting.getElmt(x, y).getSlotID());
                            NonTool* newItem = new NonTool(this->crafting.getElmt(x, y).getItem()->getId(), this->crafting.getElmt(x, y).getItem()->getType(), this->crafting.getElmt(x, y).getItem()->getVarian());
                            newSlot->setItem(newItem);
                            newSlot->setQuantity(this->crafting.getElmt(x, y).getQuantity() - 1);
                            this->crafting.setElmt(x, y, *newSlot);
                            
                            resultQuantity += result.getJumlah();
                            // If the item quantity inside the grid turned to 0, then it's no longer possible to craft
                            if (this->crafting.getGrid().at(x).at(y).getQuantity() == 0) {
                                // Move resulting item to inventory
                                NonTool* resultItem = new NonTool(id, resultName, varian);
                                giveItem(resultItem, resultQuantity);

                                // Clear the crafting grid
                                NonTool* itemdefault = new NonTool(0, "-", "-");
                                newSlot->setSlotID(this->crafting.getElmt(x, y).getSlotID());
                                newSlot->setItem(itemdefault);
                                newSlot->setQuantity(0);
                                this->crafting.setElmt(x, y, *newSlot);
                                delete newSlot;

                                // Set possible to false to break the loop
                                possible = false;
                            } 
                        } 
                    } else if (category == "TOOL") {
                        if (this->crafting.getGrid().at(x).at(y).getQuantity() != 0) {
                            // Create newSlot to override current crafting slot
                            CraftingSlot* newSlot = new CraftingSlot();
                            newSlot->setSlotID(this->crafting.getElmt(x, y).getSlotID());
                            Tool* newItem = new Tool(this->crafting.getElmt(x, y).getItem()->getId(), this->crafting.getElmt(x, y).getItem()->getType(), this->crafting.getElmt(x, y).getItem()->getVarian(), 10);
                            newSlot->setItem(newItem);
                            newSlot->setQuantity(this->crafting.getElmt(x, y).getQuantity() - 1);
                            this->crafting.setElmt(x, y, *newSlot);
                            
                            resultQuantity += result.getJumlah();
                            // If the item quantity inside the grid turned to 0, then it's no longer possible to craft
                            if (this->crafting.getGrid().at(x).at(y).getQuantity() == 0) {
                                // Move resulting item to inventory
                                Tool* resultItem = new Tool(id, resultName, varian, 10);
                                giveItem(resultItem, resultQuantity);

                                // Clear the crafting grid
                                NonTool* itemdefault = new NonTool(0, "-", "-");
                                newSlot->setSlotID(this->crafting.getElmt(x, y).getSlotID());
                                newSlot->setItem(itemdefault);
                                newSlot->setQuantity(0);
                                this->crafting.setElmt(x, y, *newSlot);
                                delete newSlot;

                                // Set possible to false to break the loop
                                possible = false;
                            } 
                        } 
                    } 
                }
            }
        }
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
        if (this->itemlist[i].get_item()->getCategory() == "Tool") {
            int dur = this->itemlist[i].get_item()->getDurability();
            cout << "[" << id << ":" << dur << "]";
        } else {
            int qty = this->itemlist[i].get_quantity();
            cout << "[" << id << ":" << qty << "]";
        }
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
            file << this->itemlist[i].get_item()->getId() << ":" << this->itemlist[i].get_quantity(); 
            if (i != CAPACITY - 1) {
                file << endl;
            }
        }
    }
    file.close();
}
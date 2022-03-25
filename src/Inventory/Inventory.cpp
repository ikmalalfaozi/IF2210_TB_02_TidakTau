// -----------Inventory implementation-------------
#include "Inventory.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Inventory::Inventory() : crafting(3,3) {
    this->itemlist = new InventorySlot<Item*>[CAPACITY];
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
    
    this->itemlist = new InventorySlot<Item*>[CAPACITY];
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
                if (this->itemlist[i].get_item()->getCategory() == "NonTool") {
                    int currentQuantity = this->itemlist[i].get_quantity();
                    if (currentQuantity + quantity > 64) {
                        this->itemlist[i].set_quantity(64);
                        quantity -= 64 - currentQuantity;
                    } else {
                        this->itemlist[i].set_quantity(currentQuantity + quantity);
                        quantity = 0;
                    }
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
    if (this->itemlist[src].get_item()->getId() != 0) {
        while (i < 3 && !finish) {
            int j = 0;
            while (j < 3 && !finish) {
                
                if (slotIDdest == this->crafting.getElmt(i, j).getSlotID()) {
                    if (this->crafting.getElmt(i, j).getItem()->getId() == 0) {
                        CraftingSlot* newSlot = new CraftingSlot();
                        newSlot->setSlotID(this->crafting.getElmt(i, j).getSlotID());
                        newSlot->setItem(this->itemlist[src].get_item());
                        // Change quantity
                        newSlot->setQuantity(this->crafting.getElmt(i, j).getQuantity() + 1);
                        this->crafting.setElmt(i, j, *newSlot);
                        delete newSlot;

                        discardItem(slotIDsrc, 1);
                        finish = true;
                    } else{ // tidak 0
                        if (this->crafting.getElmt(i, j).getItem()->getId() == this->itemlist[src].get_item()->getId()) {
                            if (this->crafting.getElmt(i, j).getQuantity() + 1 <= 64) {
                                CraftingSlot* newSlot = new CraftingSlot();
                                newSlot->setSlotID(this->crafting.getElmt(i, j).getSlotID());
                                newSlot->setItem(this->itemlist[src].get_item());
                                // Change quantity
                                newSlot->setQuantity(this->crafting.getElmt(i, j).getQuantity() + 1);
                                this->crafting.setElmt(i, j, *newSlot);
                                delete newSlot;

                                discardItem(slotIDsrc, 1);
                                finish = true;
                            }
                            
                        } 
                    }
                }
                j++;
            }
            i++;
        }
    }
}

void Inventory::moveCraftingToInventory(string slotIDsrc, string slotIDdest) {
    /* KAMUS LOKAL */
    bool found, finish;
    int i, j;
    int dst, quantity;
    int srcX, srcY;
    Item* item;

    /* ALGORITMA */
    found = false;
    i = 0;
    while (i < 3 && !found) {
        j = 0;
        while (j < 3 && !found) {
            if (slotIDsrc == this->crafting.getElmt(i, j).getSlotID()) {
                srcX = i;
                srcY = j;
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
    
    if (this->crafting.getElmt(srcX, srcY).getItem()->getId() == this->itemlist[dst].get_item()->getId()) {
        item = this->crafting.getElmt(srcX, srcY).getItem();
        quantity = this->crafting.getElmt(srcX, srcY).getQuantity();
        this->itemlist[dst].set_item(item);
        this->itemlist[dst].set_quantity(this->itemlist[dst].get_quantity() + quantity); 
        NonTool* itemdefault = new NonTool(0, "-", "-");
        CraftingSlot* newSlot = new CraftingSlot();
        newSlot->setSlotID(this->crafting.getElmt(srcX, srcY).getSlotID());
        newSlot->setItem(itemdefault);
        newSlot->setQuantity(0);
        this->crafting.setElmt(srcX, srcY, *newSlot);
        delete newSlot;
    }
    else if (this->itemlist[dst].get_item()->getId() == 0) {
        item = this->crafting.getElmt(srcX, srcY).getItem();
        quantity = this->crafting.getElmt(srcX, srcY).getQuantity();
        this->itemlist[dst].set_item(item);
        this->itemlist[dst].set_quantity(quantity); 
        NonTool* itemdefault = new NonTool(0, "-", "-");
        CraftingSlot* newSlot = new CraftingSlot();
        newSlot->setSlotID(this->crafting.getElmt(srcX, srcY).getSlotID());
        newSlot->setItem(itemdefault);
        newSlot->setQuantity(0);
        this->crafting.setElmt(srcX, srcY, *newSlot);
        delete newSlot;
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
                if (currentDurability <= 1){
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
        int toolCounter = 0;
        bool notFound = false;
        int x = 0;
        int durability1, durability2;
        int firstToolID = 0;
        string type;
        while (x < 3 && !notFound) {
            int y = 0;
            while (y < 3 && !notFound) {
                // If there are more than 2 tools in the grid, it can't be crafter
                if (toolCounter > 2) {
                    notFound = true;
                }
                // If there are tools in the grid, add the counter
                if (this->crafting.getElmt(x, y).getItem()->getCategory() == "Tool") {
                    // If toolCounter = 0, find the first tool id
                    if (toolCounter == 0) {
                        firstToolID = this->crafting.getElmt(x, y).getItem()->getId();
                        type = this->crafting.getElmt(x, y).getItem()->getType();
                        durability1 = this->crafting.getElmt(x, y).getItem()->getDurability();
                        toolCounter++;
                    } else if ((toolCounter == 1) && (this->crafting.getElmt(x, y).getItem()->getId() == firstToolID)) {
                        durability2 = this->crafting.getElmt(x, y).getItem()->getDurability();
                        toolCounter++;
                    }
                }
                y++;
            }
            x++;
        }

        // If there are 2 tools in the grid, combine them and add the durability
        if (toolCounter == 2) {
            int newDurability = durability1 + durability2;
            if (newDurability > 10) {
                newDurability = 10;
            }
            giveItem(new Tool(firstToolID, type, "-", newDurability), 1);

            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    if (this->crafting.getElmt(x, y).getItem()->getCategory() == "Tool") {
                        CraftingSlot* newSlot = new CraftingSlot();
                        // Clear the crafting grid
                        NonTool* itemdefault = new NonTool(0, "-", "-");
                        newSlot->setSlotID(this->crafting.getElmt(x, y).getSlotID());
                        newSlot->setItem(itemdefault);
                        newSlot->setQuantity(0);
                        this->crafting.setElmt(x, y, *newSlot);
                        delete newSlot;
                    }
                }
            }
        } else {
            throw "Invalid Recipe";
        }
    } else {
        bool possible = true;
        int resultQuantity = 0;
        string resultName = result.getHasilRecipe();
        // Get item data from its name
        int id = config.getItemElmt(resultName).getId();
        string varian = config.getItemElmt(resultName).getVarian();
        string category = config.getItemElmt(resultName).getCategory();
        
        while (possible) {
            // Outer main loop
            int x = 0;
            while (x < 3 && possible) {
                int y = 0;
                while (y < 3 && possible) {
                    if (category == "NONTOOL") {
                        // Check if the recipe is still possible
                        Recipe checkResult = this->crafting.getRecipe(fullRecipeList);
                        if (checkResult.getHasilRecipe() != "Dummy Recipe") {
                            resultQuantity += result.getJumlah();
                            // Inner loop
                            for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                    // Find the slot with an item in it
                                    if (this->crafting.getGrid().at(i).at(j).getItem()->getId() != 0) {
                                        // Create newSlot to override current crafting slot
                                        CraftingSlot* newSlot = new CraftingSlot();
                                        newSlot->setSlotID(this->crafting.getElmt(i, j).getSlotID());
                                        NonTool* newItem = new NonTool(this->crafting.getElmt(i, j).getItem()->getId(), this->crafting.getElmt(i, j).getItem()->getType(), this->crafting.getElmt(i, j).getItem()->getVarian());
                                        newSlot->setItem(newItem);
                                        // Reduce the quantity by 1
                                        newSlot->setQuantity(this->crafting.getElmt(i, j).getQuantity() - 1);
                                        this->crafting.setElmt(i, j, *newSlot);
                                        delete newSlot;

                                        if (this->crafting.getGrid().at(i).at(j).getQuantity() == 0) {
                                            // Clear the crafting grid
                                            NonTool* itemdefault = new NonTool(0, "-", "-");
                                            newSlot->setSlotID(this->crafting.getElmt(i, j).getSlotID());
                                            newSlot->setItem(itemdefault);
                                            newSlot->setQuantity(0);
                                            this->crafting.setElmt(i, j, *newSlot);
                                            delete newSlot;
                                        } 
                                    }
                                }
                            }
                        } else {
                            // If recipe is no longer available, set the flag to false
                            possible = false;
                        }
                        if (!possible) {
                            NonTool* resultItem = new NonTool(id, resultName, varian);
                            giveItem(resultItem, resultQuantity);
                        }
                        
                    } else if (category == "TOOL") {
                        // Check if the recipe is still possible
                        Recipe checkResult = this->crafting.getRecipe(fullRecipeList);
                        if (checkResult.getHasilRecipe() != "Dummy Recipe") {
                            resultQuantity += result.getJumlah();
                            // Inner loop
                            for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                    // Find the slot with an item in it
                                    if (this->crafting.getGrid().at(i).at(j).getItem()->getId() != 0) {
                                        // Create newSlot to override current crafting slot
                                        CraftingSlot* newSlot = new CraftingSlot();
                                        newSlot->setSlotID(this->crafting.getElmt(i, j).getSlotID());
                                        NonTool* newItem = new NonTool(this->crafting.getElmt(i, j).getItem()->getId(), this->crafting.getElmt(i, j).getItem()->getType(), this->crafting.getElmt(i, j).getItem()->getVarian());
                                        newSlot->setItem(newItem);
                                        // Reduce the quantity by 1
                                        newSlot->setQuantity(this->crafting.getElmt(i, j).getQuantity() - 1);
                                        this->crafting.setElmt(i, j, *newSlot);
                                        delete newSlot;

                                        if (this->crafting.getGrid().at(i).at(j).getQuantity() == 0) {
                                            // Clear the crafting grid
                                            NonTool* itemdefault = new NonTool(0, "-", "-");
                                            newSlot->setSlotID(this->crafting.getElmt(i, j).getSlotID());
                                            newSlot->setItem(itemdefault);
                                            newSlot->setQuantity(0);
                                            this->crafting.setElmt(i, j, *newSlot);
                                            delete newSlot;
                                        } 
                                    }
                                }
                            }
                        } else {
                            // If recipe is no longer available, set the flag to false
                            possible = false;
                        }

                        // Move resulting item to inventory
                        if (!possible) {
                            Tool* resultItem = new Tool(id, resultName, varian, 10);
                            for (int i = 0; i < resultQuantity; i++) {
                                giveItem(resultItem, 1);
                            }
                        }
                    }
                    y++;
                }
                x++;
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
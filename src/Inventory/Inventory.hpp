#ifndef INVENTORY_H
#define INVENTORY_H
#define CAPACITY 27
#include <string>
#include <variant>
#include <iostream>
#include "../Item/Item.hpp"
#include "InventorySlot.hpp"

// BELUM SELESAI

class Inventory {
private:
    int activesize;
    InventorySlot* itemlist;
public:
    Inventory();
    Inventory(Inventory&);
    ~Inventory();

    void addItem(Item* item, int quantity);// Menambah item ke inventory
    void deleteItem(string slotID, int quantity); // Membuang item dari inventory
    void stackItem(string slotIDsrc, string slotIDdest); // Menumpuk item non tool yang sama pada inventory
    void useItem(string slotID); // Menggunakan item
    
    void showInventory() const; // Mencetak inventory
    void exportInventory(string filename); // Meng-export inventory
};

#endif
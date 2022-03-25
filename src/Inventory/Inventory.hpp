#ifndef INVENTORY_H
#define INVENTORY_H
#define CAPACITY 27
#include <string>
#include <iostream>
#include "../Item/Item.hpp"
#include "../Item/Tool.hpp"
#include "../Item/NonTool.hpp"
#include "../Crafting/craftingSlot.hpp"
#include "../Crafting/crafting.hpp"
#include "InventorySlot.hpp"


class Inventory {
private:
    Crafting crafting;
    InventorySlot<Item*>* itemlist;
public:
    Inventory();
    Inventory(Inventory&);
    ~Inventory();

    Crafting getCrafting();

    void giveItem(Item* item, int quantity);// Menambah item ke inventory
    void discardItem(string slotID, int quantity); // Membuang item dari inventory
    void moveStackItem(string slotIDsrc, string slotIDdest); // Menumpuk item non tool yang sama pada inventory
    void moveInventoryToCrafting(string slotIDsrc, string slotIDdest); // Memindahkan item dri inventory ke crafting
    void moveCraftingToInventory(string slotIDsrc, string slotIDdest); // Memindahkan item dari crafting ke inventory
    void useItem(string slotID); // Menggunakan item
    void Craft(ItemList config, vector<Recipe> recipeList); // Melakukan craft item pada Crafting
    
    void showInventory(); // Mencetak inventory
    void exportInventory(string filename); // Meng-export inventory
};

#endif
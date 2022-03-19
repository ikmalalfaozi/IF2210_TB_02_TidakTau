#ifndef INVENTORYSLOT_H
#define INVENTORYSLOT_H
#define CAPACITY 27
#include <string>
#include <variant>
#include <iostream>
#include "Item.hpp"

// Tahap perencanaan
class InventorySlot {
    private:
        // Karena kelas item belum ada, 
        // sementara pakai tipe data integer
        string slotID;
        variant<Item, Tool, NonTool> item;
        int quantity;
    public:
        InventorySlot();

        InventorySlot& operator=(const InventorySlot&);

        void set_slotID(string slotid);
        void set_item(Item itemid);
        void set_quantity(int quantity);

        string get_slotID() const;
        variant<Item, Tool, NonTool>& get_item();
        int get_quantity() const;
};

#endif
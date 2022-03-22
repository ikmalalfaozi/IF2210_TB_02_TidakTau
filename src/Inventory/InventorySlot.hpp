#ifndef INVENTORYSLOT_H
#define INVENTORYSLOT_H
#define CAPACITY 27
#include <string>
#include <iostream>
#include "../Item/Item.hpp"
#include "../Item/Tool.hpp"
#include "../Item/NonTool.hpp"

// Tahap perencanaan
class InventorySlot {
    private:
        string slotID;
        Item* item;
        int quantity;
    public:
        InventorySlot();

        InventorySlot& operator=(const InventorySlot&);

        void set_slotID(string slotid);
        void set_item(Item* itemid);
        void set_quantity(int quantity);

        string get_slotID() const;
        Item* get_item() const;
        int get_quantity() const;
};

#endif
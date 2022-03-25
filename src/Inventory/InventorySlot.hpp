#ifndef INVENTORYSLOT_H
#define INVENTORYSLOT_H
#define CAPACITY 27
#include <string>
#include <iostream>
#include "../Item/Item.hpp"
#include "../Item/Tool.hpp"
#include "../Item/NonTool.hpp"

// Tahap perencanaan
template <class T>
class InventorySlot {
    private:
        string slotID;
        T item;
        int quantity;
    public:
        InventorySlot();

        InventorySlot<T>& operator=(const InventorySlot<T>&);

        void set_slotID(string slotid);
        void set_item(T itemid);
        void set_quantity(int quantity);

        string get_slotID() const;
        T get_item() const;
        int get_quantity() const;
};

template class InventorySlot<Item*>;

#endif
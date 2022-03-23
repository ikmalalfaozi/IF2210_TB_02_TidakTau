#ifndef _CRAFTING_SLOT_HPP_
#define _CRAFTING_SLOT_HPP_

#include "../Item/Item.hpp"
#include "../Item/Tool.hpp"
#include "../Item/NonTool.hpp"
#include <string>
#include <iostream>

class CraftingSlot {
    private:
        string slotID;
        Item* item;
        int quantity;
    public:
        CraftingSlot();
        CraftingSlot(int id, Item* item, int quantity);
        CraftingSlot& operator=(const CraftingSlot&);

        string getSlotID() const;
        Item* getItem() const;
        int getQuantity() const;

        void setSlotID(string slotID);
        void setItem(Item* item);
        void setQuantity(int quantity);
};

#endif
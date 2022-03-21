#ifndef _CRAFTING_SLOT_HPP_
#define _CRAFTING_SLOT_HPP_

#include "../src/Item/Item.hpp"
#include <string>

class CraftingSlot {
    private:
        string slotID;
        Item item;
        int quantity;
    public: 
        static int idCounter;

        CraftingSlot();
        CraftingSlot(int quantity);

        int getId() const;
        Item getItem() const;
        int getQuantity() const;

        void setSlotID(string slotID);
        void setQuantity(int quantity);
    
};

#endif
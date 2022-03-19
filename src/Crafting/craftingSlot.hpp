#ifndef _CRAFTING_SLOT_HPP_
#define _CRAFTING_SLOT_HPP_

#include "../src/Item/Item.hpp"

class CraftingSlot {
    private:
        const int id;
        Item item;
        int quantity;
    public:
        static int idNumber;
        
        CraftingSlot();
        CraftingSlot(int quantity);

        int getId() const;
        int getQuantity() const;
        Item getItem() const;
    
};

#endif
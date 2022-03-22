#ifndef _CRAFTING_SLOT_HPP_
#define _CRAFTING_SLOT_HPP_

#include "../Item/Item.hpp"
#include "../Item/Tool.hpp"
#include "../Item/NonTool.hpp"
#include <string>

class CraftingSlot {
    private:
        const int id;
        string slotID;
        Item* item;
        int quantity;
        static int idCounter;
    public:
        CraftingSlot();
        CraftingSlot(Item* item, int quantity);

        string getSlotID() const;
        Item* getItem() const;
        int getQuantity() const;

        void setSlotID(string slotID);
        void setItem(Item* item);
        void setQuantity(int quantity);
};

#endif
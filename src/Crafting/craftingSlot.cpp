#include "craftingSlot.hpp"

CraftingSlot::CraftingSlot() {
    NonTool* itemdefault = new NonTool(0, "-", "-");
    this->slotID = "C" + to_string(0);
    this->item = itemdefault;
    this->quantity = 0;
}

CraftingSlot::CraftingSlot(int id, Item* item, int quantity) {
    this->slotID = "C" + to_string(id);
    this->item = item;
    this->quantity = quantity;
}

CraftingSlot& CraftingSlot::operator=(const CraftingSlot& other) {
    this->slotID = other.slotID;
    this->item = other.item;
    this->quantity = other.quantity;
    return *this;
}

string CraftingSlot::getSlotID() const {
    return this->slotID;
}

Item* CraftingSlot::getItem() const {
    return this->item;
}

int CraftingSlot::getQuantity() const {
    return this->quantity;
}

void CraftingSlot::setSlotID(string slotID) {
    this->slotID = slotID;
}

void CraftingSlot::setItem(Item* item) {
    this->item = item;
}

void CraftingSlot::setQuantity(int quantity) {
    this->quantity = quantity;
}
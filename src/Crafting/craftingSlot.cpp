#include "craftingSlot.hpp"

int CraftingSlot::idCounter = 0;

CraftingSlot::CraftingSlot() : id(idCounter) {
    NonTool* itemdefault = new NonTool(0, "-", "-");
    this->slotID = "C" + to_string(this->id);
    this->item = itemdefault;
    this->quantity = 0;
    this->idCounter = this->idCounter + 1;
}

CraftingSlot::CraftingSlot(Item* item, int quantity) : id(idCounter) {
    this->slotID = "C" + to_string(this->id);
    this->item = item;
    this->quantity = quantity;
    this->idCounter = this->idCounter + 1;
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
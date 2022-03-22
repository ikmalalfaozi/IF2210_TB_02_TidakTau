#include "craftingSlot.hpp"

int CraftingSlot::idCounter = 0;

CraftingSlot::CraftingSlot() {
    this->slotID = "C" + idCounter;
    this->quantity = 0;
    idCounter++;
}

CraftingSlot::CraftingSlot(Item* item, int quantity) {
    this->slotID = "C" + idCounter;
    this->item = item;
    this->quantity = quantity;
    idCounter++;
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
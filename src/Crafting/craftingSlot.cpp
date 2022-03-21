#include "craftingSlot.hpp"

int CraftingSlot::idCounter = 0;

CraftingSlot::CraftingSlot() {
    this->slotID = "C" + idCounter;
    this->item = Item();
    this->quantity = 0;
    idCounter++;
}

CraftingSlot::CraftingSlot(int quantity) {
    this->slotID = "C" + idCounter;
    this->item = Item();
    this->quantity = quantity;
    idCounter++;
}

int CraftingSlot::getSlotId() const {
    return this->slotID
}

int CraftingSlot::getQuantity() const {
    return this->quantity
}

Item CraftingSlot::getItem() const {
    return this->item
}

void CraftingSlot::setSlotID(string slotID) {
    this->slotID = slotID;
}

void CraftingSlot::setQuantity(int quantity) {
    this->quantity = quantity;
}
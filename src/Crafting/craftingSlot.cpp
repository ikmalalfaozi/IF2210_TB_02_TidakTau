#include "craftingSlot.hpp"

int CraftingSlot::idNumber = -1;

CraftingSlot::CraftingSlot() : id(idNumber + 1) {
    this->quantity = quantity;
    idNumber++;
}

CraftingSlot::CraftingSlot(int quantity) : id(idNumber + 1) {
    this->quantity = quantity;
    idNumber++;
}

int CraftingSlot::getId() const {
    return this->id
}

int CraftingSlot::getQuantity() const {
    return this->quantity
}

Item CraftingSlot::getItem() const {
    return this->item
}
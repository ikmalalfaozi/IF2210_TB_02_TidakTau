#include "Item.hpp"

Item::Item(int id, string category) {
    this->id = id;
    this->category = category;
}

Item::Item(const Item& item) {
    this->id = item.id;
    this->category = item.category;
}

Item::~Item() {}

Item& Item::operator=(const Item& item) {
    this->id = item.id;
    this->category = item.category;
    return *this;
}

int Item::getId() const {
    return id;
}

string Item::getCategory() const {
    return category;
}
#include "ItemElmt.hpp"

ItemElmt::ItemElmt() {
    this->category = "None";
    this->id = -1;
    this->varian = "None";
}

ItemElmt::ItemElmt(string category, int id, string varian) {
    this->category = category;
    this->id = id;
    this->varian = varian;
}

string ItemElmt::getCategory() {
    return this->category;
}

int ItemElmt::getId() {
    return this->id;
}

string ItemElmt::getVarian() {
    return this->varian;
}
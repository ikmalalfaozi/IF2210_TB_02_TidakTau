#include "ItemList.hpp"

ItemList::ItemList() {
    this->type = "-";
    configList[this->type] = ItemElmt("-", 0, "-");
}

/*
ItemList::ItemList(string name, int id, string category, string varian) {
    configList[name] = ItemElmt(category, id, varian);
    this->name = name;
} */

//method
string ItemList::getType() const {
    return this->type;
}

map<string, ItemElmt> ItemList::getConfigList() const {
    return this->configList;
}

ItemElmt ItemList::getItemElmt(string type) {
    return this->configList[type];
}

void ItemList::setType(string name) {
    this->type = type;
}

void ItemList::addItemElmt(string type, int id, string category, string varian) {
    this->configList[type] = ItemElmt(category, id, varian);
}
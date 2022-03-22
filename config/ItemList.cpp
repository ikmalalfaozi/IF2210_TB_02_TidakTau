#include "ItemList.hpp"

ItemList::ItemList(){
    configList[name] = ItemElmt("-", 0, "-");
    this->name = "-";
}

ItemList::ItemList(string name, int id, string category, string varian) {
    configList[name] = ItemElmt(category, id, varian);
    this->name = name;
}

//method
string ItemList::getName() const {
    return this->name;
}

map<string, ItemElmt> ItemList::getConfigList() const {
    return this->configList;
}
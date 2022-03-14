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


NonTool::NonTool(int id, string type) : Item(id, "NonTool") {
    this->type = type;
    this->varian = "None";
}

NonTool::NonTool(int id, string type, string varian) : Item (id, "NonTool") {
    this->type = type;
    this->varian = varian;
}

NonTool::NonTool(const NonTool& nt) : Item(nt.id, nt.category) {
    this->type = nt.type;
    this->varian = nt.varian;
}

NonTool::~NonTool() {};

NonTool& NonTool::operator=(const NonTool& nt) {
    this->id = nt.id;
    this->category = nt.category;
    this->type = nt.type;
    this->varian = nt.varian;
    return *this;
}

string NonTool::getType() const {
    return type;
}

string NonTool::getVarian() const {
    return varian;
}


Tool::Tool(int id, string type, string varian, int durability) : Item(id, "Tool") {
    this->type = type;
    this->varian = varian;
    this->durability = durability;
}

Tool::Tool(const Tool& t) : Item(t.id, t.category){
    this->type = t.type;
    this->varian = t.varian;
    this->durability = t.durability;
}

Tool::~Tool() {}

Tool& Tool::operator=(const Tool& t) {
    this->id = t.id;
    this->category = t.category;
    this->type = t.type;
    this->varian = t.varian;
    this->durability = t.durability;
}

string Tool::getType() const {
    return type;
}

string Tool::getVarian() const {
    return varian;
}

int Tool::getDurability() {
    return durability;
}

void Tool::setDuarbility(int durability) {
    this->durability = durability;
}
#include "Tool.hpp"

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
    return *this;
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

void Tool::setDurability(int durability) {
    this->durability = durability;
}
#include "NonTool.hpp"

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

// KETERANGAN: 
// NONTOOL SEHARUSNYA TIDAK MEMILIKI DURABILITY, SEHINGGA
// PEMANGGILAN GET AKAN MERETURN 0
// PEMANGGILAN SET TIDAK AKAN MELAKUKAN APA-APA
int NonTool::getDurability() {
    return 0;
}

void NonTool::setDurability(int durability) {
    //
}
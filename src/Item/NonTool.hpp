#ifndef NONTOOL_H
#define NONTOOL_H
#include <string>
#include "Item.hpp"

class NonTool : public Item {
protected:
    string type;
    string varian;
public:
    NonTool(int id, string type);
    NonTool(int id, string type, string varian);
    NonTool(const NonTool&);
    ~NonTool();
    NonTool& operator=(const NonTool&);

    string getType() const;
    string getVarian() const;

    // KETERANGAN: 
    // NONTOOL SEHARUSNYA TIDAK MEMILIKI DURABILITY, SEHINGGA
    // PEMANGGILAN GET AKAN MERETURN 0
    // PEMANGGILAN SET TIDAK AKAN MELAKUKAN APA-APA
    int getDurability();
    void setDurability(int durability);
};

#endif
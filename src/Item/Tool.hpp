#ifndef TOOL_H
#define TOOL_H
#include <string>
#include "Item.hpp"

class Tool : public Item {
protected:
    string type;
    string varian;
    int durability;
public:
    Tool(int id, string type, string varian, int durability);
    Tool(const Tool&);
    ~Tool();
    Tool& operator=(const Tool&);

    string getType() const;
    string getVarian() const;
    int getDurability();
    void setDurability(int durability);
};

#endif
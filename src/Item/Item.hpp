#ifndef ITEM_H
#define ITEM_H
#include <string>

using namespace std;

class Item {
protected:
    int id;
    string category;
public:
    Item(){
        this->id = -111;
        this->category = "none";
    }
    // Penambahan default constructor item
    Item(int id, string category);
    Item(const Item&);
    ~Item();
    Item& operator=(const Item&);

    int getId() const;
    string getCategory() const;

    virtual string getType() const = 0;
    virtual string getVarian() const = 0;
    virtual int getDurability() = 0;
    virtual void setDurability(int durability) = 0;
};

#endif
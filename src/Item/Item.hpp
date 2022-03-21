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

class NonTool : public Item {
protected:
    string type;
    string varian;
private:
    NonTool(int id, string type);
    NonTool(int id, string type, string varian);
    NonTool(const NonTool&);
    ~NonTool();
    NonTool& operator=(const NonTool&);

    string getType() const;
    string getVarian() const;
};

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
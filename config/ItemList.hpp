#ifndef ITEM_LIST_HPP
#define ITEM_LIST_HPP

#include "ItemElmt.hpp"
#include <string>
#include <map>
#include <iterator>
using namespace std;

class ItemList
{
private:
    string type;
    map<string, ItemElmt> configList;
public:
    ItemList();
    //ItemList(string type, int id, string category, string varian);

    //method
    string getType() const;
    map<string, ItemElmt> getConfigList() const;
    ItemElmt getItemElmt(string type);

    void setType(string type);
    void addItemElmt(string type, int id, string category, string varian);
};

#endif
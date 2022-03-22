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
    string name;
    map<string, ItemElmt> configList;
public:
    ItemList();
    ItemList(string name, int id, string category, string varian);

    //method
    string getName() const;
    map<string, ItemElmt> getConfigList() const;
};

#endif
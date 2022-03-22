#ifndef _ITEM_ELMT_HPP_
#define _ITEM_ELMT_HPP_

#include <string>
using namespace std;

class ItemElmt {
private:
    string category;
    int id;
    string varian;
public:
    ItemElmt();
    ItemElmt(string category, int id, string varian);
    string getCategory();
    int getId();
    string getVarian();
};

#endif
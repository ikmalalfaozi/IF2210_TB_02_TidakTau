/* 
 * File: ItemTest.cpp
 * compile test: g++ ./Item/Item.cpp ./Item/Tool.cpp ./Item/NonTool.cpp ./Item/ItemTest.cpp -o itemTest
 */

#include "Item.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
#include <iostream>
#include <string>

void printItem(Item* item)
{
    cout << "Item ID : " << item->getId() << endl;
    cout << "Item Category: " << item->getCategory() << endl;
    cout << "Item Type: " << item->getType() << endl;
    cout << "Item Varian : " << item->getVarian() << endl;
    if (item->getCategory() == "Tool") {
        cout << "Item Durability : " << item->getDurability() << endl;
    }
    }

int main()
{
    /* ALGORITMA */
    int testChoice;
    cout << "Test 1: Tool; 2: NonTool" << endl;
    cout << "Input test number: ";
    cin >> testChoice;

    if (testChoice == 1)
    {
        Tool* item1 = new Tool(21, "-", "WOODEN_SWORD", 1);
        cout << "Item 1 (Tool)" << endl;
        printItem(item1);
    } 
    else 
    {
        // KETERANGAN: 
        // NONTOOL SEHARUSNYA TIDAK MEMILIKI DURABILITY, NAMUN AKHIRNYA DISET MENJADI 0
        NonTool* item2 = new NonTool(1, "LOG", "OAK_LOG");
        cout << "Item 2 (NonTool)" << endl;
        printItem(item2);
    }
}
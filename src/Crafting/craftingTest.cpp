/* 
 * File: craftingTest.cpp
 * compile test: g++ ./Crafting/crafting.cpp ./Crafting/craftingSlot.cpp ./Crafting/craftingTest.cpp ../config/recipe.cpp ../config/ItemList.cpp ../config/ItemElmt.cpp ./Item/Item.cpp ./Item/Tool.cpp ./Item/NonTool.cpp -o cTest
 */

#include "crafting.hpp"
#include "craftingSlot.hpp"
#include <iostream>
#include <string>

int main() {

    // Crafting* crafting = new Crafting(3,3);
    CraftingSlot* c1 = new CraftingSlot();
    CraftingSlot* c2 = new CraftingSlot();
    CraftingSlot* c3 = new CraftingSlot();

    cout << c1->getSlotID() << endl;
    cout << c2->getSlotID() << endl;
    cout << c3->getSlotID() << endl;
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         cout << crafting->getElmt(i,j).getSlotID() << endl;
    //     }
    // }
}
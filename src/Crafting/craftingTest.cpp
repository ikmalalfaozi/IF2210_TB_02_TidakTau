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
    Crafting craft(3,3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << craft.getGrid().at(i).at(j).getQuantity() << endl;
        }
    }

    CraftingSlot cSlot;
    cSlot.setQuantity(5);
    craft.setElmt(0, 0, cSlot);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << craft.getGrid().at(i).at(j).getQuantity() << endl;
        }
    }
}
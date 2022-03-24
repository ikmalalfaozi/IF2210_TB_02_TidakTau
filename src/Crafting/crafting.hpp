#ifndef _CRAFTING_HPP_
#define _CRAFTING_HPP_

#include <iostream>
#include <vector>
#include "craftingSlot.hpp"
#include "../Item/Item.hpp"
#include "../../config/recipe.hpp"
#include "../../config/ItemList.hpp"
using namespace std;

class Crafting {
    private:
        vector<vector<CraftingSlot>> grid;
        int rows;
        int cols;
    public:
        Crafting();
        Crafting(int rows, int cols);

        Crafting& operator=(const Crafting&);
    
        /* Functions for crafting grid itself */
        CraftingSlot getElmt(int i, int j);
        vector<vector<CraftingSlot>> getGrid();

        void setElmt(int i, int j, CraftingSlot& value);

        // Display grid
        void displayCraftingGrid();

        // Test if items in the grid is the same with the recipe
        bool testRecipe(vector<Recipe> recipeList);

        // Get the recipe information
        Recipe getRecipe(vector<Recipe> recipeList);

        // Create an empty recipe matrix
        Recipe createEmptyRecipe();

        // Input new recipes
        Recipe inputNewRecipe(Recipe recipe);

        // Find possibilities for recipes
        int findMirrorPossibilities(Recipe recipe);

        // Create mirrored recipes for 3x3 recipes
        vector<Recipe> createMirroredRecipe(Recipe recipe);

        // Create full recipe list
        vector<Recipe> createFullRecipeList(vector<Recipe> originalList);
        //void Craft(ItemList config, Inventory& inventory, vector<Recipe> recipeList);

        void moveCraftingToInventory(string slotIDsrc, string slotIDdest);
        //void moveResulttoInventory(Inventory& inventory, Item* item, int resultQuantity);
};

#endif
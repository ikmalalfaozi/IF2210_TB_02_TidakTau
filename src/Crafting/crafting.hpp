#ifndef _CRAFTING_HPP_
#define _CRAFTING_HPP_

#include <iostream>
#include <vector>
#include "../config/recipe.hpp"
#include "craftingSlot.hpp"
using namespace std;

class Crafting {
    private:
        vector<vector<CraftingSlot>> grid;
        int rows;
        int cols;
    public:
        Crafting();
        Crafting(int rows, int cols);
        /* Functions for crafting grid itself */
        CraftingSlot getElmt(int i, int j) const;
        int getGridRows() const;
        int getGridCols() const;

        /* Functions for recipe */
        int getRecipeRows() const;
        int getRecipeCols() const;

        void setElmt(int i, int j, int value);

        Recipe getRecipe(vector<Recipe> recipeList, vector<vector<CraftingSlot>> craftingSlots);
        bool testRecipe(Recipe recipe, vector<vector<CraftingSlot>> craftingSlots);

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
        void Craft();
        void moveResulttoInventory();
};

#endif
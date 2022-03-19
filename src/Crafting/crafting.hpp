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
        Recipe r;
        int rows;
        int cols;
    public:
        /* Functions for crafting grid itself */
        CraftingSlot getElmt(int i, int j) const;
        int getGridRows() const;
        int getGridCols() const;

        /* Functions for recipe */
        int getRecipeRows() const;
        int getRecipeCols() const;

        void setElmt(int i, int j, int value);
        void printGrid();

        // Create an empty recipe matrix
        vector<vector<string>> createEmptyRecipe();

        int findRealColumnSize(Recipe recipe);
        int countOccurence(int id);
        Recipe getRecipe(vector<Recipe> recipeList, vector<vector<CraftingSlot>> craftingSlots);
        bool testRecipe(Recipe recipe, vector<vector<CraftingSlot>> craftingSlots);

        // Find possibilities for 3x3 recipes
        int findMirrorPossibilities1(Recipe recipe);

        // Find possibilities for recipes other than 3x3 ones
        int findMirrorPossibilities2(Recipe recipe);

        // Create mirrored recipes for 3x3 recipes
        vector<Recipe> createMirroredRecipe1(Recipe recipe);

        // Create mirrored recipes for recipes other than 3x3 ones
        vector<Recipe> createMirroredRecipe2(Recipe recipe);

        // Create full recipe list
        vector<Recipe> createFullRecipeList(vector<Recipe> originalList);
        void Craft();
        void moveResulttoInventory();
};

#endif
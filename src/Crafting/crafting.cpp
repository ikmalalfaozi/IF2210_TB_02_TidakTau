#include "crafting.hpp"
using namespace std;

Crafting::Crafting() : grid(vector<vector<CraftingSlot>>(0, vector<CraftingSlot>(0, CraftingSlot()))) {
    this->rows = 0;
    this->cols = 0;
}

Crafting::Crafting(int rows, int cols) : grid(vector<vector<CraftingSlot>>(rows, vector<CraftingSlot>(rows, CraftingSlot()))) {
    this->rows = rows;
    this->cols = cols;
}

CraftingSlot Crafting::getElmt(int i, int j) const {
    return this->grid[i][j];
}

int Crafting::getGridRows() const {
    return this->grid.size();
}

int Crafting::getGridCols() const {
    return this->grid[0].size();
}

/* MASIH RUSAK
void Crafting::setElmt(int i, int j, int value) {
    this->grid[i][j] = value;
} */

// Test if items in the grid is the same with the recipe
bool Crafting::testRecipe(vector<Recipe> recipeList) {
    vector<Recipe>::iterator it;

    for (it = recipeList.begin(); it != recipeList.end(); ++it) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // INI HARUS NYAMAIN DATA RECIPE SAMA DATA CRAFTING SLOTS
                /*
                if (recipe.getData()[i][j] != this->grid...) {
                    return false;
                } */
            }
        }
    }
    
    return true;
}

// Create an empty 3x3 recipe matrix
Recipe Crafting::createEmptyRecipe() {
    Recipe newRecipe;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            newRecipe.setElemen(i, j, "-");
        }
    }
    return newRecipe;
}

// Input new recipes
Recipe Crafting::inputNewRecipe(Recipe recipe) {
    Recipe newRecipe;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            newRecipe.setElemen(i, j, recipe.getData()[i][j]);
        }
    }
    return newRecipe;
}

// Find possibilities for 3x3 recipes
int Crafting::findMirrorPossibilities(Recipe recipe) {
    // If recipe is 3x1, then it can be mirrored twice
    if (recipe.getRow() == 3 && recipe.getCol() == 1) {
        return 2;
    }

    // If recipe is 3x2, then it can be mirrored once
    if (recipe.getRow() == 3 && recipe.getCol() == 2) {
        return 1;
    }

    // If recipe is 3x3, then it can't be mirrored
    if (recipe.getRow() == 3 && recipe.getCol() == 3) {
        return 0;
    }

    // If recipe is 1x1, then it can be mirrored 9 times
    if (recipe.getRow() == 1 && recipe.getCol() == 1) {
        return 9;
    }

    // If recipe is 2x1, then it can be mirrored 6 times
    if (recipe.getRow() == 2 && recipe.getCol() == 1) {
        return 6;
    }
}

// Create mirrored recipes for 3x3 recipes
vector<Recipe> Crafting::createMirroredRecipe(Recipe recipe) {
    int possibilities = findMirrorPossibilities(recipe);
    if (possibilities == 1) {
        vector<Recipe> mirroredList;
        Recipe newRecipe(recipe.getRow(), recipe.getCol(), recipe.gethasilRecipe(), recipe.getJumlah());

        for (int i = 0; i < 3; i++) {
            int x = 0;
            for (int j = 2; j >= 0; j--) {
                int y = 0;
                newRecipe.setElemen(x, y, recipe.getDataElmt(i, j));
                y++;
            }
            mirroredList.push_back(newRecipe);
            x++;
        }
        return mirroredList;
    }

    if (possibilities == 2) {
        vector<string> recipeShape;
        vector<string>::iterator it;
        vector<Recipe> mirroredList;
        Recipe emptyRecipe(recipe.getRow(), recipe.getCol(), recipe.gethasilRecipe(), recipe.getJumlah());

        for (int i = 0; i < 3; i++) {
            recipeShape.push_back(recipe.getDataElmt(i, 1));
        }

        for (int i = 0; i < 3; i += 2) {
            emptyRecipe = createEmptyRecipe();
            it = recipeShape.begin();
            for (int j = 0; j < 3; j++) {
                if (it != recipeShape.end()) {
                    emptyRecipe.setElemen(j, i, *it);
                    ++it;
                }
            }
            mirroredList.push_back(emptyRecipe);
        }
        return mirroredList;
    }

    if (possibilities == 6) {
        vector<Recipe> mirroredList;
        Recipe emptyRecipe(recipe.getRow(), recipe.getCol(), recipe.gethasilRecipe(), recipe.getJumlah());

        for (int i = 0; i < 3; i++) {
            emptyRecipe = createEmptyRecipe();
            for (int j = 0; j < 2; j++) {
                emptyRecipe.setElemen(j, i, recipe.getDataElmt(j, 0));
            }
            mirroredList.push_back(emptyRecipe);
        }
        
        for (int i = 0; i < 3; i++) {
            emptyRecipe = createEmptyRecipe();
            int k = 0;
            for (int j = 0; j < 2; j++) {
                emptyRecipe.setElemen(j, i, recipe.getDataElmt(k, 0));
                k++;
            }
            mirroredList.push_back(emptyRecipe);
        }
        return mirroredList;
    }

    if (possibilities == 9) {
        vector<Recipe> mirroredList;
        Recipe emptyRecipe(recipe.getRow(), recipe.getCol(), recipe.gethasilRecipe(), recipe.getJumlah());

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                emptyRecipe = createEmptyRecipe();
                emptyRecipe.setElemen(j, i, recipe.getDataElmt(0, 0));
                mirroredList.push_back(emptyRecipe);
            }
        }
        return mirroredList;
    }
}

// Create full recipe list
vector<Recipe> Crafting::createFullRecipeList(vector<Recipe> originalList) {
    vector<Recipe> recipeList;
    vector<Recipe> mirrorRecipeList;
    vector<Recipe>::iterator it;
    vector<Recipe>::iterator it2;
    for (it = originalList.begin(); it != originalList.end(); ++it) {
        if ((it->getRow() != 1) || (it->getRow() != 2) && (it->getCol() != 1)) {
            recipeList.push_back(*it);
        }
    }

    for (it = originalList.begin(); it != originalList.end(); ++it) {
        if (it->getRow() == 3 && it->getCol() == 3) {
            mirrorRecipeList = createMirroredRecipe(*it);
            for (it2 = mirrorRecipeList.begin(); it2 != mirrorRecipeList.end(); ++it2) {
                recipeList.push_back(*it2);
            }
        }

        if (it->getRow() == 1 && it->getCol() == 1) {
            mirrorRecipeList = createMirroredRecipe(*it);
            for (it2 = mirrorRecipeList.begin(); it2 != mirrorRecipeList.end(); ++it2) {
                recipeList.push_back(*it2);
            }
        }

        if (it->getRow() == 2 && it->getCol() == 1) {
            mirrorRecipeList = createMirroredRecipe(*it);
            for (it2 = mirrorRecipeList.begin(); it2 != mirrorRecipeList.end(); ++it2) {
                recipeList.push_back(*it2);
            }
        }
    }

    return recipeList;
}

void Crafting::Craft(vector<Recipe> recipeList) {
    recipeList = createFullRecipeList(recipeList);
    if (testRecipe(recipeList)) {
        
    }
}

void Crafting::moveResulttoInventory() {

}
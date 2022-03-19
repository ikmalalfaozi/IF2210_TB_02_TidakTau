#include <vector>
#include "crafting.hpp"
using namespace std;

Crafting::Crafting() {
    this->rows = 0;
    this->cols = 0;
}

Crafting::Crafting(int rows, int cols) : grid(vector<vector<int>>(rows, vector<int>(cols, 0))) {
    this->rows = rows;
    this->cols = cols;
}

Crafting::~Crafting() {}

int Crafting::getElmt(int i, int j) const {
    return this->grid[i][j];
}

int Crafting::getGridRows() const {
    return this->grid.size();
}

int Crafting::getGridCols() const {
    return this->grid[0].size();
}

int Crafting::getRecipeRows() const {
    return this->r.rows;
}

int Crafting::getRecipeCols() const {
    return this->r.cols;
}

void Crafting::setElmt(int i, int j, int value) {
    this->grid[i][j]= value;
}

void Crafting::printGrid() {
    int i, j;
    for (i=0;i<this->getGridRows();i++) {
        for (j=0;j<this->getGridCols();j++) {
            cout << this->getElmt(i, j) << "\t";
        }
        cout << endl;
    }
}

// Create an empty recipe matrix
vector<vector<string>> Crafting::createEmptyRecipe() {

}

int Crafting::findRealColumnSize(Recipe recipe) {
    int originalSize = recipe.getCol();
    int emptyColCount = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (recipe.getData()[x][y] == "-") {
                emptyColCount++;
            }
            if (emptyColCount == 3) {
                originalSize--;
                emptyColCount = 0;
            }
        }
    }
    return originalSize;
}

int Crafting::countOccurence(int id);

Recipe Crafting::getRecipe(vector<Recipe> recipeList, vector<vector<CraftingSlot>> craftingSlots) {
    vector<Recipe>::iterator it;

    for (it = recipeList.begin(); it != recipeList.end(); ++it) {
        if (testRecipe(it, craftingSlots)) {
            return it;
        }
    }
    return NULL;
}

bool Crafting::testRecipe(Recipe recipe, vector<vector<CraftingSlot>> craftingSlots) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // INI HARUS NYAMAIN DATA RECIPE SAMA DATA CRAFTING SLOTS
            if (recipe.getData()[i][j] != craftingSlots[i][j].getId()) {
                return false;
            }
        }
    }
    return true;
}

// Find possibilities for 3x3 recipes
int Crafting::findMirrorPossibilities1(Recipe recipe) {
    // If recipe is only 1 wide, then it can be mirrored twice
    if (findRealColumnSize(recipe) == 1) {
        return 2;
    }

    // If recipe is 2 wide, then it can be mirrored once
    if (findRealColumnSize(recipe) == 2) {
        return 1;
    }

    // If recipe is 3 wide, then it can't be mirrored
    if (findRealColumnSize(recipe) == 3) {
        return 0;
    }
}

// Find possibilities for recipes other than 3x3 ones
int Crafting::findMirrorPossibilities2(Recipe recipe) {
    // If recipe is only 1x1, then it can be mirrored 9 times
    if (recipe.getRow() == 1 && recipe.getCol() == 1) {
        return 9;
    }

    // If recipe is 2x1, then it can be mirrored 6 times;
    if (recipe.getRow() == 2 && recipe.getCol() == 1) {
        return 6;
    }
}

// Create mirrored recipes for 3x3 recipes
vector<Recipe> Crafting::createMirroredRecipe1(Recipe recipe) {
    vector<Recipe>::iterator it;
    vector<Recipe>::iterator it2;

    int possibilities = findMirrorPossibilities1(recipe);
    if (possibilities == 1) {
        vector<Recipe> mirroredList;

        for (int i = 0; i < 3; i++) {
            for (int j = 2; j >= 0; j--) {
                Recipe newRecipe = new Recipe(recipe.getRow(), recipe.getCol(), recipe.getHasil(), recipe.jumlah());
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        newRecipe.setElemen(x, y, recipe.getData()[x][y]);
                    }
                }
                mirroredList.push_back(newRecipe);
            }
        }
        return mirroredList;
    }

    if (possibilities == 2) {
        vector<string> recipeShape;
        vector<Recipe> mirroredList;

        vector<string>::iterator it;

        for (int i = 0; i < 3; i++) {
            recipeShape.push_back(recipe.getData()[i][1]);
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 2; j >= 0; j--) {
                Recipe newRecipe = new Recipe(recipe.getRow(), recipe.getCol(), recipe.getHasil(), recipe.jumlah());
                mirroredList.push_back(newRecipe);
            }
        }
        return mirroredList;
    }
}

// Create mirrored recipes for recipes other than 3x3 ones
vector<Recipe> Crafting::createMirroredRecipe2(Recipe recipe);

// Create full recipe list
vector<Recipe> Crafting::createFullRecipeList(vector<Recipe> originalList) {
    vector<Recipe> recipeList;
    vector<Recipe> mirrorRecipeList;
    vector<Recipe>::iterator it;
    vector<Recipe>::iterator it2;

    for (it = originalList.begin(); it != originalList.end(); ++it) {
        if (it->getRow() == 3 && it->getCol() == 3) {
            mirrorRecipeList = createMirroredRecipe1(it);
            for (it2 = mirrorRecipeList.begin(); it2 != mirrorRecipeList.end(); ++it2) {
                recipeList.push_back(it2)
            }
        }

        if (it->getRow() == 1 && it->getCol() == 1) {
            mirrorRecipeList = createMirroredRecipe2(it);
            for (it2 = mirrorRecipeList.begin(); it2 != mirrorRecipeList.end(); ++it2) {
                recipeList.push_back(it2)
            }
        }

        if (it->getRow() == 2 && it->getCol() == 1) {
            mirrorRecipeList = createMirroredRecipe2(it);
            for (it2 = mirrorRecipeList.begin(); it2 != mirrorRecipeList.end(); ++it2) {
                recipeList.push_back(it2)
            }
        }
    }

    return recipeList;
}

void Crafting::Craft();
void Crafting::moveResulttoInventory();
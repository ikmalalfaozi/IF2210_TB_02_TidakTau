#include "crafting.hpp"
using namespace std;

Crafting::Crafting() : grid(0, vector<CraftingSlot>(0, CraftingSlot())) {
    this->rows = 0;
    this->cols = 0;
}

Crafting::Crafting(int rows, int cols) : grid(rows, vector<CraftingSlot>(cols, CraftingSlot())){
    int counter = 0;
    vector<vector<CraftingSlot>>::iterator it;
    vector<CraftingSlot>::iterator it2;
    for (it = this->grid.begin(); it != this->grid.end(); ++it) {
        for (it2 = it->begin(); it2 != it->end(); ++it2) {
            it2->setSlotID("C" + to_string(counter));
            counter++;
        }
    }
    this->rows = rows;
    this->cols = cols;
}


Crafting& Crafting::operator=(const Crafting& other) {
    this->grid = other.grid;
    return *this;
} 

CraftingSlot Crafting::getElmt(int i, int j) {
    return this->grid.at(i).at(j);
}

vector<vector<CraftingSlot>> Crafting::getGrid() {
    return this->grid;
}

// MASIH RUSAK

void Crafting::setElmt(int i, int j, CraftingSlot& value) {
    this->grid.at(i).at(j) = value;
} 

// Display grid
void Crafting::displayCraftingGrid() {
    vector<vector<CraftingSlot>>::iterator it;
    vector<CraftingSlot>::iterator it2;
    for (it = this->grid.begin(); it != this->grid.end(); ++it) {
        cout << "\t\t\t";
        for (it2 = it->begin(); it2 != it->end(); ++it2) {
            cout << "[" << it2->getItem()->getId() << ":" << it2->getQuantity() << "]\t";
        }
        cout << endl;
    }
}

// Test if items in the grid is the same with the recipe
bool Crafting::testRecipe(vector<Recipe> recipeList) {
    vector<Recipe>::iterator it;

    for (it = recipeList.begin(); it != recipeList.end(); ++it) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // INI HARUS NYAMAIN DATA RECIPE SAMA DATA CRAFTING SLOTS
                if ((*it).getDataElmt(i, j) != getElmt(i, j).getItem()->getType()) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

// Get the recipe information
Recipe Crafting::getRecipe(vector<Recipe> recipeList) {
    vector<Recipe>::iterator it;
    Recipe* ifNotFound = new Recipe();
    bool found = false;

    for (it = recipeList.begin(); it != recipeList.end(); ++it) {
        if (testRecipe(recipeList)) {
            found = true;
            return (*it);
        }
    }

    // throw "Recipe Not Found";
    return *ifNotFound;
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
    return -1;
}

// Create mirrored recipes for 3x3 recipes
vector<Recipe> Crafting::createMirroredRecipe(Recipe recipe) {
    int possibilities = findMirrorPossibilities(recipe);
    vector<Recipe> ifNotFound;
    if (possibilities == 1) {
        vector<Recipe> mirroredList;
        Recipe newRecipe(recipe.getRow(), recipe.getCol(), recipe.getHasilRecipe(), recipe.getJumlah());

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
        Recipe emptyRecipe(recipe.getRow(), recipe.getCol(), recipe.getHasilRecipe(), recipe.getJumlah());

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
        Recipe emptyRecipe(recipe.getRow(), recipe.getCol(), recipe.getHasilRecipe(), recipe.getJumlah());

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
        Recipe emptyRecipe(recipe.getRow(), recipe.getCol(), recipe.getHasilRecipe(), recipe.getJumlah());

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                emptyRecipe = createEmptyRecipe();
                emptyRecipe.setElemen(j, i, recipe.getDataElmt(0, 0));
                mirroredList.push_back(emptyRecipe);
            }
        }
        return mirroredList;
    }

    return ifNotFound;
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

/*
void Crafting::Craft(ItemList config, Inventory& inventory, vector<Recipe> recipeList) {
    recipeList = createFullRecipeList(recipeList);
    // If the recipe is corrent, craft the item
    if (testRecipe(recipeList)) {
        Recipe result = getRecipe(recipeList);
        bool possible = true;
        int resultQuantity = 0;
        string resultName = result.gethasilRecipe();
        while (possible) {
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    vector<CraftingSlot> gridRow = this->grid.at(x);
                    // If there's an item inside the grid, then decrease the amount
                    if (gridRow.at(y).getQuantity() != 0) {
                        // If the item quantity inside the grid is 0, then it's no longer possible to craft
                        if (gridRow.at(y).getQuantity() == 0) {
                            possible = false;
                        } else {
                            resultQuantity += result.getJumlah();
                            gridRow.at(y).setQuantity(gridRow.at(y).getQuantity() - 1);
                        }
                    }
                }
            }
        }
        int id = config.getConfigList()[resultName].getId();
        string varian = config.getConfigList()[resultName].getVarian();
        string category = config.getConfigList()[resultName].getCategory();
        if (category == "TOOL") {
            Tool* resultTool = new Tool(id, resultName, varian, 10);
        } else if (category == "NONTOOL") {
            NonTool* resultNonTool = new NonTool(id, resultName, varian);
        }

    } else {
        throw "Invalid Recipe";
    }
} */

/*
void Crafting::moveCraftingToInventory(string slotIDsrc, string slotIDdest) {

}

void Crafting::moveResulttoInventory(Inventory& inventory, Item* item, int resultQuantity) {
    inventory.giveItem(item, resultQuantity);
} */
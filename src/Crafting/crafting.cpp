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
    Recipe dummyRecipe;
    bool found = false;

    for (it = recipeList.begin(); it != recipeList.end(); ++it) {
        if (testRecipe(recipeList)) {
            found = true;
            return (*it);
        }
    }

    return dummyRecipe;
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
    // If recipe is 1x1, then it can create 9 different recipes
    if (recipe.getRow() == 1 && recipe.getCol() == 1) {
        return 9;
    }

    // If recipe is 2x1, then it can create 6 different recipes
    if (recipe.getRow() == 2 && recipe.getCol() == 1) {
        return 6;
    }

    // If recipe is 3x1, then it can create 3 different recipes
    if (recipe.getRow() == 3 && recipe.getCol() == 1) {
        return 3;
    }

    // If recipe is 3x2, then it can create 2 different recipes
    if (recipe.getRow() == 3 && recipe.getCol() == 2) {
        return 2;
    }

    // If recipe is 3x3, then it can create 1 different recipes
    if (recipe.getRow() == 3 && recipe.getCol() == 3) {
        return 1;
    }

    
    return -1;
}

// Create mirrored recipes for 3x3 recipes
vector<Recipe> Crafting::createMirroredRecipe(Recipe recipe) {
    int possibilities = findMirrorPossibilities(recipe);
    vector<Recipe> dummyRecipe;
    // Possibility = 2, recipe is 3x2
    if (possibilities == 2) {
        vector<Recipe> mirroredList;
        Recipe emptyRecipe(recipe.getRow(), recipe.getCol(), recipe.getHasilRecipe(), recipe.getJumlah());

        // Get recipe elements
        vector<string> recipeElmt;
        vector<string>::iterator it;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                recipeElmt.push_back(recipe.getDataElmt(i, j));
            }
        }

        // Create left oriented recipe
        emptyRecipe = createEmptyRecipe();
        for (int i = 0; i < 3; i++) {
            it = recipeElmt.begin();
            for (int j = 0; j < 2; j++) {
                if (it != recipeElmt.end()) {
                    emptyRecipe.setElemen(i, j, *it);
                    ++it;
                }
            }
        }
        mirroredList.push_back(emptyRecipe);

        // Create right oriented recipe
        emptyRecipe = createEmptyRecipe();
        for (int i = 0; i < 3; i++) {
            it = recipeElmt.begin();
            for (int j = 2; j  <= 0; j--) {
                if (it != recipeElmt.end()) {
                    emptyRecipe.setElemen(i, j, *it);
                    ++it;
                }
            }
        }
        mirroredList.push_back(emptyRecipe);

        return mirroredList;
    }

    // Possibility = 3, recipe is 3x1
    if (possibilities == 3) {
        vector<Recipe> mirroredList;
        Recipe emptyRecipe(recipe.getRow(), recipe.getCol(), recipe.getHasilRecipe(), recipe.getJumlah());

        // Get recipe elements
        vector<string> recipeElmt;
        vector<string>::iterator it;
        for (int i = 0; i < 3; i++) {
            recipeElmt.push_back(recipe.getDataElmt(i, 0));
        }

        // Iterate 3 times because there are 3 recipes
        for (int i = 0; i < 3; i++) {
            it = recipeElmt.begin();
            emptyRecipe = createEmptyRecipe();
            for (int j = 0; j < 3; j++) {
                if (it != recipeElmt.end()) {
                    emptyRecipe.setElemen(j, i, *it);
                }
            }
            mirroredList.push_back(emptyRecipe);
        }

        return mirroredList;
    }

    // Possibility = 6, recipe is 2x1
    if (possibilities == 6) {
        vector<Recipe> mirroredList;
        Recipe emptyRecipe(recipe.getRow(), recipe.getCol(), recipe.getHasilRecipe(), recipe.getJumlah());

        // Create recipe for the top half
        for (int i = 0; i < 3; i++) {
            emptyRecipe = createEmptyRecipe();
            for (int j = 0; j < 2; j++) {
                emptyRecipe.setElemen(j, i, recipe.getDataElmt(j, 0));
            }
            mirroredList.push_back(emptyRecipe);
        }
        
        // Create recipe for the bottom half
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

    // Possibility = 9, recipe is 1x1
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

    return dummyRecipe;
}

// Create full recipe list
vector<Recipe> Crafting::createFullRecipeList(vector<Recipe> originalList) {
    vector<Recipe> recipeList;
    vector<Recipe> mirrorRecipeList;
    vector<Recipe>::iterator it;
    vector<Recipe>::iterator it2;

    // Add recipes only if it's 3x3
    for (it = originalList.begin(); it != originalList.end(); ++it) {
        if ((it->getRow() == 3) && (it->getCol() == 3)) {
            recipeList.push_back(*it);
        }
    }

    // Iterate for the other recipes
    for (it = originalList.begin(); it != originalList.end(); ++it) {
        if (it->getRow() == 3 && it->getCol() == 2) {
            mirrorRecipeList = createMirroredRecipe(*it);
            for (it2 = mirrorRecipeList.begin(); it2 != mirrorRecipeList.end(); ++it2) {
                recipeList.push_back(*it2);
            }
        }

        if (it->getRow() == 3 && it->getCol() == 1) {
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

        if (it->getRow() == 1 && it->getCol() == 1) {
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
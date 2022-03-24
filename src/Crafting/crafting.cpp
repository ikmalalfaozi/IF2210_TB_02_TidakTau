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
bool Crafting::testRecipe(Recipe recipe) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << recipe.getDataElmt(i, j) << endl;
            cout << getElmt(i, j).getItem()->getVarian() << endl;
            if (recipe.getDataElmt(i, j) != getElmt(i, j).getItem()->getVarian()) {
                return false;
            }
        }
    }
    
    return true;
}

// Get the recipe information
Recipe Crafting::getRecipe(vector<Recipe> recipeList) {
    vector<Recipe>::iterator it;
    Recipe dummyRecipe(3, 3, "Dummy Recipe", 0);
    bool found = false;

    for (it = recipeList.begin(); it != recipeList.end(); ++it) {
        if (testRecipe(*it)) {
            found = true;
            return (*it);
        }
    }

    return dummyRecipe;
}

// Create an empty 3x3 recipe matrix
void Crafting::createEmptyRecipe(Recipe& recipe) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            recipe.setElemen(i, j, "-");
        }
    }
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
        int x;
        vector<Recipe> mirroredList;
        Recipe* emptyRecipe = new Recipe(3, 3, recipe.getHasilRecipe(), recipe.getJumlah());

        // Get recipe elements
        vector<string> recipeElmt;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                recipeElmt.push_back(recipe.getDataElmt(i, j));
            }
        }

        // Create left oriented recipe
        createEmptyRecipe(*emptyRecipe);
        x = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                emptyRecipe->setElemen(i, j, recipeElmt.at(x));
                x++;
            }
        }
        mirroredList.push_back(*emptyRecipe);

        // Create right oriented recipe
        createEmptyRecipe(*emptyRecipe);
        x = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 2; j > 0; j--) {
                emptyRecipe->setElemen(i, j, recipeElmt.at(x));
                x++;
            }
        }
        mirroredList.push_back(*emptyRecipe);
        delete emptyRecipe;
        return mirroredList;
    }

    // Possibility = 3, recipe is 3x1
    if (possibilities == 3) {
        vector<Recipe> mirroredList;
        Recipe* emptyRecipe = new Recipe(3, 3, recipe.getHasilRecipe(), recipe.getJumlah());

        // Get recipe elements
        vector<string> recipeElmt;
        vector<string>::iterator it;
        for (int i = 0; i < 3; i++) {
            recipeElmt.push_back(recipe.getDataElmt(i, 0));
        }

        // Iterate 3 times because there are 3 recipes
        for (int i = 0; i < 3; i++) {
            it = recipeElmt.begin();
            createEmptyRecipe(*emptyRecipe);
            int x = 0;
            for (int j = 0; j < 3; j++) {
                if (it != recipeElmt.end()) {
                    emptyRecipe->setElemen(j, i, recipeElmt.at(x));
                    x++;
                }
            }
            mirroredList.push_back(*emptyRecipe);
        }
        delete emptyRecipe;
        return mirroredList;
    }

    // Possibility = 6, recipe is 2x1
    if (possibilities == 6) {
        vector<Recipe> mirroredList;
        Recipe* emptyRecipe = new Recipe(3, 3, recipe.getHasilRecipe(), recipe.getJumlah());

        // Create recipe for the top half
        for (int i = 0; i < 3; i++) {
            createEmptyRecipe(*emptyRecipe);
            for (int j = 0; j < 2; j++) {
                emptyRecipe->setElemen(j, i, recipe.getDataElmt(j, 0));
            }
            mirroredList.push_back(*emptyRecipe);
        }
        
        // Create recipe for the bottom half
        for (int i = 0; i < 3; i++) {
            createEmptyRecipe(*emptyRecipe);
            int k = 0;
            for (int j = 1; j < 3; j++) {
                emptyRecipe->setElemen(j, i, recipe.getDataElmt(k, 0));
                k++;
            }
            mirroredList.push_back(*emptyRecipe);
        }
        delete emptyRecipe;
        return mirroredList;
    }

    // Possibility = 9, recipe is 1x1
    if (possibilities == 9) {
        vector<Recipe> mirroredList;
        Recipe* emptyRecipe = new Recipe(3, 3, recipe.getHasilRecipe(), recipe.getJumlah());
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                createEmptyRecipe(*emptyRecipe);
                emptyRecipe->setElemen(j, i, recipe.getDataElmt(0, 0));
                mirroredList.push_back(*emptyRecipe);
            }
        }
        delete emptyRecipe;
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
            //cout << "3x2 recipe"<< endl;
            mirrorRecipeList = createMirroredRecipe(*it);
            for (it2 = mirrorRecipeList.begin(); it2 != mirrorRecipeList.end(); ++it2) {
                //cout << "3x2 recipes list" << endl;
                //it2->printRecipe();
                recipeList.push_back(*it2);
            }
        }

        if (it->getRow() == 3 && it->getCol() == 1) {
            //cout << "3x1 recipe"<< endl;
            mirrorRecipeList = createMirroredRecipe(*it);
            for (it2 = mirrorRecipeList.begin(); it2 != mirrorRecipeList.end(); ++it2) {
                recipeList.push_back(*it2);
            }
        }

        if (it->getRow() == 2 && it->getCol() == 1) {
            //cout << "2x1 recipe"<< endl;
            mirrorRecipeList = createMirroredRecipe(*it);
            for (it2 = mirrorRecipeList.begin(); it2 != mirrorRecipeList.end(); ++it2) {
                recipeList.push_back(*it2);
            }
        }

        if (it->getRow() == 1 && it->getCol() == 1) {
            //cout << "1x1 recipe"<< endl;
            mirrorRecipeList = createMirroredRecipe(*it);
            for (it2 = mirrorRecipeList.begin(); it2 != mirrorRecipeList.end(); ++it2) {
                recipeList.push_back(*it2);
            }
        }        
    }

    return recipeList;
}
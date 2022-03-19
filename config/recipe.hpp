#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <string>
#include <vector>
using namespace std;

class Recipe
{
private:
    vector<vector<string>> recipe;
    int row;
    int column;
    string hasilRecipe;
    int jumlah;

public:
    Recipe();
    Recipe(int row, int column, string hasilRecipe, int jumlah);

    int getRow() const;
    int getCol() const;
    vector<vector<string>> getData() const;
    string gethasilRecipe() const;
    int getJumlah() const;

    void setElemen();
    void setElemen(int i, int j, string input);
    void setHasilRecipe(string hasilRecipe);
    void setJumlah(int jumlah);

    void printRecipe();
};

#endif
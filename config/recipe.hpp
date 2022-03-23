#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <string>
#include <vector>
using namespace std;

class Recipe
{
private:
    vector<vector<string>> recipe;
    int rows;
    int cols;
    string hasilRecipe;
    int jumlah;

public:
    Recipe();
    Recipe(int rows, int cols, string hasilRecipe, int jumlah);

    int getRow() const;
    int getCol() const;
    vector<vector<string>> getData() const;
    string getDataElmt(int i, int j) const;
    string getHasilRecipe() const;
    int getJumlah() const;

    void setRows(int rows);
    void setCols(int cols);
    void setElemen(int i, int j, string input);
    void setHasilRecipe(string hasilRecipe);
    void setJumlah(int jumlah);

    void printRecipe();
};

#endif
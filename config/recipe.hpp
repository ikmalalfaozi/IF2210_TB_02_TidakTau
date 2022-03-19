#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <string>
#include <vector>
using namespace std;

#define row 3
#define column 3

class Recipe
{
private:
    string recipe[row][column];
    string hasilRecipe;
    int jumlah;

public:
    Recipe();
    Recipe(string hasilRecipe, int jumlah);

    int getRow() const;
    int getCol() const;
    string getData() const;
    string gethasilRecipe() const;
    int getJumlah() const;

    void setElemen();
    void setElemen(int i, int j, string input);
    void setHasilRecipe(string hasilRecipe);
    void setJumlah(int jumlah);

    void printRecipe();
};

#endif
#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <string>
using namespace std;

class Recipe
{
private:
    int row, column;
    string *data;
    string hasil;
    int jumlah;

public:
    Recipe(int row, int column);
    Recipe(int row, int column, string hasil, int jumlah);
    Recipe(const Recipe &recipe);
    ~Recipe();

    void setElemen();
    void setElemen(int row, int column, string input);
    void setHasil(string hasil);
    void setJumlah(int jumlah);

    void printRecipe();
};

#endif
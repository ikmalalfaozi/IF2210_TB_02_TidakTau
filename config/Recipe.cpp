#include "recipe.hpp"
#include <iostream>

using namespace std;

Recipe::Recipe()
{
    this->hasilRecipe = "-";
    this->jumlah = 0;
}

Recipe::Recipe(string hasilRecipe, int jumlah)
{
    this->hasilRecipe = hasilRecipe;
    this->jumlah = jumlah;
}

int Recipe::getRow() const
{
    return row;
}

int Recipe::getCol() const
{
    return column;
}

Recipe Recipe::getData() const
{
    Recipe *matrikRecipe = new Recipe();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            matrikRecipe->recipe[i][j] = this->recipe[i][j];
        }
    }
    return *matrikRecipe;
}

string Recipe::gethasilRecipe() const
{
    return this->hasilRecipe;
}

int Recipe::getJumlah() const
{
    return this->jumlah;
}

void Recipe::setElemen()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cin >> recipe[i][j];
        }
    }
}

void Recipe::setElemen(int i, int j, string input)
{
    recipe[i][j] = input;
}

void Recipe::setHasilRecipe(string hasilRecipe)
{
    this->hasilRecipe = hasilRecipe;
}

void Recipe::setJumlah(int jumlah)
{
    this->jumlah = jumlah;
}

void Recipe::printRecipe()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cout << recipe[i][j] << "\t";
        }
        cout << endl;
    }
}
#include "recipe.hpp"
#include <iostream>

using namespace std;

Recipe::Recipe() : recipe(vector<vector<string>>(0, vector<string>(0, "-")))
{
    this->row = 0;
    this->column = 0;
    this->hasilRecipe = "-";
    this->jumlah = 0;
}

Recipe::Recipe(int row, int column, string hasilRecipe, int jumlah) : recipe(vector<vector<string>>(0, vector<string>(0, "-")))
{
    this->row = row;
    this->column = column;
    this->hasilRecipe = hasilRecipe;
    this->jumlah = jumlah;
}

int Recipe::getRow() const
{
    return this->row;
}

int Recipe::getCol() const
{
    return this->column;
}

vector<vector<string>> Recipe::getData() const
{
    return recipe;
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
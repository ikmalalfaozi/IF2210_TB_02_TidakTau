#include "recipe.hpp"
#include <iostream>

using namespace std;

Recipe::Recipe() : recipe(3, vector<string>(3, "-"))
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->recipe.at(i).at(j) = "-";
        }
    }
    this->rows = 0;
    this->cols = 0;
    this->hasilRecipe = "-";
    this->jumlah = 0;
}

Recipe::Recipe(int rows, int cols, string hasilRecipe, int jumlah) : recipe(vector<vector<string>>(rows, vector<string>(cols, "-")))
{
    this->rows = rows;
    this->cols = cols;
    this->hasilRecipe = hasilRecipe;
    this->jumlah = jumlah;
}

int Recipe::getRow() const
{
    return this->rows;
}

int Recipe::getCol() const
{
    return this->cols;
}

vector<vector<string>> Recipe::getData() const
{
    return this->recipe;
}

string Recipe::getDataElmt(int i, int j) const 
{
    vector<string> recipeRow = this->recipe.at(i);
    return recipeRow.at(j);
}


string Recipe::getHasilRecipe() const
{
    return this->hasilRecipe;
}

int Recipe::getJumlah() const
{
    return this->jumlah;
}

void Recipe::setElemen(int i, int j, string input)
{
    recipe.at(i).at(j) = input;
}

void Recipe::setRows(int rows) {
    this->rows = rows;
}

void Recipe::setCols(int cols) {
    this->cols = cols;
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
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            cout << this->recipe.at(i).at(j) << "\t";
        }
        cout << endl;
    }
}
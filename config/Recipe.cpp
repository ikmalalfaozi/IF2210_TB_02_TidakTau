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

string Recipe::getData() const
{
    return "a"; // belum tau bagaimana yang benar
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

int main()
{
    Recipe A, B;
    A.setElemen();
    B.setElemen();
    A.printRecipe();
    B.printRecipe();
}
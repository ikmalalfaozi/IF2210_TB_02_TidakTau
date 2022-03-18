#include "recipe.hpp"
#include <iostream>

Recipe::Recipe(int row, int column)
{
    this->row = row;
    this->column = column;
    this->data = new string[row * column];
}

Recipe::Recipe(int row, int column, string hasil, int jumlah)
{
    this->row = row;
    this->column = column;
    this->data = new string[row * column];
    this->hasil = hasil;
    this->jumlah = jumlah;
}
Recipe::Recipe(const Recipe &r)
{
    this->row = r.row;
    this->column = r.column;
    this->data = new string[row * column];
    for (int i = 0; i < row * column; i++)
    {
        data[i] = r.data[i];
    }
    this->hasil = r.hasil;
    this->jumlah = r.jumlah;
}

Recipe::~Recipe()
{
    delete[] data;
}

void Recipe::setElemen()
{
    for (int i = 0; i < this->row * this->column; i++)
    {
        string input;
        cin >> input;
        data[i] = input;
    }
}

void Recipe::setElemen(int row, int column, string input)
{
    this->data[row * 3 + column] = input;
}

void Recipe::setHasil(string hasil)
{
    this->hasil = hasil;
}

void Recipe::setJumlah(int jumlah)
{
    this->jumlah = jumlah;
}

void Recipe::printRecipe()
{
    for (int i = 0; i < this->row * this->column; i++)
    {
        if (i == 0)
        {
            cout << data[i] << " ";
        }
        else if (i % (this->row) != 0)
        {
            cout << data[i] << " ";
        }
        else
        {
            cout << data[i] << endl;
        }
    }
}
#include "Inventory.hpp"
#include <iostream>
#include <string>

using namespace std;

Inventory::Inventory(){}

Inventory::Inventory(Inventory& other){
    for (int i = 0; i < sizeof(other); i++){
        for (int j = 0; j < sizeof(other); j++){
            this->itemchest[i][j] = other.itemchest[i][j];
        }
    }
}

Inventory::~Inventory(){
    delete this->itemchest;
}

void Inventory::addItem(int item, int quantity){

}

void Inventory::deleteItem(int slotID, int quantity){
    
}

void Inventory::stackItem(int slotIDsrc, int slotIDdest){
    
}

void Inventory::useItem(int slotID){
    
}
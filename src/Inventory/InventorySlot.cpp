// -----------InventorySlot implementation-------------
#include "InventorySlot.hpp"
#include <iostream>
#include <string>

using namespace std;

template<class T>
InventorySlot<T>::InventorySlot(){
    this->slotID = "II";
    NonTool* itemdefault = new NonTool(0, "-", "-");
    this->item = itemdefault;
    this->quantity = 0;
}

template<class T>
InventorySlot<T>& InventorySlot<T>::operator=(const InventorySlot<T>& ivslot){
    this->slotID = ivslot.slotID;
    this->quantity = ivslot.quantity;
    this->item = ivslot.item;
    return *this;
}

template<class T>
void InventorySlot<T>::set_slotID(string slotid){
    this->slotID = slotid;
}

template<class T>
void InventorySlot<T>::set_item(T item){
    this->item = item;
}

template<class T>
void InventorySlot<T>::set_quantity(int quantity){
    this->quantity = quantity;
}

template<class T>
string InventorySlot<T>::get_slotID() const{
    return this->slotID;
}

template<class T>
T InventorySlot<T>::get_item() const{
    return this->item;
}

template<class T>
int InventorySlot<T>::get_quantity() const{
    return this->quantity;
}
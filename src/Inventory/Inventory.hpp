#ifndef INVENTORY_H
#define INVENTORY_H
#define CAPACITY 27
#include <string>
#include <variant>
#include "Item.hpp"

// BELUM SELESAI

class Inventory {
private:
    int activesize;
    InventorySlot* itemlist;
public:
    Inventory();
    Inventory(Inventory&);
    ~Inventory();
    void addItem(variant<Item, Tool, NonTool> item, int quantity);// Menambah item ke inventory
    void deleteItem(string slotID, int quantity); // Membuang item dari inventory
    void stackItem(string slotIDsrc, string slotIDdest); // Menumpuk item non tool yang sama pada inventory
    void useItem(int slotID); // Menggunakan item
};

// Tahap perencanaan
class InventorySlot {
    private:
        // Karena kelas item belum ada, 
        // sementara pakai tipe data integer
        string slotID;
        variant<Item, Tool, NonTool> item;
        int quantity;
    public:
        InventorySlot();

        InventorySlot& operator=(const InventorySlot&);

        void set_slotID(string slotid);
        void set_item(variant<Item, Tool, NonTool>& itemid);
        void set_quantity(int quantity);

        string get_slotID() const;
        variant<Item, Tool, NonTool>& get_item();
        int get_quantity() const;
};

#endif
#ifndef INVENTORY_H
#define INVENTORY_H
#define CAPACITY 27
#include <string>

// BELUM SELESAI

class Inventory {
private:
    int activesize;
    InventorySlot* itemlist;
public:
    Inventory();
    Inventory(Inventory&);
    ~Inventory();
    void addItem(int itemID, int quantity);// Menambah item ke inventory
    void deleteItem(int slotID, int quantity); // Membuang item dari inventory
    void stackItem(int slotIDsrc, int slotIDdest); // Menumpuk item non tool yang sama pada inventory
    void useItem(int slotID); // Menggunakan item
};

// Tahap perencanaan
class InventorySlot {
    private:
        // Karena kelas item belum ada, 
        // sementara pakai tipe data integer
        string slotID;
        int itemID;
        int quantity;
    public:
        InventorySlot();

        void set_slotID(string slotid);
        void set_itemID(int itemid);
        void set_quantity(int quantity);

        string get_slotID() const;
        int get_itemID() const;
        int get_quantity() const;
};

#endif
#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>

// BELUM SELESAI

class Inventory {
private:
    InventorySlot itemchest[3][9];
public:
    Inventory();
    Inventory(Inventory&);
    ~Inventory();
    void addItem(int item, int quantity);// Menambah item ke inventory
    void deleteItem(int slotID, int quantity); // Membuang item dari inventory
    void stackItem(int slotIDsrc, int slotIDdest); // Menumpuk item non tool yang sama pada inventory
    void useItem(int slotID); // Menggunakan item
};

// Tahap perencanaan
class InventorySlot : public Inventory {
    private:
        // Karnea kelas item belum ada, 
        // sementara pakai tipe data integer
        int item;
        string slotID;
};

#endif
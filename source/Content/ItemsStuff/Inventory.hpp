#ifndef INVENTORY
#define INVENTORY

constexpr int INV_SIZE_ROW = 8;
constexpr int INV_SIZE_COL = 5;

#include "Coins.hpp"
#include "Item.hpp"
#include "Items/ItemRegister.hpp"

class Cell {
public:
	std::unique_ptr<Item> mItem;

	bool isEmpty() const { return mItem == nullptr; }
	void unique_swap(std::unique_ptr<Item>& item) {	mItem.swap(item);}
	void removeItem() { mItem.reset(); }
};

class Inventory {
private:
	std::vector<Cell> mInventory;
	Coins m_Coins;

public:
	Inventory();
	virtual ~Inventory();

	size_t getSize();

	const std::string getInfo() const;
	inline const Coins& getCoins() { return m_Coins; }

	// return true if item fully moved to slot/free slo
	// return false if item was stacked by half 
	// (im mean	what this item still exist with another amount)
	bool addItem(Item& item);

	bool removeItemByID(uint32_t id);
	bool removeItemByItem(Item& item);
};

#endif /* INVENTORY */

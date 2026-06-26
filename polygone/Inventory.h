#ifndef POLY_INVENTORY_HPP
#define POLY_INVENTORY_HPP

#include "Header.h"
class Item {
private:
	std::string name;
	std::string textureName;
	int32_t price;
	int16_t count;
	int16_t maxAmmount;
	uint32_t mID;
	bool mStackable;
	bool isUsable;
public:
	Item() {}

	bool isStackable() const { return mStackable; }
	uint32_t getID() const { return mID; }
	int16_t getAmmount() const { return count; }
	int16_t getMaxAmmount() const { return maxAmmount; }

	// return false if item fully stacked
	// return true if item have some amount
	bool addAmount(Item& item) {
		auto amount = item.getAmmount();
		auto overflowAmount = count + amount - maxAmmount;
		if (overflowAmount > 0) {
			count += amount - overflowAmount;
			item.setAmmount(overflowAmount);
			return true;
		} else
			count += amount;

		return false;
	}

	void setAmmount(int16_t ammount) noexcept { count = ammount; }
};

class Cell {

public:
	std::unique_ptr<Item> mItem;

	bool isEmpty() const { return mItem == nullptr; }
	void  removeItem() { mItem.reset(); }
};

class Inventory {
private:
	short sizeX, sizeY;
	std::vector<Cell> mInventory;

public:
	Inventory();
	virtual ~Inventory();

	size_t getSize();


	// return true if item fully moved to slot/free slo
	// return false if item was stacked by half 
	// (im mean	what this item still exist with another amount)
	bool addItem(Item& item);
	bool removeItemByID(uint32_t id);
	bool removeItemByItem(Item& item);
};

#endif
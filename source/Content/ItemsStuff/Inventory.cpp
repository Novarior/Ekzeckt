
#include "Inventory.hpp"

Inventory::Inventory() {
	int nsize = INV_SIZE_ROW * INV_SIZE_COL;
	mInventory.resize(nsize);
}

Inventory::~Inventory() {}

size_t Inventory::getSize() {
	return mInventory.size();
}

const std::string Inventory::getInfo() const {
	std::string ss;

	ss.clear();
	ss.append("Current vecSize: ").append(std::to_string(mInventory.size())).append("\n");
	for (int it = 0; it < mInventory.size(); it++) {

		if (!mInventory[it].isEmpty() && mInventory[it].mItem != nullptr)
			ss.append("vIndex: ").append(std::to_string(it)).append(" exist Item: ").append(mInventory[it].mItem.get()->getName()).append("\n");
		else if (mInventory[it].isEmpty())
			ss.append("vIndex: ").append(std::to_string(it)).append(" isEmpty\n");
		else
			ss.append("vIndex: ").append(std::to_string(it)).append(" Cell Exist with item\n");
	}

	return ss;
}

bool Inventory::addItem(Item& item) {
	// if item is stackable
	Cell* firstFreeSlot = nullptr;
	bool firstFree = false;
	if (item.isStackable()) {
		for (auto& slot : mInventory) {
			if (slot.isEmpty()) {
				if (!firstFree) {
					firstFree = !firstFree;
					firstFreeSlot = &slot;
				}
				continue;
			}

			if (slot.mItem->getID() != item.getID())
				continue;

			if (slot.mItem->getAmount() == slot.mItem->getMaxAmount())
				continue;

			if (slot.mItem->addAmount(item))
				continue;

			// item wass fully moved to slot
			return true;
		}
	} else {
		// else item is not stackable forund first free position
		for (auto& slot : mInventory)
			if (slot.isEmpty()) {
				slot.mItem = std::make_unique<Item>(item);

				return true;
			}
	}

	return false; // inventory is Full
}

bool Inventory::removeItemByID(uint32_t ID) {
	// find item on vec using ID as reference
	auto it = std::find_if(mInventory.begin(), mInventory.end(), [ID](Cell& slot) {
		return slot.mItem.get()->getID() == ID;
	});

	if (it != mInventory.end()) {
		it->removeItem();
		// Item was deleted
		return true;
	}
	return false; // Item with this ID not found
}

bool Inventory::removeItemByItem(Item& item) {
	// find item on vec using item as reference
	auto it = std::find_if(mInventory.begin(), mInventory.end(), [item](Cell& slot) {
		return slot.mItem.get() == &item;
	});

	if (it != mInventory.end()) {
		it->removeItem();
		// Item was deleted
		return true;
	}
	// item not Found
	return false;
}

//#include "Inventory.h"
//
//Inventory::Inventory() {
//	int nsize = INV_SIZE_ROW * INV_SIZE_COL;
//	mInventory.resize(nsize);
//}
//
//Inventory::~Inventory() {}
//
//size_t Inventory::getSize() {
//	return mInventory.size();
//}
//
//const std::string Inventory::getInfo() const {
//	std::string ss;
//
//	ss.clear();
//	ss.append("Current vecSize: ").append(std::to_string(mInventory.size())).append("\n");
//	for (int it = 0; it < mInventory.size(); it++) {
//
//		if (!mInventory[it].isEmpty() && mInventory[it].mItem != nullptr)
//			ss.append("vIndex: ").append(std::to_string(it)).append(" exist Item: ").append(mInventory[it].mItem.get()->getName()).append("\n");
//		else if (mInventory[it].isEmpty())
//			ss.append("vIndex: ").append(std::to_string(it)).append(" isEmpty\n");
//		else
//			ss.append("vIndex: ").append(std::to_string(it)).append(" Cell Exist with item\n");
//	}
//
//	return ss;
//}
//
//bool Inventory::addItem(Item& item) {
//	// if item is stackable
//	Cell* firstFreeSlot = nullptr;
//	bool firstFree = false;
//	if (item.isStackable()) {
//		for (auto& slot : mInventory) {
//			if (slot.isEmpty()) {
//				if (!firstFree) {
//					firstFree = !firstFree;
//					firstFreeSlot = &slot;
//				}
//				continue;
//			}
//
//			if (slot.mItem->getID() != item.getID())
//				continue;
//
//			if (slot.mItem->getAmmount() == slot.mItem->getMaxAmmount())
//				continue;
//
//			if (slot.mItem->addAmount(item))
//				continue;
//
//			// item wass fully moved to slot
//			return true;
//		}
//	} else {
//		// else item is not stackable forund first free position
//		for (auto& slot : mInventory)
//			if (slot.isEmpty()) {
//				slot.mItem = std::make_unique<Item>(item);
//
//				return true;
//			}
//	}
//
//	return false; // inventory is Full
//}
//
//bool Inventory::removeItemByID(uint32_t ID) {
//	// find item on vec using ID as reference
//	auto it = std::find_if(mInventory.begin(), mInventory.end(), [ID](Cell& slot) {
//		return slot.mItem.get()->getID() == ID;
//	});
//
//	if (it != mInventory.end()) {
//		it->removeItem();
//		// Item was deleted
//		return true;
//	}
//	return false; // Item with this ID not found
//}
//
//bool Inventory::removeItemByItem(Item& item) {
//	// find item on vec using item as reference
//	auto it = std::find_if(mInventory.begin(), mInventory.end(), [item](Cell& slot) {
//		return slot.mItem.get() == &item;
//	});
//
//	if (it != mInventory.end()) {
//		it->removeItem();
//		// Item was deleted
//		return true;
//	}
//	// item not Found
//	return false;
//}
#include "Inventory.h"

Inventory::Inventory() {}

Inventory::~Inventory() {}

size_t Inventory::getSize() {
	return mInventory.size();
}

bool Inventory::addItem(Item& item) {
	// if item is stackable
	if (item.isStackable())
		for (auto& slot : mInventory) {
			if (slot.isEmpty())
				continue;

			if (slot.mItem->getID() != item.getID())
				continue;

			if (slot.mItem->getAmmount() == slot.mItem->getMaxAmmount())
				continue;

			if (slot.mItem->addAmount(item))
				continue;

			// item wass fully moved to slot
			return true;
		}

	// else item is not stackable forund first free position
	for (auto& slot : mInventory)
		if (!slot.isEmpty()) {
			slot.mItem.reset(&item);
			return true;
		}

	return false; // Инвентарь заполнен
}

bool Inventory::removeItemByID(uint32_t ID) {
	auto it = std::find_if(mInventory.begin(), mInventory.end(), [ID](std::unique_ptr<Item> slot) {
		return slot && slot->getID() == ID;
	});

	if (it != mInventory.end()) {
		it->removeItem();
		return true;
	}

	return false; // Предмет с таким ID не найден
}

bool Inventory::removeItemByItem(Item& item) {
	auto it = std::remove(mInventory.begin(), mInventory.end(), [item](std::unique_ptr<Item> slot) {
		return slot.get() == item;
	});
	std::remove_if

	return false;
}`
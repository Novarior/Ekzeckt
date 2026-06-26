#ifndef ITEMREGISTER
#define ITEMREGISTER

#include "../../../core/tools/LOGGER.hpp"
#include "../Item.hpp"
#include "all_items.hpp"

class ItemRegistry {
private:
	static std::map<int, std::shared_ptr<Item>> items;

public:
	static bool registerItem(int id, std::shared_ptr<Item> item) {
		if (items.find(id) == items.end()) {
			unsigned int itemID = item->getID();
			for (const auto& pair : items) {
				if (pair.second->getID() == itemID && id != itemID) {
					Logger::logStatic("Collision detected: Item with ID " + std::to_string(itemID) + " already exists with a different registry key: " + std::to_string(pair.first), "ItemRegistry", logType::LWARNING);
					return false;
				}
			}

			items[id] = item;
			Logger::logStatic("Item with id: " + std::to_string(id) + " has been registered", "ItemRegistry", logType::LINFO);
			return true;
		} else {
			Logger::logStatic("Item with id: " + std::to_string(id) + " alredy was bew registered", "ItemRegistry", logType::LWARNING);
			return false; // Item with this ID already exists
		}
	}

	static std::shared_ptr<Item> getItem(int id) {
		auto it = items.find(id);
		if (it != items.end())
			return it->second; // Возвращаем
		else
			return items[0]; // Return a default item if not found
	}

	static const std::map<int, std::shared_ptr<Item>>& getAllItems() { return items; }

	static void unregisterItem(int id) { items.erase(id); }

	static bool containsItem(int id) { return items.find(id) != items.end(); }
};

#endif /* ITEMREGISTER */

#ifndef ITEM_HPP
#define ITEM_HPP

#include "../../core/dataCollector/_man_Texture.hpp"
#include "Coins.hpp"

class Item {
protected:
	struct ItemData {
		std::string m_name = "";
		int16_t m_amount = -1;
		int16_t m_maxAmount = -1;
		int16_t durability = -1;
		int16_t maxDurability = -1;
		int32_t m_itemID = -1;
		bool m_pickable = false;
		bool m_stackable = false;
		bool m_usable = false;

		// Flag for delete from inventory
		// when item is used and when amount is 0
		bool flagForDeleteFromInventory = false;
	} iData;

	Coins m_price;
	sf::Texture& m_texture;
public:
	Item(uint32_t id = 0, const std::string& name = "NULL",
		 bool pickable = false, bool stackable = false, bool usable = false,
		 int amount = 0, int16_t maxAmount = 0, int16_t durability = 0,
		 int16_t maxDurability = 0, const Coins& price = {0, 0, 0},
		 sf::Texture& texture = TextureManager::getTexture("items_NULL")): m_texture(texture), m_price(price) {
		iData.m_name = name;
		iData.m_itemID = id;
		iData.m_pickable = pickable;
		iData.m_stackable = stackable;
		iData.m_usable = usable;
		iData.m_amount = amount;
		iData.m_maxAmount = maxAmount;
	}
	Item(ItemData _data, const Coins& price = {0, 0, 0},
		 sf::Texture& texture = TextureManager::getTexture("items_NULL")):iData(_data), m_texture(texture), m_price(price) {}

	virtual ~Item() noexcept = default;

	const sf::Texture& getTexture() { return m_texture; }

	// Modifiers
	void addAmount(int16_t _amount) noexcept {
		iData.m_amount = std::min(static_cast<int>(iData.m_maxAmount), iData.m_amount + iData.m_amount);
	}
	void removeAmount(int16_t _amount) noexcept {
		iData.m_amount = std::max(0, iData.m_amount - iData.m_amount);
		if (iData.m_amount == 0)
			iData.flagForDeleteFromInventory = true;
	}

	/// item is stackable?
	inline const bool isStackable() const noexcept { return iData.m_stackable; }
	///  get ID of item
	inline const int32_t getID() const noexcept { return iData.m_itemID; }
	/// get amount of item
	inline const int16_t getAmount() const noexcept { return iData.m_amount; }
	/// get max amount of item
	inline const int16_t getMaxAmount() const noexcept { return iData.m_maxAmount; }
	///  get name of item
	inline const std::string getName() const noexcept { return iData.m_name; }
	/// item is usable?
	bool isUsable() const noexcept { return iData.m_usable; }
	/// item is pickable?
	bool isPickable() const noexcept { return iData.m_pickable; }
	/// get "price" of item
	const Coins& getPrice() const noexcept { return m_price; }


	// return false if item fully stacked
	// return true if item have some amount
	bool addAmount(Item& item) noexcept {
		auto amount = item.getAmount();
		auto overflowAmount = iData.m_amount + amount - iData.m_maxAmount;
		if (overflowAmount > 0) {
			iData.m_amount += amount - overflowAmount;
			item.setAmmount(overflowAmount);
			return true;
		} else
			iData.m_amount += amount;

		return false;
	}


	/// get self as shared_ptr<Item> for next interactions after
	/// @return shared_ptr<Item>
	/// @note for example: when you use item, you need to get self item
	std::shared_ptr<Item> getSelf() noexcept { return std::make_shared<Item>(*this); }

	// Setters
	void setID(const int32_t ID) noexcept { iData.m_itemID = ID; }
	void setName(const std::string& _val) noexcept { iData.m_name = _val; }
	void setDurability(const int16_t _val)noexcept { iData.durability = _val; }
	void setAmmount(const int16_t ammount) noexcept { iData.m_amount = ammount; }
	void setPickable(const bool pickable) noexcept { iData.m_pickable = pickable; }
	void setStackable(const bool stackable) noexcept { iData.m_stackable = stackable; }

	virtual void useItem() {}
	virtual void update(float delta_time) {}
	virtual void update(float delta_time, sf::Vector2i mouse_pos) {}
};

#endif /* ITEM */

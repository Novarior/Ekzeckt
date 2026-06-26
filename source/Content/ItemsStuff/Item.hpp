#ifndef ITEM_HPP
#define ITEM_HPP
#include "../../core/dataCollector/_man_Texture.hpp"
#include "../../core/header.h"
#include "Coins.hpp"
#include "itemtextures.hpp"

class Item {
public:
	Item(unsigned int id = 0, const std::string& name = "NULL",
		 bool pickable = false, bool stackable = false, bool usable = false,
		 int amount = 0, unsigned maxAmount = 0, int durability = 0,
		 int maxDurability = 0, const Coins& price = {0, 0, 0},
		 const sf::Texture& texture = TextureManager::getTexture("items_NULL")) {
		iINFO.m_name = name;
		iINFO.item_ID = id;
		iData.m_pickable = pickable;
		iData.m_stackable = stackable;
		iData.m_usable = usable;
		iData.m_amount = amount;
		iData.m_maxAmount = maxAmount;
		m_price = price;
	}

	virtual ~Item() noexcept = default;

	// Modifiers
	void addAmount(int _amount) noexcept {
		iData.m_amount = std::fmin(static_cast<int>(iData.m_maxAmount), iData.m_amount + iData.m_amount);
	}
	void removeAmount(int _amount) noexcept {
		iData.m_amount = std::fmax(0, iData.m_amount - iData.m_amount);
		if (iData.m_amount == 0)
			iData.flagForDeleteFromInventory = true;
	}

	// Getters
	/// @brief get ID of item
	/// @return unsigned int
	unsigned int getID() const noexcept { return iINFO.item_ID; }

	/// @brief get name of item
	/// @return std::string
	const std::string& getName() const noexcept { return iINFO.m_name; }

	/// @brief get amount of item
	/// @return int
	int getAmount() const noexcept { return iData.m_amount; }

	/// @brief get max amount of item
	int getMaxAmount() const noexcept { return iData.m_maxAmount; }

	/// @brief item is pickable?
	bool isPickable() const noexcept { return iData.m_pickable; }

	/// @brief item is stackable?
	bool isStackable() const noexcept { return iData.m_stackable; }

	/// @brief item is usable?
	bool isUsable() const noexcept { return iData.m_usable; }

	/// @brief get "price" of item
	/// @return Coins
	Coins& getPrice() noexcept { return m_price; }

	/// @brief get self item for next interactions after
	/// @return shared_ptr<Item>
	/// @note for example: when you use item, you need to get self item
	std::shared_ptr<Item> getSelf() noexcept {
		return std::make_shared<Item>(*this);
	}

	// Setters
	void setID(unsigned int ID) noexcept { iINFO.item_ID = ID; }
	void setName(const std::string& name) noexcept { iINFO.m_name = name; }
	void setAmount(int amount) noexcept { iData.m_amount = amount; }
	void setPickable(bool pickable) noexcept { iData.m_pickable = pickable; }
	void setStackable(bool stackable) noexcept { iData.m_stackable = stackable; }

	virtual void useItem() {}
	virtual void update(float delta_time, sf::Vector2i mouse_pos) {}
	virtual void render(sf::RenderTarget& target) noexcept { target.draw(m_item_shape); }

	inline void setPosition(sf::Vector2f position) noexcept { m_item_shape.setPosition(position); }
	inline void setSize(sf::Vector2f size) noexcept { m_item_shape.setSize(size); }

protected:
	struct ItemLINFO {
		std::string m_name;
		unsigned int item_ID;
	} iINFO;

	struct ItemData {
		bool m_pickable;
		bool m_stackable;
		bool m_usable;
		int m_amount;
		int m_maxAmount;
		int durability;
		int maxDurability;

		// Flag for delete from inventory
		// when item is used and when amount is 0
		bool flagForDeleteFromInventory = false;
	} iData;

	Coins m_price;

	sf::RectangleShape m_item_shape;
};

#endif /* ITEM */

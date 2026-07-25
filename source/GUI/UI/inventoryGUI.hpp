#ifndef INVENTORYGUI
#define INVENTORYGUI


#include "../../Content/ItemsStuff/Inventory.hpp"
//#include "../components/button.hpp"
//#include "checkbox.hpp"
//#include "progressBar.hpp"
//#include "../tools/textbox.hpp

namespace gui {
class InventoryGUI: public sf::Drawable {
private:
	struct definid {
		sf::Color COL_SLOTSHAPE;

	}mDefs;

	struct InventorySlot {
		sf::RectangleShape shapeBack;
		sf::Sprite* spriteItem = nullptr;

		uint16_t id;
	} sSlot;

	std::weak_ptr<Inventory> m_inventory;

	bool isOpen;

	// main constructions 
	sf::RectangleShape m_background, m_headerBackground;
	std::vector<InventorySlot> vSlots;

	void initBackground(sf::Vector2f screenSize, sf::Vector2<uint16_t> _size);
	void initHeader(sf::Vector2<uint16_t> _size);
	void initSlots(sf::Vector2<uint16_t> _size);
	//void initCapacityLINFO();
	//void initCurrencyLINFO();

public:
	InventoryGUI(sf::Vector2f screenSize, sf::Font& font, std::shared_ptr<Inventory> inv, unsigned int characterSize = 16);
	virtual ~InventoryGUI();

	void linkInventory(std::shared_ptr<Inventory> inv);

	void update(const sf::Vector2i& mousePos);
	//void handleEvent(const sf::Event& event, const sf::Vector2i& mousePos);

	inline bool isVisible() const { return isOpen; }
	inline void setVisible(const bool val) { isOpen = val; }
	inline void toggleVisible() { isOpen = !isOpen; }



	// render
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
} // namespace GUI

#endif /* INVENTORYGUI */

#include "inventoryGUI.hpp"

void gui::InventoryGUI::initBackground(sf::Vector2f screenSize, sf::Vector2<uint16_t> _size) {
	float sumShapeSize = 50.f;
	float offset = 20.f;

	sf::Vector2f size(offset / 2.f + sumShapeSize * _size.x, offset * 1.5 + sumShapeSize * _size.y);
	sf::Vector2f position(30.f, 30.f);

	// basic bg
	m_background.setSize(size);
	m_background.setPosition(position);
	m_background.setFillColor(sf::Color(30, 30, 35, 230));
	m_background.setOutlineThickness(1.f);
	m_background.setOutlineColor(sf::Color(100, 100, 100));

	// head bg
	m_headerBackground.setSize(sf::Vector2f(size.x, 20.f));
	m_headerBackground.setPosition(position);
	m_headerBackground.setFillColor(sf::Color(40, 40, 45, 255));
}

void gui::InventoryGUI::initHeader(sf::Vector2<uint16_t> _size) {}

void gui::InventoryGUI::initSlots(sf::Vector2<uint16_t> _size) {
	float spacing = 10.f;
	float sizeshape = 40.f;

	sf::Vector2f offset = {m_headerBackground.getPosition().x + spacing , m_headerBackground.getPosition().y + m_headerBackground.getSize().y + spacing};

	mDefs.COL_SLOTSHAPE = {100, 100, 100, 50};
	sf::RectangleShape shape;
	shape.setSize({sizeshape,sizeshape});
	shape.setFillColor(mDefs.COL_SLOTSHAPE);
	shape.setOutlineColor(sf::Color(180, 120, 0));
	shape.setOutlineThickness(-2.f);
	int sizei = _size.x * _size.y;

	InventorySlot tempSlot;

	for (size_t it = 0; it < sizei; it++) {
		shape.setPosition({offset.x + (sizeshape * 1.25f * (it % _size.x)), offset.y + (sizeshape * 1.25f * std::floorf(it / _size.x))});
		tempSlot.shapeBack = shape;
		tempSlot.id = it;
		vSlots.push_back(tempSlot);
	}
}

gui::InventoryGUI::InventoryGUI(sf::Vector2f screenSize, sf::Font& font, std::shared_ptr<Inventory> inv, unsigned int characterSize) {
	isOpen = true;
	sf::Vector2<uint16_t> size(INV_SIZE_ROW, INV_SIZE_COL);
	initBackground(screenSize,size);
	initHeader(size);
	initSlots(size); 
	linkInventory(inv);
}

gui::InventoryGUI::~InventoryGUI() {
	vSlots.clear();
}


void gui::InventoryGUI::update(const sf::Vector2i& mousePos) {
	sf::Color modcolor = mDefs.COL_SLOTSHAPE;
	modcolor.a += 30;

	for (auto& slot : vSlots) {
		slot.shapeBack.setFillColor(mDefs.COL_SLOTSHAPE);
		if (slot.shapeBack.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
			slot.shapeBack.setFillColor(modcolor);
		}
	}
}

void gui::InventoryGUI::linkInventory(std::shared_ptr<Inventory> inv) {
	m_inventory = inv;
	int sizeshape = 40;
	sf::IntRect irect({0,0}, {sizeshape,sizeshape});


	for (int i = 0; i < vSlots.size(); i++) {
		auto& it = inv.get()->getSlotByID(i);

		if (!it.isEmpty()) {
			vSlots[i].spriteItem = new sf::Sprite(it.mItem->getTexture(), irect);
			vSlots[i].spriteItem->setPosition(vSlots[i].shapeBack.getPosition());
		}
	}
}

void gui::InventoryGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(m_background, states);
	target.draw(m_headerBackground, states);

	for (auto& it : vSlots) {
		target.draw(it.shapeBack, states);

		if (it.spriteItem != nullptr)
			target.draw(*it.spriteItem, states);
	}
}

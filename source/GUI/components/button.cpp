#include "button.hpp"

gui::Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, unsigned int id)
	:mText(*FontManager::getFont(FontID::FONT_GAMEF_01), text, 32U), mID(id) {
	mState = ComponentState::CS_IDLE;

	mData.position = position;
	mData.size = size;
	//mData.font = FontManager::getFont(FontID::FONT_GAMEF_01);
	mData.characterSize = 32U;
	mData.isActive = true;


	mShape.setPosition(sf::Vector2f(position.x, position.y));
	mShape.setSize(sf::Vector2f(size.x, size.y));
	mShape.setFillColor(mColors.shapeIdleColor);
	mShape.setOutlineThickness(-1.f);
	mShape.setOutlineColor(mColors.outlineIdleColor);
	
	mText.setFillColor(mColors.textIdleColor);
	mText.setPosition({mData.position.x + (mData.size.x / 2.f) - mText.getGlobalBounds().size.x / 2.f,
					 mData.position.y + mData.size.y / 2 - mText.getGlobalBounds().size.y});
}

void gui::Button::update(const sf::Vector2f& mousePosWindow) {
	if (!mData.isActive) {
		mState = ComponentState::CS_DISABLED;
		return;
	}

	mState = ComponentState::CS_IDLE;
	if (mShape.getGlobalBounds().contains(mousePosWindow)) {
		mState = ComponentState::CS_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			mState = ComponentState::CS_ACTIVE;
	}

	updateColor();
}

void gui::Button::setPosition(const sf::Vector2f pos) {
	mShape.move(pos);
	mText.move(pos);
}

void gui::Button::updateColor() {
	switch (mState) {
	case ComponentState::CS_IDLE:
		mShape.setFillColor(mColors.shapeIdleColor);
		mShape.setOutlineColor(mColors.outlineIdleColor);
		mText.setFillColor(mColors.textIdleColor);
		break;

	case ComponentState::CS_HOVER:
		mShape.setFillColor(mColors.shapeHoverColor);
		mShape.setOutlineColor(mColors.outlineHoverColor);
		mText.setFillColor(mColors.textHoverColor);
		break;

	case ComponentState::CS_ACTIVE:
		mShape.setFillColor(mColors.shapeActiveColor);
		mShape.setOutlineColor(mColors.outlineActiveColor);
		mText.setFillColor(mColors.textActiveColor);
		break;

	case ComponentState::CS_DISABLED:
		mShape.setFillColor(mColors.shapeDisableColor);
		mShape.setOutlineColor(mColors.outlineDisableColor);
		mText.setFillColor(mColors.textDisableColor);
		break;
	}
}

void gui::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mShape, states);
	target.draw(mText, states);
}

const unsigned int gui::Button::getID() const { return mID; }
void gui::Button::setID(const unsigned int val) { mID = val; }
void gui::Button::setText(const std::string val) { mText.setString(val); }
const std::string gui::Button::getText() const { return mText.getString().toAnsiString(); }
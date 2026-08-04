#include "GUI_Component.hpp"

gui::GuiComponent::GuiComponent():
	mData(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), FontManager::getFont(FontID::FONT_GAMEF_01), 18U, true),
	mState(ComponentState::CS_IDLE), mColors() {}

gui::GuiComponent::~GuiComponent() {}

void gui::GuiComponent::togleActive() {
	mData.isActive = !mData.isActive;
	if (mData.isActive)
		mState = ComponentState::CS_IDLE;
	else
		mState = ComponentState::CS_DISABLED;
}
void gui::GuiComponent::changeActivity(const bool _value) {
	mData.isActive = _value;
	if (_value)
		mState = ComponentState::CS_IDLE;
	else
		mState = ComponentState::CS_DISABLED;
}
void gui::GuiComponent::setPosition(const sf::Vector2f pos) {}
void gui::GuiComponent::updateColor() {}
const sf::Vector2f gui::GuiComponent::getPosition() const { return mData.position; }
const bool gui::GuiComponent::isDisabled() const { return !mData.isActive; }
const bool gui::GuiComponent::isActived() const { return mData.isActive; }
const bool gui::GuiComponent::isPressed() const { return (mState == ComponentState::CS_ACTIVE && mData.isActive) ? true : false; }
const bool gui::GuiComponent::isHover() const { return (mState == ComponentState::CS_HOVER && mData.isActive) ? true : false; }


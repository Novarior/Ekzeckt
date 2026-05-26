#ifndef GUI_COMPONENT_HPP
#define GUI_COMPONENT_HPP

#include "../core/header.h"

#include "../core/_myFiles.h"
#include "../core/_myConst.h"
#include "../core/tools/path.hpp"
#include "../core/math/mymath.hpp"

namespace gui {
namespace styles {	// styles
namespace buttons {
const char btn_default[] = "default";   // default style
const char btn_apply[] = "apply";       // green outline & background
const char btn_cancel[] = "cancel";     // red outline & background
const char btn_dropdown[] = "dropdown"; // light-gray outline, gray back
const char btn_delete[] = " delete ";   // red colors, wOut text
const char btn_slot[] = "slot";         // dark-gray back, wout text, and gray back
const char btn_tab[] = "tab";
const char btn_hide[] = "hide_btn";
const char btn_selector[] = "selector";
const char btn_pause[] = "pause";
const char btn_editor[] = "editor";
const char btn_tools[] = "tool";
}; // namespace buttons
}; // namespace styles
namespace type {	// type
const char BUTTON[] = "button_style";
const char SLIDER[] = "slider_style";
const char CHECKBOX[] = "checkbox_style";
const char TEXTBOX[] = "textbox_style";
const char LABEL[] = "";
const char PROGRESSBAR[] = "";
};  // namespace type

enum class ComponentState {
	IDLE = 0,
	HOVER,
	ACTIVE,
	DISABLED
};

class GuiComponent: public sf::Drawable {
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(mDraw.shape, states);
		target.draw(mDraw.text, states);
	}

	static sf::Color parceColor(const json& collorarray) {
		return sf::Color(collorarray[0].get<uint8_t>(), collorarray[1].get<uint8_t>(), collorarray[2].get<uint8_t>(), collorarray[3].get<uint8_t>());
	}

	// general variables
	struct ComponentData {
		ComponentData(sf::Vector2f _position, sf::Vector2f _size, sf::Font _font, unsigned _characterSize,
					  std::string _textString, bool _isActive, ComponentState _state, std::string _style, unsigned _id)
			: position(_position), size(_size), font(_font), characterSize(_characterSize),
			textString(_textString), isActive(_isActive), state(_state), styleName(_style), id(_id) {}

		sf::Vector2f position;
		sf::Vector2f size;
		sf::Font font;
		unsigned characterSize;
		std::string textString;
		bool isActive;
		ComponentState state;
		std::string styleName;
		unsigned id;
	} mData;
	// component who will be drawn
	struct ComponentDraw {
		ComponentDraw(sf::RectangleShape _shape, sf::Font _font, std::string _text, uint8_t _charshize)
			: shape(_shape), text(_font, _text, _charshize) {}
		sf::RectangleShape shape;
		sf::Text text;
	} mDraw;
	// component colors
	struct ComponentColors {
		ComponentColors(sf::Color _color)
			: shapeIdleColor(_color), shapeHoverColor(_color), shapeActiveColor(_color), shapeDisableColor(_color),
			outlineIdleColor(_color), outlineHoverColor(_color), outlineActiveColor(_color), outlineDisableColor(_color),
			textIdleColor(_color), textHoverColor(_color), textActiveColor(_color), textDisableColor(_color) {}
		sf::Color shapeIdleColor;
		sf::Color shapeHoverColor;
		sf::Color shapeActiveColor;
		sf::Color shapeDisableColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;
		sf::Color outlineDisableColor;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;
		sf::Color textDisableColor;

		sf::Color textOutlineColor = sf::Color::Black; // default value
	} mColors;

public:
	GuiComponent();
	virtual	~GuiComponent();

	   // set style like a string
	const std::string getStyle() const;
	bool loadStyle(std::string _style, std::string _type);

	const std::string getText() const;
	void setText(std::string _text);
	const unsigned& getID() const;
	void setID(unsigned _id);

	const bool isActive() const;
	void changeActivity(const bool _value);
	void togleActive();

	const sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f _newPos);

	const sf::Vector2f getSize() const;

	const bool isDisabled()const;
	const bool isPressed() const;
	const bool isHover() const;

	void update(const sf::Vector2i& mousePosWindow);

	void updateAfterLoadStyle();
};
} // namespace gui


#endif /* GUI_COMPONENT */
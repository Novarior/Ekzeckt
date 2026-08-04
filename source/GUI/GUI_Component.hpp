#ifndef GUI_COMPONENT_HPP
#define GUI_COMPONENT_HPP

#include "ComponentData.hpp"
#include "ComponentColors.hpp"

#include "../core/header.h"

#include "../core/_myFiles.h"
#include "../core/tools/appfn_consts.h"
#include "../core/tools/appfn_pathtool.hpp"
#include "../core/tools/appfn_logger.hpp"
#include "../core/math/mymath.hpp"
#include "../core/dataCollector/_man_Fonts.hpp"


namespace gui {
enum class ComponentState {
	CS_IDLE = 0,
	CS_HOVER,
	CS_ACTIVE,
	CS_DISABLED
};

class GuiComponent: public sf::Drawable {
private:
protected:
	ComponentData mData;
	ComponentColors mColors;
	ComponentState mState;
public:
	GuiComponent();
	virtual	~GuiComponent();
	// change state of activity ov component
	virtual const bool isActived() const;
	virtual void changeActivity(const bool _value);
	virtual void togleActive();
	// behavior
	virtual const bool isDisabled() const;
	virtual const bool isPressed() const;
	virtual const bool isHover() const;
	virtual const ComponentState& getState() const { return mState; }

	virtual const sf::Vector2f getPosition() const;
	virtual void setPosition(const sf::Vector2f pos);
	virtual void updateColor();

	virtual void update(const sf::Vector2f& mousePosWindow) = 0;
	virtual	void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
} // namespace gui
#endif /* GUI_COMPONENT */
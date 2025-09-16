#include "GUI_Component.hpp"
#include <filesystem>

gui::GuiComponent::GuiComponent()
    : mData({0, 0}, {0, 0}, sf::Font(), 0, " ", false, ComponentState::ACTIVE,
            "default", 0),
      mDraw(sf::RectangleShape(), sf::Font(), " ", 1),
      mColors(sf::Color::Black) {}

gui::GuiComponent::~GuiComponent() {}

void gui::GuiComponent::loadStyle(std::string _namestyle, std::string _type) {
  // Load the style from a JSON file (multi-component loader)

  std::filesystem::path fpath(
      ApplicationsFunctions::get_resources_dir().append("/styles").append(
          AppFiles::config_style));
  std::fstream fs;

  fs.open(fpath);
  if (!fs.is_open())
    throw std::filesystem::exists(fpath);

  json js;
  fs >> js;

  // check if "components" section exists
  if (!js.contains("components")) {
    throw std::runtime_error("Missing 'components' section in style file");
  }

  // get seection
  const auto &componentStyles = js["components"][_type];
  if (componentStyles.is_null()) {
    throw std::runtime_error("Component type '" + _type + "' not found");
  }

  // get current style from _namestyle
  // Получаем конкретный стиль (default, cancel и т.д.)
  const auto &style = componentStyles[_namestyle];
  if (style.is_null()) {
    throw std::runtime_error("Style '" + _namestyle + "' not found for " +
                             _type);
  }

  // upload shit
  auto &buttonStyles = js["components"]["button_style"];

  mData.styleName = style["name"].get<std::string>();

  // forall styles have same color loader
  // load fucked colors
  auto &textColors = style["colors"]["text"];
  mColors.textIdleColor = parceColor(textColors["idle"]);
  mColors.textHoverColor = parceColor(textColors["hover"]);
  mColors.textActiveColor = parceColor(textColors["active"]);
  mColors.textDisableColor = parceColor(textColors["disabled"]);

  auto &bgColors = style["colors"]["background"];
  mColors.shapeIdleColor = parceColor(bgColors["idle"]);
  mColors.shapeHoverColor = parceColor(bgColors["hover"]);
  mColors.shapeActiveColor = parceColor(bgColors["active"]);
  mColors.shapeDisableColor = parceColor(bgColors["disabled"]);

  auto &outlineColors = style["colors"]["outline"];
  mColors.outlineIdleColor = parceColor(outlineColors["idle"]);
  mColors.outlineHoverColor = parceColor(outlineColors["hover"]);
  mColors.outlineActiveColor = parceColor(outlineColors["active"]);
  mColors.outlineDisableColor = parceColor(outlineColors["disabled"]);

  auto &trinc = style["outline_thickness"];
  mDraw.shape.setOutlineThickness(trinc.get<float>());

  auto &txt = style["text"];
  if (txt["font"] == "default") {
    mData.font = sf::Font(
        std::filesystem::path(ApplicationsFunctions::get_resources_dir().append(
            myConst::fonts::data_gameproces_font_path_3)));
  } else {
    std::filesystem::path fpath(
        ApplicationsFunctions::get_resources_dir().append("/fonts").append(
            txt["font"].get<std::string>()));
    if (!std::filesystem::exists(fpath))
      throw std::runtime_error("Font file not found: " + fpath.string());

    mData.font = sf::Font(fpath);
  }

  updateAfterLoadStyle();
}

void gui::GuiComponent::setPosition(sf::Vector2f _newPos) {
  mData.position = _newPos;
  mDraw.shape.setPosition(_newPos);
  mDraw.text.setPosition(
      {mData.position.x + (mData.size.x / 2.f) -
           mDraw.text.getGlobalBounds().size.x / 2.f,
       mData.position.y + mDraw.text.getGlobalBounds().size.y / 2.f});
}

void gui::GuiComponent::update(const sf::Vector2i &mousePosWindow) {
  if (!mData.isActive)
    mData.state = ComponentState::DISABLED;
  else {
    mData.state = ComponentState::IDLE;

    if (mDraw.shape.getGlobalBounds().contains(
            static_cast<sf::Vector2f>(mousePosWindow))) {
      mData.state = ComponentState::HOVER;

      // Pressed
      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        mData.state = ComponentState::ACTIVE;
    }
  }

  switch (mData.state) {
  case ComponentState::IDLE:
    mDraw.shape.setFillColor(mColors.shapeIdleColor);
    mDraw.shape.setOutlineColor(mColors.outlineIdleColor);
    mDraw.text.setFillColor(mColors.textIdleColor);
    break;

  case ComponentState::HOVER:
    mDraw.shape.setFillColor(mColors.shapeHoverColor);
    mDraw.shape.setOutlineColor(mColors.outlineHoverColor);
    mDraw.text.setFillColor(mColors.textHoverColor);
    break;

  case ComponentState::ACTIVE:
    mDraw.shape.setFillColor(mColors.shapeActiveColor);
    mDraw.shape.setOutlineColor(mColors.outlineActiveColor);
    mDraw.text.setFillColor(mColors.textActiveColor);
    break;

  case ComponentState::DISABLED:
    mDraw.shape.setFillColor(mColors.shapeDisableColor);
    mDraw.shape.setOutlineColor(mColors.outlineDisableColor);
    mDraw.text.setFillColor(mColors.textDisableColor);
    break;

  default:
    mDraw.shape.setFillColor(sf::Color::Red);
    mDraw.shape.setOutlineColor(sf::Color::Green);
    mDraw.text.setFillColor(sf::Color::Blue);
    break;
  }
}

void gui::GuiComponent::updateAfterLoadStyle() {
  mDraw.text.setFont(mData.font);
  mDraw.text.setFillColor(mColors.textIdleColor);
  mDraw.text.setCharacterSize(mmath::p2pX(mData.characterSize, mData.size.y));
  mDraw.text.setPosition(
      {mData.position.x + (mData.size.x / 2.f) -
           mDraw.text.getGlobalBounds().size.x / 2.f,
       mData.position.y + mDraw.text.getGlobalBounds().size.y / 2.f});
  mDraw.text.setString(mData.textString);
}
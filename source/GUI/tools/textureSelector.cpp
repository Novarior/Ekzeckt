#include "textureSelector.hpp"

gui::TextureSelector::TextureSelector(float x, float y, float width,
                                      float height, float gridSize,
                                      const sf::Texture &texture_sheet,
                                      sf::Font &font, std::string text)
    : keytimeMax(1.5f), keytime(0.f), sheet(texture_sheet) {
  this->gridSize = gridSize;
  this->active = false;
  this->hidden = false;
  float offset = gridSize;

  this->bounds.setSize({width, height});
  this->bounds.setPosition({x + offset, y});
  this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
  this->bounds.setOutlineThickness(1.f);
  this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

  this->sheet.setPosition({x + offset, y});

  if (this->sheet.getGlobalBounds().size.x >
      this->bounds.getGlobalBounds().size.y)
    this->sheet.setTextureRect(sf::IntRect(
        {0, 0}, {static_cast<int>(this->bounds.getGlobalBounds().size.x),
                 static_cast<int>(this->sheet.getGlobalBounds().size.y)}));

  if (this->sheet.getGlobalBounds().size.x >
      this->bounds.getGlobalBounds().size.x)
    this->sheet.setTextureRect(sf::IntRect(
        {0, 0}, {static_cast<int>(this->sheet.getGlobalBounds().size.x),
                 static_cast<int>(this->bounds.getGlobalBounds().size.y)}));

  this->selector.setPosition({x + offset, y});
  this->selector.setSize(sf::Vector2f(gridSize, gridSize));
  this->selector.setFillColor(sf::Color::Transparent);
  this->selector.setOutlineThickness(1.f);
  this->selector.setOutlineColor(sf::Color::Red);

  this->textureRect.size.x = static_cast<int>(gridSize);
  this->textureRect.size.y = static_cast<int>(gridSize);

  this->hide_btn =
      new gui::Button(sf::Vector2f(x, y), sf::Vector2f(50.f, 50.f), text,
                      gui::styles::buttons::btn_hide, gui::type::BUTTON);
}

gui::TextureSelector::~TextureSelector() { delete this->hide_btn; }

// Accessors
const bool &gui::TextureSelector::getActive() const { return this->active; }

const sf::IntRect &gui::TextureSelector::getTextureRect() const {
  return this->textureRect;
}

const bool gui::TextureSelector::getKeytime() {
  if (this->keytime >= this->keytimeMax) {
    this->keytime = 0.f;
    return true;
  }
  return false;
}

// Functions
void gui::TextureSelector::updateKeytime(const float &dt) {
  if (this->keytime < this->keytimeMax)
    this->keytime += dt;
}

void gui::TextureSelector::update(const sf::Vector2i &mousePosWindow,
                                  const float &dt) {
  this->updateKeytime(dt);
  this->hide_btn->update(mousePosWindow);

  if (this->hide_btn->isPressed() && this->getKeytime()) {
    if (this->hidden)
      this->hidden = false;
    else
      this->hidden = true;
  }

  if (!this->hidden) {
    this->active = false;

    if (this->bounds.getGlobalBounds().contains(
            static_cast<sf::Vector2f>(mousePosWindow))) {
      this->active = true;

      this->mousePosGrid.x =
          (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) /
          static_cast<unsigned>(this->gridSize);
      this->mousePosGrid.y =
          (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) /
          static_cast<unsigned>(this->gridSize);

      this->selector.setPosition(
          {this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
           this->bounds.getPosition().y +
               this->mousePosGrid.y * this->gridSize});

      // Update texture rectangle
      this->textureRect.position.x = static_cast<int>(
          this->selector.getPosition().x - this->bounds.getPosition().x);
      this->textureRect.position.y = static_cast<int>(
          this->selector.getPosition().y - this->bounds.getPosition().y);
    }
  }
}

void gui::TextureSelector::render(sf::RenderTarget &target) {
  if (!this->hidden) {
    target.draw(this->bounds);
    target.draw(this->sheet);

    if (this->active)
      target.draw(this->selector);
  }
  target.draw(*this->hide_btn);
}

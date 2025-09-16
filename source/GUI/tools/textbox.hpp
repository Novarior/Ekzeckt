#ifndef TEXTBOX
#define TEXTBOX

#include "../../core/header.h"

namespace gui {

enum textbox_states { TEXTBOX_IDLE = 0, TEXTBOX_HOVER, TEXTBOX_ACTIVE };

class TextBox : public sf::Drawable {
private:
  short unsigned textboxState;
  bool selected;

  sf::RectangleShape shape;
  sf::Text text;
  sf::Text placeholderText;
  sf::RectangleShape cursor;

  sf::Clock cursorBlinkTimer;
  bool showCursor;

  sf::Color textIdleColor;
  sf::Color textHoverColor;
  sf::Color textActiveColor;

  sf::Color idleColor;
  sf::Color hoverColor;
  sf::Color activeColor;

  sf::Color outlineIdleColor;
  sf::Color outlineHoverColor;
  sf::Color outlineActiveColor;

  sf::Color placeholderColor;

  unsigned limit;
  bool multiline;

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    target.draw(this->shape, states);
    target.draw(this->text, states);

    if (this->selected && this->showCursor)
      target.draw(this->cursor, states);

    if (this->text.getString().getSize() == 0 && !this->selected)
      target.draw(this->placeholderText, states);
  }

  void inputLogic(unsigned int charTyped) {
    // Если нажат Backspace и строка не пустая - удаляем последний символ
    if (charTyped == 8 && this->text.getString().getSize() > 0) {
      deleteLastChar();
    }
    // Если не превышен лимит и введенный символ - печатаемый
    else if (charTyped != 8 && charTyped != 13 &&
             (this->limit == 0 ||
              this->text.getString().getSize() < this->limit)) {
      // Если это многострочное поле и нажат Enter, добавляем перенос строки
      if (this->multiline && charTyped == 13) {
        this->text.setString(this->text.getString() + "\n");
      }
      // Иначе добавляем введенный символ
      else if (charTyped < 128) {
        this->text.setString(this->text.getString() +
                             static_cast<char>(charTyped));
      }
    }

    // Обновляем позицию курсора
    updateCursorPosition();
  }

  void deleteLastChar() {
    std::string str = this->text.getString();
    if (!str.empty()) {
      str.pop_back();
      this->text.setString(str);
      updateCursorPosition();
    }
  }

  void updateCursorPosition() {
    // Позиционируем курсор в конец текста
    if (this->text.getString().isEmpty()) {
      this->cursor.setPosition({this->shape.getPosition().x + 5.f,
                                this->shape.getPosition().y + 5.f});
    } else {
      sf::Vector2f charPos =
          this->text.findCharacterPos(this->text.getString().getSize());
      this->cursor.setPosition({charPos.x, charPos.y});
    }
  }

public:
  /**
   * @brief Construct a new Text Box object
   *
   * @param position - position of textbox
   * @param size - size of textbox
   * @param font - font of text
   * @param placeholder - placeholder text when empty
   * @param character_size - text size
   * @param character_limit - max character limit (0 for unlimited)
   * @param multiline - allows multiline input
   */
  TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font &font,
          std::string placeholder = "", unsigned character_size = 24,
          unsigned character_limit = 0, bool multiline = false);

  ~TextBox();

  // Accessors
  const std::string getText() const;
  const bool isSelected() const;
  const bool isHover() const;

  // Modifiers
  void setLimit(unsigned limit);
  void setMultiline(bool multiline);
  void setSelected(bool selected);
  void setText(const std::string text);
  void setPlaceholder(const std::string placeholder);

  // Functions
  void update(const sf::Vector2i &mousePosWindow);
  void handleInput(const sf::Event &event);
};

} // namespace gui
#endif /* TEXTBOX */

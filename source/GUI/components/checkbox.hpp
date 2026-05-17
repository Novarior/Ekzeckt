#ifndef GUI_SIMPLE_CHECKBOX_HPP
#define GUI_SIMPLE_CHECKBOX_HPP

#include "../../core/header.h"

namespace gui
{

    class CheckBox : public sf::Drawable
    {
    private:
        short unsigned checkboxState;
        bool checked;
        bool was_pressed = false;

        sf::RectangleShape boxShape;
        sf::RectangleShape checkShape;
        sf::Text text;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color uncheckedIdleColor;
        sf::Color uncheckedHoverColor;
        sf::Color uncheckedActiveColor;

        sf::Color checkedIdleColor;
        sf::Color checkedHoverColor;
        sf::Color checkedActiveColor;

        sf::Color outlineIdleColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(this->boxShape, states);
            if (this->checked)
                target.draw(this->checkShape, states);
            target.draw(this->text, states);
        }

    public:
        /**
         * @brief Construct a new CheckBox object
         *
         * @param position - position of checkbox
         * @param size - size of checkbox
         * @param font - font of text
         * @param text - description text
         * @param character_size - text size
         * @param initial_state - initial checked state
         */
        CheckBox(sf::Vector2f position, sf::Vector2f size, sf::Font &font, std::string text, unsigned character_size, bool initial_state = false);

        ~CheckBox();

        // Accessors
        const bool isChecked() const;
        const bool isPressed() const;
        const bool isHover() const;

        // Modifiers
        void setText(const std::string text);
        void setChecked(const bool checked);
        void toggle();

        // Functions
        void update(const sf::Vector2i &mousePosWindow);
    };

} // namespace gui
#endif // GUI_SIMPLE_CHECKBOX_HPP
#ifndef GUI_SIMPLE_DROPDOWNLIST_HPP
#define GUI_SIMPLE_DROPDOWNLIST_HPP

#include "button.hpp"

namespace gui
{
    class DropDownList : sf::Drawable
    {
    private:
        float keytime;
        float keytimeMax;

        sf::Font font;
        gui::Button *activeElement;
        std::vector<gui::Button *> list;
        bool showList;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(*this->activeElement, states);

            if (this->showList)
                for (auto &btn : this->list)
                    target.draw(*btn, states);
        };

    public:
        /// @brief Construct a new Drop Down List object
        /// @param x position on screen
        /// @param y position on screen
        /// @param width size of list
        /// @param height size of list
        /// @param font font of list
        /// @param char_size size of text
        /// @param list pushed elements in list
        /// @param nrOfElements size of list (string data)
        /// @param default_index default index of list (default = 0)

        DropDownList(float x, float y, float width, float height, sf::Font &font, unsigned char_size, std::string list[], unsigned nrOfElements, unsigned default_index = 0);
        ~DropDownList();

        // Accessors
        const unsigned short getActiveElementId() const;

        // Functions
        const bool getKeytime();
        void updateKeytime(const float &dt);
        void update(const sf::Vector2i &mousePosWindow, const float &dt);

    }; // namespace gui
} // namespace gui
#endif // !GUI_DROPDOWNLIST_HPP
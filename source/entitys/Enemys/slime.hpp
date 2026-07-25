#ifndef CPP_TEST_CLASS_HPP
#define CPP_TEST_CLASS_HPP
#include "../AI/AIComponent.hpp"
class Slime : public Entity
{
private:
    std::unique_ptr<AIComponent> ai_component;

public:
    /// @brief Construct a new Slime object
    /// @param spawn_pos a position to spawn
    /// @param texture a texture to use for the slime
    /// @param targer_follow a target to follow (player)
    Slime(float spawn_pos_x, float spawn_pos_y, Entity *targer_follow);
    virtual ~Slime();

    void e_update(const float &delta_time);
    void e_render(sf::RenderTarget &target, const bool show_hitbox = false);
};

#endif
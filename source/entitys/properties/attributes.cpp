#include "attributes.hpp"

Attributes::Attributes(Atri *attributes)
{
  if (attributes != nullptr)
    this->m_attributes = *attributes;
  else
    this->m_attributes = Atri();
}

Attributes::~Attributes() {}

// chek if experience_for_level bigger than experience, if true level up and set experience to 0, after level up set experience_for_level to 1.5 * experience_for_level
void Attributes::chekForLevel(int experience)
{
  if (this->m_attributes.experience >= this->m_attributes.experience_for_level)
  {
    this->m_attributes.level++;
    this->m_attributes.some_points += 5;
    this->m_attributes.experience -= this->m_attributes.experience_for_level;
    this->m_attributes.experience_for_level = 100 + ((this->m_attributes.level - 1) * 65);
    // calculate new max health using max health and level and some_points
    this->m_attributes.max_health = 200 + std::floor(5 * (this->m_attributes.level - 1)) + (this->m_attributes.some_points * 18);
    this->m_attributes.max_mana = 10 + std::floor(5 * (this->m_attributes.level * 0.25)) + (this->m_attributes.some_points / 16) * 10;

    // set health to max health
    // calculate new regen using max health and level
    this->m_attributes.regeneration_health = 1 + (this->m_attributes.level * 0.15) + (this->m_attributes.some_points * 0.0625 / 2);
    this->m_attributes.regeneration_mana = 1 + (this->m_attributes.level + (this->m_attributes.some_points * 0.01 - 1)) * 0.1;
  }
}

void Attributes::update(const float &delta_time)
{
  if (this->m_attributes.isAlive)
  {
    this->chekForLevel(this->m_attributes.experience);
    // renerate health per second if health is not full
    if (this->m_attributes.health < this->m_attributes.max_health)
    {
      this->m_attributes.health += this->m_attributes.regeneration_health * delta_time;
      // chek if health is full
      if (this->m_attributes.health > this->m_attributes.max_health)
        this->m_attributes.health = this->m_attributes.max_health;
    }

    // renerate mana per second if mana is not full
    if (this->m_attributes.mana < this->m_attributes.max_mana)
    {
      this->m_attributes.mana += this->m_attributes.regeneration_mana * delta_time;
      // chek if mana is full
      if (this->m_attributes.mana > this->m_attributes.max_mana)
        this->m_attributes.mana = this->m_attributes.max_mana;
    }
  }
}

void Attributes::takeDamage(int _damage)
{
  this->m_attributes.health -= _damage;
  if (this->m_attributes.health <= 0)
  {
    this->m_attributes.health = 0;
    this->m_attributes.isAlive = false;
  }
}

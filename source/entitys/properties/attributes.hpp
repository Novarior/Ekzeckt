#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

#include "../../core/header.h"

struct Atri
{
  float health = 10;
  float max_health = 10;
  float regeneration_health = 0;
  float mana = 0;
  float max_mana = 0;
  float regeneration_mana = 0;
  int experience_for_level = 1;
  int experience = 0;
  int level = 1;
  int some_points = 0;
  bool isAlive = true;
  float damage = 1;
};

class Attributes
{
private:
  Atri m_attributes;

public:
  Attributes(Atri *attributes = nullptr);
  virtual ~Attributes();

  // functions for save and load attributes
  std::string saveAttributesAsString();
  void loadAttributesFromString(const std::string attributes_string);

  void takeDamage(int damage);
  void takeMana(int mana) { this->m_attributes.mana -= mana; }

  // functions for get and set attributes
  inline const float getMaxHealth() { return this->m_attributes.max_health; }
  inline const float getCurrentHealth() { return this->m_attributes.health; }
  inline void setMaxHealth(float health) { this->m_attributes.max_health = health; }
  inline void setCurrentHealth(float health) { this->m_attributes.health = health; }

  // chek if experience_for_level
  void chekForLevel(int experience);
  inline void addExperience(int experience) { this->m_attributes.experience += experience; }

  // get and set experience
  inline const int getExperience() { return this->m_attributes.experience; }
  inline void setExperience(const int experience) { this->m_attributes.experience = experience; }

  inline const Atri &getAttributes() { return this->m_attributes; }

  void setAttributes(const Atri attributes) { this->m_attributes = attributes; }

  void update(const float &delta_time);
};
#endif // ATTRIBUTES_HPP
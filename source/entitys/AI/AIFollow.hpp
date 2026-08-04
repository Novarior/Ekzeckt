#ifndef AI_FOLLOW_HPP
#define AI_FOLLOW_HPP

#include "AIOption.hpp"

class AIFollow : public AIOption
{
private:
  int _ai_stopDistance;

public:
  AIFollow(Entity *self, Entity *entity, int stopDistance = 500);
  ~AIFollow();

  void update(const float &delta_time);
  bool isCloseEnough();
};
#endif
#pragma once
#include"AbsCollider.h"
#include"Vec2.h"

class CircleCollider : public AbsCollider
{
private:
  float radius;
  Vec2 pos;

public:
  CircleCollider(Vec2 pos, float radius);
  bool collides(const AbsCollider& other) const;
  bool collides(const Vec2& circlePos, float circleRadius) const;
  bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
  bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
  void setPositionCollider(const Vec2& _pos) override;
  Vec2 getPositionCollider() override;
  void setRadius(float _radius);
  float getRadius();
};


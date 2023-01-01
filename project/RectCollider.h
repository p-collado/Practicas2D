#pragma once
#include"AbsCollider.h"
#include"Vec2.h"
class RectCollider:public AbsCollider
{
private:
  Vec2 size;
  Vec2 pos;
public:
  RectCollider(Vec2 pos, Vec2 _size);
  bool collides(const AbsCollider& other) const;
  bool collides(const Vec2& circlePos, float circleRadius) const;
  bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
  bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
  void setPositionCollider(const Vec2& _pos) override;
  Vec2 getPositionCollider() override;
  void setSize(Vec2 _size);
  Vec2 getSize();
};


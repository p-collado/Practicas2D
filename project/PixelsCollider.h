#pragma once
#include"AbsCollider.h"
#include"Vec2.h"

class PixelsCollider : public AbsCollider
{
private:
  
  uint8_t* pixel;
  Vec2 pos;
  Vec2 size;

public:

  ~PixelsCollider();
  PixelsCollider(Vec2 _pos, Vec2 _size, uint8_t* _pixel);
  bool collides(const AbsCollider& other) const;
  bool collides(const Vec2& circlePos, float circleRadius) const;
  bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
  bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
  void setPositionCollider(const Vec2& _pos);
  Vec2 getPositionCollider();
};


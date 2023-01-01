#include "RectCollider.h"

RectCollider::RectCollider(Vec2 _pos, Vec2 _size)
{
  pos = _pos;
  size = _size;
}

bool RectCollider::collides(const AbsCollider& other) const
{
  return other.collides(pos, size);
}

bool RectCollider::collides(const Vec2& circlePos, float circleRadius) const
{
  return checkCircleRect(circlePos, circleRadius, pos, size);
}

bool RectCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
  return checkRectRect(rectPos, rectSize, pos, size);
}

bool RectCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
  return checkPixelsRect(pixelsPos, pixelsSize, pixels, pos, size);
}

void RectCollider::setPositionCollider(const Vec2& _pos)
{
  pos = *(new Vec2(_pos));
}

Vec2 RectCollider::getPositionCollider()
{
  return pos;
}

void RectCollider::setSize(Vec2 _size)
{
  size = *(new Vec2(_size));
}

Vec2 RectCollider::getSize()
{
  return size;
}

#include "PixelsCollider.h"

PixelsCollider::~PixelsCollider()
{
  
}

PixelsCollider::PixelsCollider(Vec2 _pos, Vec2 _size, uint8_t* _pixels)
{
  pixel = _pixels;
  pos = _pos;
  size = _size;
}

bool PixelsCollider::collides(const AbsCollider& other) const
{
  return other.collides(pos, size,pixel);
}

bool PixelsCollider::collides(const Vec2& circlePos, float circleRadius) const
{
  return checkCirclePixels(circlePos, circleRadius, pos, size, pixel);
}

bool PixelsCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
  return checkPixelsRect(pos, size, pixel, rectPos, rectSize);
}

bool PixelsCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
  return checkPixelsPixels(pos, size, pixel, pixelsPos, pixelsSize, pixels);
}

void PixelsCollider::setPositionCollider(const Vec2& _pos)
{
  pos = Vec2(_pos);
}

Vec2 PixelsCollider::getPositionCollider()
{
  return pos;
}

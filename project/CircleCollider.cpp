#include "CircleCollider.h"

CircleCollider::~CircleCollider()
{
  
}

CircleCollider::CircleCollider(Vec2 _pos, float _radius)
{
  radius = _radius;
  pos = _pos;
}

bool CircleCollider::collides(const AbsCollider& other) const
{
  return other.collides(pos,radius);
}

bool CircleCollider::collides(const Vec2& circlePos, float circleRadius) const
{
  return checkCircleCircle(circlePos, circleRadius, pos, radius);
}

bool CircleCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
  return checkCircleRect(pos,radius,rectPos,rectSize);
}

bool CircleCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
  return checkCirclePixels(pos, radius, pixelsPos, pixelsSize, pixels);
}

void CircleCollider::setPositionCollider(const Vec2& _pos)
{
  pos = Vec2(_pos) + radius;
}

Vec2 CircleCollider::getPositionCollider()
{
  return pos;
}

void CircleCollider::setRadius(float _radius)
{
  radius = _radius;
}

float CircleCollider::getRadius()
{
  return radius;
}

#include "AbsCollider.h"
#include "Vec2.h"

bool AbsCollider::checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2)
{
  Vec2 resta = pos1 - pos2;
  float distance = resta.Longitud();

  return distance < (radius1 + radius2);
}

bool AbsCollider::checkCircleRect(const Vec2& circlepos, float circleradius, const Vec2& rectpos, const Vec2& rectsize)
{
  Vec2 rightBottomRect = rectpos + rectsize;
  Vec2 rightUpRect = *(new Vec2(rectpos.GetfX() + rectsize.GetfX(), rectpos.GetfY()));
  Vec2 leftBottomRect = *(new Vec2(rectpos.GetfX(), rectpos.GetfY() + rectsize.GetfY()));
  int closestX = clamp(circlepos.GetfX(), rectpos.GetfX(), rightBottomRect.GetfX());
  int closestY = clamp(circlepos.GetfY(), rectpos.GetfY(), rightBottomRect.GetfY());
  Vec2 closest(closestX, closestY);

  Vec2 resta = closest - circlepos;
  float distance = resta.Longitud();

  return distance < circleradius;
}

bool AbsCollider::checkRectRect(const Vec2& rectpos1, const Vec2& rectsize1, const Vec2& rectpos2, const Vec2& rectsize2)
{
  Vec2 rectEnd1 = rectpos1 + rectsize1;
  Vec2 rectEnd2 = rectpos2 + rectsize2;

  if (rectpos1.GetfX() > rectEnd2.GetfX() ||
    rectEnd1.GetfX() < rectpos2.GetfX() ||
    rectpos1.GetfY() > rectEnd2.GetfY() ||
    rectEnd1.GetfY() < rectpos2.GetfY())
    return false;

  else return true;
}

bool AbsCollider::checkCirclePixels(const Vec2& circlepos, float circleradius, const Vec2& pixelpos, const Vec2& pixelsize, const uint8_t* pixels)
{
  return false;
}

bool AbsCollider::checkPixelsPixels(const Vec2& pixelspos1, const Vec2& pixelssize1, const uint8_t* pixels1, const Vec2& pixelspos2, const Vec2& pixelssize2, const uint8_t* pixels2)
{
  return false;
}

bool AbsCollider::checkPixelsRect(const Vec2& pixelspos1, const Vec2& pixelssize1, const uint8_t* pixels1, const Vec2& rectpos, const Vec2& rectsize)
{
  return false;
}

int AbsCollider::clamp(int pos1, int pos2, int pos3)
{
  if (pos1 < pos2)
    return pos2;
  else if (pos1 > pos3)
    return pos3;
  else return pos1;
}

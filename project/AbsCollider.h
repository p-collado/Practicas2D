#pragma once
#include <cstdint>

class Vec2; //Forwarding

class AbsCollider
{
public:

  virtual ~AbsCollider() {};
  virtual void setPositionCollider(const Vec2& _pos) = 0;
  virtual Vec2 getPositionCollider() = 0;
  virtual bool collides(const AbsCollider& other) const = 0;
  virtual bool collides(const Vec2& circlePos, float circleRadius) const = 0;
  virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const = 0;
  virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const = 0;
  static bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2);
  static bool checkCircleRect(const Vec2& circlepos, float circleradius, const Vec2& rectpos, const Vec2& rectsize);
  static bool checkRectRect(const Vec2& rectpos1, const Vec2& rectsize1, const Vec2& rectpos2, const Vec2& rectsize2);
  static bool checkCirclePixels(const Vec2& circlepos, float circleradius, const Vec2& pixelpos, const Vec2& pixelsize, const uint8_t* pixels);
  static bool checkPixelsPixels(const Vec2& pixelspos1, const Vec2& pixelssize1, const uint8_t* pixels1, const Vec2& pixelspos2, const Vec2& pixelssize2, const uint8_t* pixels2);
  static bool checkPixelsRect(const Vec2& pixelspos1, const Vec2& pixelssize1, const uint8_t* pixels1, const Vec2& rectpos, const Vec2& rectsize);
  static int Myclamp(int pos1, int pos2, int pos3);
  static int Mymax(int a, int b);
  static int Mymin(int x, int z);
  static int Myabs(int x);
};
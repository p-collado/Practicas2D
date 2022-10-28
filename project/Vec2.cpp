#include "Vec2.h"
#include <math.h>

Vec2::Vec2()
{
  fx = 0.f;
  fy = 0.f;
}

Vec2::Vec2(float _x, float _y)
{
  fx = _x;
  fy = _y;
}

void Vec2::SetfX(float _x)
{
  fx = _x;
}

void Vec2::SetfY(float _y)
{
  fy = _y;
}

Vec2 Vec2::operator=(Vec2& _vec)
{
  return *(new Vec2(fx = _vec.GetfX(), fy = _vec.GetfY()));
}

Vec2 Vec2::operator+(Vec2& _vec)
{
  return *(new Vec2(fx + _vec.GetfX(), fy + _vec.GetfY()));
}

Vec2 Vec2::operator*(Vec2& _vec)
{
  return *(new Vec2(fx * _vec.GetfX(), fy * _vec.GetfY()));
}

Vec2 Vec2::operator/(Vec2& _vec)
{
  return *(new Vec2(fx / _vec.GetfX(), fy / _vec.GetfY()));
}

Vec2 Vec2::ValorAbsoluto()
{
  Vec2 Temp;

  if (fx < 0)
  {
    Temp.SetfX(fx * -1);
  }

  if (fy < 0)
  {
    Temp.SetfY(fy * -1);
  }

  return *(new Vec2(Temp.GetfX(), Temp.GetfY()));

}

float Vec2::Longitud()
{
  float fLong = 0.f;

  fLong = sqrt(static_cast<float>((fx * fx) + (fy * fy)));

  return fLong;
}

double Vec2::ProductoEscalar(Vec2* _vec1, Vec2* _vec2, float _angulo)
{
  return _vec1->Longitud() * _vec2->Longitud() * cos(_angulo);
}

Vec2 Vec2::Normalvector(Vec2 _vec)
{
  return *(new Vec2(_vec.fx / _vec.Longitud(), _vec.fy / _vec.Longitud()));
}

float Vec2::Angle(const Vec2& other) const
{
  float angle = 0.f;

 // angle = (fx * other.);
  return 0.f;
}
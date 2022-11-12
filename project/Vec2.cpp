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

Vec2 Vec2::operator+(Vec2& _vec) const
{
  return *(new Vec2(fx + _vec.GetfX(), fy + _vec.GetfY()));
}

Vec2 Vec2::operator+(const Vec2& _vec) const
{
  return *(new Vec2(fx + _vec.GetfX(), fy + _vec.GetfY()));
}

Vec2 Vec2::operator*(Vec2& _vec) const
{
  return *(new Vec2(fx * _vec.GetfX(), fy * _vec.GetfY()));
}

Vec2 Vec2::operator*(float _a) const
{
  return *(new Vec2(this->fx*_a,this->fy*_a));
}

Vec2 Vec2::operator/(Vec2& _vec) const
{
  return *(new Vec2(fx / _vec.GetfX(), fy / _vec.GetfY()));
}

Vec2 Vec2::operator-(Vec2& _vec) const
{
  return *(new Vec2 (fx - _vec.GetfX(), fy - _vec.GetfY()));
}

Vec2 Vec2::operator-(const Vec2& _vec) const
{
  return *(new Vec2(fx - _vec.GetfX(), fy - _vec.GetfY()));
}

Vec2 Vec2::ValorAbsoluto() const
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

float Vec2::Longitud() const
{
  float fLong = 0.f;

  fLong = sqrt(static_cast<float>((fx * fx) + (fy * fy)));

  return fLong;
}

double Vec2::ProductoEscalar(Vec2* _Other) const
{
  return (this->GetfX() * _Other->GetfX()) + (this->GetfY() * _Other->GetfY());
}

Vec2 Vec2::Normalvector(Vec2 _vec) const
{
  return *(new Vec2(_vec.fx / _vec.Longitud(), _vec.fy / _vec.Longitud()));
}

float Vec2::Angle(Vec2 &other) const
{
  //acos(this->ProductoEscalar(&other) / (this->Longitud() * other.Longitud())) * 57.29577;
  return atan2(other.GetfY()-fy,other.GetfX() - fx) * 57.29577;
}

float Vec2::Distance(Vec2& other) const
{
  return ((*this - other).Longitud());
}
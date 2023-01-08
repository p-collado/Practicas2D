#pragma once
class Vec2
{

private:

  float fx;
  float fy;

public:
  Vec2();
  Vec2(float _x, float _y);
  const float GetfX() const { return fx; } 
  const float GetfY() const { return fy; }
  void SetfX(float _x);
  void SetfY(float _y);
  Vec2 operator=(Vec2& _vec);
  Vec2 operator+(Vec2& _vec) const;
  Vec2 operator+(float add);
  Vec2 operator+(const Vec2& _vec) const;
  Vec2 operator*(Vec2& _vec) const;
  Vec2 operator*(float _a) const;
  Vec2 operator/(Vec2& _vec) const;
  Vec2 operator/(int div) const;
  Vec2 operator/(float div) const;
  Vec2 operator-(Vec2& _vec) const;
  Vec2 operator-(const Vec2& _vec) const;
  bool operator==(Vec2& _vec) const;
  bool operator==(const Vec2& _vec) const;
  Vec2 ValorAbsoluto() const;
  float Longitud() const ;
  double ProductoEscalar(Vec2* _vec1) const;
  Vec2 Normalvector(Vec2 _vec) const;
  float Angle(Vec2& other) const;
  float Distance(Vec2& other) const;
};


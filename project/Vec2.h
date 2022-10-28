#pragma once
class Vec2
{

private:

  float fx;
  float fy;

public:
  Vec2();
  Vec2(float _x, float _y);
  float GetfX() { return fx; }
  const float GetfY() { return fy; }
  void SetfX(float _x);
  void SetfY(float _y);
  Vec2 operator=(Vec2& _vec);
  Vec2 operator+(Vec2& _vec);
  Vec2 operator*(Vec2& _vec);
  Vec2 operator/(Vec2& _vec);
  Vec2 ValorAbsoluto();
  float Longitud();
  double ProductoEscalar(Vec2* _vec1, Vec2* _vec2, float _ángulo);
  Vec2 Normalvector(Vec2 _vec);
  float Angle(const Vec2& other) const;
  float distance(const Vec2& other) const;
};


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

  int closestX = Myclamp(circlepos.GetfX(), rectpos.GetfX(), rightBottomRect.GetfX());
  int closestY = Myclamp(circlepos.GetfY(), rectpos.GetfY(), rightBottomRect.GetfY());

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
  if (checkCircleRect(circlepos,circleradius,pixelpos,pixelsize))
  {

    Vec2 rectEnd1 = pixelpos + pixelsize;

    int min_x = Mymax(pixelpos.GetfX() , circlepos.GetfX() - circleradius );
    int max_x = Mymin(rectEnd1.GetfX() , circlepos.GetfX() + circleradius );
    int min_y = Mymax(pixelpos.GetfY() , circlepos.GetfY() - circleradius );
    int max_y = Mymin(rectEnd1.GetfY() , circlepos.GetfY() + circleradius );

    int fila = 0;
    int columna = 0;
    int index = 0;



    for (size_t i = min_y; i < max_y; i++)
    {
      fila = i - pixelpos.GetfY();


      for (size_t j = min_x; j < max_x; j++)
      {
        columna = j - pixelpos.GetfX();
        index = fila * pixelsize.GetfX() + columna;

        if ((pixels[(index * 4) + 3] > 0) && circlepos.Distance(Vec2(j,i)) <= circleradius)
        {
          return true;
        }
      }
    }
  }
  return false;
}

bool AbsCollider::checkPixelsPixels(const Vec2& pixelspos1, const Vec2& pixelssize1, const uint8_t* pixels1, const Vec2& pixelspos2, const Vec2& pixelssize2, const uint8_t* pixels2)
{

  if(checkRectRect(pixelspos1, pixelssize1, pixelspos2, pixelssize2))
  {

    Vec2 rectEnd1 = pixelspos1 + pixelssize1;
    Vec2 rectEnd2 = pixelspos2 + pixelssize2;

    int min_x = Mymax(pixelspos1.GetfX(), pixelspos2.GetfX());
    int max_x = Mymin(rectEnd1.GetfX(), rectEnd2.GetfX());
    int min_y = Mymax(pixelspos1.GetfY(), pixelspos2.GetfY());
    int max_y = Mymin(rectEnd1.GetfY(), rectEnd2.GetfY());

    for (size_t i = min_y; i < max_y; i++)
    {
        int fila = i - pixelspos1.GetfY();
        int fila2 = i - pixelspos2.GetfY();

      for (size_t j = min_x; j < max_x; j++)
      {
        int columna = j - pixelspos1.GetfX();
        int columna2 = j - pixelspos2.GetfX();
        int index = fila * pixelssize1.GetfX() + columna;
        int index2 = fila2  * pixelssize2.GetfX() + columna2;

        if (pixels1[(index * 4) + 3] > 0 && pixels2[(index2 * 4) + 3] > 0)
        {
          return true;
        }
      }
    }
  }
  return false;
}

bool AbsCollider::checkPixelsRect(const Vec2& pixelspos1, const Vec2& pixelssize1, const uint8_t* pixels1, const Vec2& rectpos, const Vec2& rectsize)
{

  if (checkRectRect(pixelspos1, pixelssize1, rectpos, rectsize))
  {


    Vec2 rectEnd1 = pixelspos1 + pixelssize1;
    Vec2 rectEnd2 = rectpos + rectsize;

    int min_x = Mymax(pixelspos1.GetfX(), rectpos.GetfX());
    int max_x = Mymin(rectEnd1.GetfX(), rectEnd2.GetfX());
    int min_y = Mymax(pixelspos1.GetfY(), rectpos.GetfY());
    int max_y = Mymin(rectEnd1.GetfY(), rectEnd2.GetfY());

    int fila = 0;
    int columna = 0;
    int index = 0;

    for (size_t i = min_y; i < max_y; i++)
    {
      fila = i - pixelspos1.GetfY();

      for (size_t j = min_x; j < max_x; j++)
      {
        columna = j - pixelspos1.GetfX();
        index = fila * pixelssize1.GetfX() + columna;

        if (pixels1[(index * 4) + 3] > 0)
        {
          return true;
        }
      }
    }
    return false;
  }
}

int AbsCollider::Myclamp(int pos1, int pos2, int pos3)
{
  if (pos1 < pos2)
    return pos2;
  else if (pos1 > pos3)
    return pos3;
  else return pos1;
}

int AbsCollider::Mymax(int a, int b)
{
 
  if (a > b)
  {
    return a;
  }
  else 
    
    return b;
}

int AbsCollider::Mymin(int a, int b)
{
  if (a > b)
  {
    return b;
  }
  else
    return a;
}

int AbsCollider::Myabs(int x)
{
  if (x < 0)
    return x * -1;
  else 
    return x;
}

#include "World.h"

World::World(float clearRed, float clearGreen, float clearBlue, const ltex_t* back0, const ltex_t* back1,
    const ltex_t* back2, const ltex_t* back3)
{
    background[0] = back0;
    background[1] = back1;
    background[2] = back2;
    background[3] = back3;
}

float World::getClearedRed() const
{
  return clearRed;
}

float World::getClearedGreen() const
{
  return clearGreen;
}

float World::getClearedBlue() const
{
  return clearBlue;
}

const ltex_t* World::getBackground(size_t layer) const
{
  return background[layer];
}

float World::getScrollRatio(size_t layer) const
{
  return backgroundRatio[layer];
}

void World::setScrollRatio(size_t layer,const float ratio)
{
  backgroundRatio[layer] = ratio;
}

const Vec2& World::getScrollSpeed(size_t layer) const
{
  return backgroundSpeed[layer];
}

void World::setScrollSpeed(size_t layer, Vec2& speed)
{
  backgroundSpeed[layer] = speed;
}

const Vec2& World::getCameraPosition() const
{
  return cameraPos;
}

void World::addSprite(CSprite& sprite)
{
  Sprites.push_back(&sprite);
}

void World::removeSprite(CSprite& sprite)
{
  
}

void World::draw(const Vec2& screenSize)
{
  int vx = 0;
  int fx = 1;
  lgfx_clearcolorbuffer(clearRed, clearGreen, clearBlue);
  ltex_drawrotsized(background[0], 0, 0, 0, 0, 0, screenSize.GetfX(), screenSize.GetfY(), 0, 0, 0.25, 1);
}

void World::setCameraPosition(Vec2& pos)
{
  cameraPos = pos;
}

void World::update(float deltatime)
{
  //backgroundRatio[0] = (backgroundRatio[0] * deltatime);


  for each (CSprite* i in Sprites)
  {
    i->draw();
  }
}
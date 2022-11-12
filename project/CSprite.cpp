#include "CSprite.h"
#include "..\project\Vec2.h"
#include <iostream>

CSprite::CSprite(const ltex_t* tex, int hframes = 1, int vframes = 1, lblend_t _mode = lblend_t::BLEND_ALPHA)
{
  memorytexture = new ltex_t(*(tex));
  this->hframes = hframes;
  this->vframes = vframes;
  this->mode = _mode;
  this->fps = 0;
  this->counterTime = 0.f;
}

CSprite::~CSprite()
{
  delete[] memorytexture;
  delete[] pFile;
  //delete[] data;
  delete &pos;
  delete &scale;
  delete &pivot;
}

const ltex_t* CSprite::getTexture() const
{
  return memorytexture;
}

void CSprite::setTexture(const ltex_t* tex, int hframes, int vframes)
{
  memorytexture = new ltex_t(*(tex));
  this->hframes = hframes;
  this->vframes = vframes;
}

lblend_t CSprite::getBlend() const
{
  return mode;
}

void CSprite::setBlend(lblend_t mode)
{
  this->mode = mode;
}

float CSprite::getRed() const
{
  return red;
}

float CSprite::getGreen() const
{
  return green;
}

float CSprite::getBlue() const
{
  return blue;
}

float CSprite::getAlpha() const
{
  return alpha;
}

void CSprite::setColor(float r, float g, float b, float a)
{
  red = r;
  green = g;
  blue = b;
  alpha = a;
}

const Vec2& CSprite::getPosition() const
{
  return pos;
}

void CSprite::setPosition(const Vec2& pos)
{
  this->pos = *(new Vec2(pos.GetfX(),pos.GetfY()));
}

float CSprite::getAngle() const
{
  return angle;
}

void CSprite::setAngle(float angle)
{
  this->angle = angle;
}

const Vec2& CSprite::getScale() const
{
  return scale;
}

void CSprite::setScale(const Vec2& scale)
{
  this->scale = *(new Vec2 (scale.GetfX(), scale.GetfY()));
}

Vec2 CSprite::getSize() const
{
  return *(new Vec2(hframes * scale.GetfX(), vframes * scale.GetfY()));
}

const Vec2& CSprite::getPivot() const
{
  return pivot;
}

void CSprite::setPivot(const Vec2& pivot)
{
  this->pivot = *(new Vec2(pivot.GetfX(), pivot.GetfY()));
}

int CSprite::getHframes() const
{
  return hframes;
}

int CSprite::getVframes() const
{
  return vframes;
}

int CSprite::getFps() const
{
  return fps;
}

void CSprite::setFps(int fps)
{
  this->fps = fps;
}

void CSprite::draw() const
{
  float u0 = 1/hframes * currentframe;
  printf("%f, %d\n", u0, currentframe);
  float u1 = u0 + (1 / hframes);
  float v0 = (1 / hframes) * currentframe;
  float v1 = v0 + (1 / hframes);
  ltex_drawrotsized(memorytexture, pos.GetfX(), pos.GetfY(), angle,pivot.GetfX(),pivot.GetfY(),memorytexture->width/8,memorytexture->height,u0,0, u1 + 0.125,1);
}

CSprite* CSprite::loadTexture(const char* filename)
{
  ltex_t* mem;

  int ancho = 0;
  int alto;
  int comp;
  unsigned char* _Buffer;

  
 
  _Buffer = stbi_load(filename, &ancho, &alto, &comp, 4);
  mem = ltex_alloc(ancho, alto, 0);
  ltex_setpixels(mem, _Buffer);
  CSprite* temp = new CSprite(mem, 8, 1, lblend_t::BLEND_ALPHA);

  return temp;
}

void CSprite::update(float deltaTime) 
{
  counterTime += deltaTime;

  if (counterTime > (1 / 8))
  {
    currentframe = (currentframe + 1) % 8;
    counterTime = 0;
  }

  draw();
}

void CSprite::setCurrentFrame(int frame) 
{



  currentframe = frame;
}

float CSprite::getCurrentFrame() const
{
  return currentframe;
}

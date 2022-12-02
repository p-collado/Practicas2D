#include "CSprite.h"
#include "..\project\Vec2.h"
#include <iostream>

CSprite::CSprite(const ltex_t* tex, int _hframes = 1, int _vframes = 1, lblend_t _mode = lblend_t::BLEND_ALPHA)
{
  memorytexture = new ltex_t(*(tex));
  hframes = _hframes;
  vframes = _vframes;
  mode = _mode;
  fps = 0;
  counterTime = 0.f;
  currentframe = 0;
  maxRot = 0.f;
  scale.SetfX(1.f); 
  scale.SetfY(1.f);
  pivot.SetfX(0.5);
  pivot.SetfY(0.5);
  red = 1.f;
  green = 1.f;
  blue = 1.f;
  alpha = 1.f;
  angle = 0;
}

CSprite::~CSprite()
{
  delete[] memorytexture;
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
  float u0 = (1.f/hframes) * currentframe;
  float u1 = u0 + (1.f / hframes);
  float v0 = vframes - 1;
  float v1 = vframes;
  ltex_drawrotsized(memorytexture, pos.GetfX(), pos.GetfY(), angle,pivot.GetfX(), pivot.GetfY(), memorytexture->width / hframes * scale.GetfX(), memorytexture->height / vframes * scale.GetfY(), u0, v0, u1, v1);
}

void CSprite::setMaxRot(float _maxrot)
{
  maxRot = _maxrot;
}

const float CSprite::getMaxRot()
{
  return maxRot;
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
  behaviour(*this, deltaTime);
  counterTime += deltaTime;
  if (counterTime >= (1.f / 8))
  {
    currentframe = (currentframe + 1) % 8;
    counterTime = 0;
  }

  //Rotation
  if (angle > this->getMaxRot())
  {
    if (static_cast<Vec2*>(data)->GetfX() > this->getPosition().GetfX())
    {
      angle -= 32 * deltaTime;
      //this->setAngle(angle);
    }
  }

  if (angle < (this->getMaxRot()) * -1)
  {
    if (static_cast<Vec2*>(data)->GetfX() < this->getPosition().GetfX())
    {
      angle += 32 * deltaTime;
    }
  }

  //Flip logic
  if (static_cast<Vec2*>(data)->GetfX() <= this->getPosition().GetfX() && this->getScale().GetfX() != -1)
  {
    if (this->getPosition().GetfX() - static_cast<Vec2*>(data)->GetfX() >= 1)
      this->setScale(Vec2(-1.f, 1.f));
  }
  else if (static_cast<Vec2*>(data)->GetfX() > this->getPosition().GetfX() && this->getScale().GetfX() != 1)
  {
    if (static_cast<Vec2*>(data)->GetfX() - this->getPosition().GetfX() >= 1)
      this->setScale(Vec2(1.f, 1.f));
  }


  //Idle Logic
  if (fabs(static_cast<Vec2*>(data)->GetfX() - this->getPosition().GetfX()) < 1)
  {
    if (this->getAngle() < 0)
    {
      angle += 32 * deltaTime;
    }

    if (this->getAngle() > 0)
    {
      angle -= 32 * deltaTime;
    }
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

void 	CSprite::setCallback(CallbackFunc func)
{
  behaviour = func;
}

void* CSprite::getUserData() 
{
  return data;
}

void CSprite::setUserData(void* data)
{
  this->data = data;
}
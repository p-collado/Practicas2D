#include "CSprite.h"
#include "..\project\Vec2.h"
#include <iostream>
#include "CircleCollider.h"
#include "RectCollider.h"
#include "PixelsCollider.h"

CSprite::CSprite(ltex_t* tex, uint8_t* _pixels, int _hframes = 1, int _vframes = 1, lblend_t _mode = lblend_t::BLEND_ALPHA)
{
  escalado = 0.25f;
  memorytexture = tex;
  pixels = _pixels;
  hframes = _hframes;
  vframes = _vframes;
  mode = _mode;
  fps = 0;
  counterTime = 0.f;
  currentframe = 0;
  maxRot = 0.f;
  scale.SetfX(1.f); 
  scale.SetfY(1.f);
  pivot.SetfX(0.0);
  pivot.SetfY(0.0);
  red = 1.f;
  green = 1.f;
  blue = 1.f;
  alpha = 1.f;
  angle = 0;
  size = Vec2(memorytexture->width, memorytexture->height);
}

CSprite::~CSprite()
{
  ltex_free(memorytexture);
  delete[] pixels;
  delete collider;
}

const ltex_t* CSprite::getTexture() const
{
  return memorytexture;
}

void CSprite::setTexture(const ltex_t* tex, int hframes, int vframes)
{
  if (memorytexture)
  {
    delete[] memorytexture;
  }

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

void CSprite::setPosition(const Vec2& _pos)
{
  if (collider)
  {
    collider->setPositionCollider(_pos - (pivot * Vec2(memorytexture->width, memorytexture->height)));
  }
  pos = Vec2(_pos.GetfX(), _pos.GetfY());
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
  this->scale = Vec2(scale.GetfX(), scale.GetfY());
}

Vec2 CSprite::getSize() const
{
  return Vec2(hframes * scale.GetfX(), vframes * scale.GetfY());
}

const Vec2& CSprite::getPivot() const
{
  return pivot;
}

void CSprite::setPivot(const Vec2& pivot)
{
  this->pivot = Vec2(pivot.GetfX(), pivot.GetfY());
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
  lgfx_setcolor(red, green, blue, alpha);
  float u0 = (1.f/hframes) * currentframe;
  float u1 = u0 + (1.f / hframes);
  float v0 = vframes - 1;
  float v1 = vframes;
  ltex_drawrotsized(memorytexture, pos.GetfX(), pos.GetfY(), angle, pivot.GetfX(), pivot.GetfY(), memorytexture->width / hframes * scale.GetfX(), memorytexture->height / vframes * scale.GetfY(), u0, v0, u1, v1);
}

void CSprite::setMaxRot(float _maxrot)
{
  maxRot = _maxrot;
}

const float CSprite::getMaxRot()
{
  return maxRot;
}

void CSprite::setCollisionType(CollisionType type)
{

  if (collider)
  {
    delete collider;
  }

  float radius = 0.f;

  switch (type)
  {
  case CSprite::COLLISION_NONE:
    break;

  case CSprite::COLLISION_CIRCLE:
    collisiontypes = COLLISION_CIRCLE;
    radius= memorytexture-> width / 2;
    collider = new CircleCollider(pos - (pivot * Vec2(memorytexture->width, memorytexture->height)), radius);
    break;

  case CSprite::COLLISION_RECT:
    collisiontypes = COLLISION_RECT;
    collider = new RectCollider(pos - (pivot * Vec2(memorytexture->width, memorytexture->height)), Vec2(memorytexture->width, memorytexture->height));
    break;

  case CSprite::COLLISION_PIXELS:
    collisiontypes = COLLISION_PIXELS;
    collider = new PixelsCollider(pos - (pivot * Vec2(memorytexture->width, memorytexture->height)), Vec2(memorytexture->width, memorytexture->height), pixels);
    break;

  default:
    break;
  }
}

CSprite::CollisionType CSprite::getCollisionType() const
{
  return collisiontypes;
}

const AbsCollider* CSprite::getCollider() const
{
  return collider;
}

bool CSprite::collides(const CSprite& other) const
{
  return collider->collides(*(other.getCollider()));
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

  uint8_t* pixels = new uint8_t[4 * ancho * alto];

  ltex_setpixels(mem, _Buffer);
  stbi_image_free(_Buffer);
  ltex_getpixels(mem, pixels);

  return new CSprite(mem, pixels, 1, 1, lblend_t::BLEND_ALPHA);
}

void CSprite::update(float deltaTime) 
{
  behaviour(*this, &escalado ,deltaTime);
 
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
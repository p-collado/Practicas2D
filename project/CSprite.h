#pragma once

#include "litegfx.h"
#include "stb_image.h"
#include "..\project\Vec2.h"
#include "CircleCollider.h"

class CSprite
{
private:

	double escalado;
	uint8_t* pixels;
	float red;
	float blue;
	float green;
	float alpha;
	lblend_t mode;
	ltex_t* memorytexture;
	float angle;
	int vframes;
	int hframes;
	Vec2 size;
	Vec2 pos;
	Vec2 scale;
	Vec2 pivot;
	int fps;
	float counterTime;
	float maxRot;
	CSprite(ltex_t* tex, uint8_t* pixels, int hframes, int vframes, lblend_t _mode);
	AbsCollider* collider;
	

public:
	enum CollisionType {
		COLLISION_NONE,
		COLLISION_CIRCLE,
		COLLISION_RECT,
		COLLISION_PIXELS
	}collisiontypes;


	void* data;
	typedef void (*CallbackFunc)(CSprite& _sprite, double* _scale, double _delta);
	CallbackFunc behaviour;
	 int currentframe;
	 static CSprite* loadTexture(const char* filename);
	~CSprite();
	void setCallback(CallbackFunc func);
	void* getUserData();
	void setUserData(void* data);
	const ltex_t* getTexture() const;
	void setTexture(const ltex_t* tex, int hframes = 1, int vframes = 1);
	lblend_t getBlend() const; 
	void setBlend(lblend_t mode);
	float getRed() const; 
	float getGreen() const; 
	float getBlue() const; 
	float getAlpha() const;
	void setColor(float r, float g, float b, float a);
	const Vec2& getPosition() const;
	void setPosition(const Vec2& pos);
	float getAngle() const; 
	void setAngle(float angle);
	const Vec2& getScale() const; 
	void setScale(const Vec2& scale);
	Vec2 getSize() const;
	const Vec2& getPivot() const; 
	void setPivot(const Vec2& pivot);
	int getHframes() const; 
	int getVframes() const;
	int getFps() const; 
	void setFps(int fps);
	float getCurrentFrame() const; 
	void setCurrentFrame(int frame);
	void update(float _deltaTime); 
	void draw() const;
	void setMaxRot(float _maxrot);
	const float getMaxRot();
	void setCollisionType(CollisionType type);
	CollisionType getCollisionType() const;
	const AbsCollider* getCollider() const;
	bool collides(const CSprite& other) const;
};


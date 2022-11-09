#pragma once

#include "litegfx.h"
#include "stb_truetype.h"
#include <iostream>
#include "..\project\Vec2.h"

class cFont
{
public:
	
	float height;
	ltex_t* memorytexture;
	FILE* pFile;
	stbtt_bakedchar* data;
	static cFont* load(const char* _filename, float height, float _r, float _g, float _b);
	float getHeight() const;
	Vec2  getTextSize(const char* _text) const;
	void draw(const char* _text, const Vec2& _pos) const;
	~cFont();

private:
	cFont(ltex_t* _texture, stbtt_bakedchar* data, FILE* _file, float height);
};


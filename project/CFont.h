#pragma once

#include "litegfx.h"
#include "stb_truetype.h"
#include <iostream>
#include "..\project\Vec2.h"

class cFont
{
public:

	static ltex_t* memorytexture;
	static FILE* pFile;
	static unsigned char* colorbuffer;
	static unsigned char* pixels;
	float height;
	static stbtt_bakedchar* data;
	static cFont* load(const char* _filename, float height, float _r);
	float getHeight() const;
	Vec2  getTextSize(const char* _text) const;
	void draw(const char* _text, const Vec2& _pos) const;

private:
	cFont();
};


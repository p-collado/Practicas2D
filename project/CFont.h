#pragma once

<<<<<<< HEAD
#define STB_TRUETYPE_IMPLEMENTATION

#include<litegfx.h>
#include <iostream>
#include "stb_truetype.h"
=======
#include "litegfx.h"
#include "stb_truetype.h"
#include <iostream>
#include "..\project\Vec2.h"
>>>>>>> Practica 3 arreglo includes

class cFont
{
public:

	static ltex_t* memorytexture;
	static FILE* pFile;
	static unsigned char* colorbuffer;
	static unsigned char* pixels;
	float height;
	static stbtt_bakedchar* data;

<<<<<<< HEAD
	static cFont* load(const char* _filename, float height, float _r)
	{
		cFont* temp = new cFont();
		int tamaño;
		fopen_s(&pFile, _filename, "r");
		fseek(pFile, 0, SEEK_END);
		tamaño = ftell(pFile);
		unsigned char* max = new unsigned char[tamaño];
		rewind(pFile);
		fread_s(max, tamaño * sizeof(char), sizeof(char), tamaño, pFile);
		pixels = new unsigned char[1024 * 1024];
		data = new stbtt_bakedchar[58];
		int bitmap = 0;
		bitmap = stbtt_BakeFontBitmap(max, 0, 64.f, pixels, 1024, 1024, 65, 58, data);

		if (bitmap < 0 || bitmap == 0)
		{
			printf("ERROR: %d", bitmap);
			return nullptr;
		}

		colorbuffer = new unsigned char[1024 * 1024 * 4];

		int j = 0;
		for (size_t i = 1; i < 1024 * 1024 * 4; i++)
		{
			colorbuffer[i] = _r;
			if (!(i % 4))
			{
				colorbuffer[i - 1] = pixels[j];
				j++;
			}
		}
		memorytexture = ltex_alloc(1024, 1024, 0);
		ltex_setpixels(memorytexture, colorbuffer);
		return temp;
	}

=======
	static cFont* load(const char* _filename, float height, float _r);
>>>>>>> Practica 3 arreglo includes
	float getHeight() const;
	Vec2  getTextSize(const char* _text) const;
	void draw(const char* _text, const Vec2& _pos) const;

private:
	cFont();
};


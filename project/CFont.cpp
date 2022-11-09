#include"CFont.h"
#include"Vec2.h"
#include<iostream>
#include <time.h>
#include<stdlib.h>



cFont* cFont::load(const char* _filename, float _height, float _r, float _g, float _b)
{
	FILE* file = nullptr;
	stbtt_bakedchar* data = nullptr;
	float height = _height;
	ltex_t* texture = nullptr;
	int tamaño;

	fopen_s(&file, _filename, "r");
	fseek(file, 0, SEEK_END);
	tamaño = ftell(file);
	unsigned char* max = new unsigned char[tamaño];
	rewind(file);
	fread_s(max, tamaño * sizeof(char), sizeof(char), tamaño, file);
	unsigned char*  pixels = new unsigned char[1024 * 1024];
	data = new stbtt_bakedchar[90];
	int bitmap = 0;
	bitmap = stbtt_BakeFontBitmap(max, 0, _height, pixels, 1024, 1024, 32, 90, data);
	if (bitmap < 0 || bitmap == 0)
	{
		printf("ERROR: %d", bitmap);
		return nullptr;
	}

	unsigned char * colorbuffer = new unsigned char[1024 * 1024 * 4];

	int j = 0;
	for (size_t i = 0; i < 1024 * 1024 * 4; i+=4)
	{
		colorbuffer[i + 0] = _r;
		colorbuffer[i + 1] = _g;
		colorbuffer[i + 2] = _b;
		colorbuffer[i + 3] = pixels[j];
		j++;
	}


	texture = ltex_alloc(1024, 1024, 0);
	ltex_setpixels(texture, colorbuffer);

	delete[] max;
	delete[] pixels;
	delete[] colorbuffer;

	cFont* temp = new cFont(texture, data, file, height);

	return temp;
}

float cFont::getHeight() const
{
	return height;
}

Vec2 cFont::getTextSize(const char* _text) const
{
	Vec2 result;

	float* aux = new float(10.f);

	float sumax = 0.f;
	float maxy = 0.f;
	stbtt_aligned_quad quad;

	for (size_t i = 0; i < strlen(_text); i++)
	{
		stbtt_GetBakedQuad(data, 1024, 1024, _text[i] - 32, aux, aux, &quad, true);
		sumax += quad.x1 - quad.x0;
		if (quad.y1 - quad.y0 >= maxy)
		{
			maxy = quad.y1 - quad.y0;
		}
	}

	return Vec2(sumax,maxy);
}

void cFont::draw(const char* _text, const Vec2& _pos) const
{
	float xpos = _pos.GetfX();
	float ypos = _pos.GetfY();
	stbtt_aligned_quad quad;
	for (size_t i = 0; i < strlen(_text); i++)
	{
		stbtt_GetBakedQuad(data, 1024, 1024, _text[i]  - 32 ,&xpos , &ypos, &quad, true);
		ltex_drawrotsized(memorytexture, quad.x0, quad.y0, 0, 0, 0, quad.x1-quad.x0,	quad.y1-quad.y0, quad.s0, quad.t0, quad.s1, quad.t1);
	}
}

cFont::~cFont()
{
	delete[] memorytexture;
	delete[] pFile;
	delete[] data;
}

cFont::cFont(ltex_t* _texture, stbtt_bakedchar* _data, FILE* _file, float _height)
{
	data = _data;
	memorytexture = _texture;
	pFile = _file;
	height = _height;
}
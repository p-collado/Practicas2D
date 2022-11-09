#include"CFont.h"
#include"Vec2.h"
#include<iostream>
#include <time.h>
#include<stdlib.h>


ltex_t* cFont::memorytexture;
FILE* cFont::pFile;
unsigned char* cFont::colorbuffer;
unsigned char* cFont::pixels;
stbtt_bakedchar* cFont::data;

cFont* cFont::load(const char* _filename, float _height, float _r)
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
	temp->colorbuffer = colorbuffer;
	temp->data = data;
	temp->memorytexture = memorytexture;

	memorytexture = ltex_alloc(1024, 1024, 0);
	ltex_setpixels(memorytexture, colorbuffer);
}

cFont::cFont()
{

}
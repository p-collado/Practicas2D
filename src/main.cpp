#define STB_TRUETYPE_IMPLEMENTATION
#include "..\project\cFont.h"
#define LITE_GFX_IMPLEMENTATION
#include "litegfx.h"

#include <glfw3.h>
//#include "..\project\Vec2.h"
//#include "stb_truetype.h
#include <time.h>
#include <stdlib.h>
//#include <fstream>
//#include <iostream>
//#include <sstream>


#define HEIGHT 720
#define WIDTH 1280

using namespace std;

//template <typename T> std::string stringFromNumber(T val)
//{
//	std::ostringstream stream; 
//	stream << std::fixed << val; 
//	return stream.str();
//}

//ltex_t* loadTexture(const char* filename);

float xpos;
float ypos;

int main() 
{
	srand(time(NULL));

	if (!glfwInit())
	{
		printf("ERROR EN INICIALIZAR");
		return -1;
	}
	double x = 0.f;
	double y = 0.f;

	Vec2 Cursor(x, y);

	GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Prueba", nullptr, nullptr);
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwMakeContextCurrent(pWindow);
	
	lgfx_setup2d(WIDTH, HEIGHT);

	cFont* font = cFont::load("C:\\Users\\pedro\\source\\repos\\p-collado\\PracticasJavier.Alegre\\fonts\\SFSlapstickComic.ttf", 1024, rand() % 255);

	
	/*FILE* pFile;
	fopen_s(&pFile,"C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\fonts\\SFSlapstickComic.ttf", "r");

	unsigned char max[25276];
	int leidos = 0;

	int contador = 0;

	fseek(pFile, 0, SEEK_END);
	
	rewind(pFile);

	fread_s(max, 25276 * sizeof(char), sizeof(char), 25276, pFile);

	unsigned char* pixels = new unsigned char[512 * 512];
	stbtt_bakedchar* data = new stbtt_bakedchar[58];
	int bitmap = 0;
	bitmap = stbtt_BakeFontBitmap(max, 0, 64.f, pixels, 512 ,512, 65, 58, data);

	printf("Alpha solo: %d", bitmap);
  unsigned char* colorbuffer = new unsigned char[512 * 512 * 4];
	int j = 0;
	for (size_t i = 1; i < 512 * 512 * 4; i++)
	{
		colorbuffer[i] = 128;
		if (!(i % 4))
		{
			colorbuffer[i-1] = pixels[j];
			j++;
		}
	}*/

	//ltex_t* memorytexture;
	//memorytexture = ltex_alloc(512, 512, 0);

	//ltex_setpixels(memorytexture, colorbuffer);
	//delete[] colorbuffer;
	//delete[] pixels;

	
	double time = 0.f;
	double deltaTime = 0;
	
	stbtt_aligned_quad quad;

	stbtt_GetBakedQuad(font->data, 1024, 1024, 1, &xpos, &ypos, &quad, true);


	while (!glfwWindowShouldClose(pWindow) && time < 20)
	{
		deltaTime = glfwGetTime() - time;
		/* Poll for and process events */
		glfwPollEvents();
		glfwGetCursorPos(pWindow,&x , &y);
	
		Cursor = Vec2(x,y);
		xpos = Cursor.GetfX();
		ypos = Cursor.GetfY();
	
		/* Render here */
		lgfx_clearcolorbuffer(0.f, 0.f, 0.f);
		
		lgfx_setblend(BLEND_ALPHA);

		ltex_drawrotsized(font->memorytexture, xpos, ypos, 0, 0, 0, 200, 200, quad.s0,quad.t0,quad.s1,quad.t1);
		
		time = glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
	}

	//stbi_image_free();
	//stbi_image_free();
	//stbi_image_free();
	//stbi_image_free();

	void glfwTerminate();
	return 0;
}

//ltex_t* loadTexture(const char* filename)
//{
//	ltex_t* temp;
//	int ancho;
//	int alto;
//	int comp;
//	unsigned char* _Buffer;
//	_Buffer = stbi_load(filename, &ancho, &alto, &comp, 4);
//	temp = ltex_alloc(ancho, alto, 0);
//	ltex_setpixels(temp, _Buffer);
//	return temp;
//}

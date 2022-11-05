#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "..\project\Vec2.h"
#include "stb_image.h"
#include "stb_truetype.h"


#define HEIGHT 720
#define WIDTH 1280

using namespace std;

template <typename T> std::string stringFromNumber(T val)
{
	std::ostringstream stream; 
	stream << std::fixed << val; 
	return stream.str();
}

ltex_t* loadTexture(const char* filename);


int main() 
{

	FILE* pFile;
	fopen_s(&pFile,"C:\\Users\\pedro\\source\\repos\\p-collado\\PracticasJavier.Alegre\\fonts\\SFSlapstickComic.ttf", "r");

	unsigned char max[25276];
	int leidos = 0;

	int contador = 0;

	fseek(pFile, 0, SEEK_END);

	rewind(pFile);

	fread_s(max, 25276 * sizeof(char), sizeof(char), 25276, pFile);

	unsigned char* pixels = new unsigned char[512 * 512];
	stbtt_bakedchar* data = new stbtt_bakedchar[57];
	int bitmap = 0;
	bitmap = stbtt_BakeFontBitmap(max, 0, 16.f, pixels, 512 ,512, 65, 57, data);

	printf("Alpha solo: %d", bitmap);
  unsigned char* colorbuffer = new unsigned char[512 * 512 * 4];
	int j = 0;
	for (size_t i = 0; i < 512 * 512; i++)
	{
		colorbuffer[i] = 0.5;
		if (i % 4)
		{
			colorbuffer[i-1] = pixels[j];
			j++;
		}
	}

	for (size_t i = 0; i < 512*512*4; i++)
	{
		printf("%d, %c\n",i, colorbuffer[i]);
	}

	string title;
	bool direc = true;

	double x = 0.f;
	double y = 0.f;
	double time = 0.f;
	double deltaTime = 0;

	if (!glfwInit())
	{
		printf("ERROR EN INICIALIZAR");
		return -1;
	}
	

	Vec2 Cursor(x, y);

	GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Prueba", nullptr, nullptr);
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwMakeContextCurrent(pWindow);


	while (!glfwWindowShouldClose(pWindow) && time < 20)
	{

		deltaTime = glfwGetTime() - time;
		/* Poll for and process events */
		glfwPollEvents();
		glfwGetCursorPos(pWindow,&x , &y);
	
		Cursor = Vec2(x,y);
		
	
		/* Render here */
		lgfx_setup2d(WIDTH, HEIGHT);
		lgfx_clearcolorbuffer(1.f, 1.f, 1.f);
	
		
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

ltex_t* loadTexture(const char* filename)
{
	ltex_t* temp;
	int ancho;
	int alto;
	int comp;
	unsigned char* _Buffer;
	_Buffer = stbi_load(filename, &ancho, &alto, &comp, 4);
	temp = ltex_alloc(ancho, alto, 0);
	ltex_setpixels(temp, _Buffer);
	return temp;
}

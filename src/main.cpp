#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include <sstream>
#include "..\project\Vec2.h"
#include "stb_image.h"

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

	string title;
	bool direc = true;

	double x = 0.f;
	double y = 0.f;
	int rotdir = 10;
	double time = 0.f;
	float angle = 1.f;
	double deltaTime = 0;
	float escalado = 128.f;
	float ancho = 256.f;
	float alto = 256.f;

	if (!glfwInit())
	{
		printf("ERROR EN INICIALIZAR");
		return -1;
	}
	

	Vec2 Cursor(x, y);

	GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Prueba", nullptr, nullptr);
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwMakeContextCurrent(pWindow);


	ltex_t* ptrmalla2 = loadTexture("C:\\Users\\pedro\\source\\repos\\p-collado\\PracticasJavier.Alegre\\sprites\\grille.png");
	ltex_t* ptrBaack = loadTexture("C:\\Users\\pedro\\source\\repos\\p-collado\\PracticasJavier.Alegre\\sprites\\wall.jpg");
	ltex_t* ptr = loadTexture("C:\\Users\\pedro\\source\\repos\\p-collado\\PracticasJavier.Alegre\\sprites\\fire.png");
	ltex_t* ptrlight = loadTexture("C:\\Users\\pedro\\source\\repos\\p-collado\\PracticasJavier.Alegre\\sprites\\light.png");

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
		glClear(GL_COLOR_BUFFER_BIT);
	

		lgfx_setblend(BLEND_SOLID);

		for (size_t i = 0; i < 4; i++)
		{
			for(size_t j = 0; j < 3 ; j++)
				ltex_drawrotsized(ptrBaack, i * 415, j * 304, 0, 0, 0, 415, 304, 0, 0, 1, 1);
		}

		lgfx_setblend(BLEND_ADD);
		ltex_drawrotsized(ptr, x, y, angle , 0.5, 0.8, ancho,alto, 0, 0, 1, 1);


		if (ancho > (256 * 1.2) || ancho < (256*0.8))
		{
			escalado *= -1;
		}

		ancho += escalado * deltaTime;
		alto += escalado * deltaTime;
	
		if (angle > 10 || angle < -10)
		{
			rotdir *= -1;
		}
		angle += rotdir * deltaTime;

		printf("%f, %f\n",ancho,alto);
	
		lgfx_setblend(BLEND_ALPHA);
		for (size_t i = 0; i < 7 ; i++)
		{
			for (size_t j = 0; j < 4; j++)
				ltex_drawrotsized(ptrmalla2, i * 205, j * 205, 0, 0, 0, 205, 205, 0, 0, 1, 1);
		}

		lgfx_setblend(BLEND_MUL);
		ltex_drawrotsized(ptrlight, x-ptrlight->width/2, y - ptrlight->height/2, 0, 0, 0, 1024, 1024, 0, 0, 1, 1);

		lgfx_setcolor(0, 0, 0, 0);
		//arriba
		lgfx_drawrect(x - 3200/2 , y - 1200, 3200, 720);
		//abajo
		lgfx_drawrect(x - 3200/2 , y + 500 , 3200, 720);
		//derecha
		lgfx_drawrect(x + 500, y - 750, 1280, 1500);
		//izquierda
		lgfx_drawrect(x - 1780 ,y - 750, 1280, 1500);
		
		
		time = glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
	}

	stbi_image_free(ptrmalla2);
	stbi_image_free(ptrBaack);
	stbi_image_free(ptr);
	stbi_image_free(ptrlight);

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

#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include <sstream>
#include "..\project\Vec2.h"
#include "stb_image.h"

#define HEIGHT 720
#define WIDTH 1280
#define ANGULO 32 * 0.0174532925


using namespace std;

template <typename T> std::string stringFromNumber(T val)
{
	std::ostringstream stream; 
	stream << std::fixed << val; 
	return stream.str();
}

int main() 
{

	string title;

	double x = 0.f;
	double y = 0.f;
	double time = 0.f;


	struct sTam {
		int ancho;
		int alto;
		int* Comp;
	};



	if (!glfwInit())
	{
		printf("ERROR EN INICIALIZAR");
		return -1;
	}
	
	Vec2 Cursor(x, y);
	Vec2 PosObject;
	sTam Fire, valla, fondo, filtro;

	GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Prueba", nullptr, nullptr);
	glfwMakeContextCurrent(pWindow);

	Fire.alto = 256 / 2;
	Fire.ancho = 256 / 2;

	unsigned char* ptrs = stbi_load("sprites\\fire.png",&Fire.ancho,&Fire.alto,Fire.Comp,4);

	stbi_image_free(Fire.Comp);


	while (!glfwWindowShouldClose(pWindow))
	{
		
		/* Poll for and process events */
		glfwPollEvents();
		glfwGetCursorPos(pWindow,&x , &y);
	
		Cursor = Vec2(x,y);
		
		//title = "Distancia: " + stringFromNumber(distance) + " -- Angulo: " + stringFromNumber(angulo);
		glfwSetWindowTitle(pWindow, title.c_str());
	
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		lgfx_setcolor(0.f, 1.f, 0.f, 0.f);
		lgfx_drawrect(x - 50, y - 50, 100, 100);

		ltex_t * ptr = ltex_alloc(Fire.ancho, Fire.alto,0);

		ltex_setpixels(ptr, ptrs);

		time = glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
		lgfx_setup2d(WIDTH, HEIGHT);
		lgfx_clearcolorbuffer(1.f, 1.f, 1.f);

	}

	void glfwTerminate();
	return 0;
}

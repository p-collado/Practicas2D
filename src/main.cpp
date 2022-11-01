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


struct sTam {
	int ancho;
	int alto;
	int* Comp;
};

ltex_t* loadTexture(const char* filename, sTam* Stam, unsigned char* _Buffer);

sTam Fire, malla, fondo, filtro;


int main() 
{

	string title;
	bool direc = true;

	double x = 0.f;
	double y = 0.f;
	double time = 0.f;
	int angle = 1;
	double deltaTime = 0.f;
	float escalado = 0.010f;
	int ancho = 256;
	int alto = 256;

	unsigned char* ptrbackground = nullptr;
	unsigned char* ptrmalla = nullptr;
	unsigned char* ptrs = nullptr;
	unsigned char* ptrfilter = nullptr;

	if (!glfwInit())
	{
		printf("ERROR EN INICIALIZAR");
		return -1;
	}
	

	Vec2 Cursor(x, y);
	/*sTam Fire, malla, fondo, filtro;*/

	GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Prueba", nullptr, nullptr);
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwMakeContextCurrent(pWindow);
	

	/*Fire.Comp = nullptr;
	malla.Comp = nullptr;
	fondo.Comp = nullptr;
	filtro.Comp = nullptr;*/

	/*unsigned char* ptrbackground = stbi_load("C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\sprites\\wall.jpg", &fondo.ancho, &fondo.alto, fondo.Comp, 4);
	unsigned char* ptrmalla = stbi_load("C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\sprites\\grille.png", &malla.ancho, &malla.alto, malla.Comp, 4);
	unsigned char* ptrs = stbi_load("C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\sprites\\fire.png",&Fire.ancho,&Fire.alto,Fire.Comp,4);
	unsigned char* ptrfilter = stbi_load("C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\sprites\\light.png", &filtro.ancho, &filtro.alto, filtro.Comp, 4);*/


	ltex_t* ptrmalla2 = loadTexture("C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\sprites\\grille.png", &malla, ptrmalla); /*= ltex_alloc(malla.ancho, malla.alto, 0);*/
	ltex_t* ptrBaack = loadTexture("C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\sprites\\wall.jpg", &fondo, ptrbackground); /*= ltex_alloc(fondo.ancho, fondo.alto, 0); */
	ltex_t* ptr = loadTexture("C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\sprites\\fire.png", &Fire, ptrs); /*ltex_alloc(Fire.ancho, Fire.alto, 0);*/
	ltex_t* ptrlight = loadTexture("C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\sprites\\light.png", &filtro, ptrfilter); /*= ltex_alloc(filtro.ancho, filtro.alto, 0);*/

	//ltex_setpixels(ptrmalla2, ptrmalla);
	//ltex_setpixels(ptrBaack, ptrbackground);
	//ltex_setpixels(ptr, ptrs);
	//ltex_setpixels(ptrlight, ptrfilter);

	while (!glfwWindowShouldClose(pWindow))
	{

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
		ltex_drawrotsized(ptr, x, y, (cos(angle*0.0174533) * 10), 0.5, 0.8, ancho + (256 * escalado * deltaTime), alto + (256 * escalado * deltaTime), 0, 0, 1, 1);

		ancho += (256 * escalado);
		alto += (256 * escalado);

		if (ancho > (256 * 1.2) || ancho < (256*0.8))
		{
			escalado *= -1;
		}
	
		angle++;
		angle = angle % 360;

		if (angle == 10)
		{
			printf("time : %f\n", time);
		}
	
		lgfx_setblend(BLEND_ALPHA);
		for (size_t i = 0; i < 7 ; i++)
		{
			for (size_t j = 0; j < 4; j++)
				ltex_drawrotsized(ptrmalla2, i * 205, j * 205, 0, 0, 0, 205, 205, 0, 0, 1, 1);
		}

		lgfx_setblend(BLEND_MUL);
		ltex_drawrotsized(ptrlight, x-filtro.ancho/2, y - filtro.alto/2, 0, 0, 0, 1024, 1024, 0, 0, 1, 1);

		lgfx_setcolor(0, 0, 0, 0);
		//arriba
		lgfx_drawrect(x - 3200/2 , y - 1200, 3200, 720);
		//abajo
		lgfx_drawrect(x - 3200/2 , y + 500 , 3200, 720);
		//derecha
		lgfx_drawrect(x + 500, y - 750, 1280, 1500);
		//izquierda
		lgfx_drawrect(x - 1780 ,y - 750, 1280, 1500);
		
		deltaTime = glfwGetTime() - time;
		time = glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
	}

	stbi_image_free(ptrbackground);
	stbi_image_free(ptrmalla);
	stbi_image_free(ptrs);
	stbi_image_free(ptrfilter);

	void glfwTerminate();
	return 0;
}

ltex_t* loadTexture(const char* filename, sTam* struc, unsigned char* _Buffer) //DUDA ESTO ESTA BIEN????
{
	ltex_t* temp;
	_Buffer = stbi_load(filename, &struc->ancho, &struc->alto, struc->Comp, 4);
	temp = ltex_alloc(struc->ancho, struc->alto, 0);
	ltex_setpixels(temp, _Buffer);
	return temp;
}

#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include <sstream>
#include "..\project\Vec2.h"

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
	double objx = 0.f;
	double objy = 0.f;
	double time = 0.f;
	double angulo = 0.f;
	double distance = 0.f;
	double mov = 0.f;



	if (!glfwInit())
	{
		printf("ERROR EN INICIALIZAR");
		return -1;
	}
	
	Vec2 Cursor(x, y);
	Vec2 PosObject;

	GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Prueba", nullptr, nullptr);
	glfwMakeContextCurrent(pWindow);

	while (!glfwWindowShouldClose(pWindow))
	{
		
		/* Poll for and process events */
		glfwPollEvents();
		glfwGetCursorPos(pWindow,&x , &y);
	
		Cursor = Vec2(x,y);
		title = "Distancia: " + stringFromNumber(distance) + " -- Angulo: " + stringFromNumber(angulo);
		glfwSetWindowTitle(pWindow, title.c_str());
		mov += ANGULO * (time - glfwGetTime());
		objx = Cursor.GetfX() + 100 * sin(mov) - 25;
		objy = Cursor.GetfY() + 100 * cos(mov) - 25;
		PosObject = Vec2(objx, objy);
		angulo = Cursor.Angle(PosObject);
		distance = Cursor.Distance(Vec2(WIDTH/2, HEIGHT/2));
	
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		lgfx_setcolor(1.f, 0.f, 0.f, 0.f);
		lgfx_drawrect((WIDTH / 2) - 50, (HEIGHT / 2) - 50, 100, 100);


		lgfx_setcolor(0.f, 1.f, 0.f, 0.f);
		lgfx_drawrect(x - 50, y - 50, 100, 100);

		lgfx_setcolor(0.f, 0.f, 1.f, 0.f);
		lgfx_drawoval(objx, objy, 50, 50);

		time = glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
		lgfx_setup2d(WIDTH, HEIGHT);
		lgfx_clearcolorbuffer(1.f, 1.f, 1.f);

	}

	void glfwTerminate();
	return 0;
}

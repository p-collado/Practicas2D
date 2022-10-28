#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include "C:\Users\pedro\source\repos\p-collado\programacion2d\project\Vec2.h"

#define HEIGHT 720
#define WIDTH 1280


using namespace std;

int main() 
{
	if (!glfwInit())
	{
		printf("ERROR EN INICIALIZAR");
		return -1;
	}

	GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Prueba", nullptr, nullptr);
	glfwMakeContextCurrent(pWindow);

	while (!glfwWindowShouldClose(pWindow))
	{
		/* Poll for and process events */
		glfwPollEvents();
		void glfwGetCursorPos(GLFWwindow * pWindow, double* xpos, double* ypos);
		
		double glfwGetTime();
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		lgfx_setcolor(1.f, 0.f, 0.f, 0.f);
		lgfx_drawrect(WIDTH / 2, HEIGHT / 2, 10, 10);

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
		lgfx_setup2d(WIDTH, HEIGHT);
		lgfx_clearcolorbuffer(1.f, 1.f, 1.f);

	}

	void glfwTerminate();
	return 0;
}

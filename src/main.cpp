#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include "C:\Users\pedro\source\repos\p-collado\PracticasJavier.Alegre\project\Vec2.h"


using namespace std;

int main() 
{
	glfwInit();
	if (!glfwInit())//DUDAAA
	{
		printf("ERROR EN INICIALIZAR");
		return -1;
	}

	GLFWwindow* pWindow = glfwCreateWindow(800, 800, "Prueba", nullptr, nullptr);
	glfwMakeContextCurrent(pWindow);

	while (!glfwWindowShouldClose(pWindow))
	{
		/* Poll for and process events */
		glfwPollEvents();
		void glfwGetCursorPos(GLFWwindow * pWindow, double* xpos, double* ypos);


		double glfwGetTime();
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
		lgfx_setup2d(800, 800);

		lgfx_clearcolorbuffer(1.f, 1.f, 1.f);

	}

	void glfwTerminate();
	return 0;
}

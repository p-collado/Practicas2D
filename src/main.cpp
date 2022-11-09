#define STB_TRUETYPE_IMPLEMENTATION
#include "..\project\cFont.h"
#define LITE_GFX_IMPLEMENTATION
#include "litegfx.h"
#include <glfw3.h>
#include <time.h>
#include <stdlib.h>
#include "..\project\InstanceWord.h"



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

	cFont* font;

	Vec2 Cursor(x, y);

	GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Prueba", nullptr, nullptr);
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwMakeContextCurrent(pWindow);
	
	lgfx_setup2d(WIDTH, HEIGHT);

	InstanceWord* instances[30];

	for (size_t i = 0; i < 30; i++)
	{
		if (rand() % 2)
		{
			font = cFont::load("C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\fonts\\SFSlapstickComic.ttf", (rand() % 64) + 32, rand() % 256, rand() % 256, rand() % 256);
		}
		else
		{
			font = cFont::load("C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\fonts\\Orange.ttf", (rand() % 64) + 32, rand() % 256, rand() % 256, rand() % 256);
		}

		instances[i] = new InstanceWord(font);
	}
	
	double time = 0.f;
	double deltaTime = 0;

	float tamaño = 0.f;

	while (!glfwWindowShouldClose(pWindow))
	{
		deltaTime = glfwGetTime() - time;
		/* Poll for and process events */
		glfwPollEvents();
		glfwGetCursorPos(pWindow,&x , &y);
		int choosen = rand() % 30;
		if (rand() % 101 == 0)
		{
			if (!instances[choosen]->active)
			{
				InstanceWord* aux = instances[choosen];
				aux->pos = Vec2(WIDTH, rand() % HEIGHT);
				aux->speed = (rand() % 200) + 20;
				aux->active = true;
			}
			else 
			{
				if ((instances[choosen]->font->getTextSize("Hello Word").GetfX() + instances[choosen]->pos.GetfX()) <= 0.f)
				{
					printf("%f", instances[choosen]->font->getTextSize("Hello World").GetfX());
					instances[choosen]->active = false;
				}
			}
		}


		Cursor = Vec2(x,y);
		xpos = Cursor.GetfX();
		ypos = Cursor.GetfY();
	
		InstanceWord* aux;
		/* Render here */
		lgfx_clearcolorbuffer(0.f, 0.f, 0.f);
		
		lgfx_setblend(BLEND_ALPHA);
		for (int i = 0; i < 30; i++) {
			aux = instances[i];
			if (aux->active)
			{
				aux->font->draw("Hello Word", aux->pos);
				aux->pos = Vec2(aux->pos.GetfX() - (aux->speed * deltaTime), aux->pos.GetfY());
			}
		}

		time = glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
	}

	for (size_t i = 0; i < 30; i++)
	{
		delete instances[i];
	};

	void glfwTerminate();
	return 0;
}

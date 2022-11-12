#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "..\project\CSprite.h"
//#include "litegfx.h"
#include <glfw3.h>
//#include"stb_image.h"
#include "..\project\Vec2.h"



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
	if (!glfwInit())
	{
		printf("ERROR EN INICIALIZAR");
		return -1;
	}
	double x = 0.f;
	double y = 0.f;
	GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Prueba", nullptr, nullptr);
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwMakeContextCurrent(pWindow);
	
	lgfx_setup2d(WIDTH, HEIGHT);

	CSprite* abeja = CSprite::loadTexture("C:\\Users\\pedro\\source\\repos\\p-collado\\PracticasJavier.Alegre\\sprites\\bee_anim.png");
	abeja->setFps(8);
	Vec2 Cursor(x, y);
	Vec2 Distance;


	
	double time = 0.f;
	double deltaTime = 0;

	while (!glfwWindowShouldClose(pWindow))
	{
		deltaTime = glfwGetTime() - time;
		/* Poll for and process events */
		glfwPollEvents();
		glfwGetCursorPos(pWindow,&x , &y);

		Cursor = Vec2(x,y);
		Distance = Cursor - abeja->getPosition();
		Distance = Cursor.Normalvector(Distance);
		
		Vec2 NewPos = Distance * 128.f * deltaTime;
		NewPos = NewPos + abeja->getPosition();
		abeja->setPosition(NewPos);

		xpos = Cursor.GetfX();
		ypos = Cursor.GetfY();
	
		/* Render here */
		lgfx_clearcolorbuffer(0.f, 0.f, 0.f);
		
		lgfx_setblend(BLEND_ALPHA);
		abeja->update(deltaTime);

		time = glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
	}

	void glfwTerminate();
	return 0;
}

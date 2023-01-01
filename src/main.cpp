#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "..\project\CSprite.h"
#include <glfw3.h>
#include "..\project\Vec2.h"
#include <math.h>

#define HEIGHT 720
#define WIDTH 1280

using namespace std;

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

	CSprite* bee = CSprite::loadTexture("sprites\\ball.png");
	bee->setCollisionType(CSprite::COLLISION_CIRCLE);
	CSprite* ball = CSprite::loadTexture("sprites\\box.png");
	ball->setCollisionType(CSprite::COLLISION_RECT);
	CSprite* box = CSprite::loadTexture("sprites\\box.png");
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

		xpos = Cursor.GetfX();
		ypos = Cursor.GetfY();
	
		/* Render here */
		lgfx_clearcolorbuffer(0.f, 0.f, 0.f);
		lgfx_setblend(BLEND_ALPHA);

		bee->setPosition(Vec2(200,400));
		ball->setPosition(Cursor);

		bee->draw();
		ball->draw();

		printf("%d\n",bee->getCollider()->collides(*(ball->getCollider())));


		time = glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
	}

	void glfwTerminate();

	return 0;
}

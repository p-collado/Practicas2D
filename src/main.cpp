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

void Scale(CSprite& _sprite, double* _scale, double _deltaTime)
{
	if (_sprite.getScale().GetfX() >  1.1 || _sprite.getScale().GetfX() < 0.9)
	{
		*_scale *= -1;
	}
	_sprite.setScale(Vec2(_sprite.getScale().GetfX() + (*(_scale) * _deltaTime), _sprite.getScale().GetfY() + (*(_scale) * _deltaTime)));
}



int main() 
{
	if (!glfwInit())
	{
		printf("ERROR EN INICIALIZAR");
		return -1;
	}

	double escalado = 0.f;
	double x = 0.f;
	double y = 0.f;

	GLFWwindow* pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Prueba", nullptr, nullptr);
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwMakeContextCurrent(pWindow);
	
	lgfx_setup2d(WIDTH, HEIGHT);
	CSprite* bee = CSprite::loadTexture("..\\sprites\\bee.png");
	bee->setCollisionType(CSprite::COLLISION_PIXELS);
	CSprite* ball = CSprite::loadTexture("..\\sprites\\ball.png");
	ball->setCollisionType(CSprite::COLLISION_CIRCLE);
	CSprite* box = CSprite::loadTexture("..\\sprites\\box.png");
	box->setCollisionType(CSprite::COLLISION_RECT);
	CSprite* circle = CSprite::loadTexture("..\\sprites\\circle.png");
	circle->setCollisionType(CSprite::COLLISION_CIRCLE);

	Vec2 Cursor(x, y);
	Vec2 Distance;

	double time = 0.f;
	double deltaTime = 0;

	ball->setCallback(&Scale);
	box->setCallback(&Scale);

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

		box->setPosition(Vec2(1000, HEIGHT / 2));
		bee->setPosition(Vec2(WIDTH / 2 - 50, HEIGHT / 2));
		ball->setPosition(Vec2(200, HEIGHT / 2));
		circle->setPosition(Cursor);

		if (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			delete circle;
			circle = CSprite::loadTexture("..\\sprites\\circle.png");
			circle->setCollisionType(CSprite::COLLISION_CIRCLE);
		}

		if (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			delete circle;
			circle = CSprite::loadTexture("..\\sprites\\rect.png");
			circle->setCollisionType(CSprite::COLLISION_RECT);
		}

		if (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
		{
			delete circle;
			circle = CSprite::loadTexture("..\\sprites\\bee.png");
			circle->setCollisionType(CSprite::COLLISION_PIXELS);
		}


		if (glfwGetKey(pWindow, GLFW_KEY_H) == GLFW_PRESS)
		{
			int a = 1;
		}

		if (box->collides(*circle) || ball->collides(*circle) || bee->collides(*circle))
		{
			lgfx_setcolor(1, 0, 0, 0.5);
		}

		else 
		{
			lgfx_setcolor(1, 1, 1, 1);
		}

		ball->update(deltaTime);
		box->update(deltaTime);
		bee->draw();
		circle->draw();

		time = glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
	}

	void glfwTerminate();

	return 0;
}
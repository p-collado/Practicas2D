#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "..\project\CSprite.h"
#include <glfw3.h>
#include "..\project\Vec2.h"
#include <cstdio>
#include "World.h"

#define HEIGHT 720
#define WIDTH 1280

using namespace std;

float xpos;
float ypos;

void Scale(CSprite& _sprite, double* _scale, double _deltaTime)
{
	if (_deltaTime < 0.1) //delay
	{
		if (_sprite.getScale().GetfX() >  1.1 || _sprite.getScale().GetfX() < 0.9)
		{
			*_scale *= -1;
		}
		_sprite.setScale(Vec2(_sprite.getScale().GetfX() + (*(_scale) * _deltaTime), _sprite.getScale().GetfY() + (*(_scale) * _deltaTime)));
	}
}


void BehaviourBee()
{

}


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
	CSprite* bee = CSprite::loadTexture("..\\sprites\\bee.png");
	CSprite* back1 = CSprite::loadTexture("..\\sprites\\level.png");
	bee->setCollisionType(CSprite::COLLISION_PIXELS);
	World world(0.15,0.15,0.15,back1->getTexture(),nullptr,nullptr,nullptr);
	world.addSprite(*bee);
	world.setScrollRatio(0, 1.f);

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
		world.setCameraPosition(Cursor);

		xpos = Cursor.GetfX();
		ypos = Cursor.GetfY();
	
		/* Render here */
		lgfx_clearcolorbuffer(0.f, 0.f, 0.f);
		lgfx_setblend(BLEND_ALPHA);

		bee->setPosition(Cursor);


		if (glfwGetKey(pWindow, GLFW_KEY_P))
		{
			int b = 0;
		}
		world.draw(Vec2(WIDTH,HEIGHT));
		world.update(deltaTime);
		//bee->draw();

		time = glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);
	}

	void glfwTerminate();

	return 0;
}
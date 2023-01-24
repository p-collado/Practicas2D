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


void BehaviourBee(CSprite& _Sprite, double _delta)
{
	Vec2 Distance;
	Vec2 Cursor = *(static_cast<Vec2*>(_Sprite.getUserData()));

	Distance = Cursor - _Sprite.getPosition();
	if (!(Distance.GetfX() == 0.f && Distance.GetfY() == 0))
	{
		Distance = Cursor.Normalvector(Distance);
		Vec2 NewPos = Distance * 128.f * _delta;
		NewPos = NewPos + _Sprite.getPosition();
		_Sprite.setPosition(NewPos);
	}
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
	CSprite* bee = CSprite::loadTexture("..\\sprites\\bee_anim.png");
	CSprite* back1 = CSprite::loadTexture("..\\sprites\\level.png");
	CSprite* back2 = CSprite::loadTexture("..\\sprites\\trees1.png");
	CSprite* back3 = CSprite::loadTexture("..\\sprites\\trees2.png");
	CSprite* back4 = CSprite::loadTexture("..\\sprites\\clouds.png");

	bee->setCollisionType(CSprite::COLLISION_PIXELS);
	bee->setFps(8);
	bee->setMaxRot(-15);
	bee->sethframes(8);
	bee->setCallback(&BehaviourBee);

	World world(0.15,0.15,0.15,back4->getTexture(),back3->getTexture(), back2->getTexture(), back1->getTexture());

	world.addSprite(*bee);
	world.setScrollRatio(0, 1.f);

	Vec2 Worldcursor(x, y);
	Vec2 Distance;

	double time = 0.f;
	double deltaTime = 0;

	while (!glfwWindowShouldClose(pWindow))
	{
		deltaTime = glfwGetTime() - time;
		/* Poll for and process events */
		glfwPollEvents();
		glfwGetCursorPos(pWindow,&x , &y);

		Worldcursor = Vec2(x + bee->getPosition().GetfX() - WIDTH/2, y + bee->getPosition().GetfY() - HEIGHT/2);
		world.setCameraPosition(Vec2(bee->getPosition().GetfX() - WIDTH/2, bee->getPosition().GetfY() - HEIGHT/2));
		bee->setUserData(&Worldcursor);
	

		xpos = Worldcursor.GetfX();
		ypos = Worldcursor.GetfY();
	
		/* Render here */
		lgfx_clearcolorbuffer(0.f, 0.f, 0.f);
		lgfx_setblend(BLEND_ALPHA);

		//bee->setPosition(Worldcursor);

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
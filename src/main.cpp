#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "..\project\CSprite.h"
//#include "litegfx.h"
#include <glfw3.h>
//#include"stb_image.h"
#include "..\project\Vec2.h"
#include <math.h>



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

	CSprite* abeja = CSprite::loadTexture("C:\\Users\\pedro\\source\\repos\\p-collado\\programacion2d\\sprites\\bee_anim.png");
	abeja->setFps(8);
	abeja->setMaxRot(-15);
	Vec2 Cursor(x, y);
	Vec2 Distance;


	float angle = 0.f;
	double time = 0.f;
	double deltaTime = 0;
	float resta = 0.f;
	while (!glfwWindowShouldClose(pWindow))
	{
		deltaTime = glfwGetTime() - time;
		/* Poll for and process events */
		glfwPollEvents();
		glfwGetCursorPos(pWindow,&x , &y);


		//Seek mouse and bee Movement
		Cursor = Vec2(x,y);
		Distance = Cursor - abeja->getPosition();
		Distance = Cursor.Normalvector(Distance);
		Vec2 NewPos = Distance * 128.f * deltaTime;
		NewPos = NewPos + abeja->getPosition();
		abeja->setPosition(NewPos);


		//Rotation
		if (angle > abeja->getMaxRot())
		{
			if (Cursor.GetfX() > abeja->getPosition().GetfX())
			{
				angle -= 32 * deltaTime;
				abeja->setAngle(angle);
			}
		}

		if (angle < (abeja->getMaxRot())*-1)
		{
			if (Cursor.GetfX() < abeja->getPosition().GetfX())
			{
				angle += 32 * deltaTime;
				abeja->setAngle(angle);
			}
		}


		//Flip logic
		if (Cursor.GetfX()<abeja->getPosition().GetfX() - 1)//DUDA:se raya cuando el numero son casi iguales, DUDA, FLIP Y ROTACION
		{
			abeja->setScale(Vec2(-1.f,1.f));
		}
		if(Cursor.GetfX() > abeja->getPosition().GetfX() - 1)
		{
			abeja->setScale(Vec2(1.f, 1.f));
		}

		//Idle Logic
		if (fabs(Cursor.GetfX() - abeja->getPosition().GetfX()) < 1)
		{
			if(abeja->getAngle() < 0)
			{
				angle += 32 * deltaTime;
				abeja->setAngle(angle);
			}

			if (abeja->getAngle() > 0)
			{
				angle -= 32 * deltaTime;
				abeja->setAngle(angle);
			}
		}

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

#include "PLAYER.h"

GLfloat mouseDeg = 0.f;
GLboolean plusDeg = true;

void PLAYER::init(string str)
{
	ReadObj(str, vertexInfo);
	initBuffer(&VAO, &VBO, vertexInfo);
}

//--- 스케일 변환
void PLAYER::scaleTransform(float x, float y, float z)
{
	scale = glm::mat4(1.0f);

	scale = glm::scale(glm::vec3(x, y, z));
	vec_transform.emplace_back(scale);
}

//--- 회전 변환
void PLAYER::rotateTransform(float x, float y, float z, float degree)
{
	rotate = glm::mat4(1.0f);

	rotate = glm::rotate(glm::radians(degree), glm::vec3(x, y, z));
	vec_transform.emplace_back(rotate);
}

//--- 위치 변환
void PLAYER::moveTranform(float x, float y, float z)
{
	move = glm::mat4(1.0f);

	move = glm::translate(glm::vec3(x, y, z));
	vec_transform.emplace_back(move);
}

RECT PLAYER::get_BB()
{
	RECT temp;
	
	temp.left   = x - 10.0;
	temp.top    = z - 10.0;
	temp.right  = x + 10.0;
	temp.bottom = z + 10.0;
	
	return temp;
}

void PLAYER::update()
{
	merge = glm::mat4(1.0f);

	for (int i = 0; i < vec_transform.size(); ++i)
	{
		merge = vec_transform[i] * merge;
	}
	vec_transform.clear();

}

void PLAYER::draw(int R, int G, int B)
{
	changeColor(R, G, B);
	glBindVertexArray(VAO);
	unsigned int alpa = glGetUniformLocation(shaderID, "lighting_switch");
	glUniform1i(alpa, 0);
	unsigned int modelTransform = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelTransform, 1, GL_FALSE, glm::value_ptr(merge));
	if (isOn)
		glDrawArrays(GL_TRIANGLES, 0, vertexInfo.size());
}

void PLAYER::changeColor(int R, int G, int B)
{
	float r = (float)R / 255.f;
	float g = (float)G / 255.f;
	float b = (float)B / 255.f;

	glUniform3f(glGetUniformLocation(shaderID, "objectColor"), r, g, b);
}

void PLAYER::reset_pos()
{
	isOn = TRUE;

	float temp_x = 250-get_xPos();
	float temp_z = 270.0-get_zPos();
	x += temp_x;
	z += temp_z;
}

PLAYER::PLAYER()
{
	mouseDeg  = 0.f;
	objectDeg = 0.f;
	size = 0.f;
}

PLAYER::~PLAYER()
{
}

GLvoid initPlayer()
{
	//pacmanTop.init(255, 255, 0, "asset/packman_top.obj");
	//pacmanBot.init(255, 255, 0, "asset/packman_bottom.obj");
	//pacmanEyes.init(0, 0, 0, "asset/packman_eyes.obj");
	//pacmanNose.init(255, 255, 0, "asset/packman_nose.obj");
	pacmanTop.init( "asset/packman_top.obj");
	pacmanBot.init( "asset/packman_bottom.obj");
	pacmanEyes.init( "asset/packman_eyes.obj");
	pacmanNose.init( "asset/packman_nose.obj");

	pacmanTop .moveObject(250, 270);
	pacmanBot .moveObject(250, 270);
	pacmanEyes.moveObject(250, 270);
	pacmanNose.moveObject(250, 270);

	pacmanTop.scaleTransform(25.0, 25.0, 25.0);
	pacmanBot.scaleTransform (25.0, 25.0, 25.0);
	pacmanEyes.scaleTransform(25.0, 25.0, 25.0);
	pacmanNose.scaleTransform(25.0, 25.0, 25.0);

	pacmanTop.update();
	pacmanBot.update();
	pacmanEyes.update();
	pacmanNose.update();
}

GLvoid ResetPlayer()
{
	pacmanTop.reset_pos();
	pacmanBot.reset_pos();
	pacmanEyes.reset_pos();
	pacmanNose.reset_pos();

}

GLvoid redrawPlayer()
{
	// getsize추가
	pacmanTop.scaleTransform  (25.0 + pacmanTop.get_size(), 25.0 + pacmanTop.get_size(), 25.0 + pacmanTop.get_size());
	pacmanTop.rotateTransform (1.f, 0.f, 0.f, -mouseDeg);
	pacmanTop.rotateTransform (0.f, 1.f, 0.f, pacmanTop.get_Deg());
	pacmanTop.moveTranform    (pacmanTop.get_xPos(), 0.f, pacmanTop.get_zPos());

	pacmanBot.scaleTransform  (25.0 + pacmanBot.get_size(), 25.0 + pacmanBot.get_size(), 25.0 + pacmanBot.get_size());
	pacmanBot.rotateTransform (1.f, 0.f, 0.f, mouseDeg);
	pacmanBot.rotateTransform (0.f, 1.f, 0.f, pacmanBot.get_Deg());
	pacmanBot.moveTranform    (pacmanBot.get_xPos(), 0.f, pacmanBot.get_zPos());

	pacmanEyes.scaleTransform  (25.0 + pacmanEyes.get_size(), 25.0 + pacmanEyes.get_size(), 25.0 + pacmanEyes.get_size());
	pacmanEyes.rotateTransform (1.f, 0.f, 0.f, -mouseDeg);
	pacmanEyes.rotateTransform (0.f, 1.f, 0.f, pacmanEyes.get_Deg());
	pacmanEyes.moveTranform    (pacmanEyes.get_xPos(), 0.f, pacmanEyes.get_zPos());

	pacmanNose.scaleTransform  (25.0 + pacmanNose.get_size(), 25.0 + pacmanNose.get_size(), 25.0 + pacmanNose.get_size());
	pacmanNose.rotateTransform (1.f, 0.f, 0.f, -mouseDeg);
	pacmanNose.rotateTransform (0.f, 1.f, 0.f, pacmanNose.get_Deg());
	pacmanNose.moveTranform    (pacmanNose.get_xPos(), 0.f, pacmanNose.get_zPos());

	pacmanTop.update();
	pacmanBot.update();
	pacmanEyes.update();
	pacmanNose.update();
}

GLvoid animatePlayer()
{
	if (plusDeg) 
	{ 
		mouseDeg += 1.0f; 
		if (mouseDeg >= 20.0f)
		{
			plusDeg = false;
		}
	}
	else
	{
		mouseDeg -= 1.0f;
		if (mouseDeg <= 0.0f)
		{
			plusDeg = true;
		}
	}
}


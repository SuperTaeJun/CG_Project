#include "PET.h"

void PET::init(string str)
{
	ReadObj(str, vertexInfo);
	initBuffer(&VAO, &VBO, vertexInfo);
}

//--- 스케일 변환
void PET::scaleTransform(float x, float y, float z)
{
	scale = glm::mat4(1.0f);

	scale = glm::scale(glm::vec3(x, y, z));
	vec_transform.emplace_back(scale);
}

//--- 회전 변환
void PET::rotateTransform(float x, float y, float z, float degree)
{
	rotate = glm::mat4(1.0f);

	rotate = glm::rotate(glm::radians(degree), glm::vec3(x, y, z));
	vec_transform.emplace_back(rotate);
}

//--- 위치 변환
void PET::moveTranform(float x, float y, float z)
{
	move = glm::mat4(1.0f);

	move = glm::translate(glm::vec3(x, y, z));
	vec_transform.emplace_back(move);
}

RECT PET::get_BB()
{
	RECT temp;

	temp.left = x - 10.0;
	temp.top = z - 10.0;
	temp.right = x + 10.0;
	temp.bottom = z + 10.0;

	return temp;
}

void PET::update()
{
	merge = glm::mat4(1.0f);

	for (int i = 0; i < vec_transform.size(); ++i)
	{
		merge = vec_transform[i] * merge;
	}
	vec_transform.clear();

}

void PET::draw(int R, int G, int B)
{
	changeColor(R, G, B);
	glBindVertexArray(VAO);
	unsigned int modelTransform = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelTransform, 1, GL_FALSE, glm::value_ptr(merge));
	glDrawArrays(GL_TRIANGLES, 0, vertexInfo.size());
}

void PET::changeColor(int R, int G, int B)
{
	float r = (float)R / 255.f;
	float g = (float)G / 255.f;
	float b = (float)B / 255.f;

	glUniform3f(glGetUniformLocation(shaderID, "objectColor"), r, g, b);
}

PET::PET()
{
	mouseDeg = 0.f;
	objectDeg = 0.f;
	isJump = false;
}

PET::~PET()
{
}

GLvoid initPET()
{
	petTop.init("asset/packman_top.obj");
	petBot.init("asset/packman_bottom.obj");
	petEyes.init("asset/packman_eyes.obj");
	petNose.init("asset/packman_nose.obj");

	/*petTop.moveObject (230, 270);
	petBot.moveObject (230, 270);
	petEyes.moveObject(230, 270);
	petNose.moveObject(230, 270);*/

	petTop.moveObject(250, 270);
	petBot.moveObject(250, 270);
	petEyes.moveObject(250, 270);
	petNose.moveObject(250, 270);

	petTop.scaleTransform (12.5, 12.5, 12.5);
	petBot.scaleTransform (12.5, 12.5, 12.5);
	petEyes.scaleTransform(12.5, 12.5, 12.5);
	petNose.scaleTransform(12.5, 12.5, 12.5);

	petTop.update();
	petBot.update();
	petEyes.update();
	petNose.update();
}

GLvoid redrawPET()
{
	petTop.scaleTransform(12.5, 12.5, 12.5);
	petTop.rotateTransform(1.f, 0.f, 0.f, -mouseDeg);
	petTop.moveTranform(petTop.get_xPos() + 15 * glm::cos(glm::radians(petTop.get_Deg())), petTop.get_yPos(), petTop.get_zPos() + 15 * glm::sin(glm::radians(petTop.get_Deg())));
	//petTop.rotateTransform(0.f, 1.f, 0.f, petTop.get_Deg());

	petBot.scaleTransform(12.5, 12.5, 12.5);
	petBot.rotateTransform(1.f, 0.f, 0.f, mouseDeg);
	petBot.moveTranform(petBot.get_xPos() + 15 * glm::cos(glm::radians(petBot.get_Deg())), petBot.get_yPos(), petBot.get_zPos() + 15 * glm::sin(glm::radians(petBot.get_Deg())));
	//petBot.rotateTransform(0.f, 1.f, 0.f, petBot.get_Deg());

	petEyes.scaleTransform(12.5, 12.5, 12.5);
	petEyes.rotateTransform(1.f, 0.f, 0.f, -mouseDeg);
	petEyes.moveTranform(petEyes.get_xPos() + 15 * glm::cos(glm::radians(petEyes.get_Deg())), petEyes.get_yPos(), petEyes.get_zPos() + 15 * glm::sin(glm::radians(petEyes.get_Deg())));
	//petEyes.rotateTransform(0.f, 1.f, 0.f, petEyes.get_Deg());

	petNose.scaleTransform(12.5, 12.5, 12.5);
	petNose.rotateTransform(1.f, 0.f, 0.f, -mouseDeg);
	petNose.moveTranform(petNose.get_xPos() + 15 * glm::cos(glm::radians(petNose.get_Deg())), petNose.get_yPos(), petNose.get_zPos() + 15 * glm::sin(glm::radians(petNose.get_Deg())));
	//petNose.rotateTransform(0.f, 1.f, 0.f, petNose.get_Deg());

	petTop.update();
	petBot.update();
	petEyes.update();
	petNose.update();
}

GLvoid animatePET()
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


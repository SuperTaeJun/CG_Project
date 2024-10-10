#include "START.h"

void START::init()
{
	ReadObj("asset/logo_startbutton.obj", vertexInfo);
	initBuffer(&VAO, &VBO, vertexInfo);
	ReadObj("asset/logo_1playeronly.obj", vertexInfo2);
	initBuffer(&VAO2, &VBO2, vertexInfo2);
}

void START::scaleTransform(float x, float y, float z)
{
	scale = glm::mat4(1.0f);

	scale = glm::scale(glm::vec3(x, y, z));
	vec_transform.emplace_back(scale);
}

void START::rotateTransform(float x, float y, float z, float degree)
{
	rotate = glm::mat4(1.0f);

	rotate = glm::rotate(glm::radians(degree), glm::vec3(x, y, z));
	vec_transform.emplace_back(rotate);
}

void START::moveTranform(float x, float y, float z)
{
	move = glm::mat4(1.0f);

	move = glm::translate(glm::vec3(x, y, z));
	vec_transform.emplace_back(move);
}

void START::update()
{
	merge = glm::mat4(1.0f);

	for (int i = 0; i < vec_transform.size(); ++i)
	{
		merge = vec_transform[i] * merge;
	}
	vec_transform.clear();
}

void START::draw(int R, int G, int B,int R2, int G2, int B2)
{
	//logo_startbutton
	changeColor(R, G, B);
	glBindVertexArray(VAO);
	unsigned int alpa = glGetUniformLocation(shaderID, "lighting_switch");
	glUniform1i(alpa, 0);
	scaleTransform(2.0, 10000.0, 5.0);
	rotateTransform(1.0, 0.0, 0.0, 90);
	moveTranform(0.0, 180.0, 0.0);
	moveTranform(0.0, drop, 0.0);
	update();
	unsigned int modelTransform = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelTransform, 1, GL_FALSE, glm::value_ptr(merge));
	glDrawArrays(GL_TRIANGLES, 0, vertexInfo.size());

	// logo_1playeronly
	changeColor(R2, G2, B2);
	glBindVertexArray(VAO2);
	scaleTransform(2.0, 10000.0, 2.0);
	rotateTransform(1.0, 0.0, 0.0, 90);
	moveTranform(0.0, 100.0, 0.0);
	moveTranform(0.0, 0.0, drop);
	update();
	modelTransform = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelTransform, 1, GL_FALSE, glm::value_ptr(merge));
	glDrawArrays(GL_TRIANGLES, 0, vertexInfo.size());

}

void START::changeColor(int R, int G, int B)
{
	float r = (float)R / 255.f;
	float g = (float)G / 255.f;
	float b = (float)B / 255.f;


	glUniform3f(glGetUniformLocation(shaderID, "objectColor"), r, g, b);
}

void START::animate(int y)
{
	drop = y;

	if (drop == 150)
	{
		change_state();
	}
}

void InitStart()
{
}

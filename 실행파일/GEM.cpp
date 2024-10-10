#include "GEM.h"

void GEM::init( string str)
{
	ReadObj(str, vertexInfo);
	initBuffer(&VAO, VBO, vertexInfo);
}

//--- 스케일 변환
void GEM::scaleTransform(float x, float y, float z)
{
	scale = glm::mat4(1.0f);

	scale = glm::scale(glm::vec3(x, y, z));
	vec_transform.emplace_back(scale);
}

//--- 회전 변환
void GEM::rotateTransform(float x, float y, float z, float degree)
{
	rotate = glm::mat4(1.0f);

	rotate = glm::rotate(glm::radians(degree), glm::vec3(x, y, z));
	vec_transform.emplace_back(rotate);
}

//--- 위치 변환
void GEM::moveTranform(float x, float y, float z)
{
	pos_x = x;
	pos_z = z;

	move = glm::mat4(1.0f);

	move = glm::translate(glm::vec3(x, y, z));
	vec_transform.emplace_back(move);
}

RECT GEM::get_BB()
{
	RECT temp;

	temp.left = pos_x - 1.0;
	temp.top = pos_z - 1.0;
	temp.right = pos_x + 1.0;
	temp.bottom = pos_z + 1.0;

	return temp;
}

void GEM::update()
{
	merge = glm::mat4(1.0f);

	for (int i = 0; i < vec_transform.size(); ++i)
	{
		merge = vec_transform[i] * merge;
	}
	vec_transform.clear();
}

void GEM::draw(int R, int G, int B)
{
	changeColor(R, G, B);
	glBindVertexArray(VAO);
	glEnable(GL_BLEND);
	unsigned int alpa = glGetUniformLocation(shaderID, "lighting_switch");
	glUniform1i(alpa, 1);
	unsigned int modelTransform = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelTransform, 1, GL_FALSE, glm::value_ptr(merge));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if(isOn)
		glDrawArrays(GL_TRIANGLES, 0, vertexInfo.size());
	glDisable(GL_BLEND);
}

void GEM::changeColor(int R, int G, int B)
{
	float r = (float)R / 255.f;
	float g = (float)G / 255.f;
	float b = (float)B / 255.f;


	glUniform3f(glGetUniformLocation(shaderID, "objectColor"), r, g, b);
}

void GEM::collid()
{
	isOn = FALSE;
}

void GEM::reset()
{
	isOn = TRUE;
}

GEM::GEM()
{
}

GEM::~GEM()
{
}

void InitGem(GEM gem[100])
{
	for (int i{}; i < 12; ++i)
	{
		gem[i].init("asset/tile.obj");
		gem[i].scaleTransform(35.0f, 35.0f, 35.0f);
		gem[i].moveTranform(-270.0+(i*20.0), 0.0, -270.0);
		gem[i].update();
		gem[i+12].init("asset/tile.obj");
		gem[i+12].scaleTransform(35.0f, 35.0f, 35.0f);
		gem[i+12].moveTranform(250.0 - (i * 20.0), 0.0, -270.0);
		gem[i+12].update();
		if (i < 7)
		{
			gem[i+24].init("asset/tile.obj");
			gem[i+24].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i+24].moveTranform(-270.0 , 0.0, -250.0 + (i * 20.0));
			gem[i+24].update();
			gem[i+31].init("asset/tile.obj");
			gem[i+31].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i+31].moveTranform(+250.0, 0.0, -250.0 + (i * 20.0));
			gem[i+31].update();
		}
		gem[i + 38].init("asset/tile.obj");
		gem[i + 38].scaleTransform(35.0f, 35.0f, 35.0f);
		gem[i + 38].moveTranform(-170.0, 0.0, -250.0 + (i * 20.0));
		gem[i + 38].update();
		gem[i + 50].init("asset/tile.obj");
		gem[i + 50].scaleTransform(35.0f, 35.0f, 35.0f);
		gem[i + 50].moveTranform(150.0, 0.0, -250.0 + (i * 20.0));
		gem[i + 50].update();
		if (i < 4)
		{
			gem[i + 62].init("asset/tile.obj");
			gem[i + 62].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 62].moveTranform(-250.0 + (i * 20.0), 0.0, -190.0);
			gem[i + 62].update();
			gem[i + 66].init("asset/tile.obj");
			gem[i + 66].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 66].moveTranform(-250.0 + (i * 20.0), 0.0, -130.0);
			gem[i + 66].update();
			gem[i + 70].init("asset/tile.obj");
			gem[i + 70].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 70].moveTranform(+230.0 - (i * 20.0), 0.0, -190.0);
			gem[i + 70].update();
			gem[i + 74].init("asset/tile.obj");
			gem[i + 74].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 74].moveTranform(+230.0 - (i * 20.0), 0.0, -130.0);
			gem[i + 74].update();
		}
		if (i < 8)
		{
			gem[i + 78].init("asset/tile.obj");
			gem[i + 78].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 78].moveTranform(-150.0 + (i * 20.0), 0.0, -190.0);
			gem[i + 78].update();
			gem[i + 86].init("asset/tile.obj");
			gem[i + 86].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 86].moveTranform(130.0 - (i * 20.0), 0.0, -190.0);
			gem[i + 86].update();
		}
		if (i < 3)
		{
			gem[i + 94].init("asset/tile.obj");
			gem[i + 94].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 94].moveTranform(-50.0, 0.0, -250.0 + (i * 20.0));
			gem[i + 94].update();
			gem[i + 97].init("asset/tile.obj");
			gem[i + 97].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 97].moveTranform(30.0, 0.0, -250.0 + (i * 20.0));
			gem[i + 97].update();
			gem[i + 100].init("asset/tile.obj");
			gem[i + 100].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 100].moveTranform(-110.0, 0.0, -170.0 + (i * 20.0));
			gem[i + 100].update();
			gem[i + 103].init("asset/tile.obj");
			gem[i + 103].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 103].moveTranform(90.0, 0.0, -170.0 + (i * 20.0));
			gem[i + 103].update();
			gem[i + 106].init("asset/tile.obj");
			gem[i + 106].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 106].moveTranform(-90.0 + (i * 20.0), 0.0, -130.0);
			gem[i + 106].update();
			gem[i + 109].init("asset/tile.obj");
			gem[i + 109].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 109].moveTranform(70.0 - (i * 20.0), 0.0, -130.0);
			gem[i + 109].update();
		}
		if (i < 2)
		{
			gem[i + 112].init("asset/tile.obj");
			gem[i + 112].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 112].moveTranform(-50.0, 0.0, -110.0 + (i * 20.0));
			gem[i + 112].update();
			gem[i + 114].init("asset/tile.obj");
			gem[i + 114].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 114].moveTranform(30.0, 0.0, -110.0 + (i * 20.0));
			gem[i + 114].update();
		}
		if (i < 11)
		{
			gem[i + 116].init("asset/tile.obj");
			gem[i + 116].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 116].moveTranform(-110.0 + (i * 20.0), 0.0, -70.0);
			gem[i + 116].update();
		}
		gem[i + 127].init("asset/tile.obj");
		gem[i + 127].scaleTransform(35.0f, 35.0f, 35.0f);
		gem[i + 127].moveTranform(-110.0 , 0.0, -50.0 + (i * 20.0));
		gem[i + 127].update();
		gem[i + 139].init("asset/tile.obj");
		gem[i + 139].scaleTransform(35.0f, 35.0f, 35.0f);
		gem[i + 139].moveTranform(90.0, 0.0, -50.0 + (i * 20.0));
		gem[i + 139].update();
		if (i < 9)
		{
			gem[i + 151].init("asset/tile.obj");
			gem[i + 151].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 151].moveTranform(-290.0 + (i * 20.0), 0.0, 10.0);
			gem[i + 151].update();
			gem[i + 160].init("asset/tile.obj");
			gem[i + 160].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 160].moveTranform(270.0 - (i * 20.0), 0.0, 10.0);
			gem[i + 160].update();
		}
		if (i < 5)
		{
			gem[i + 169].init("asset/tile.obj");
			gem[i + 169].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 169].moveTranform(-170.0 , 0.0, 50.0 + (i * 20.0));
			gem[i + 169].update();
			gem[i + 174].init("asset/tile.obj");
			gem[i + 174].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 174].moveTranform(150.0, 0.0, 50.0 + (i * 20.0));
			gem[i + 174].update();
		}
		if (i < 8)
		{
			gem[i + 179].init("asset/tile.obj");
			gem[i + 179].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 179].moveTranform(-270.0 + (i * 20.0), 0.0, 150.0 );
			gem[i + 179].update();
			gem[i + 187].init("asset/tile.obj");
			gem[i + 187].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 187].moveTranform(250.0 - (i * 20.0), 0.0, 150.0);
			gem[i + 187].update();
		}
		if (i < 6)
		{
			gem[i + 195].init("asset/tile.obj");
			gem[i + 195].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 195].moveTranform(-270.0, 0.0, 170.0 + (i * 20.0));
			gem[i + 195].update();
			gem[i + 201].init("asset/tile.obj");
			gem[i + 201].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 201].moveTranform(250.0, 0.0, 170.0 + (i * 20.0));
			gem[i + 201].update();
		}
		gem[i + 207].init("asset/tile.obj");
		gem[i + 207].scaleTransform(35.0f, 35.0f, 35.0f);
		gem[i + 207].moveTranform(-250.0 + (i * 20.0), 0.0, 270.0 );
		gem[i + 207].update();
		gem[i + 219].init("asset/tile.obj");
		gem[i + 219].scaleTransform(35.0f, 35.0f, 35.0f);
		gem[i + 219].moveTranform(230.0 - (i * 20.0), 0.0, 270.0);
		gem[i + 219].update();
		if (i < 8)
		{
			gem[i + 231].init("asset/tile.obj");
			gem[i + 231].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 231].moveTranform(-250.0 + (i * 20.0), 0.0, 210.0);
			gem[i + 231].update();
			gem[i + 239].init("asset/tile.obj");
			gem[i + 239].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 239].moveTranform(230.0 - (i * 20.0), 0.0, 210.0);
			gem[i + 239].update();
		}
		if (i < 7)
		{
			gem[i + 247].init("asset/tile.obj");
			gem[i + 247].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 247].moveTranform(-50.0, 0.0, 250.0 - (i * 20.0));
			gem[i + 247].update();
			gem[i + 254].init("asset/tile.obj");
			gem[i + 254].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 254].moveTranform(30.0, 0.0, 250.0 - (i * 20.0));
			gem[i + 254].update();
		}
		if (i < 3)
		{
			gem[i + 261].init("asset/tile.obj");
			gem[i + 261].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 261].moveTranform(-30.0 + (i * 20.0), 0.0, 190.0 );
			gem[i + 261].update();
		}
		if (i < 10)
		{
			gem[i + 264].init("asset/tile.obj");
			gem[i + 264].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 264].moveTranform(-110.0 + (i * 20.0), 0.0, 70.0);
			gem[i + 264].update();
		}
		if (i < 2)
		{
		
			gem[i + 274].init("asset/tile.obj");
			gem[i + 274].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 274].moveTranform(-90.0 + (i * 20.0), 0.0, 130.0);
			gem[i + 274].update();
			gem[i + 276].init("asset/tile.obj");
			gem[i + 276].scaleTransform(35.0f, 35.0f, 35.0f);
			gem[i + 276].moveTranform(70.0 - (i * 20.0), 0.0, 130.0);
			gem[i + 276].update();
		}
		gem[278].init("asset/tile.obj");
		gem[278].scaleTransform(35.0f, 35.0f, 35.0f);
		gem[278].moveTranform(-110.0, 0.0, 190.0);
		gem[278].update();
		gem[279].init("asset/tile.obj");
		gem[279].scaleTransform(35.0f, 35.0f, 35.0f);
		gem[279].moveTranform(90.0, 0.0, 190.0);
		gem[279].update();

	}
}

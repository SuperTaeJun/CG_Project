#include "MONSTER.h"

void GHOST::init(int R, int G, int B, string str,float pos_x,float pos_z)
{
	ReadObj(str, vertexInfo);
	initBuffer(&VAO, VBO, vertexInfo);
	//changeColor(R, G, B);
	x = pos_x;
	z = pos_z;
}

void GHOST::ResetGhost(float _posX, float _posZ)
{
	float temp_x = _posX - x;
	float temp_z = _posZ - z;
	x += temp_x;
	z += temp_z;
	//moveTranform(temp_x, 0.0, temp_z);
	//update();
}

//--- 스케일 변환
void GHOST::scaleTransform(float x, float y, float z)
{
	scale = glm::mat4(1.0f);

	scale = glm::scale(glm::vec3(x, y, z));
	vec_transform.emplace_back(scale);
}

//--- 회전 변환
void GHOST::rotateTransform(float x, float y, float z, float degree)
{
	rotate = glm::mat4(1.0f);

	rotate = glm::rotate(glm::radians(degree), glm::vec3(x, y, z));
	vec_transform.emplace_back(rotate);
}

//--- 위치 변환
void GHOST::moveTranform(float x, float y, float z)
{
	move = glm::mat4(1.0f);

	move = glm::translate(glm::vec3(x, y, z));
	vec_transform.emplace_back(move);
}

RECT GHOST::get_BB()
{
	RECT temp;

	// 제자리 바운딩 박스
	temp.left   = x - 10.0;
	temp.top    = z - 10.0;
	temp.right  = x + 10.0;
	temp.bottom = z + 10.0;

	return temp;
}

RECT GHOST::get_Top_BB()
{
	RECT temp;

	// 상 바운딩 박스
	temp.left   = x - 10.0;
	temp.top    = (z - 20.0) - 10.0;
	temp.right  = x + 10.0;
	temp.bottom = (z - 20.0) + 10.0;

	return temp;
}

RECT GHOST::get_Bottom_BB()
{
	RECT temp;

	// 하 바운딩 박스
	temp.left = (x) - 10.0;
	temp.top = (z + 20.0) - 10.0;
	temp.right = (x) + 10.0;
	temp.bottom = (z + 20.0) + 10.0;

	return temp;
}

RECT GHOST::get_Left_BB()
{
	RECT temp;

	// 좌 바운딩 박스
	temp.left = (x - 20.0) - 10.0;
	temp.top = (z) - 10.0;
	temp.right = (x - 20.0) + 10.0;
	temp.bottom = (z) + 10.0;

	return temp;
}

RECT GHOST::get_Right_BB()
{
	RECT temp;

	// 우 바운딩 박스
	temp.left = (x + 20.0) - 10.0;
	temp.top = (z) - 10.0;
	temp.right = (x + 20.0) + 10.0;
	temp.bottom = (z) + 10.0;

	return temp;
}

void GHOST::update()
{
	merge = glm::mat4(1.0f);

	for (int i = 0; i < vec_transform.size(); ++i)
	{
		merge = vec_transform[i] * merge;
	}
	vec_transform.clear();
}

void GHOST::draw(int R,int G,int B)
{
	changeColor(R, G, B);
	glBindVertexArray(VAO);
	unsigned int alpa = glGetUniformLocation(shaderID, "lighting_switch");
	glUniform1i(alpa, 0);
	unsigned int modelTransform = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelTransform, 1, GL_FALSE, glm::value_ptr(merge));
	//glDrawElements(GL_TRIANGLES, faceData.size() * 3, GL_UNSIGNED_INT, 0); 
	glDrawArrays(GL_TRIANGLES, 0, vertexInfo.size());
}

void GHOST::changeColor(int R, int G, int B)
{
	float r = (float)R / 255.f;
	float g = (float)G / 255.f;
	float b = (float)B / 255.f;


	glUniform3f(glGetUniformLocation(shaderID, "objectColor"), r, g, b);
}

int GHOST::AI()
{
	int direction = 0;
	int max_score = -10000;
	int score_top = 0, score_bot = 0, score_left = 0, score_right = 0;

	for (int i = 1; i < 5; ++i)
	{
		switch (i)
		{
		case 1: // 상
			for (int j = 0; j < 327; ++j)
			{
				if (MyintersectRect(get_Top_BB(), map[j].get_BB())) 
				{ 
					score_top -= 99999; 
					break;
				}
			}
			score_top -= abs((int(get_Top_xPos()) - int(pacmanBot.get_xPos()))) + abs((int(get_Top_zPos()) - int(pacmanBot.get_zPos())));
			break;
		case 2: // 하
			for (int j = 0; j < 327; ++j)
			{
				if (MyintersectRect(get_Bottom_BB(), map[j].get_BB())) 
				{ 
					score_bot -= 99999; 
					break;
				}
			}
			score_bot -= abs((int(get_Bot_xPos()) - int(pacmanBot.get_xPos()))) + abs((int(get_Bot_zPos()) - int(pacmanBot.get_zPos())));
			break;
		case 3: // 좌
			for (int j = 0; j < 327; ++j)
			{
				if (MyintersectRect(get_Left_BB(), map[j].get_BB())) 
				{ 
					score_left -= 99999; 
					break;
				}
			}
			score_left -= abs((int(get_Left_xPos()) - int(pacmanBot.get_xPos()))) + abs((int(get_Left_zPos()) - int(pacmanBot.get_zPos())));
			break;
		case 4: // 우
			for (int j = 0; j < 327; ++j)
			{
				if (MyintersectRect(get_Right_BB(), map[j].get_BB())) 
				{ 
					score_right -= 99999; 
					break;
				}
			}
			score_right -= abs((int(get_Right_xPos()) - int(pacmanBot.get_xPos()))) + abs((int(get_Right_zPos()) - int(pacmanBot.get_zPos())));
			break;
		}
	}

	if (score_top   >= max_score) { max_score = score_top,   direction = 1; }
	if (score_bot   >= max_score) { max_score = score_bot,   direction = 2; }
	if (score_left  >= max_score) { max_score = score_left,  direction = 3; }
	if (score_right >= max_score) { max_score = score_right, direction = 4; }

	return direction;
}

void GHOST::chase(int dir)
{
	scaleTransform(20., 20., 20.);
	switch (dir)
	{
	case 0:
		dz = 0.f;
		dx = 0.f;
		break;
	case 1://상
		dx = 0.f;
		dz = -20.;
		rotateTransform(0.0, 1.0, 0.0, -180.f);
		break;
	case 2://하
		dx = 0.f;
		dz = 20.;
		rotateTransform(0.0, 1.0, 0.0, -0.f);
		break;
	case 3://좌
		dx = -20.;
		dz = 0.f;
		rotateTransform(0.0, 1.0, 0.0, -90.f);
		break;
	case 4://우
		dx = 20.;
		dz = 0.f;
		rotateTransform(0.0, 1.0, 0.0, 90.f);
		break;
	default:
		break;
	}
	x += dx;
	z += dz;
	moveTranform(x, 0.0, z);
	update();
}

GHOST::GHOST()
{
}

GHOST::~GHOST()
{
}

void InitGhost(GHOST& body, GHOST& eye,float pos_x,float pos_z)
{

	body.init(0, 255, 0, "asset/ghost_body.obj", pos_x,pos_z);
	eye.init(255, 0, 0, "asset/ghost_eyes.obj", pos_x,pos_z);

	body.x = pos_x;
	body.z = pos_z;
	eye.x = pos_x;
	eye.z = pos_z;

	body.scaleTransform(20., 20., 20.);
	eye.scaleTransform(20., 20., 20.);

	body.moveTranform(pos_x, 0.0, pos_z);
	eye.moveTranform(pos_x, 0.0, pos_z);


	body.update();
	eye.update();
}

void ResetGhost(float _firstX, float _firstZ, float _secondX, float _secondZ, float _thirdX, float _thirdZ)
{
	
}

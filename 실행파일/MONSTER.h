#pragma once
#include "pch.h"

class GHOST
{
private:
	// 좌표, 바운딩박스
	

	GLfloat dx = 0;
	GLfloat dz = 0;

	// VAO, VBO, EBO
	GLuint VAO, VBO[2], EBO;

	// vertex, color, face
	vector<glm::vec3> vertexInfo;

	// 스케일, 회전, 이동
	glm::mat4 scale;  //--- 스케일 행렬
	glm::mat4 rotate; //--- 회전 행렬 
	glm::mat4 move;   //--- 이동 행렬
	glm::mat4 merge;  //--- 합성 변환 행렬
	vector<glm::mat4> vec_transform;


public:
	GLfloat x;
	GLfloat z;
	void init(int R, int G, int B, string str,float pos_x, float pos_z); //--- 초기화(ReadObj, initBuffer)
	void ResetGhost(float _posX, float _posZ);
	void scaleTransform(float x, float y, float z); //--- 스케일 변환
	void rotateTransform(float x, float y, float z, float degree); //--- 회전 변환
	void moveTranform(float x, float y, float z); //--- 이동 변환

	RECT get_BB();
	float get_xPos() { return x; }
	float get_zPos() { return z; }

	RECT get_Top_BB();
	float get_Top_xPos() { return x; }
	float get_Top_zPos() { return z - 20.0; }

	RECT get_Bottom_BB();
	float get_Bot_xPos() { return x; }
	float get_Bot_zPos() { return z + 20.0; }

	RECT get_Left_BB();
	float get_Left_xPos() { return x - 20.0; }
	float get_Left_zPos() { return z; }

	RECT get_Right_BB();
	float get_Right_xPos() { return x + 20.0; }
	float get_Right_zPos() { return z; }
	
	void update();
	void draw(int R,int G,int B);
	void chase(int dir);
	void changeColor(int R, int G, int B);

	//void changeColor(int R, int G, int B); // 색 변경 (0 ~ 255)

	
	int AI();
	
public:
	GHOST();
	~GHOST();
};


void InitGhost(GHOST& body, GHOST& eye, float pos_x, float pos_z);

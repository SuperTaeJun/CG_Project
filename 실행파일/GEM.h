#pragma once
#include "pch.h"

class GEM
{
	// 좌표, 바운딩박스
	GLfloat pos_x;
	GLfloat pos_y;
	GLfloat pos_z;
	RECT rect;

	bool isOn{ TRUE };
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
	void init( string str); //--- 초기화(ReadObj, initBuffer)

	void scaleTransform(float x, float y, float z); //--- 스케일 변환
	void rotateTransform(float x, float y, float z, float degree); //--- 회전 변환
	void moveTranform(float x, float y, float z); //--- 이동 변환
	RECT get_BB();

	void update();
	void draw(int R, int G, int B);

	void changeColor(int R, int G, int B); // 색 변경 (0 ~ 255)
	void collid();
	void reset();
	bool get_isOn() { return isOn; }
public:
	GEM();
	~GEM();
};

void InitGem(GEM gem[100]);



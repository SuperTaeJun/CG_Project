#pragma once
#include "pch.h"
class START
{
private:

	// logo_startbutton.obj
	GLuint VAO, VBO;
	vector<glm::vec3> vertexInfo;
	//	logo_1playeronly.obj
	GLuint VAO2, VBO2;
	vector<glm::vec3> vertexInfo2;
	// 스케일, 회전, 이동
	glm::mat4 scale;  //--- 스케일 행렬
	glm::mat4 rotate; //--- 회전 행렬 
	glm::mat4 move;   //--- 이동 행렬
	glm::mat4 merge;  //--- 합성 변환 행렬
	vector<glm::mat4> vec_transform;

	bool start_state = TRUE;

	int drop;

public:
	/*void init(int R, int G, int B,float vertices[]);*/
	void init();
	//--- 초기화(ReadObj, initBuffer)
	void scaleTransform(float x, float y, float z); //--- 스케일 변환
	void rotateTransform(float x, float y, float z, float degree); //--- 회전 변환
	void moveTranform(float x, float y, float z); //--- 이동 변환
	void update();
	void draw(int R, int G, int B, int R2, int G2, int B2);

	void changeColor(int R, int G, int B); // 색 변경 (0 ~ 255)

	void change_state() { start_state = FALSE; }
	bool get_state() { return start_state; }

	void animate(int );
};
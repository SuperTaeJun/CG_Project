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
	// ������, ȸ��, �̵�
	glm::mat4 scale;  //--- ������ ���
	glm::mat4 rotate; //--- ȸ�� ��� 
	glm::mat4 move;   //--- �̵� ���
	glm::mat4 merge;  //--- �ռ� ��ȯ ���
	vector<glm::mat4> vec_transform;

	bool start_state = TRUE;

	int drop;

public:
	/*void init(int R, int G, int B,float vertices[]);*/
	void init();
	//--- �ʱ�ȭ(ReadObj, initBuffer)
	void scaleTransform(float x, float y, float z); //--- ������ ��ȯ
	void rotateTransform(float x, float y, float z, float degree); //--- ȸ�� ��ȯ
	void moveTranform(float x, float y, float z); //--- �̵� ��ȯ
	void update();
	void draw(int R, int G, int B, int R2, int G2, int B2);

	void changeColor(int R, int G, int B); // �� ���� (0 ~ 255)

	void change_state() { start_state = FALSE; }
	bool get_state() { return start_state; }

	void animate(int );
};
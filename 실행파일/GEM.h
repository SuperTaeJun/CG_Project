#pragma once
#include "pch.h"

class GEM
{
	// ��ǥ, �ٿ���ڽ�
	GLfloat pos_x;
	GLfloat pos_y;
	GLfloat pos_z;
	RECT rect;

	bool isOn{ TRUE };
	// VAO, VBO, EBO
	GLuint VAO, VBO[2], EBO;

	// vertex, color, face
	vector<glm::vec3> vertexInfo;

	// ������, ȸ��, �̵�
	glm::mat4 scale;  //--- ������ ���
	glm::mat4 rotate; //--- ȸ�� ��� 
	glm::mat4 move;   //--- �̵� ���
	glm::mat4 merge;  //--- �ռ� ��ȯ ���
	vector<glm::mat4> vec_transform;


public:
	void init( string str); //--- �ʱ�ȭ(ReadObj, initBuffer)

	void scaleTransform(float x, float y, float z); //--- ������ ��ȯ
	void rotateTransform(float x, float y, float z, float degree); //--- ȸ�� ��ȯ
	void moveTranform(float x, float y, float z); //--- �̵� ��ȯ
	RECT get_BB();

	void update();
	void draw(int R, int G, int B);

	void changeColor(int R, int G, int B); // �� ���� (0 ~ 255)
	void collid();
	void reset();
	bool get_isOn() { return isOn; }
public:
	GEM();
	~GEM();
};

void InitGem(GEM gem[100]);



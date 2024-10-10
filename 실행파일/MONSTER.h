#pragma once
#include "pch.h"

class GHOST
{
private:
	// ��ǥ, �ٿ���ڽ�
	

	GLfloat dx = 0;
	GLfloat dz = 0;

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
	GLfloat x;
	GLfloat z;
	void init(int R, int G, int B, string str,float pos_x, float pos_z); //--- �ʱ�ȭ(ReadObj, initBuffer)
	void ResetGhost(float _posX, float _posZ);
	void scaleTransform(float x, float y, float z); //--- ������ ��ȯ
	void rotateTransform(float x, float y, float z, float degree); //--- ȸ�� ��ȯ
	void moveTranform(float x, float y, float z); //--- �̵� ��ȯ

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

	//void changeColor(int R, int G, int B); // �� ���� (0 ~ 255)

	
	int AI();
	
public:
	GHOST();
	~GHOST();
};


void InitGhost(GHOST& body, GHOST& eye, float pos_x, float pos_z);

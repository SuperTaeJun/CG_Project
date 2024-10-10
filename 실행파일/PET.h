#pragma once
#include "pch.h"

class PET
{
	// ��ǥ, �ٿ���ڽ�
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat objectDeg;

	GLint jumpHeight;
	RECT rect;
	bool isJump;

	// VAO, VBO, EBO
	//GLuint VAO, VBO[2], EBO;
	GLuint VAO, VBO;
	// vertex, color, face
	vector<glm::vec3> vertexInfo;
	// ������, ȸ��, �̵�
	glm::mat4 scale;  //--- ������ ���
	glm::mat4 rotate; //--- ȸ�� ��� 
	glm::mat4 move;   //--- �̵� ���
	glm::mat4 merge;  //--- �ռ� ��ȯ ���
	vector<glm::mat4> vec_transform;

public:
	void init(string str); //--- �ʱ�ȭ(ReadObj, initBuffer)

	void scaleTransform(float x, float y, float z); //--- ������ ��ȯ
	void rotateTransform(float x, float y, float z, float degree); //--- ȸ�� ��ȯ
	void moveTranform(float x, float y, float z); //--- �̵� ��ȯ

	void setObjectDeg(float degree)  { objectDeg = degree; }
	void plusObjectDeg(float degree) { objectDeg += degree; }

	void moveObject(float x, float z) { this->x = x, this->z = z; }
	void set_yPos(float y) { this->y = y; }
	void setHeight() { this->y += 0.98f * 1 * jumpHeight--; }
	void jump() { if (!isJump) { jumpHeight = 10, isJump = true; } }
	void stopJump() { isJump = false; }

	float get_xPos() { return x; }
	float get_yPos() { return y; }
	float get_zPos() { return z; }
	float get_Deg() { return objectDeg; }
	bool  get_isJump() { return isJump; }

	RECT get_BB();

	void update();
	void draw(int R, int G, int B);

	void changeColor(int R, int G, int B); // �� ���� (0 ~ 255)

public:
	PET();
	~PET();
};

//�÷��̾� ��ü (����, �Ʒ���, ��, ��)
extern PET petTop;
extern PET petBot;
extern PET petEyes;
extern PET petNose;

GLvoid initPET();
GLvoid redrawPET();
GLvoid animatePET();
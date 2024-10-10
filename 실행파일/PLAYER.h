#pragma once
#include "pch.h"

class PLAYER
{
	// ��ǥ, �ٿ���ڽ�
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat objectDeg;
	// size �߰�
	GLfloat size;

	RECT rect;

	bool isOn = TRUE;

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

	void setObjectDeg(float degree)   { objectDeg = degree; }
	void moveObject(float x, float z) { this->x += x, this->z += z; }
	// �߰�
	void plusSize(float _size) { size += _size; }

	float get_xPos() { return x; }
	float get_zPos() { return z; }
	// size �߰�
	float get_size() { return size; }
	float get_Deg()  { return objectDeg; }

	RECT get_BB();

	void update();
	void draw(int R, int G, int B);

	void isOn_FALSE() { isOn = FALSE; }
	void isOn_TRUE() { isOn = TRUE; }

	void changeColor(int R, int G, int B); // �� ���� (0 ~ 255)

	void reset_pos();
public:
	PLAYER();
	~PLAYER();
};

//�÷��̾� ��ü (����, �Ʒ���, ��, ��)
extern PLAYER pacmanTop;
extern PLAYER pacmanBot;
extern PLAYER pacmanEyes;
extern PLAYER pacmanNose;


GLvoid initPlayer();
GLvoid ResetPlayer();
GLvoid redrawPlayer();
GLvoid animatePlayer();
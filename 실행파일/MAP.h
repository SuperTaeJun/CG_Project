#pragma once
#include "pch.h"

class MAP
{
private:
	// ��ǥ, �ٿ���ڽ�
	GLfloat pos_x;
	GLfloat pos_z;

	RECT rect;
	// VAO, VBO, EBO
	GLuint VAO, VBO;

	// vertex, color, face
	//vector<glm::vec3>  vertexData;
	//vector<glm::vec3>  colorData;
	//vector<glm::ivec3> faceData;
	vector<glm::vec3> vertexInfo;

	// ������, ȸ��, �̵�
	glm::mat4 scale;  //--- ������ ���
	glm::mat4 rotate; //--- ȸ�� ��� 
	glm::mat4 move;   //--- �̵� ���
	glm::mat4 merge;  //--- �ռ� ��ȯ ���
	vector<glm::mat4> vec_transform;


public:
	/*void init(int R, int G, int B,float vertices[]);*/
	void init(int ,int ,int);
	//--- �ʱ�ȭ(ReadObj, initBuffer)
	void scaleTransform(float x, float y, float z); //--- ������ ��ȯ
	void rotateTransform(float x, float y, float z, float degree); //--- ȸ�� ��ȯ
	void moveTranform(float x, float y, float z); //--- �̵� ��ȯ
	void update();
	void draw(int R, int G, int B);
	RECT get_BB();

	void changeColor(int R, int G, int B); // �� ���� (0 ~ 255)
public:
	MAP();
	~MAP();
};

extern MAP map[327];

void InitMap(MAP map[327]);
#pragma once
#include "pch.h"

class PLAYER
{
	// 좌표, 바운딩박스
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat objectDeg;
	// size 추가
	GLfloat size;

	RECT rect;

	bool isOn = TRUE;

	// VAO, VBO, EBO
	//GLuint VAO, VBO[2], EBO;
	GLuint VAO, VBO;
	// vertex, color, face
	vector<glm::vec3> vertexInfo;
	// 스케일, 회전, 이동
	glm::mat4 scale;  //--- 스케일 행렬
	glm::mat4 rotate; //--- 회전 행렬 
	glm::mat4 move;   //--- 이동 행렬
	glm::mat4 merge;  //--- 합성 변환 행렬
	vector<glm::mat4> vec_transform;

public:
	void init(string str); //--- 초기화(ReadObj, initBuffer)

	void scaleTransform(float x, float y, float z); //--- 스케일 변환
	void rotateTransform(float x, float y, float z, float degree); //--- 회전 변환
	void moveTranform(float x, float y, float z); //--- 이동 변환

	void setObjectDeg(float degree)   { objectDeg = degree; }
	void moveObject(float x, float z) { this->x += x, this->z += z; }
	// 추가
	void plusSize(float _size) { size += _size; }

	float get_xPos() { return x; }
	float get_zPos() { return z; }
	// size 추가
	float get_size() { return size; }
	float get_Deg()  { return objectDeg; }

	RECT get_BB();

	void update();
	void draw(int R, int G, int B);

	void isOn_FALSE() { isOn = FALSE; }
	void isOn_TRUE() { isOn = TRUE; }

	void changeColor(int R, int G, int B); // 색 변경 (0 ~ 255)

	void reset_pos();
public:
	PLAYER();
	~PLAYER();
};

//플레이어 객체 (윗몸, 아랫몸, 눈, 코)
extern PLAYER pacmanTop;
extern PLAYER pacmanBot;
extern PLAYER pacmanEyes;
extern PLAYER pacmanNose;


GLvoid initPlayer();
GLvoid ResetPlayer();
GLvoid redrawPlayer();
GLvoid animatePlayer();
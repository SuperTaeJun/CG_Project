#pragma once
#include "pch.h"

class PET
{
	// 좌표, 바운딩박스
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

	void changeColor(int R, int G, int B); // 색 변경 (0 ~ 255)

public:
	PET();
	~PET();
};

//플레이어 객체 (윗몸, 아랫몸, 눈, 코)
extern PET petTop;
extern PET petBot;
extern PET petEyes;
extern PET petNose;

GLvoid initPET();
GLvoid redrawPET();
GLvoid animatePET();
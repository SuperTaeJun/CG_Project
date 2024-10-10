#pragma once
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib,"winmm.lib")

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <random>
#include <math.h>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtx/rotate_vector.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "MAP.h"
#include "PLAYER.h"

//���� �������
#include <mmsystem.h>
#include <Digitalv.h>
#include "sound.h"

using namespace std;
extern GLuint shaderID;
extern GLfloat winWidth, winHeight;
extern GLboolean plusDeg;
extern GLfloat   mouseDeg;



//void ReadObj(string file, vector<glm::vec3>* vertexData, vector<glm::vec3>* colorData, vector<glm::ivec3>* faceData); //--- ������Ʈ �о����
void ReadObj(std::string file, vector<glm::vec3>& vertexInfo);
//void initBuffer(GLuint* VAO, GLuint* VBO, GLuint* EBO, vector<glm::vec3> vertexData, vector<glm::vec3> colorData, vector<glm::ivec3> faceData); //--- ������Ʈ ���� �����ϱ�
void initBuffer(GLuint* VAO, GLuint* VBO, vector<glm::vec3> vertexInfo); //--- ������Ʈ ���� �����ϱ�
void initBuffer(GLuint* VAO, GLuint* VBO, float vertexInfo[]);
bool MyintersectRect(RECT a, RECT b);

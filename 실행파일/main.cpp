#include "pch.h"
#include "PLAYER.h"
#include "MONSTER.h"
#include "GEM.h"
#include "PET.h"
#include "MAP.h"
#include "CAMERA.h"
#include "shader.h"
#include "SCENE.h"

// 콜백 함수들
GLvoid Reshape(int w, int h);
GLvoid Render();
GLvoid KeyboardDown(unsigned char key, int x, int y);
GLvoid KeyboardUp(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);
void TimerFunction2(int value);
void TimerFunction3(int value);

//게임 리셋
void GameReset();

//사운드
int first_check{};
int playbgm_check{};
void BackgrandBgm();
SOUND sound;
//void playingShuffleSound();
//MCI_PLAY_PARMS playBgm;
//MCI_OPEN_PARMS openBgm;
//#define BGM "asset/sound/pacman_eatgem.wav"    //BGM 경로 지정
//int dwID;


// 윈도우 관련 변수
GLfloat winWidth, winHeight;

// 쉐이더 관련 함수, 변수

GLuint shaderID; //--- 세이더 프로그램 이름

// lighting
glm::vec3 lightPos(10.0, 100.0, -3.0);

//입력함수들
void mouse_passive(int x, int y); //1인칭 시점때 사용
void sp_keybord(int key, int x, int y); //1인칭 시점때 이동

// 플레이어 객체 (윗몸, 아랫몸, 눈, 코)
PLAYER pacmanTop;
PLAYER pacmanBot;
PLAYER pacmanEyes;
PLAYER pacmanNose;

// 펫
PET petTop;
PET petBot;
PET petEyes;
PET petNose;

//고스트 객체 5마리 예정
GHOST first_ghost_body;
GHOST first_ghost_eye;
GHOST second_ghost_body;
GHOST second_ghost_eye;
GHOST third_ghost_body;
GHOST third_ghost_eye;
GHOST forth_ghost_body;
GHOST forth_ghost_eye;

// 맵
MAP map[327];

// 젬
GEM gem[280]{};

// 시작씬
int chage_state{0};//0시작화면 1게임오버 2클리어 3 플레이
int drop{};
START start;
GAMEOVER gameover;
CLEAR clear;

// 카메라
CAMERA camera;
glm::vec3 cameraPos = glm::vec3(250., 10.f, -250.);
glm::vec3 cameraFront = glm::vec3(0.0, 0.0, 0.0);
glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);


void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	winWidth = 1600.f;
	winHeight = 900.f;
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, -500);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("CG_TermProject");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	Shader shader("new_vertex.glsl", "new_fragment.glsl");
	shaderID = shader.ID;
	glUseProgram(shaderID);

	shader.setVec3("lightPos", lightPos);
	shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	shader.setVec3("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
	//--- 세이더 읽어와서 세이더 프로그램 만들기
	//make_vertexShader(); //--- 버텍스 세이더 만들기
	//make_fragmentShader(); //--- 프래그먼트 세이더 만들기
	//shaderID = make_shaderProgram(); //--- 세이더 프로그램 만들기
	//glUseProgram(shaderID);


	glEnable(GL_DEPTH_TEST);    // 은면 제거
	glEnable(GL_DITHER);        // 표면을 매끄럽게
	glEnable(GL_CULL_FACE);     // 컬링
	glEnable(GL_LINE_SMOOTH);   // 안티 앨리어싱
	glEnable(GL_POLYGON_SMOOTH);// 안티 앨리어싱
	glShadeModel(GL_SMOOTH);    // 부드러운 음영을 수행합니다.

	start.init();
	gameover.init();
	clear.init();

	initPlayer();
	initPET();
	// 유령객체 Init
	InitGhost(first_ghost_body, first_ghost_eye, 250., -270.);
	InitGhost(second_ghost_body, second_ghost_eye, 90., 210.);
	InitGhost(third_ghost_body, third_ghost_eye, -250, -270);
	InitGhost(forth_ghost_body, forth_ghost_eye, -110.,  210.);
	//맵 Init
	InitMap(map);
	//젬 Init
	InitGem(gem);

	//사운드
	BackgrandBgm();

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutPassiveMotionFunc(mouse_passive);
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(sp_keybord);
	glutTimerFunc(10, TimerFunction, 1);
	glutTimerFunc(500, TimerFunction3, 1);
	glutMainLoop();
}
bool firstMouse{ TRUE };
float yaw{};
float pitch{};
float lastX = 800, lastY = 400;

void mouse_passive(int x, int y)
{
	float xpos = static_cast<float>(x);
	float ypos = static_cast<float>(y);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.5;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 10.0f)
		pitch = 10.0f;
	if (pitch < -10.0f)
		pitch = -10.0f;
	if (pitch > 1.0f)
		pitch = 1.0f;
	if (pitch < -1.f)
		pitch = -1.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	camera.process_mouse_movement(xoffset, yoffset);
	glutPostRedisplay();
}

void setCamera() {

	if (camera.camera_change == 2)
	{
		pacmanBot.isOn_TRUE();
		pacmanTop.isOn_TRUE();
		pacmanEyes.isOn_TRUE();
		pacmanNose.isOn_TRUE();
		camera.set_top();
	}
	else if (camera.camera_change == 1)
	{
		pacmanBot.isOn_TRUE();
		pacmanTop.isOn_TRUE();
		pacmanEyes.isOn_TRUE();
		pacmanNose.isOn_TRUE();
		camera.set_third_person();
	}
	else if (camera.camera_change == 0)
	{
		pacmanBot.isOn_FALSE();
		pacmanTop.isOn_FALSE();
		pacmanEyes.isOn_FALSE();
		pacmanNose.isOn_FALSE();
		camera.set_frist_person(pacmanBot.get_xPos(), pacmanBot.get_zPos());
	}

	camera.get_view();
}
void setProjection()
{
	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(45.0f), winWidth / winHeight, 0.1f, 1000.0f);
	/*projection = glm::rotate(projection, glm::radians(0.f), glm::vec3(0.0, 1.0, 0.0));*/

	unsigned int projectionLocation = glGetUniformLocation(shaderID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}

void Render()
{
	srand(time(nullptr));
	if (camera.camera_change == 0) glViewport(0, 0, winWidth * 0.8, winHeight * 0.8);
	else glViewport(0, 0, winWidth, winHeight);

	glClearColor(0.0, 0.0, 0.0, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setCamera();     // 카메라 설정
	setProjection();

	if (chage_state == 3)
	{
		for (int i{}; i < 327; ++i)
			map[i].draw(132, 123, 134);

		pacmanTop.draw(255, 242, 0);
		pacmanBot.draw(255, 242, 0);
		pacmanNose.draw(0, 0, 0);
		pacmanEyes.draw(0, 0, 0);

		petTop.draw(217, 65, 197);
		petBot.draw(217, 65, 197);
		petNose.draw(0, 0, 0);
		petEyes.draw(0, 0, 0);

		first_ghost_body.draw(255, 24, 21);
		first_ghost_eye.draw(255, 255, 255);

		second_ghost_body.draw(240, 199, 255);
		second_ghost_eye.draw(255, 255, 255);

		third_ghost_body.draw(0, 229, 253);
		third_ghost_eye.draw(255, 255, 255);

		forth_ghost_body.draw(255, 184, 73);
		forth_ghost_eye.draw(255, 255, 255);

		for (int i{}; i < 280; ++i)
			gem[i].draw(0, 0, 255);
		/// 그리기 (변환은 타이머에서 적용해주고, 마지막에 update 넣어주기)
		if (camera.camera_change == 0)
		{
			glViewport(winWidth - 395, winHeight - 290, 480, 270);
			// 추가
			pacmanTop.isOn_TRUE();
			pacmanBot.isOn_TRUE();
			pacmanNose.isOn_TRUE();
			pacmanEyes.isOn_TRUE();
			camera.set_top();     // 카메라 설정
			setProjection();

			for (int i{}; i < 327; ++i)
				map[i].draw(132, 123, 134);

			pacmanTop.draw(255, 255, 0);
			pacmanBot.draw(255, 255, 0);
			pacmanNose.draw(0, 0, 0);
			pacmanEyes.draw(0, 0, 0);

			petTop.draw(217, 65, 197);
			petBot.draw(217, 65, 197);
			petNose.draw(0, 0, 0);
			petEyes.draw(0, 0, 0);

			first_ghost_body.draw(255, 0, 0);
			first_ghost_eye.draw(255, 255, 255);
			second_ghost_body.draw(0, 255, 0);
			second_ghost_eye.draw(255, 255, 255);
			third_ghost_body.draw(0, 0, 255);
			third_ghost_eye.draw(255, 255, 255);
			forth_ghost_body.draw(255, 184, 73);
			forth_ghost_eye.draw(0, 0, 0);

			for (int i{}; i < 280; ++i)
				gem[i].draw(0, 0, 255);
		}
	}
	else if(chage_state == 0)
	{
		start.draw(255, 0, 0, 0, 255, 0);

		for (int i{}; i < 327; ++i)
			map[i].draw(132, 123, 134);

		for (int i{}; i < 280; ++i)
			gem[i].draw(0, 0, 255);

	}
	else if (chage_state == 1)
	{
		gameover.draw(255, 0, 0);

		for (int i{}; i < 327; ++i)
			map[i].draw(132, 123, 134);

		for (int i{}; i < 280; ++i)
			gem[i].draw(0, 0, 255);
	}
	else if (chage_state == 2)
	{
		clear.draw(0,255,255);

		for (int i{}; i < 327; ++i)
			map[i].draw(132, 123, 134);

		for (int i{}; i < 280; ++i)
			gem[i].draw(0, 0, 255);
	}
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	winWidth = w;
	winHeight = h;
}

bool immortal{ FALSE };
//// 키보드 눌림
GLvoid KeyboardDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'1':
		camera.camera_change = 0;
		break;
	case'2':
		camera.camera_change = 1;
		//glutPostRedisplay();
		break;
	case'3':
		camera.camera_change = 2;
		//glutPostRedisplay();
		break;
	case 'w':
		pacmanTop .setObjectDeg(180.f);
		pacmanBot .setObjectDeg(180.f);
		pacmanNose.setObjectDeg(180.f);
		pacmanEyes.setObjectDeg(180.f);

		pacmanTop.moveObject (0.f, -20.f);
		pacmanBot.moveObject (0.f, -20.f);
		pacmanNose.moveObject(0.f, -20.f);
		pacmanEyes.moveObject(0.f, -20.f);

		if (camera.camera_change == 0) camera.setdeg(-90.);

		for (int i = 0; i < 327; ++i)
		{
			if (MyintersectRect(pacmanBot.get_BB(), map[i].get_BB()))
			{
				pacmanTop.moveObject(0.f, 20.f);
				pacmanBot.moveObject(0.f, 20.f);
				pacmanNose.moveObject(0.f, 20.f);
				pacmanEyes.moveObject(0.f, 20.f);
				return;
			}
		}
		
		/*petTop.moveObject(pacmanTop.get_xPos(),  pacmanTop.get_zPos() + 20.f);
		petBot.moveObject(pacmanBot.get_xPos(),  pacmanBot.get_zPos() + 20.f);
		petNose.moveObject(pacmanNose.get_xPos(), pacmanNose.get_zPos() + 20.f);
		petEyes.moveObject(pacmanEyes.get_xPos(), pacmanEyes.get_zPos() + 20.f);*/

		petTop.moveObject(pacmanTop.get_xPos(), pacmanTop.get_zPos());
		petBot.moveObject(pacmanBot.get_xPos(), pacmanBot.get_zPos());
		petNose.moveObject(pacmanNose.get_xPos(), pacmanNose.get_zPos());
		petEyes.moveObject(pacmanEyes.get_xPos(), pacmanEyes.get_zPos());
		break;
	case 'a':
		pacmanTop.setObjectDeg (-90.f);
		pacmanBot.setObjectDeg (-90.f);
		pacmanNose.setObjectDeg(-90.f);
		pacmanEyes.setObjectDeg(-90.f);

		pacmanTop.moveObject (-20.f, 0.f);
		pacmanBot.moveObject (-20.f, 0.f);
		pacmanNose.moveObject(-20.f, 0.f);
		pacmanEyes.moveObject(-20.f, 0.f);

		if (pacmanBot.get_xPos() <= -320)
		{
			pacmanTop.moveObject(620.f, 0.f);
			pacmanBot.moveObject(620.f, 0.f);
			pacmanNose.moveObject(620.f, 0.f);
			pacmanEyes.moveObject(620.f, 0.f);
		}

		if (camera.camera_change == 0) camera.setdeg(-180.);

		for (int i = 0; i < 327; ++i)
		{
			if (MyintersectRect(pacmanBot.get_BB(), map[i].get_BB()))
			{
				pacmanTop.moveObject(20.f, 0.f);
				pacmanBot.moveObject(20.f, 0.f);
				pacmanNose.moveObject(20.f, 0.f);
				pacmanEyes.moveObject(20.f, 0.f);
				return;
			}
		}

		/*petTop.moveObject(pacmanTop.get_xPos() + 20.f, pacmanTop.get_zPos());
		petBot.moveObject(pacmanBot.get_xPos() + 20.f, pacmanBot.get_zPos());
		petNose.moveObject(pacmanNose.get_xPos() + 20.f, pacmanNose.get_zPos());
		petEyes.moveObject(pacmanEyes.get_xPos() + 20.f, pacmanEyes.get_zPos());*/

		petTop.moveObject(pacmanTop.get_xPos(), pacmanTop.get_zPos());
		petBot.moveObject(pacmanBot.get_xPos(), pacmanBot.get_zPos());
		petNose.moveObject(pacmanNose.get_xPos(), pacmanNose.get_zPos());
		petEyes.moveObject(pacmanEyes.get_xPos(), pacmanEyes.get_zPos());
		break;
	case 's':
		pacmanTop.setObjectDeg(0.f);
		pacmanBot.setObjectDeg(0.f);
		pacmanNose.setObjectDeg(0.f);
		pacmanEyes.setObjectDeg(0.f);

		pacmanTop.moveObject (0.f, 20.f);
		pacmanBot.moveObject (0.f, 20.f);
		pacmanNose.moveObject(0.f, 20.f);
		pacmanEyes.moveObject(0.f, 20.f);

		if (camera.camera_change == 0) camera.setdeg(90.);

		for (int i = 0; i < 327; ++i)
		{
			if (MyintersectRect(pacmanBot.get_BB(), map[i].get_BB()))
			{
				pacmanTop.moveObject(0.f, -20.f);
				pacmanBot.moveObject(0.f, -20.f);
				pacmanNose.moveObject(0.f, -20.f);
				pacmanEyes.moveObject(0.f, -20.f);
				return;
			}
		}

		/*petTop.moveObject(pacmanTop.get_xPos(), pacmanTop.get_zPos() - 20.f);
		petBot.moveObject(pacmanBot.get_xPos(), pacmanBot.get_zPos() - 20.f);
		petNose.moveObject(pacmanNose.get_xPos(), pacmanNose.get_zPos() - 20.f);
		petEyes.moveObject(pacmanEyes.get_xPos(), pacmanEyes.get_zPos() - 20.f);*/

		petTop.moveObject(pacmanTop.get_xPos(), pacmanTop.get_zPos());
		petBot.moveObject(pacmanBot.get_xPos(), pacmanBot.get_zPos());
		petNose.moveObject(pacmanNose.get_xPos(), pacmanNose.get_zPos());
		petEyes.moveObject(pacmanEyes.get_xPos(), pacmanEyes.get_zPos());
		break;
	case 'd':
		pacmanTop.setObjectDeg (90.f);
		pacmanBot.setObjectDeg (90.f);
		pacmanNose.setObjectDeg(90.f);
		pacmanEyes.setObjectDeg(90.f);

		pacmanTop.moveObject (20.f, 0.f);
		pacmanBot.moveObject (20.f, 0.f);
		pacmanNose.moveObject(20.f, 0.f);
		pacmanEyes.moveObject(20.f, 0.f);

		if (pacmanBot.get_xPos() >= 300) 
		{
			pacmanTop.moveObject(-620.f, 0.f);
			pacmanBot.moveObject(-620.f, 0.f);
			pacmanNose.moveObject(-620.f, 0.f);
			pacmanEyes.moveObject(-620.f, 0.f);
		}

		if (camera.camera_change == 0) camera.setdeg(0.);

		for (int i = 0; i < 327; ++i)
		{
			if (MyintersectRect(pacmanBot.get_BB(), map[i].get_BB()))
			{
				pacmanTop.moveObject(-20.f, 0.f);
				pacmanBot.moveObject(-20.f, 0.f);
				pacmanNose.moveObject(-20.f, 0.f);
				pacmanEyes.moveObject(-20.f, 0.f);
				return;
			}
		}

		/*petTop.moveObject(pacmanTop.get_xPos() - 20.f, pacmanTop.get_zPos());
		petBot.moveObject(pacmanBot.get_xPos() - 20.f, pacmanBot.get_zPos());
		petNose.moveObject(pacmanNose.get_xPos() - 20.f, pacmanNose.get_zPos());
		petEyes.moveObject(pacmanEyes.get_xPos() - 20.f, pacmanEyes.get_zPos());*/

		petTop.moveObject(pacmanTop.get_xPos(), pacmanTop.get_zPos());
		petBot.moveObject(pacmanBot.get_xPos(), pacmanBot.get_zPos());
		petNose.moveObject(pacmanNose.get_xPos(), pacmanNose.get_zPos());
		petEyes.moveObject(pacmanEyes.get_xPos(), pacmanEyes.get_zPos());
		break;
	case 32: // space바
		if (chage_state == 0) {
			playbgm_check = 0;
			glutTimerFunc(10, TimerFunction2, 1);
		}
		else if (chage_state == 1)
		{
			GameReset();
			chage_state = 0;
			BackgrandBgm();
		}
		else if (chage_state == 2)
		{
			
			GameReset();
			chage_state = 0;
			BackgrandBgm();
		}
		break;
	case'h':
		immortal = TRUE;
		break;
	case'H':
		immortal = FALSE;
		break;
	case VK_ESCAPE:
		glutLeaveMainLoop();
		break;
	}

	for (int i = 0; i < 280; ++i)
	{
		if (MyintersectRect(pacmanBot.get_BB(), gem[i].get_BB()) && gem[i].get_isOn())
		{
			sound.playingEatSound();
			gem[i].collid();
			// 추가
			pacmanTop.plusSize(0.05f);
			pacmanBot.plusSize(0.05f);
			pacmanNose.plusSize(0.05f);
			pacmanEyes.plusSize(0.05f);
			
			petTop.jump();
			petBot.jump();
			petNose.jump();
			petEyes.jump();
		}
	}
	glutPostRedisplay();
}

//// 키보드 올림
GLvoid KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
		break;
	}
}
//스페셜 키보드~
void sp_keybord(int key, int x, int y)
{
	float cameraSpeed = 1.5f;
	if (key == GLUT_KEY_UP)
	{
		cameraPos += cameraSpeed * cameraFront;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		cameraPos -= cameraSpeed * cameraFront;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	else if (key == GLUT_KEY_RIGHT)
	{

		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	glutPostRedisplay();
}
void TimerFunction(int value) {
	if (chage_state == 3)
	{
		
		

		if (playbgm_check == 0)
		{
			playbgm_check++;
			BackgrandBgm();
		}
		if (!immortal)
		{
			if (MyintersectRect(pacmanBot.get_BB(), first_ghost_body.get_BB()))
			{
				sound.playingDietSound();
				cout << "first" << endl;
				chage_state = 1;
				if (camera.camera_change == 0) camera.camera_change = 1;
				//glutLeaveMainLoop();
			}

			if (MyintersectRect(pacmanBot.get_BB(), second_ghost_body.get_BB()))
			{
				sound.playingDietSound();
				cout << "second" << endl;
				chage_state = 1;
				if (camera.camera_change == 0) camera.camera_change = 1;
				//glutLeaveMainLoop();
			}

			if (MyintersectRect(pacmanBot.get_BB(), third_ghost_body.get_BB()))
			{
				sound.playingDietSound();
				cout << "third" << endl;
				chage_state = 1;
				if (camera.camera_change == 0) camera.camera_change = 1;
				//glutLeaveMainLoop();
			}

			if (MyintersectRect(pacmanBot.get_BB(), forth_ghost_body.get_BB()))
			{
				sound.playingDietSound();
				cout << "forth" << endl;
				chage_state = 1;
				if (camera.camera_change == 0) camera.camera_change = 1;
				//glutLeaveMainLoop();
			}
		}
		if (petBot.get_isJump())
		{
			petTop.setHeight();
			petBot.setHeight();
			petEyes.setHeight();
			petNose.setHeight();

			if (petBot.get_yPos() <= 0.f)
			{
				petTop.set_yPos(0.f);
				petBot.set_yPos(0.f);
				petEyes.set_yPos(0.f);
				petNose.set_yPos(0.f);

				petTop.stopJump();
				petBot.stopJump();
				petEyes.stopJump();
				petNose.stopJump();
			}
		}

		petTop.plusObjectDeg(1.f);
		petBot.plusObjectDeg(1.f);
		petEyes.plusObjectDeg(1.f);
		petNose.plusObjectDeg(1.f);

		int check{};
		for (int i{}; i < 280; ++i)
		{
			if (gem[i].get_isOn() == FALSE) ++check;

			if (check == 280)
				chage_state = 2;
		}

		//// 타이머 (객체 변환은 여기서, 변환 다 했으면 마지막에 update 넣어주기)

		redrawPlayer();
		redrawPET();
		animatePlayer();
	}

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}
void TimerFunction2(int value)
{
	drop += 1;
	start.animate(drop,chage_state);

	glutPostRedisplay();
	if (chage_state == 0)
		glutTimerFunc(10, TimerFunction2, 1);
}
void TimerFunction3(int value)
{
	if (chage_state == 3)
	{
		first_ghost_body.chase(first_ghost_body.AI());
		first_ghost_eye.chase(first_ghost_eye.AI());
		
		if (MyintersectRect(first_ghost_body.get_BB(), second_ghost_body.get_BB()))
		{
			first_ghost_body.ResetGhost(250., -270.);
			first_ghost_eye.ResetGhost(250., -270.);
		}
		else if (MyintersectRect(first_ghost_body.get_BB(), third_ghost_body.get_BB()))
		{
			first_ghost_body.ResetGhost(250., -270.);
			first_ghost_eye.ResetGhost(250., -270.);
		}
		else if (MyintersectRect(first_ghost_body.get_BB(), forth_ghost_body.get_BB()))
		{
			first_ghost_body.ResetGhost(250., -270.);
			first_ghost_eye.ResetGhost(250., -270.);
		}

		second_ghost_body.chase(second_ghost_body.AI());
		second_ghost_eye.chase(second_ghost_eye.AI());

		if (MyintersectRect(second_ghost_body.get_BB(), first_ghost_body.get_BB()))
		{
			second_ghost_body.ResetGhost(90., 210.);
			second_ghost_eye.ResetGhost(90., 210.);
		}
		else if (MyintersectRect(second_ghost_body.get_BB(), third_ghost_body.get_BB()))
		{
			second_ghost_body.ResetGhost(90., 210.);
			second_ghost_eye.ResetGhost(90., 210.);
		}
		else if (MyintersectRect(second_ghost_body.get_BB(), forth_ghost_body.get_BB()))
		{
			second_ghost_body.ResetGhost(90., 210.);
			second_ghost_eye.ResetGhost(90., 210.);
		}

		third_ghost_body.chase(third_ghost_body.AI());
		third_ghost_eye.chase(third_ghost_eye.AI());

		if (MyintersectRect(third_ghost_body.get_BB(), first_ghost_body.get_BB()))
		{
			third_ghost_body.ResetGhost(-250., -270.);
			third_ghost_eye.ResetGhost(-250., -270.);
		}
		else if (MyintersectRect(third_ghost_body.get_BB(), second_ghost_body.get_BB()))
		{
			third_ghost_body.ResetGhost(-250., -270.);
			third_ghost_eye.ResetGhost(-250., -270.);
		}
		else if (MyintersectRect(third_ghost_body.get_BB(), forth_ghost_body.get_BB()))
		{
			third_ghost_body.ResetGhost(-250., -270.);
			third_ghost_eye.ResetGhost(-250., -270.);
		}

		forth_ghost_body.chase(forth_ghost_body.AI());
		forth_ghost_eye.chase(forth_ghost_eye.AI());

		if (MyintersectRect(forth_ghost_body.get_BB(), second_ghost_body.get_BB()))
		{
			forth_ghost_body.ResetGhost(-110., 210.);
			forth_ghost_eye.ResetGhost(-110., 210.);
		}
		else if (MyintersectRect(forth_ghost_body.get_BB(), third_ghost_body.get_BB()))
		{
			forth_ghost_body.ResetGhost(-110., 210.);
			forth_ghost_eye.ResetGhost(-110., 210.);
		}
		else if (MyintersectRect(forth_ghost_body.get_BB(), first_ghost_body.get_BB()))
		{
			forth_ghost_body.ResetGhost(-110., 210.);
			forth_ghost_eye.ResetGhost(-110., 210.);
		}
		
	}
	glutTimerFunc(250, TimerFunction3, 1);
}
void BackgrandBgm()
{
	PlaySound(NULL, 0, 0);
	if(chage_state == 0)PlaySound(TEXT("asset/sound/pacman_beginning.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if(chage_state ==3) PlaySound(TEXT("asset/sound/pacman_backgroud.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void GameReset()
{
	for (int i{}; i < 280; ++i)
	{
		gem[i].reset();
	}
	ResetPlayer();

	first_ghost_body.ResetGhost(250., -270.);
	first_ghost_eye.ResetGhost(250., -270.);

	second_ghost_body.ResetGhost(90., 210.);
	second_ghost_eye.ResetGhost(90., 210.);

	third_ghost_body.ResetGhost(-250., -270.);
	third_ghost_eye.ResetGhost(-250., -270.);

	forth_ghost_body.ResetGhost(-110., 210.);
	forth_ghost_eye.ResetGhost(-110., 210.);

	start.reset();
	drop = 0;
}

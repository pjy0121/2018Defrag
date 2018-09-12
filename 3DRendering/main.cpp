#ifndef UNICODE
#define UNICODE
#endif 
// color buffer 필요, 두께 buffer 필요

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <Leap.h>
#include <Windows.h>
#include "math.h"
#include "MyListener.h"
#include <random>
#include "MyFile.h"
#include "MyComponents.h"

// const int width_window = 640;
// const int height_window = 480;

const int width_window = 1280;
const int height_window = 960;

using namespace std;
using namespace glm;
using namespace Leap;

// global variables
Controller controller;
MyListener listener;

// key board input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// 그리기 중단(TAB)
	if (key == GLFW_KEY_TAB && action == GLFW_RELEASE)
		listener.isStop = true;
	// 그리기 시작(ENTER)
	else if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
		listener.isStop = false;

	// 현재의 그림을 파일로 저장(F)
	else if (key == GLFW_KEY_F && action == GLFW_RELEASE)
		MyFile::saveFile(listener);		
	// 파일 로드(L)
	else if (key == GLFW_KEY_L && action == GLFW_RELEASE)
	{
		// 현재 그리던 그림을 flush
		listener.posBuffer.clear();
		listener.colorBuffer.clear();
		listener.sizeBuffer.clear();

		MyFile::loadFile(listener);		// 파일 불러오기
	}
	
	// 화면 지우기(B)
	else if (key == GLFW_KEY_B && action == GLFW_RELEASE) {
		// 버퍼들 비우기
		listener.posBuffer.clear();
		listener.colorBuffer.clear();
		listener.sizeBuffer.clear();
	}

	// 프로그램 종료(Q)
	else if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {
		glfwTerminate();
		exit(0);
	}

	// x축 기준 회전 속도 조절(빠르게 : A, 느리게 : D)
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		MyComponents::rotationDegreeX += 1.0f;
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		MyComponents::rotationDegreeX -= 1.0f;
	// y축 기준 회전 속도 조절(빠르게 : W, 느리게 : S)
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		MyComponents::rotationDegreeY += 1.0f;
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		MyComponents::rotationDegreeY -= 1.0f;

	// 점의 크기(그림 전체의 두께) 설정(굵게 : L, 얇게 : K)
	else if (key == GLFW_KEY_L && action == GLFW_RELEASE)
		listener.size += 1.0f;
	else if (key == GLFW_KEY_K && action == GLFW_RELEASE)
		listener.size -= 1.0f;

	// 그리기 색깔 설정
	else if (key == GLFW_KEY_1 && action == GLFW_RELEASE)	// R
		listener.color = vec3(1.0f, 0.0f, 0.0f);
	else if (key == GLFW_KEY_2 && action == GLFW_RELEASE)	// G
		listener.color = vec3(0.0f, 1.0f, 0.0f);
	else if (key == GLFW_KEY_3 && action == GLFW_RELEASE)	// B
		listener.color = vec3(0.0f, 0.0f, 1.0f);

	// 물체 확대 및 축소(토글식, 확대 : G, 축소 : H)
	else if (key == GLFW_KEY_G && action == GLFW_RELEASE)
	{
		if (MyComponents::scaleSize == 1.0f)
			MyComponents::scaleSize = 1.03f;
		else MyComponents::scaleSize = 1.0f;
	}
	else if (key == GLFW_KEY_H && action == GLFW_RELEASE)
	{
		if (MyComponents::scaleSize == 1.0f)
			MyComponents::scaleSize = 0.97f;
		else MyComponents::scaleSize = 1.0f;
	}

	/*
	// Object 중심점 x, y방향으로 옮기기(방향키)
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
		center.x += 0.1f;
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
		center.x -= 0.1f;
	else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
		center.y += 0.1f;
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
		center.y -= 0.1f;
	*/
}

int main()
{
	srand((unsigned)time(NULL));

	GLFWwindow *window1 = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window1 = glfwCreateWindow(width_window, height_window, "3D Rendering", NULL, NULL);

	if (!window1)
	{
		glfwTerminate();
		return -1;
	}

	// callbacks
	// key board input callback
	glfwSetKeyCallback(window1, key_callback);

	////// 선 두께, 점 크기 조정 관련
	GLfloat LineRange[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, LineRange);
	glLineWidth(LineRange[1] / 4);

	int width, height;
	glfwGetFramebufferSize(window1, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);

	controller.addListener(listener);

	// 윈도우가 닫힐 때까지 반복
	while (!glfwWindowShouldClose(window1))
	{
		/* Make the window's context current */
		glfwMakeContextCurrent(window1);
		glClearColor(0, 0, 0, 1);	// black background

		MyComponents::drawScene(window1, listener);
	}
	glfwTerminate();

	return 0;
}

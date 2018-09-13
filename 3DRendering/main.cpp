#ifndef UNICODE
#define UNICODE
#endif 

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
#include "MyComponent.h"

const int width_window = 1280;
const int height_window = 960;

using namespace std;
using namespace glm;
using namespace Leap;

////// global variables
Controller controller;
MyListener listener;
float rotSpeedX = 0.0f, rotSpeedY = 0.0f, rotSpeedZ = 0.0f;		// 회전 속도

/*
mode 0 : 그리기 모드
mode 1 : 색깔 변경 모드
mode 2 : 오브젝트 변환 모드
*/
int mode = 0;

////// callbacks
// key board input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// 그리기 중단(TAB)
	if (key == GLFW_KEY_TAB && action == GLFW_RELEASE)
	{
		listener.isStop = true;
	}
	else if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
	{
		// 그리기 모드
		if(mode == 0)
			listener.isStop = listener.isStop ? false : true;	// 그리기 시작/중단 toggle
		
		// 색깔 변경 모드
		else if (mode == 1)
		{
			float yPos = listener.currentPos.y;
			if(0.8f <= yPos && yPos <= 1.0f)
				listener.color = vec3(1.0f, 0.0f, 0.0f);	// 빨
			else if (0.6f <= yPos && yPos <= 0.8f)
				listener.color = vec3(1.0f, 128.0f / 255.0f, 0.0f);		// 주
			else if (0.4f <= yPos && yPos <= 0.6f)
				listener.color = vec3(1.0f, 1.0f, 0.0f);	// 노
			else if (0.2f <= yPos && yPos <= 0.4f)
				listener.color = vec3(0.0f, 1.0f, 0.0f);	// 초
			else if (0.0f <= yPos && yPos <= 0.2f)
				listener.color = vec3(0.0f, 0.0f, 1.0f);	// 파
			else if (-0.2f <= yPos && yPos <= 0.0f)
				listener.color = vec3(0.0f, 64.0f / 255.0f, 128.0f / 255.0f);	// 남
			else if (-0.4f <= yPos && yPos <= -0.2f)
				listener.color = vec3(128.0f / 255.0f, 0.0f, 1.0f);	// 보
			else if (-0.6f <= yPos && yPos <= -0.4f)
				listener.color = vec3(1.0f, 1.0f, 1.0f);	// 흰

			mode = 0;	// 그리기 모드로 되돌아가기
		}

		else if (mode == 2)
		{
			float xPos = listener.currentPos.x, yPos = listener.currentPos.y;

			if (0.55f <= yPos && yPos <= 0.75f)		// 화면 위쪽
			{
				// 파일 불러오기
				if (-0.9f <= xPos && xPos <= -0.75f)
				{
					// 현재 그리던 그림을 flush
					listener.posBuffer.clear();
					listener.colorBuffer.clear();
					listener.sizeBuffer.clear();

					MyFile::loadFile(listener);
				}
				// 파일 저장
				else if(-0.76f <= xPos && xPos <= -0.61f)
					MyFile::saveFile(listener);


				// X축 방향 회전
				else if (-0.4f <= xPos && xPos <= -0.3f)
					rotSpeedX += 0.3f;
				else if (-0.29f <= xPos && xPos <= -0.19f)
					rotSpeedX -= 0.3f;

				// Y축 방향 회전
				if (-0.1f <= xPos && xPos <= 0.0f)
					rotSpeedY += 0.3f;
				else if (0.01f <= xPos && xPos <= 0.11f)
					rotSpeedY -= 0.3f;

				// Z축 방향 회전
				if (0.2f <= xPos && xPos <= 0.31f)
					rotSpeedZ += 0.3f;
				else if (0.31f <= xPos && xPos <= 0.41f)
					rotSpeedZ -= 0.3f;
			}

			// 확대/축소
			else if (0.6f <= xPos && xPos <= 0.8f)
			{
				if (0.15f <= yPos && yPos <= 0.35f)
					MyComponent::scaleSize += 0.03f;
				else if (-0.35f <= yPos && yPos <= -0.15f)
					MyComponent::scaleSize -= 0.03f;
			}
		}
	}

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

	// x축 기준 회전 속도 조절(빠르게 : D, 느리게 : A)
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		rotSpeedX += 0.3f;
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		rotSpeedX -= 0.3f;
	// y축 기준 회전 속도 조절(빠르게 : W, 느리게 : S)
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		rotSpeedY += 0.3f;
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		rotSpeedY -= 0.3f;

	// 점의 크기(그림 전체의 두께) 설정(굵게 : T, 얇게 : Y)
	else if (key == GLFW_KEY_T && action == GLFW_RELEASE)
		listener.size += 1.0f;
	else if (key == GLFW_KEY_Y && action == GLFW_RELEASE)
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
		if (MyComponent::scaleSize == 1.0f)
			MyComponent::scaleSize = 1.03f;
		else MyComponent::scaleSize = 1.0f;
	}
	else if (key == GLFW_KEY_H && action == GLFW_RELEASE)
	{
		if (MyComponent::scaleSize == 1.0f)
			MyComponent::scaleSize = 0.97f;
		else MyComponent::scaleSize = 1.0f;
	}

	// 모드 변경
	// 방향키 ↑ => mode 0, 1 toggle
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
	{
		listener.isStop = true;		// 그리기 중단

		if (mode != 0)
			mode = 0;
		else mode = 1;
	}
	// 방향키 ↓ => mode 0, 2 toggle
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
	{
		listener.isStop = true;		// 그리기 중단
		if (mode != 0)
			mode = 0;
		else mode = 2;
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

	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "3D Rendering", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	////// callbacks
	// key board input callback
	glfwSetKeyCallback(window, key_callback);

	////// 선 두께, 점 크기 조정 관련
	GLfloat LineRange[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, LineRange);
	glLineWidth(LineRange[1] / 4);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);

	controller.addListener(listener);

	// 윈도우가 닫힐 때까지 반복
	while (!glfwWindowShouldClose(window))
	{
		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		glClearColor(0, 0, 0, 1);	// black background

		glClear(GL_COLOR_BUFFER_BIT);

		if (mode == 1)
		{
			MyComponent::drawMode1();
			MyComponent::drawPointer(listener);
		}
		if (mode == 2)
		{
			MyComponent::drawMode2();
			MyComponent::drawPointer(listener);
		}

		MyComponent::rotationDegreeX += rotSpeedX;
		MyComponent::rotationDegreeY += rotSpeedY;
		MyComponent::rotationDegreeZ += rotSpeedZ;

		glPushMatrix();
		MyComponent::drawScene(window, listener);
		if(mode == 0) MyComponent::drawPointer(listener);
		glPopMatrix();

		/* Swap front and back buffers(Double buffering) */
		glfwSwapBuffers(window);

		/* OS 이벤트 감지 */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	glfwTerminate();

	return 0;
}

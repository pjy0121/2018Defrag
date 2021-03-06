// always include "stdafx.h" before include other headers.
#include "stdafx.h"

#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <iostream>
#include <ctime>
#include <string>
#include <vector>

#include <Windows.h>
#include <random>
#include "math.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Leap.h>
#include "MyListener.h"
#include "MyFile.h"
#include "MyPrefab.h"
#include "MyComponent.h"

#define PREFABS_COUNT 4

using namespace System;
using namespace System::Windows::Forms; 
using namespace glm;
using namespace Leap;

const int width_window = 1280 * 1.2;		// 1280*1.2
const int height_window = 960 * 1.2;		// 960*1.2

////// global variables
Controller controller;
MyListener listener;
glm::vec3 rotSpeed(0.0f, 0.0f, 0.0f);		// 회전 속도
std::vector<bool> selected;	// prefab 선택 여부

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
	// 그리기 시작 / 중단(ENTER toggle)
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		// 그리기 모드
		if (mode == 0)
		{
			// 그리기 시작 중단 toggle, 현재까지의 위치 저장
			if (listener.isStop)
			{
				listener.isStop = false;
				listener.latest.push((int)listener.posBuffer.size());	// 최근까지 그린 인덱스 유지
			}
			else listener.isStop = true;
		}

		// 색깔 변경 모드
		else if (mode == 1)
		{
			float yPos = listener.currentPos.y;
			if (0.8f <= yPos && yPos <= 1.0f)
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
				if (-0.75f <= xPos && xPos <= -0.6f)
				{
					// 현재 그리던 그림을 flush
					listener.flush();

					MyFile::loadFile(listener);
				}
				// 파일 저장
				else if (-0.59f <= xPos && xPos <= -0.44f)
					MyFile::saveFile(listener);


				// 4면체 prefab
				else if (-0.4f <= xPos && xPos <= -0.32f && 0.64f <= yPos && yPos <= 0.75f)
				{
					if (!selected[0]) 
					{
						MyPrefab::drawPrefabTetrahedron(0.6f); 
						selected[0] = true; selected[1] = false; selected[2] = false; selected[3] = false;
					}
					else
					{ MyPrefab::clearPrefab(); selected[0] = false; }
				}
				// 6면체 prefab
				else if (-0.3f <= xPos && xPos <= -0.22f && 0.64f <= yPos && yPos <= 0.75f)
				{
					if (!selected[1])
					{ 
						MyPrefab::drawPrefabHexahedron(0.6f);
						selected[0] = false; selected[1] = true; selected[2] = false; selected[3] = false;
					}
					else
					{ MyPrefab::clearPrefab(); selected[1] = false; }
				}
				// 8면체 prefab
				else if (-0.2f <= xPos && xPos <= -0.12f && 0.64f <= yPos && yPos <= 0.75f)
				{
					if (!selected[2])
					{ 
						MyPrefab::drawPrefabOctahedron(1.2f); 
						selected[0] = false; selected[1] = false; selected[2] = true; selected[3] = false;
					}
					else
					{ MyPrefab::clearPrefab(); selected[2] = false; }
				}
				else if (-0.1f <= xPos && xPos <= -0.02f && 0.64f <= yPos && yPos <= 0.75f)
				{
					if (!selected[3])
					{ 
						MyPrefab::drawPrefabCylinder(0.3f); 
						selected[0] = false; selected[1] = false; selected[2] = false; selected[3] = true;
					}
					else
					{ MyPrefab::clearPrefab(); selected[3] = false; }
				}

				// X축 방향 회전
				else if (0.06f <= xPos && xPos <= 0.16f)
					rotSpeed.x += 0.4f;
				else if (0.17f <= xPos && xPos <= 0.27f)
					rotSpeed.x -= 0.4f;

				// Y축 방향 회전
				if (0.3f <= xPos && xPos <= 0.4f)
					rotSpeed.y += 0.4f;
				else if (0.41f <= xPos && xPos <= 0.51f)
					rotSpeed.y -= 0.4f;

				// Z축 방향 회전
				if (0.54f <= xPos && xPos <= 0.64f)
					rotSpeed.z += 0.4f;
				else if (0.65f <= xPos && xPos <= 0.75f)
					rotSpeed.z -= 0.4f;
			}

			else
			{
				// 회전 clear
				if (0.46f <= yPos && yPos <= 0.54f)
				{
					if (0.06 <= xPos && xPos <= 0.75f)
					{
						rotSpeed = glm::vec3(0.0f, 0.0f, 0.0f);
						MyComponent::rotationDegree = glm::vec3(0.0f, 0.0f, 0.0f);
					}
				}

				// 확대/축소
				else if (0.64f <= xPos && xPos <= 0.75f)
				{
					if (0.12f <= yPos && yPos <= 0.27f)
						MyComponent::scaleSize += 0.08f;
					else if (-0.25f <= yPos && yPos <= -0.1f)
						MyComponent::scaleSize -= 0.08f;
				}

				// 왼쪽 이동
				else if (-0.75f <= xPos && xPos <= -0.65f)
				{
					if (-0.05f <= yPos && yPos <= 0.08f)
						MyComponent::center.x -= 0.1f;
				}

				// 위, 아래 이동
				else if (-0.6f <= xPos && xPos <= -0.5f)
				{
					if (0.15f <= yPos && yPos <= 0.28f)		// 위 이동
						MyComponent::center.y += 0.1f;
					if (-0.25f <= yPos && yPos <= -0.12f)	// 아래 이동
						MyComponent::center.y -= 0.1f;
				}

				// 오른쪽 이동
				else if (-0.45f <= xPos && xPos <= -0.35f)
				{
					if (-0.05f <= yPos && yPos <= 0.08f)
						MyComponent::center.x += 0.1f;
				}
			}
		}
	}

	// 현재의 그림을 파일로 저장(F)
	else if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		MyFile::saveFile(listener);
	}
	// 파일 로드(L)
	else if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		MyFile::loadFile(listener);		// 파일 불러오기
	}

	// 프로그램 초기화(B)
	else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		// 화면 지우기(버퍼들 비우기)
		listener.flush();
		MyPrefab::clearPrefab();
		for(int i=0; i<selected.size(); i++)
			selected[i] = false;

		// 회전 초기화
		rotSpeed = glm::vec3(0.0f, 0.0f, 0.0f);
		MyComponent::rotationDegree = glm::vec3(0.0f, 0.0f, 0.0f);
		
		// 좌표 초기화
		MyComponent::center = glm::vec3(0.0f, 0.0f, 0.0f);

		// 배율 초기화
		MyComponent::scaleSize = 1.0f;
	}

	// 방금 그린 부분 되돌리기(TAB)
	else if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		int latest = 0;
		
		if (!listener.latest.empty())
		{
			latest = listener.latest.top();
			listener.latest.pop();
		}

		listener.posBuffer.erase(listener.posBuffer.begin() + latest, listener.posBuffer.end());
		listener.colorBuffer.erase(listener.colorBuffer.begin() + latest, listener.colorBuffer.end());
		listener.sizeBuffer.erase(listener.sizeBuffer.begin() + latest, listener.sizeBuffer.end());
	}
	
	// 프로그램 종료(Q)
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		glfwTerminate();
		exit(0);
	}

	// x축 기준 회전 속도 조절(빠르게 : D, 느리게 : A)
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
		rotSpeed.x += 0.4f;
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
		rotSpeed.x -= 0.4f;
	// y축 기준 회전 속도 조절(빠르게 : W, 느리게 : S)
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
		rotSpeed.y += 0.4f;
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
		rotSpeed.y -= 0.4f;

	// 점의 크기(그림 전체의 두께) 설정(굵게 : T, 얇게 : Y)
	else if (key == GLFW_KEY_T && action == GLFW_PRESS)
		listener.size += 1.0f;
	else if (key == GLFW_KEY_Y && action == GLFW_PRESS)
		listener.size -= 1.0f;

	// 그리기 색깔 설정
	else if (key == GLFW_KEY_1 && action == GLFW_PRESS)	// R
		listener.color = vec3(1.0f, 0.0f, 0.0f);
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS)	// G
		listener.color = vec3(0.0f, 1.0f, 0.0f);
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS)	// B
		listener.color = vec3(0.0f, 0.0f, 1.0f);

	// 물체 확대 및 축소(확대 : G, 축소 : H toggle)
	else if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		MyComponent::scaleSize += 0.08f;
	}
	else if (key == GLFW_KEY_H && action == GLFW_PRESS)
	{
		MyComponent::scaleSize -= 0.08f;
	}

	// 모드 변경
	// 방향키 ↑ => mode 0, 1 toggle
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		listener.isStop = true;		// 그리기 중단

		if (mode != 0)
			mode = 0;
		else mode = 1;
	}

	// 방향키 ↓ => mode 0, 2 toggle
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		listener.isStop = true;		// 그리기 중단
		if (mode != 0)
			mode = 0;
		else mode = 2;
	}

	
	// Object 중심점 x, y방향으로 옮기기(방향키)
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		MyComponent::center.x += 0.1f;
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		MyComponent::center.x -= 0.1f;
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		MyComponent::center.y += 0.1f;
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		MyComponent::center.y -= 0.1f;
	
	// 좌표 고정
	else if (key == GLFW_KEY_X && action == GLFW_PRESS) listener.fixX = true;
	else if(key == GLFW_KEY_X && action == GLFW_RELEASE) listener.fixX = false;
	else if (key == GLFW_KEY_C && action == GLFW_PRESS) listener.fixY = true;
	else if (key == GLFW_KEY_C && action == GLFW_RELEASE) listener.fixY = false;
	else if (key == GLFW_KEY_V && action == GLFW_PRESS) listener.fixZ = true;
	else if (key == GLFW_KEY_V && action == GLFW_RELEASE) listener.fixZ = false;
}

//Never use "using namespace std"
//int main(array<System::String ^> ^args)
int main(int argc, char* argv[])
{
	// Hide console
	FreeConsole();

	// Init Program
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);

	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// window 타이틀바 없애기
	glfwWindowHint(GLFW_DECORATED, false);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "3D Rendering", NULL, NULL);
	
	selected.resize(PREFABS_COUNT);		// prefab의 종류만큼 공간을 잡아줌

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

		// 좌표계 변경
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, -10, 10);   // 정투상(화면에서 보이는 범위 설정)

		//모델, 시점 좌표계
		glMatrixMode(GL_MODELVIEW);

		// alpha(transparency) 관련
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		MyComponent::rotationDegree.x += rotSpeed.x;
		MyComponent::rotationDegree.y += rotSpeed.y;
		MyComponent::rotationDegree.z += rotSpeed.z;

		// glScalef(-1.0f, 1.0f, 1.0f);		// 화면 반전
		glPushMatrix();
		MyComponent::drawScene(window, listener);

		if (mode == 0)
		{
			if (rotSpeed == glm::vec3(0.0f, 0.0f, 0.0f)) MyComponent::drawGridSystem();
			if (rotSpeed == glm::vec3(0.0f, 0.0f, 0.0f)) MyComponent::drawAxes();
			if (rotSpeed == glm::vec3(0.0f, 0.0f, 0.0f)) MyComponent::drawPointer(listener);
		}
		glPopMatrix();

		if (mode == 1)
		{
			MyComponent::drawMode1();
			MyComponent::drawPointer(listener);
		}
		if (mode == 2)
		{
			MyComponent::drawMode2(selected);
			MyComponent::drawPointer(listener);
		}
		// glScalef(-1.0f, 1.0f, 1.0f);		// 화면 반전
		glEnd();

		/* Swap front and back buffers(Double buffering) */
		glfwSwapBuffers(window);

		/* OS 이벤트 감지 */
		glfwPollEvents();
	}
	
	glfwTerminate();

	return 0;
}
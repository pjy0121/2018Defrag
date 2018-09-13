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

/*
mode 0 : �׸��� ���
mode 1 : ���� ���� ���
mode 2 : ������Ʈ ��ȯ ���
*/
int mode = 0;

////// callbacks
// key board input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// �׸��� �ߴ�(TAB)
	if (key == GLFW_KEY_TAB && action == GLFW_RELEASE)
	{
		listener.isStop = true;
	}
	// �׸��� ����(ENTER)
	else if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
	{
		// �׸��� ���
		if(mode == 0)
			listener.isStop = listener.isStop ? false : true;
		
		// ���� ���� ���
		else if (mode == 1)
		{
			float ypos = listener.currentPos.y;

			if (0.6f <= ypos && ypos <= 0.8f)
				listener.color = vec3(1.0f, 0.0f, 0.0f);	// ��
			else if (0.4f <= ypos && ypos <= 0.6f)
				listener.color = vec3(1.0f, 128.0f / 255.0f, 0.0f);		// ��
			else if (0.2f <= ypos && ypos <= 0.4f)
				listener.color = vec3(1.0f, 1.0f, 0.0f);	// ��
			else if (0.0f <= ypos && ypos <= 0.2f)
				listener.color = vec3(0.0f, 1.0f, 0.0f);	// ��
			else if (-0.2f <= ypos && ypos <= 0.0f)
				listener.color = vec3(0.0f, 0.0f, 1.0f);	// ��
			else if (-0.4f <= ypos && ypos <= -0.2f)
				listener.color = vec3(0.0f, 64.0f / 255.0f, 128.0f / 255.0f);	// ��
			else if (-0.6f <= ypos && ypos <= -0.4f)
				listener.color = vec3(128.0f / 255.0f, 0.0f, 1.0f);	// ��
			else if (-0.8f <= ypos && ypos <= -0.6f)
				listener.color = vec3(1.0f, 1.0f, 1.0f);	// ��

			mode = 0;	// �׸��� ���� �ǵ��ư���
		}
	}

	// ������ �׸��� ���Ϸ� ����(F)
	else if (key == GLFW_KEY_F && action == GLFW_RELEASE)
		MyFile::saveFile(listener);		
	// ���� �ε�(L)
	else if (key == GLFW_KEY_L && action == GLFW_RELEASE)
	{
		// ���� �׸��� �׸��� flush
		listener.posBuffer.clear();
		listener.colorBuffer.clear();
		listener.sizeBuffer.clear();

		MyFile::loadFile(listener);		// ���� �ҷ�����
	}
	
	// ȭ�� �����(B)
	else if (key == GLFW_KEY_B && action == GLFW_RELEASE) {
		// ���۵� ����
		listener.posBuffer.clear();
		listener.colorBuffer.clear();
		listener.sizeBuffer.clear();
	}

	// ���α׷� ����(Q)
	else if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {
		glfwTerminate();
		exit(0);
	}

	// x�� ���� ȸ�� �ӵ� ����(������ : D, ������ : A)
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		MyComponent::rotationDegreeX += 1.0f;
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		MyComponent::rotationDegreeX -= 1.0f;
	// y�� ���� ȸ�� �ӵ� ����(������ : W, ������ : S)
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		MyComponent::rotationDegreeY += 1.0f;
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		MyComponent::rotationDegreeY -= 1.0f;

	// ���� ũ��(�׸� ��ü�� �β�) ����(���� : T, ��� : Y)
	else if (key == GLFW_KEY_T && action == GLFW_RELEASE)
		listener.size += 1.0f;
	else if (key == GLFW_KEY_Y && action == GLFW_RELEASE)
		listener.size -= 1.0f;

	// �׸��� ���� ����
	else if (key == GLFW_KEY_1 && action == GLFW_RELEASE)	// R
		listener.color = vec3(1.0f, 0.0f, 0.0f);
	else if (key == GLFW_KEY_2 && action == GLFW_RELEASE)	// G
		listener.color = vec3(0.0f, 1.0f, 0.0f);
	else if (key == GLFW_KEY_3 && action == GLFW_RELEASE)	// B
		listener.color = vec3(0.0f, 0.0f, 1.0f);

	// ��ü Ȯ�� �� ���(��۽�, Ȯ�� : G, ��� : H)
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

	// ��� ����
	// ����Ű �� => mode 0, 1 toggle
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
	{
		listener.isStop = true;		// �׸��� �ߴ�

		if (mode != 0)
			mode = 0;
		else mode = 1;
	}
	// ����Ű �� => mode 0, 2 toggle
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
	{
		listener.isStop = true;		// �׸��� �ߴ�
		if (mode != 0)
			mode = 0;
		else mode = 2;
	}

	/*
	// Object �߽��� x, y�������� �ű��(����Ű)
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

	////// �� �β�, �� ũ�� ���� ����
	GLfloat LineRange[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, LineRange);
	glLineWidth(LineRange[1] / 4);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);

	controller.addListener(listener);

	// �����찡 ���� ������ �ݺ�
	while (!glfwWindowShouldClose(window))
	{
		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		glClearColor(0, 0, 0, 1);	// black background

		glClear(GL_COLOR_BUFFER_BIT);

		if (mode == 1)
		{
			listener.currentPos.z = 1.0f;	// ������ ũ�� ����
			MyComponent::drawMode1();
		}
		if (mode == 2) 
		{
			listener.currentPos.z = 1.0f;	// ������ ũ�� ����
			MyComponent::drawMode2();
		}

		MyComponent::drawScene(window, listener);

		/* Swap front and back buffers(Double buffering) */
		glfwSwapBuffers(window);

		/* OS �̺�Ʈ ���� */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	glfwTerminate();

	return 0;
}

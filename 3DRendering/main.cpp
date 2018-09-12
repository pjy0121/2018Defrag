#ifndef UNICODE
#define UNICODE
#endif 
// color buffer �ʿ�, �β� buffer �ʿ�

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
	// �׸��� �ߴ�(TAB)
	if (key == GLFW_KEY_TAB && action == GLFW_RELEASE)
		listener.isStop = true;
	// �׸��� ����(ENTER)
	else if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
		listener.isStop = false;

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

	// x�� ���� ȸ�� �ӵ� ����(������ : A, ������ : D)
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		MyComponents::rotationDegreeX += 1.0f;
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		MyComponents::rotationDegreeX -= 1.0f;
	// y�� ���� ȸ�� �ӵ� ����(������ : W, ������ : S)
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		MyComponents::rotationDegreeY += 1.0f;
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		MyComponents::rotationDegreeY -= 1.0f;

	// ���� ũ��(�׸� ��ü�� �β�) ����(���� : L, ��� : K)
	else if (key == GLFW_KEY_L && action == GLFW_RELEASE)
		listener.size += 1.0f;
	else if (key == GLFW_KEY_K && action == GLFW_RELEASE)
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

	////// �� �β�, �� ũ�� ���� ����
	GLfloat LineRange[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, LineRange);
	glLineWidth(LineRange[1] / 4);

	int width, height;
	glfwGetFramebufferSize(window1, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);

	controller.addListener(listener);

	// �����찡 ���� ������ �ݺ�
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

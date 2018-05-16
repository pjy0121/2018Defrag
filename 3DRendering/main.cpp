// color buffer �ʿ�, �β� buffer �ʿ�

#include <GL/glew.h>	
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <Leap.h>
#include <Windows.h>
#include "math.h"
#include "MyListener.h"
#include <GL/glut.h>
#include <random>

// const int width_window = 640;
// const int height_window = 480;

const int width_window = 1280;
const int height_window = 960;

using namespace std;
using namespace glm;
using namespace Leap;

///// ���� ����� ����
// ���� ���� �Լ�
void saveFile(const MyListener& L)
{
	std::ofstream outputFile("output.txt");
	for (int i = 0; i < L.posBuffer.size(); i++)
		outputFile << L.posBuffer[i].x << " " << L.posBuffer[i].y << " " << L.posBuffer[i].z << " " <<	// ���� ��ġ ����
		L.colorBuffer[i].x << " " << L.colorBuffer[i].y << " " << L.colorBuffer[i].z << " " <<		// ���� ���� ����
		L.sizeBuffer[i] << std::endl;	// ���� ũ�� ����
	outputFile.close();
}

// ������ �о�鿩 �� ���� ��ǥ�� buffer�� �Ű��ֱ�
void loadFile(const MyListener& L)
{
	string line;
	ifstream inputFile("output.txt");

	if (inputFile.is_open())
	{
		string a, b, c, d, e, f, g;
		while (inputFile >> a >> b >> c >> d >> e >> f >> g)
		{
			vec3 pos(stof(a), stof(b), stof(c));	// ���� ���� ��ǥ���� float������ �ٲ㼭 vec3�� ����
			L.posBuffer.push_back(pos);	// buffer�� ���� �־���
			vec3 color(stof(d), stof(e), stof(f));		// ���� ���� ���� �������� vec3�� ����
			L.colorBuffer.push_back(color);	// color buffer�� ���� �־���
			L.sizeBuffer.push_back(stof(g));		// ���� ���� ũ�� ������ size buffer�� ���� �־���
		}
		inputFile.close();
	}
}

// global variables
Controller controller;
MyListener listener;

vec3 center(0.0f, 0.0f, 0.0f);
float rotationDegree = 0.0f;

// key board input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_P && action == GLFW_RELEASE)
		controller.removeListener(listener);	// Listener ���� => ����(P)
	else if (key == GLFW_KEY_O && action == GLFW_RELEASE)
		controller.addListener(listener);	// Listener�� �߰� => �׸��� ����(O)
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		saveFile(listener);		// ������ �׸��� ���Ϸ� ����(S)
	else if (key == GLFW_KEY_C && action == GLFW_RELEASE) {		// ���۵� ���� => ȭ�� �����(C)
		listener.posBuffer.clear();
		listener.colorBuffer.clear();
		listener.sizeBuffer.clear();
	}
	else if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {		// ����(Q)
		glfwTerminate();
		exit(0);
	}

	// y�� ���� ȸ�� �ӵ� ����(������ : M, ������ : N)
	else if (key == GLFW_KEY_M && action == GLFW_RELEASE)
		rotationDegree += 1.0f;
	else if (key == GLFW_KEY_N && action == GLFW_RELEASE)
		rotationDegree -= 1.0f;

	// ���� ũ��(�׸� ��ü�� �β�) ����(���� : L, ��� : K)
	else if (key == GLFW_KEY_L && action == GLFW_RELEASE)
		listener.size += 1.0f;
	else if (key == GLFW_KEY_K && action == GLFW_RELEASE)
		listener.size -= 1.0f;

	// �׸��� ���� ����
	else if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
		listener.color = vec3(1.0f, 0.0f, 0.0f);
	else if (key == GLFW_KEY_2 && action == GLFW_RELEASE)
		listener.color = vec3(0.0f, 1.0f, 0.0f);
	else if (key == GLFW_KEY_3 && action == GLFW_RELEASE)
		listener.color = vec3(0.0f, 0.0f, 1.0f);

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

void drawpoint(vec3 pos, vec3 color, float pointSize)
{
	glPointSize(pointSize);
	glColor3fv(&color[0]);
	glVertex3fv(&pos[0]);
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

	// callbacks
	glfwSetKeyCallback(window, key_callback);	// key board input callback


	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // white background

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);

	////// �� �β�, �� ũ�� ���� ����
	GLfloat LineRange[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, LineRange);
	// glLineWidth(LineRange[1] / 2);
	
	loadFile(listener);		// ���� �ҷ�����

	// �����찡 ���� ������ �ݺ�
	while (!glfwWindowShouldClose(window))
	{
		glPointSize(listener.size);
		glClear(GL_COLOR_BUFFER_BIT);

		glTranslatef(center.x, center.y, center.z);
		glRotatef(rotationDegree, 0.0f, 1.0f, 0.0f);

		////// �׸� �׸��� �κ�
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f);	// default color

		// ������ ������ �� ȭ�鿡�� ����
		for (int i = 0; i < listener.posBuffer.size(); i++)
			drawpoint(listener.posBuffer[i], listener.colorBuffer[i], listener.sizeBuffer[i]);
		glEnd();

		/* Swap front and back buffers(Double buffering) */
		glfwSwapBuffers(window);

		/* OS �̺�Ʈ ���� */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	glfwTerminate();

	return 0;
}
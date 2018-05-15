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

// ���� ���� �Լ�
void saveFile(const MyListener& L, const vector<vec3>& buffer)
{
	std::ofstream outputFile("output.txt");
	for (int i = 0; i < buffer.size(); i++)
		outputFile << buffer[i].x << " " << buffer[i].y << " " << buffer[i].z << std::endl;
	for (int i = 0; i < L.buf.size(); i++)
		outputFile << L.buf[i].x << " " << L.buf[i].y << " " << L.buf[i].z << std::endl;
	outputFile.close();
}


Controller controller;
MyListener listener;
vector<vec3> filebuffer;	// �̹� �����ϴ� �׸��� ��ǥ�� ��� ����

							// key board input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_P && action == GLFW_RELEASE)
		controller.removeListener(listener);	// Listener ���� => ����
	else if (key == GLFW_KEY_O && action == GLFW_RELEASE)
		controller.addListener(listener);	// Listener�� �߰� => �׸��� ����
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		saveFile(listener, filebuffer);		// ������ �׸��� ���Ϸ� ����
	else if (key == GLFW_KEY_C && action == GLFW_RELEASE) {		// ���۵� ���� => ȭ�� �����
		filebuffer.clear();
		listener.buf.clear();
	}
	else if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
		glfwTerminate();	// ����
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

	////// ���� ����� ����
	// ������ �о�鿩 �� ���� ��ǥ�� buffer�� �Ű��ֱ�
	string line;
	ifstream inputFile("output.txt");

	if (inputFile.is_open())
	{
		string a, b, c;
		while (inputFile >> a >> b >> c)
		{
			vec3 point(stof(a), stof(b), stof(c));	// ���� ���� ��ǥ���� float������ �ٲ㼭 vec3�� ����
			filebuffer.push_back(point);	// buffer�� ���� �־���
		}
		inputFile.close();
	}

	////// �� �β�, �� ũ�� ���� ����
	GLfloat LineRange[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, LineRange);
	// glLineWidth(LineRange[1] / 2);
	glPointSize(10);

	// �����찡 ���� ������ �ݺ�
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glRotatef(1, 0.0f, 1.0f, 0.0f);

		////// �׸� �׸��� �κ�
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f);	// default color

										// ���� ������ ������ ������ ���
		if (!filebuffer.empty())
		{
			for (int i = 0; i < filebuffer.size(); i++)
				glVertex3f(filebuffer[i].x, filebuffer[i].y, filebuffer[i].z);
		}
		// ������ ������ �� ȭ�鿡�� ����
		for (int i = 0; i < listener.buf.size(); i++) {
			glVertex3f(listener.buf[i].x, listener.buf[i].y, listener.buf[i].z);
		}
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
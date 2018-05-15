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

// const int width_window = 640;
// const int height_window = 480;

const int width_window = 1280;
const int height_window = 960;

using namespace std;
using namespace glm;
using namespace Leap;

int main(void)
{
	////// 립 모션 관련 선언
	Controller controller;
	MyListener listener;
	controller.addListener(listener);

	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}
		
	// callbacks here


	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);

	vector<vec3> buffer;	// 그림의 좌표를 담는 버퍼

	/*
	// 파일을 읽어들여 그 안의 좌표를 buffer로 옮겨주기
	string line;
	ifstream myfile("drawingSample.txt");
	
	if (myfile.is_open())
	{
		string a, b, c;
		while (myfile >> a >> b >> c)
		{
			vec3 point(stof(a), stof(b), stof(c));	// 파일 안의 좌표들을 float형으로 바꿔서 vec3로 묶음
			buffer.push_back(point);	// buffer에 집어 넣어줌
		}
		myfile.close();
	}
	*/

	// 선 두께 조정
	GLfloat LineRange[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, LineRange);
	// glLineWidth(LineRange[1] / 2);

	glPointSize(10);
	
	glRotatef(90, 0.0f, 1.0f, 1.0f);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glRotatef(1, 1.0f, 1.0f, 1.0f);
		//TODO: draw here
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f);

		for(int i=0; i<listener.buf.size(); i++)
			glVertex3f(listener.buf[i].x, listener.buf[i].y, listener.buf[i].z);

		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}


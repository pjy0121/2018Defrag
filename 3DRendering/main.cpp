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
#include "math.h"

const int width_window = 640;
const int height_window = 480;

using namespace std;
using namespace glm;

int main(void)
{
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

	// 파일을 읽어들여 그 안의 좌표를 buffer로 옮겨주기
	string line;
	ifstream myfile("drawingSample.txt");
	
	vector<vec3> buffer;
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

	GLfloat LineRange[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, LineRange);
	glLineWidth(LineRange[1] / 2);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glRotatef(1, 1.0f, 1.0f, 1.0f);
		//TODO: draw here
		glBegin(GL_LINE_LOOP);

		glColor3f(1.0f, 0.0f, 0.0f);

		for (int i = 0; i < buffer.size(); i++)
		{
			glVertex3f(buffer[i].x, buffer[i].y, buffer[i].z);
		}
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


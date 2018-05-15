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

// 파일 쓰기 함수
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
vector<vec3> filebuffer;	// 이미 존재하는 그림의 좌표를 담는 버퍼

							// key board input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_P && action == GLFW_RELEASE)
		controller.removeListener(listener);	// Listener 제거 => 멈춤
	else if (key == GLFW_KEY_O && action == GLFW_RELEASE)
		controller.addListener(listener);	// Listener를 추가 => 그리기 시작
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		saveFile(listener, filebuffer);		// 현재의 그림을 파일로 저장
	else if (key == GLFW_KEY_C && action == GLFW_RELEASE) {		// 버퍼들 비우기 => 화면 지우기
		filebuffer.clear();
		listener.buf.clear();
	}
	else if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
		glfwTerminate();	// 종료
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

	////// 파일 입출력 관련
	// 파일을 읽어들여 그 안의 좌표를 buffer로 옮겨주기
	string line;
	ifstream inputFile("output.txt");

	if (inputFile.is_open())
	{
		string a, b, c;
		while (inputFile >> a >> b >> c)
		{
			vec3 point(stof(a), stof(b), stof(c));	// 파일 안의 좌표들을 float형으로 바꿔서 vec3로 묶음
			filebuffer.push_back(point);	// buffer에 집어 넣어줌
		}
		inputFile.close();
	}

	////// 선 두께, 점 크기 조정 관련
	GLfloat LineRange[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, LineRange);
	// glLineWidth(LineRange[1] / 2);
	glPointSize(10);

	// 윈도우가 닫힐 때까지 반복
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glRotatef(1, 0.0f, 1.0f, 0.0f);

		////// 그림 그리는 부분
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f);	// default color

										// 읽은 파일이 있으면 파일을 출력
		if (!filebuffer.empty())
		{
			for (int i = 0; i < filebuffer.size(); i++)
				glVertex3f(filebuffer[i].x, filebuffer[i].y, filebuffer[i].z);
		}
		// 파일이 없으면 빈 화면에서 시작
		for (int i = 0; i < listener.buf.size(); i++) {
			glVertex3f(listener.buf[i].x, listener.buf[i].y, listener.buf[i].z);
		}
		glEnd();

		/* Swap front and back buffers(Double buffering) */
		glfwSwapBuffers(window);

		/* OS 이벤트 감지 */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	glfwTerminate();

	return 0;
}
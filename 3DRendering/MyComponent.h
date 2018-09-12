#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "MyListener.h"

namespace MyComponent
{
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	float rotationDegreeY = 0.0f;
	float rotationDegreeX = 0.0f;
	float scaleSize = 1.0f;

	void drawPoint(glm::vec3 pos, glm::vec3 color, float pointSize)
	{
		glPointSize(pointSize);
		glColor3fv(&color[0]);
		glVertex3fv(&pos[0]);
	}

	// 좌표축 그리기
	void drawAxes()
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(10.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 10.0);
		glEnd();
	}

	// 정육면체 그리기
	void drawHex()
	{
		glColor3f(1.0f, 1.0f, 1.0f);

		const float range = 0.3f;
		const float vertices[8][3] = {
			{ range, range, range },
			{ range, range,-range },
			{ range,-range,-range },
			{ -range,-range,-range },
			{ -range,-range, range },
			{ -range, range, range },
			{ -range, range,-range },
			{ range,-range, range }
		};

		glBegin(GL_LINES);
		//Front Lines
		//Left
		glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
		glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
		//Top
		glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
		glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
		//Bottom
		glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
		glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
		//Right
		glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
		glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
		//Middle Lines
		//Top Left
		glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
		glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
		//Top Right
		glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
		glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
		//Bottom Left
		glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
		glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
		//Bottom Right
		glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
		glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
		//Back Lines
		//Left
		glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
		glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
		//Top
		glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
		glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
		//Bottom
		glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
		glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
		//Right
		glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
		glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);

		glEnd();
	}

	// 사용자 인터페이스 화면 그리기
	void drawInterfaceA()
	{
		////// 그림 그리는 부분
		glPointSize(100.0f);
		glBegin(GL_POINTS);
		// R
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.7f, 0.7f, 0.0f);

		// G
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.7f, 0.0f);

		// B
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.3f, 0.7f, 0.0f);

		// Y
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-0.7f, 0.5f, 0.0f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.0f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-0.3f, 0.5f, 0.0f);

		glColor3f(0.1f, 0.1f, 0.1f);
		glVertex3f(-0.7f, 0.3f, 0.0f);

		glColor3f(0.4f, 0.4f, 0.4f);
		glVertex3f(-0.5f, 0.3f, 0.0f);

		glColor3f(0.7f, 0.7f, 0.7f);
		glVertex3f(-0.3f, 0.3f, 0.0f);

		glEnd();

		glPointSize(10.0f);
	}

	void drawInterfaceB()
	{
		////// 그림 그리는 부분
		glPointSize(100.0f);
		glBegin(GL_POINTS);
		// R
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.7f, 0.7f, 0.0f);

		// G
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.7f, 0.0f);

		// B
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.3f, 0.7f, 0.0f);

		// Y
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-0.7f, 0.5f, 0.0f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.0f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-0.3f, 0.5f, 0.0f);

		glColor3f(0.1f, 0.1f, 0.1f);
		glVertex3f(-0.7f, 0.3f, 0.0f);

		glColor3f(0.4f, 0.4f, 0.4f);
		glVertex3f(-0.5f, 0.3f, 0.0f);

		glColor3f(0.7f, 0.7f, 0.7f);
		glVertex3f(-0.3f, 0.3f, 0.0f);

		glEnd();

		glPointSize(10.0f);
	}

	// 화면 그리기
	void drawScene(GLFWwindow *window, const MyListener& L)
	{
		glLineWidth(10.0f);
		glPointSize(L.size);

		glTranslatef(center.x, center.y, center.z);
		glRotatef(rotationDegreeX, 1.0f, 0.0f, 0.0f);
		glRotatef(rotationDegreeY, 0.0f, 1.0f, 0.0f);

		glScalef(scaleSize, scaleSize, scaleSize);	// 확대 및 축소

		////// 그림 그리는 부분
		drawHex();		// 정육면체 그리기

		glBegin(GL_LINE_STRIP);
		glColor3f(1.0f, 0.0f, 0.0f);	// default color

		// 파일이 없으면 빈 화면에서 시작
		for (int i = 0; i < L.posBuffer.size(); i++)
		{
			drawPoint(L.posBuffer[i], L.colorBuffer[i], L.sizeBuffer[i]);
		}
		glEnd();

		// 현재 위치 포인터 그리기
		glPointSize(abs(L.currentPos.z) * 25.0f);	// 포인터 사이즈 조절
		glBegin(GL_POINTS);
		drawPoint(L.currentPos, glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
		
		glEnd();
	}
}
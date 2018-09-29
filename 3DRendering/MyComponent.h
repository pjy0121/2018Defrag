#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>         // std::chrono::seconds
#include <GL/glut.h>
#include "MyListener.h"

// CLI�� <thread> �� �������� �ʱ� ������ ��� ���ξ����ϴ�.
// temporarily disabled because CLI doesn't support <thread>
//#include <thread>         // std::this_thread::sleep_for

namespace MyComponent
{
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	float rotationDegreeX = 0.0f;
	float rotationDegreeY = 0.0f;
	float rotationDegreeZ = 0.0f;
	float scaleSize = 1.0f;

	// ��Ʈ �׸���(ȭ�鿡 �ؽ�Ʈ �ֱ�)
	void renderBitmapCharacter(float x, float y, float z, void *font, char *string)
	{
		char *c;
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos3f(x, y, z);
		for (c = string; *c != '\0'; c++)
		{
			glutBitmapCharacter(font, *c);
		}
	}

	void drawPoint(glm::vec3 pos, glm::vec3 color, float pointSize)
	{
		glPointSize(pointSize);
		glColor3fv(&color[0]);
		glVertex3fv(&pos[0]);
	}

	// ��ǥ�� �׸���
	void drawAxes()
	{
		glLineWidth(1.0f);
		glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0);	// Green Y
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);
		glColor3f(1.0, 0.0, 0.0);	// Red X
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(10.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);	// Blue Z
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 10.0);
		glEnd();
	}

	// ������ü �׸���
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

	// �簢�� �׸��� �Լ�(���� ���� : width*height)
	void drawSquare(float x1, float y1, float width, float height)
	{
		float x2 = x1 + width;
		float y2 = y1 + height;

		glBegin(GL_POLYGON);

		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
		glVertex3f(x1, y2, 0.0f);

		glEnd();
	}

	// ���� ���� ���
	void drawMode1()
	{
		////// �׸� �׸��� �κ�
		glColor3f(1.0f, 0.0f, 0.0f);	// ��
		drawSquare(-1.0f, 0.8f, 0.2f, 0.2f);

		glColor3f(1.0f, 128.0f/255.0f, 0.0f);	// ��
		drawSquare(-1.0f, 0.6f, 0.2f, 0.2f);

		glColor3f(1.0f, 1.0f, 0.0f);	// ��
		drawSquare(-1.0f, 0.4f, 0.2f, 0.2f);

		glColor3f(0.0f, 1.0f, 0.0f);	// ��
		drawSquare(-1.0f, 0.2f, 0.2f, 0.2f);

		glColor3f(0.0f, 0.0f, 1.0f);	// ��
		drawSquare(-1.0f, 0.0f, 0.2f, 0.2f);

		glColor3f(0.0f, 64.0f/255.0f, 128.0f/255.0f);	// ��
		drawSquare(-1.0f, -0.2f, 0.2f, 0.2f);

		glColor3f(128.0f/255.0f, 0.0f, 1.0f);	// ��
		drawSquare(-1.0f, -0.4f, 0.2f, 0.2f);

		glColor3f(1.0f, 1.0f, 1.0f);	// ��
		drawSquare(-1.0f, -0.6f, 0.2f, 0.2f);
	}

	// ������Ʈ ��ȯ ���
	void drawMode2()
	{
		////// �׸� �׸��� �κ�
		renderBitmapCharacter(-0.6f, 0.8f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "File");
		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(-0.6f, 0.55f, 0.15f, 0.2f);
		renderBitmapCharacter(-0.6f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Load File");

		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(-0.44f, 0.55f, 0.15f, 0.2f);
		renderBitmapCharacter(-0.44f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Save File");

		renderBitmapCharacter(-0.1f, 0.8f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Rotation");
		glColor3f(1.0f, 0.0f, 0.0f);	// ��
		drawSquare(-0.1f, 0.55f, 0.1f, 0.2f);
		drawSquare(0.01f, 0.55f, 0.1f, 0.2f);
		renderBitmapCharacter(-0.06f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");
		renderBitmapCharacter(0.05f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
		renderBitmapCharacter(-0.1f, 0.58f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "X Rotation");

		glColor3f(0.0f, 1.0f, 0.0f);	// ��
		drawSquare(0.2f, 0.55f, 0.1f, 0.2f);
		drawSquare(0.31f, 0.55f, 0.1f, 0.2f);
		renderBitmapCharacter(0.24f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");
		renderBitmapCharacter(0.35f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
		renderBitmapCharacter(0.2f, 0.58f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Y Rotation");

		glColor3f(0.0f, 0.0f, 1.0f);	// ��
		drawSquare(0.5f, 0.55f, 0.1f, 0.2f);
		drawSquare(0.61f, 0.55f, 0.1f, 0.2f);
		renderBitmapCharacter(0.54f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");
		renderBitmapCharacter(0.65f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
		renderBitmapCharacter(0.5f, 0.58f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Z Rotation");
		
		renderBitmapCharacter(0.6f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Object Size");
		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(0.6f, 0.15f, 0.15f, 0.2f);
		renderBitmapCharacter(0.67f, 0.25f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");

		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(0.6f, -0.35f, 0.15f, 0.2f);
		renderBitmapCharacter(0.67f, -0.25f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
	}

	void drawPointer(const MyListener& L)
	{
		// ���� ��ġ ������ �׸���
		glPointSize(L.currentPos.z * 15 + 20.0f);	// ������ ������ ����

		glBegin(GL_POINTS);
		drawPoint(L.currentPos, glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
		glEnd();
	}

	// ȭ�� �׸���
	void drawScene(GLFWwindow *window, const MyListener& L)
	{
		glLineWidth(10.0f);
		glPointSize(L.size);
		glTranslatef(center.x, center.y, center.z);

		glRotatef(rotationDegreeX, 1.0f, 0.0f, 0.0f);
		glRotatef(rotationDegreeY, 0.0f, 1.0f, 0.0f);
		glRotatef(rotationDegreeZ, 0.0f, 0.0f, 1.0f);

		glScalef(scaleSize, scaleSize, scaleSize);	// Ȯ�� �� ���
	
		////// �׸� �׸��� �κ�
		drawAxes();

		glLineWidth(10.0f);
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f);	// default color

		// ������ ������ �� ȭ�鿡�� ����
		for (int i = 0; i < L.posBuffer.size(); i++)
		{
			drawPoint(L.posBuffer[i], L.colorBuffer[i], L.sizeBuffer[i]);
		}
		glEnd();
	}
}
#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "MyListener.h"
#include "MyPrefab.h"

namespace MyComponent
{
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 rotationDegree(0.0f, 0.0f, 0.0f);
	float scaleSize = 1.0f;

	// 폰트 그리기(화면에 텍스트 넣기)
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

	void drawPoint(glm::vec3 pos, glm::vec3 color)
	{
		glBegin(GL_POINTS);
		glColor3fv(&color[0]);
		glVertex3fv(&pos[0]);
		glEnd();
	}

	void drawTransparentPoint(glm::vec3 pos, glm::vec3 color, float alpha)
	{
		glBegin(GL_POINTS);
		glColor4f(color.x, color.y, color.z, alpha);
		glVertex3fv(&pos[0]);
		glEnd();
	}

	// 좌표축 그리기
	void drawAxes()
	{
		glLineWidth(5.0f);
		glBegin(GL_LINES);
		glColor3f(0.0f, 1.0f, 0.0f);	// Green Y
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 10.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);	// Red X
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);	// Blue Z
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 10.0f);
		glEnd();
	}

	void drawGridSystem()
	{
		glLineWidth(1.0f);
		glBegin(GL_LINES);

		glColor3f(0.4f, 0.4f, 0.4f);

		for (float i = 0.0f; i <= 1.25f; i += 0.1f)
		{
			glVertex3f(0.0f, 0.0f, i);
			glVertex3f(1.2f, 0.0f, i);

			glVertex3f(i, 0.0f, 0.0f);
			glVertex3f(i, 0.0f, 1.2f);

			glVertex3f(0.0f, 0.0f, -i);
			glVertex3f(1.2f, 0.0f, -i);

			glVertex3f(i, 0.0f, 0.0f);
			glVertex3f(i, 0.0f, -1.2f);
		}
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

	// 사각형 그리기 함수(변의 길이 : width*height)
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

	// 색깔 변경 모드
	void drawMode1()
	{
		////// 그림 그리는 부분
		glColor3f(1.0f, 0.0f, 0.0f);	// 빨
		drawSquare(-1.0f, 0.8f, 0.2f, 0.2f);

		glColor3f(1.0f, 128.0f/255.0f, 0.0f);	// 주
		drawSquare(-1.0f, 0.6f, 0.2f, 0.2f);

		glColor3f(1.0f, 1.0f, 0.0f);	// 노
		drawSquare(-1.0f, 0.4f, 0.2f, 0.2f);

		glColor3f(0.0f, 1.0f, 0.0f);	// 초
		drawSquare(-1.0f, 0.2f, 0.2f, 0.2f);

		glColor3f(0.0f, 0.0f, 1.0f);	// 파
		drawSquare(-1.0f, 0.0f, 0.2f, 0.2f);

		glColor3f(0.0f, 64.0f/255.0f, 128.0f/255.0f);	// 남
		drawSquare(-1.0f, -0.2f, 0.2f, 0.2f);

		glColor3f(128.0f/255.0f, 0.0f, 1.0f);	// 보
		drawSquare(-1.0f, -0.4f, 0.2f, 0.2f);

		glColor3f(1.0f, 1.0f, 1.0f);	// 흰
		drawSquare(-1.0f, -0.6f, 0.2f, 0.2f);
	}

	// 오브젝트 변환 모드
	void drawMode2(const std::vector<bool>& selected)
	{
		////// 그림 그리는 부분
		// 파일 입출력
		renderBitmapCharacter(-0.75f, 0.8f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "File");
		glColor3f(0.5f, 0.5f, 0.5f);	// 회
		drawSquare(-0.75f, 0.55f, 0.15f, 0.2f);
		renderBitmapCharacter(-0.745f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Load File");

		glColor3f(0.5f, 0.5f, 0.5f);	// 회
		drawSquare(-0.59f, 0.55f, 0.15f, 0.2f);
		renderBitmapCharacter(-0.585f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Save File");


		// prefabs
		renderBitmapCharacter(-0.4f, 0.8f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Figure");
		if (selected[0]) glColor3f(0.3f, 0.8f, 0.8f);		// 청록
		else glColor3f(0.5f, 0.7f, 0.9f);	// 연청
		drawSquare(-0.4f, 0.64f, 0.08f, 0.11f);
		renderBitmapCharacter(-0.37f, 0.68f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "4");

		if (selected[1]) glColor3f(0.3f, 0.8f, 0.8f);		// 청록
		else glColor3f(0.5f, 0.7f, 0.9f);	// 연청
		drawSquare(-0.3f, 0.64f, 0.08f, 0.11f);
		renderBitmapCharacter(-0.27f, 0.68f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "6");

		if (selected[2]) glColor3f(0.3f, 0.8f, 0.8f);		// 청록
		else glColor3f(0.5f, 0.7f, 0.9f);	// 연청
		drawSquare(-0.2f, 0.64f, 0.08f, 0.11f);
		renderBitmapCharacter(-0.17f, 0.68f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "8");

		if (selected[3]) glColor3f(0.3f, 0.8f, 0.8f);		// 청록
		else glColor3f(0.5f, 0.7f, 0.9f);	// 연청
		drawSquare(-0.1f, 0.64f, 0.08f, 0.11f);
		renderBitmapCharacter(-0.07f, 0.68f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "c");


		// 방향키
		glColor3f(0.5f, 0.5f, 0.5f);	// 회
		drawSquare(-0.6f, 0.15f, 0.1f, 0.13f);
		renderBitmapCharacter(-0.56f, 0.2f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "^");

		glColor3f(0.5f, 0.5f, 0.5f);	// 회
		drawSquare(-0.75f, -0.05f, 0.1f, 0.13f);
		renderBitmapCharacter(-0.72f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "<");

		renderBitmapCharacter(-0.62f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Position");

		glColor3f(0.5f, 0.5f, 0.5f);	// 회
		drawSquare(-0.45f, -0.05f, 0.1f, 0.13f);
		renderBitmapCharacter(-0.41f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, ">");

		glColor3f(0.5f, 0.5f, 0.5f);	// 회
		drawSquare(-0.6f, -0.25f, 0.1f, 0.13f);
		renderBitmapCharacter(-0.56f, -0.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "V");


		// 회전
		renderBitmapCharacter(0.06f, 0.8f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Rotation");
		glColor3f(1.0f, 0.0f, 0.0f);	// 빨
		drawSquare(0.06f, 0.55f, 0.1f, 0.2f);
		drawSquare(0.17f, 0.55f, 0.1f, 0.2f);
		renderBitmapCharacter(0.1f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");
		renderBitmapCharacter(0.21f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
		renderBitmapCharacter(0.09f, 0.58f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "X Rotation");

		glColor3f(0.0f, 1.0f, 0.0f);	// 초
		drawSquare(0.3f, 0.55f, 0.1f, 0.2f);
		drawSquare(0.41f, 0.55f, 0.1f, 0.2f);
		renderBitmapCharacter(0.34f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");
		renderBitmapCharacter(0.45f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
		renderBitmapCharacter(0.33f, 0.58f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Y Rotation");

		glColor3f(0.0f, 0.0f, 1.0f);	// 파
		drawSquare(0.54f, 0.55f, 0.1f, 0.2f);
		drawSquare(0.65f, 0.55f, 0.1f, 0.2f);
		renderBitmapCharacter(0.58f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");
		renderBitmapCharacter(0.69f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
		renderBitmapCharacter(0.57f, 0.58f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Z Rotation");
		
		glColor3f(0.5f, 0.7f, 0.5f);	// 카키
		drawSquare(0.06f, 0.46f, 0.69f, 0.08f);
		renderBitmapCharacter(0.36f, 0.48f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Clear");


		// 배율
		renderBitmapCharacter(0.6f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Object Size");
		glColor3f(0.5f, 0.5f, 0.5f);	// 회
		drawSquare(0.64f, 0.12f, 0.11f, 0.15f);
		renderBitmapCharacter(0.68f, 0.19f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");

		glColor3f(0.5f, 0.5f, 0.5f);	// 회
		drawSquare(0.64f, -0.25f, 0.11f, 0.15f);
		renderBitmapCharacter(0.68f, -0.18f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
	}

	void drawPointer(const MyListener& L)
	{
		// 현재 위치 포인터 그리기
		glPointSize(L.currentPos.z * 15 + 15.0f);	// 포인터 사이즈 조절

		float z = L.currentPos.z * 10;
		char* zPtr;
		sprintf(zPtr, "%.1f", z);

		renderBitmapCharacter(L.currentPos.x + 0.1f, L.currentPos.y, L.currentPos.z, GLUT_BITMAP_TIMES_ROMAN_24, zPtr);

		drawPoint(L.currentPos, glm::vec3(1.0f, 1.0f, 1.0f));
	}

	// 화면 그리기
	void drawScene(GLFWwindow *window, const MyListener& L)
	{
		glLineWidth(10.0f);
		glPointSize(L.size);
		
		glTranslatef(center.x, center.y, center.z);

		glRotatef(30 + rotationDegree.x, 1.0f, 0.0f, 0.0f);
		glRotatef(-30 + rotationDegree.y, 0.0f, 1.0f, 0.0f);
		glRotatef(rotationDegree.z, 0.0f, 0.0f, 1.0f);
		
		glScalef(scaleSize, scaleSize, scaleSize);	// 확대 및 축소
	
		////// 그림 그리는 부분
		// drawGridSystem();
		// drawAxes();
		// drawHex();

		glLineWidth(10.0f);
		glColor3f(1.0f, 0.0f, 0.0f);	// default color

		// 그림 그리기
		for (int i = 0; i < L.posBuffer.size(); i++)
		{
			glPointSize(L.posBuffer[i].z * 15 + 15.0f);

			drawPoint(L.posBuffer[i], L.colorBuffer[i]);
		}

		// prefab 그리기
		for (int i = 0; i < MyPrefab::posBuffer.size(); i++)
		{
			glPointSize(MyPrefab::posBuffer[i].z * 15 + 15.0f);

			drawTransparentPoint(MyPrefab::posBuffer[i], MyPrefab::colorBuffer[i], 0.1f);
		}
	}
}
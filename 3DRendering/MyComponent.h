#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "MyListener.h"

namespace MyComponent
{
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 rotationDegree(0.0f, 0.0f, 0.0f);
	float scaleSize = 1.2f;

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

	void drawPoint(glm::vec3 pos, glm::vec3 color)
	{
		glBegin(GL_POINTS);
		glColor3fv(&color[0]);
		glVertex3fv(&pos[0]);
		glEnd();
	}

	// ��ǥ�� �׸���
	void drawAxes()
	{
		glLineWidth(1.0f);
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
		// ���� �����
		renderBitmapCharacter(-0.75f, 0.8f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "File");
		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(-0.75f, 0.55f, 0.15f, 0.2f);
		renderBitmapCharacter(-0.745f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Load File");

		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(-0.59f, 0.55f, 0.15f, 0.2f);
		renderBitmapCharacter(-0.585f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Save File");


		// ����Ű
		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(-0.6f, 0.15f, 0.1f, 0.13f);
		renderBitmapCharacter(-0.56f, 0.2f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "^");

		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(-0.75f, -0.05f, 0.1f, 0.13f);
		renderBitmapCharacter(-0.72f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "<");

		renderBitmapCharacter(-0.62f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Position");

		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(-0.45f, -0.05f, 0.1f, 0.13f);
		renderBitmapCharacter(-0.41f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, ">");

		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(-0.6f, -0.25f, 0.1f, 0.13f);
		renderBitmapCharacter(-0.56f, -0.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "V");


		// ȸ��
		renderBitmapCharacter(0.06f, 0.8f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Rotation");
		glColor3f(1.0f, 0.0f, 0.0f);	// ��
		drawSquare(0.06f, 0.55f, 0.1f, 0.2f);
		drawSquare(0.17f, 0.55f, 0.1f, 0.2f);
		renderBitmapCharacter(0.1f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");
		renderBitmapCharacter(0.21f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
		renderBitmapCharacter(0.09f, 0.58f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "X Rotation");

		glColor3f(0.0f, 1.0f, 0.0f);	// ��
		drawSquare(0.3f, 0.55f, 0.1f, 0.2f);
		drawSquare(0.41f, 0.55f, 0.1f, 0.2f);
		renderBitmapCharacter(0.34f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");
		renderBitmapCharacter(0.45f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
		renderBitmapCharacter(0.33f, 0.58f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Y Rotation");

		glColor3f(0.0f, 0.0f, 1.0f);	// ��
		drawSquare(0.54f, 0.55f, 0.1f, 0.2f);
		drawSquare(0.65f, 0.55f, 0.1f, 0.2f);
		renderBitmapCharacter(0.58f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");
		renderBitmapCharacter(0.69f, 0.65f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
		renderBitmapCharacter(0.57f, 0.58f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Z Rotation");
		
		glColor3f(0.5f, 0.7f, 0.5f);	// īŰ
		drawSquare(0.06f, 0.46f, 0.69f, 0.08f);
		renderBitmapCharacter(0.36f, 0.48f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Clear");


		// ����
		renderBitmapCharacter(0.6f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Object Size");
		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(0.64f, 0.12f, 0.11f, 0.15f);
		renderBitmapCharacter(0.68f, 0.19f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "+");

		glColor3f(0.5f, 0.5f, 0.5f);	// ȸ
		drawSquare(0.64f, -0.25f, 0.11f, 0.15f);
		renderBitmapCharacter(0.68f, -0.18f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "-");
	}

	void drawPointer(const MyListener& L)
	{
		// ���� ��ġ ������ �׸���
		glPointSize(L.currentPos.z * 15 + 15.0f);	// ������ ������ ����

		float z = L.currentPos.z * 10;
		char* zPtr;
		sprintf(zPtr, "%.1f", z);

		renderBitmapCharacter(L.currentPos.x + 0.1f, L.currentPos.y, L.currentPos.z, GLUT_BITMAP_TIMES_ROMAN_24, zPtr);

		drawPoint(L.currentPos, glm::vec3(1.0f, 1.0f, 1.0f));
	}

	// ȭ�� �׸���
	void drawScene(GLFWwindow *window, const MyListener& L)
	{
		glLineWidth(10.0f);
		glPointSize(L.size);
		
		glTranslatef(center.x, center.y, center.z);

		glRotatef(30 + rotationDegree.x, 1.0f, 0.0f, 0.0f);
		glRotatef(-30 + rotationDegree.y, 0.0f, 1.0f, 0.0f);
		glRotatef(rotationDegree.z, 0.0f, 0.0f, 1.0f);
		
		glScalef(scaleSize, scaleSize, scaleSize);	// Ȯ�� �� ���
	
		////// �׸� �׸��� �κ�
		drawGridSystem();
		drawAxes();
		// drawHex();

		glLineWidth(10.0f);
		glColor3f(1.0f, 0.0f, 0.0f);	// default color

		// ������ ������ �� ȭ�鿡�� ����
		for (int i = 0; i < L.posBuffer.size(); i++)
		{
			glPointSize(L.posBuffer[i].z * 15 + 15.0f);

			drawPoint(L.posBuffer[i], L.colorBuffer[i]);
		}
	}


	////// �̸� �غ��� ������Ʈ �׸���
	float getDistance(glm::vec3 a, glm::vec3 b = glm::vec3(0.0f, 0.0f, 0.0f))
	{
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	}

	// a���� b���� �� �׸���
	void drawPrefabLine(glm::vec3 a, glm::vec3 b, const MyListener& L)
	{
		int pointCount = 120;
		glm::vec3 directionVector;

		float aSize = getDistance(a);	// �������� �Ÿ� ���ϱ�
		float bSize = getDistance(b);
		glm::vec3 temp = a;

		// a�� ����� ��, b�� �� ��
		if (aSize > bSize)
		{
			a = b;
			b = temp;
		}

		// ���� ���� ���ϱ�
		directionVector = b - a;
		directionVector /= pointCount;

		glm::vec3 position = a;
		glm::vec3 color(1.0f, 0.0f, 0.0f);

		for (int i = 0; i < pointCount; i++) 
		{
			color = position;
			color += 0.3f;
				
			position += directionVector;

			L.posBuffer.push_back(position);
			L.colorBuffer.push_back(color);
			L.sizeBuffer.push_back(L.size);
		}
	}
	
	// draw tri
	void  draw_tri(glm::vec3 P_1, glm::vec3 P_2, glm::vec3 P_3, const MyListener& L) {
		drawPrefabLine(P_1, P_2, L);
		drawPrefabLine(P_2, P_3, L);
		drawPrefabLine(P_3, P_1, L);
	}
	// draw sq
	void draw_sq(glm::vec3 P_1, glm::vec3 P_2, glm::vec3 P_3, glm::vec3 P_4, const MyListener& L) {
		drawPrefabLine(P_1, P_2, L);
		drawPrefabLine(P_2, P_3, L);
		drawPrefabLine(P_3, P_4, L);
		drawPrefabLine(P_4, P_1, L);
	}
	// draw cir // center != unitvec


	// ������ü �׸���
	void drawPrefabHexahedron(const MyListener& L, float size)
	{
		int hex_x[8] = { 0,1,0,0,1,0,1,1 };
		int hex_y[8] = { 0,0,1,0,1,1,0,1 };
		int hex_z[8] = { 0,0,0,1,0,1,1,1 };
		
		glm::vec3 hexahedron[8];
		
		for (int i = 0; i < 8; i++) 
		{
			hexahedron[i].x = hex_x[i] * size;
			hexahedron[i].y = hex_y[i] * size;
			hexahedron[i].z = hex_z[i] * size;
		}

		drawPrefabLine(hexahedron[0], hexahedron[1], L);
		drawPrefabLine(hexahedron[0], hexahedron[2], L);
		drawPrefabLine(hexahedron[0], hexahedron[3], L);
		drawPrefabLine(hexahedron[1], hexahedron[4], L);
		drawPrefabLine(hexahedron[1], hexahedron[6], L);
		drawPrefabLine(hexahedron[4], hexahedron[7], L);
		drawPrefabLine(hexahedron[2], hexahedron[4], L);
		drawPrefabLine(hexahedron[2], hexahedron[5], L);
		drawPrefabLine(hexahedron[5], hexahedron[7], L);
		drawPrefabLine(hexahedron[3], hexahedron[5], L);
		drawPrefabLine(hexahedron[3], hexahedron[6], L);
		drawPrefabLine(hexahedron[6], hexahedron[7], L);
	}
	// �����ü
	void darw_regular_tetrahedron(const MyListener& L, float size) {
		int tet_x[4] = { 1,0,0,1 };
		int tet_y[4] = { 0,1,0,1 };
		int tet_z[4] = { 0,0,1,1 };

		glm::vec3 tetrahedron[4];

		for (int i = 0; i < 4; i++)
		{
			tetrahedron[i].x = tet_x[i] * size;
			tetrahedron[i].y = tet_y[i] * size;
			tetrahedron[i].z = tet_z[i] * size;
		}
		draw_tri(tetrahedron[0], tetrahedron[1], tetrahedron[2],L);
		draw_tri(tetrahedron[0], tetrahedron[1], tetrahedron[3], L);
		draw_tri(tetrahedron[1], tetrahedron[2], tetrahedron[3], L);
		draw_tri(tetrahedron[0], tetrahedron[2], tetrahedron[3], L);
	}
	// ���ȸ�ü
	void draw_regular_octahedron(const MyListener& L, float size) {
		float hex_x[6] = { 0.5,  1,0.5,  0,0.5,0.5};
		float hex_y[6] = { 0  ,0.5,0.5,0.5,0.5,  1};
		float hex_z[6] = { 0.5,0.5,  0,0.5,  1,0.5};

		glm::vec3 hexahedron[6];
		for (int i = 0; i < 6; i++)
		{
			hexahedron[i].x = hex_x[i] * size;
			hexahedron[i].y = hex_y[i] * size;
			hexahedron[i].z = hex_z[i] * size;
		}
		draw_tri(hexahedron[0], hexahedron[1], hexahedron[4], L);
		draw_tri(hexahedron[0], hexahedron[1], hexahedron[2], L);
		draw_tri(hexahedron[0], hexahedron[4], hexahedron[3], L);
		draw_tri(hexahedron[0], hexahedron[2], hexahedron[3], L);

		draw_tri(hexahedron[5], hexahedron[1], hexahedron[4], L);
		draw_tri(hexahedron[5], hexahedron[1], hexahedron[2], L);
		draw_tri(hexahedron[5], hexahedron[4], hexahedron[3], L);
		draw_tri(hexahedron[5], hexahedron[2], hexahedron[3], L);
	}

	// 2d circle x,z
	void draw_cir(glm::vec3 center,float radi, const MyListener& L) {
		
		
		float two_Pi_radi = 2 * 3.141592 * radi;
		float pointCount = two_Pi_radi * 120;
		glm::vec3  input_point;
		std::vector<glm::vec3> get_point;
		input_point.y = center.y;
		for (int i = 0; i < pointCount; i++)
		{
			float angle = i * 3.141592 / 180;
			input_point.x  = radi * cos(angle) + center.x;
			input_point.z  = radi * sin(angle) + center.z;
			get_point.push_back(input_point);
		}
		glm::vec3 color(1.0f, 0.0f, 0.0f);
		for (int i = 0; i < pointCount; i++)
		{
			L.posBuffer.push_back(get_point[i]);
			color = get_point[i];
			color += 0.3f;
			L.colorBuffer.push_back(color);
			L.sizeBuffer.push_back(L.size);
		}
	}
	

}
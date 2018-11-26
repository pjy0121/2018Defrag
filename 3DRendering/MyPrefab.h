#pragma once
#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <vector>

namespace MyPrefab
{
	std::vector<glm::vec3> posBuffer;
	std::vector<glm::vec3> colorBuffer;
	std::vector<float> sizeBuffer;

	// 버퍼들 초기화
	void clearPrefab()
	{
		posBuffer.clear();
		colorBuffer.clear();
		sizeBuffer.clear();
	}

	// 두 점 사이의 거리 구하기
	float getDistance(glm::vec3 a, glm::vec3 b = glm::vec3(0.0f, 0.0f, 0.0f))
	{
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	}

	// a부터 b까지 선 그리기
	void drawPrefabLine(glm::vec3 a, glm::vec3 b)
	{
		int pointCount = 120;
		glm::vec3 directionVector;

		float aSize = getDistance(a);	// 원점과의 거리 구하기
		float bSize = getDistance(b);
		glm::vec3 temp = a;

		// a가 가까운 점, b가 먼 점
		if (aSize > bSize)
		{
			a = b;
			b = temp;
		}

		// 방향 벡터 구하기
		directionVector = b - a;
		directionVector /= pointCount;

		glm::vec3 position = a;
		glm::vec3 color(1.0f, 0.0f, 0.0f);

		for (int i = 0; i < pointCount; i++)
		{
			color = position;
			color += 0.3f;

			position += directionVector;

			posBuffer.push_back(position);
			colorBuffer.push_back(color);
			sizeBuffer.push_back(10.0f);
		}
	}

	// 삼각형 그리기
	void  drawPrefabTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
		drawPrefabLine(p1, p2);
		drawPrefabLine(p2, p3);
		drawPrefabLine(p3, p1);
	}

	//사각형 그리기
	void drawPrefabSquare(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) {
		drawPrefabLine(p1, p2);
		drawPrefabLine(p2, p3);
		drawPrefabLine(p3, p4);
		drawPrefabLine(p4, p1);
	}

	// 정육면체 그리기
	void drawPrefabHexahedron(float size)
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

		drawPrefabLine(hexahedron[0], hexahedron[1]);
		drawPrefabLine(hexahedron[0], hexahedron[2]);
		drawPrefabLine(hexahedron[0], hexahedron[3]);
		drawPrefabLine(hexahedron[1], hexahedron[4]);
		drawPrefabLine(hexahedron[1], hexahedron[6]);
		drawPrefabLine(hexahedron[4], hexahedron[7]);
		drawPrefabLine(hexahedron[2], hexahedron[4]);
		drawPrefabLine(hexahedron[2], hexahedron[5]);
		drawPrefabLine(hexahedron[5], hexahedron[7]);
		drawPrefabLine(hexahedron[3], hexahedron[5]);
		drawPrefabLine(hexahedron[3], hexahedron[6]);
		drawPrefabLine(hexahedron[6], hexahedron[7]);
	}

	// 정사면체 그리기
	void drawPrefabTetrahedron(float size) {
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
		drawPrefabTriangle(tetrahedron[0], tetrahedron[1], tetrahedron[2]);
		drawPrefabTriangle(tetrahedron[0], tetrahedron[1], tetrahedron[3]);
		drawPrefabTriangle(tetrahedron[1], tetrahedron[2], tetrahedron[3]);
		drawPrefabTriangle(tetrahedron[0], tetrahedron[2], tetrahedron[3]);
	}

	// 정팔면체 그리기
	void drawPrefabOctahedron(float size) {
		float hex_x[6] = { 0.5,  1,0.5,  0,0.5,0.5 };
		float hex_y[6] = { 0  ,0.5,0.5,0.5,0.5,  1 };
		float hex_z[6] = { 0.5,0.5,  0,0.5,  1,0.5 };

		glm::vec3 octahedron[6];
		for (int i = 0; i < 6; i++)
		{
			octahedron[i].x = hex_x[i] * size;
			octahedron[i].y = hex_y[i] * size;
			octahedron[i].z = hex_z[i] * size;
		}
		drawPrefabTriangle(octahedron[0], octahedron[1], octahedron[4]);
		drawPrefabTriangle(octahedron[0], octahedron[1], octahedron[2]);
		drawPrefabTriangle(octahedron[0], octahedron[4], octahedron[3]);
		drawPrefabTriangle(octahedron[0], octahedron[2], octahedron[3]);

		drawPrefabTriangle(octahedron[5], octahedron[1], octahedron[4]);
		drawPrefabTriangle(octahedron[5], octahedron[1], octahedron[2]);
		drawPrefabTriangle(octahedron[5], octahedron[4], octahedron[3]);
		drawPrefabTriangle(octahedron[5], octahedron[2], octahedron[3]);
	}

	// 원 그리기
	void drawPrefabCircle(glm::vec3 center, float radi)
	{
		float pointCount = 2 * 3.141592f * radi * 120.0f;
		glm::vec3 targetPoint;
		std::vector<glm::vec3> targets;
		targetPoint.y = center.y;

		for (int i = 0; i < pointCount; i++)
		{
			float angle = i * 3.141592f / 180.0f;
			targetPoint.x = radi * cos(angle) + center.x;
			targetPoint.z = radi * sin(angle) + center.z;
			targets.push_back(targetPoint);
		}

		glm::vec3 color(1.0f, 0.0f, 0.0f);
		for (int i = 0; i < pointCount; i++)
		{
			posBuffer.push_back(targets[i]);
			color = targets[i];
			color += 0.3f;
			colorBuffer.push_back(color);
			sizeBuffer.push_back(10.0f);
		}
	}

	void drawPrefabCylinder(float radi)
	{
		for (float i = -0.5f; i < 0.5f; i += 0.03f)
		{
			drawPrefabCircle(glm::vec3(0.0f, i, 0.0f), radi);
		}
	}
}
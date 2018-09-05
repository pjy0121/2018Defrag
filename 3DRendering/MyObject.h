#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

class MyObject
{
public:
	std::vector<glm::vec3> posBuffer;
	std::vector<glm::vec3> colorBuffer;
	std::vector<float> sizeBuffer;
	glm::vec3 color;
	float size;
	glm::vec3 center;

	MyObject()
		: color(glm::vec3(1.0f, 0.0f, 0.0f)), size(10.0f)
	{ }

	void drawPoint(glm::vec3 _pos, glm::vec3 _color, float _pointSize)
	{
		glPointSize(_pointSize);
		glColor3fv(&_color[0]);
		glVertex3fv(&_pos[0]);
	}

	void draw()
	{
		for (int i = 0; i < posBuffer.size(); i++)
			drawPoint(posBuffer[i] + center, colorBuffer[i], sizeBuffer[i]);
	}
};
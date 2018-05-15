#include "MyListener.h"
#include <Windows.h>
#include <fstream>
#include <iostream>

glm::vec3 MyListener::color = glm::vec3(1.0f, 0.0f, 0.0f);
std::vector<glm::vec3> MyListener::buf;

void MyListener::onConnect(const Leap::Controller& controller) {
	std::cout << " Connected" << std::endl;
}

void MyListener::onInit(const Leap::Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

// ������ ���� �� ���Ͽ� ���ۿ� �ִ� ������ ����
void MyListener::onExit(const Leap::Controller& controller)
{
	std::cout << "Connection Terminated" << std::endl;
}

// �츮 ȭ�鿡 ������ ��ǥ�� ��ġ�� �ٲ��ִ� �Լ�(����ȭ)
glm::vec3 MyListener::uniform(glm::vec3 coordinate) {
	return glm::vec3(coordinate.x * 0.005f, (coordinate.y - 150)*0.005f, coordinate.z *0.005);
}

// �� ��� �����ʰ� �޾ƿ��� �۾� ����
void MyListener::onFrame(const Leap::Controller & controller)
{
	const Leap::Frame frame = controller.frame();
	controller.setPolicy(Leap::Controller::POLICY_IMAGES);

	int count = 0;

	Leap::Tool tool = frame.tools()[0];
	Leap::Vector tip = tool.tipPosition();
	if (tool.isValid())
	{
		glm::vec3 uni = uniform(glm::vec3(tip.x, tip.y, tip.z));	// ����ȭ�� ��ǥ
		// std::cout << uni.x << " " << uni.y << " " << uni.z << std::endl;		// �ǽð� ��ǥ ���
		buf.push_back(uni);		// ���ۿ� �־���
	}
}
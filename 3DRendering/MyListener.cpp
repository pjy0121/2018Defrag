#include "stdafx.h"
#include "MyListener.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <stack>

glm::vec3 MyListener::color = glm::vec3(1.0f, 0.0f, 0.0f);
float MyListener::size = 10.0f;
std::vector<glm::vec3> MyListener::posBuffer;
std::vector<glm::vec3> MyListener::colorBuffer;
std::vector<float> MyListener::sizeBuffer;
bool MyListener::isStop = true;
glm::vec3 MyListener::currentPos;
std::stack<int> MyListener::latest;
bool MyListener::fixX = false, MyListener::fixY = false, MyListener::fixZ = false;

void MyListener::onConnect(const Leap::Controller& controller) {
	std::cout << " Connected" << std::endl;
}

void MyListener::onInit(const Leap::Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

// 연결이 끝날 때 파일에 버퍼에 있는 내용을 써줌
void MyListener::onExit(const Leap::Controller& controller)
{
	std::cout << "Connection Terminated" << std::endl;
}

// 우리 화면에 적합한 좌표로 위치를 바꿔주는 함수(정규화)
glm::vec3 MyListener::uniform(glm::vec3 coordinate) {
	return glm::vec3(coordinate.x * 0.005f, (coordinate.y - 150)*0.005f, coordinate.z *0.005);
}

// 립 모션 리스너가 받아오는 작업 수행
void MyListener::onFrame(const Leap::Controller & controller)
{
	const Leap::Frame frame = controller.frame();
	controller.setPolicy(Leap::Controller::POLICY_IMAGES);

	int count = 0;

	Leap::Tool tool = frame.tools()[0];
	Leap::Vector tip = tool.tipPosition();

	if (tool.isValid())
	{
		glm::vec3 uni = uniform(glm::vec3(tip.x, tip.y, tip.z));	// 정규화된 좌표
		// std::cout << uni.x << " " << uni.y << " " << uni.z << std::endl;		// 실시간 좌표 출력

		// 좌표 고정 관련
		if (fixX) uni.x = currentPos.x;
		if (fixY) uni.y = currentPos.y;
		if (fixZ) uni.z = currentPos.z;

		if (!isStop)	// 사용자의 입력을 받고 있을 때
		{
			posBuffer.push_back(uni);		// 버퍼에 넣어줌
			colorBuffer.push_back(color);
			sizeBuffer.push_back(size);
		}

		currentPos = uni;	// 현재 위치 포인터
	}
}

// 버퍼들과 변수들 초기화
void MyListener::flush()
{
	posBuffer.clear();
	colorBuffer.clear();
	sizeBuffer.clear();

	// 최근 그린 목록들 제거
	while (!latest.empty())
		latest.pop();

	isStop = true;
}


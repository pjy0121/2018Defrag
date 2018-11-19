#pragma once

#include <Leap.h>
#include <glm/glm.hpp>
#include <stack>
#include <vector>

class MyListener : public Leap::Listener {
public:
	static glm::vec3 color;
	static float size;
	static std::vector<glm::vec3> posBuffer;
	static std::vector<glm::vec3> colorBuffer;
	static std::vector<float> sizeBuffer;
	static bool isStop;
	static glm::vec3 currentPos;
	static std::stack<int> latest;
	static bool fixX, fixY, fixZ;

	virtual void onConnect(const Leap::Controller&);
	virtual void onFrame(const Leap::Controller&);
	virtual void onInit(const Leap::Controller&);

	// ������ ���� �� ���Ͽ� ���ۿ� �ִ� ������ ����
	virtual void onExit(const Leap::Controller&);
	virtual void flush();

	// �츮 ȭ�鿡 ������ ��ǥ�� ��ġ�� �ٲ��ִ� �Լ�(����ȭ)
	glm::vec3 uniform(glm::vec3 coordinate);
};
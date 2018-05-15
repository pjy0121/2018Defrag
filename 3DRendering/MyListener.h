#pragma once
#include <Leap.h>
#include <glm/glm.hpp>
#include <vector>

class MyListener : public Leap::Listener {
public:
	static glm::vec3 color;
	static std::vector<glm::vec3> buf;

	virtual void onConnect(const Leap::Controller&);
	virtual void onFrame(const Leap::Controller&);
	virtual void onInit(const Leap::Controller&);

	// ������ ���� �� ���Ͽ� ���ۿ� �ִ� ������ ����
	virtual void onExit(const Leap::Controller&);

	// �츮 ȭ�鿡 ������ ��ǥ�� ��ġ�� �ٲ��ִ� �Լ�(����ȭ)
	glm::vec3 uniform(glm::vec3 coordinate);
};
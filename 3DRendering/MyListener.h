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

	// 연결이 끝날 때 파일에 버퍼에 있는 내용을 써줌
	virtual void onExit(const Leap::Controller&);

	// 우리 화면에 적합한 좌표로 위치를 바꿔주는 함수(정규화)
	glm::vec3 uniform(glm::vec3 coordinate);
};
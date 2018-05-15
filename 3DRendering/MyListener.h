#pragma once
#include <Leap.h>
#include <glm/glm.hpp>
#include <vector>

class MyListener : public Leap::Listener {
public:
	static glm::vec3 cor;
	static std::vector<glm::vec3> buf;

	virtual void onConnect(const Leap:: Controller&);
	virtual void onFrame(const Leap::Controller&);
	virtual void onInit(const Leap::Controller&);
};
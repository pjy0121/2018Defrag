#include "MyListener.h"
#include <Windows.h>
#include <fstream>
#include <iostream>

glm::vec3 MyListener::cor = glm::vec3(0.0f, 0.0f, 0.0f);
std::vector<glm::vec3> MyListener::buf;

void MyListener::onConnect(const Leap::Controller& controller) {
	std::cout << " Connected" << std::endl;
}

void MyListener::onInit(const Leap::Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

void MyListener::onFrame(const Leap::Controller & controller)
{
	const Leap::Frame frame = controller.frame();
	controller.setPolicy(Leap::Controller::POLICY_IMAGES);

	int appWidth = 800;
	int appHeight = 600;

	Leap::InteractionBox iBox = frame.interactionBox();
	Leap::Pointable pointable = frame.pointables().frontmost();

	Leap::Vector leapPoint = pointable.tipPosition();//.stabilizedTipPosition();
	Leap::Vector normal = iBox.normalizePoint(leapPoint, false);

	// std::ofstream myFile("drawing.txt");
	// Get tools
	//const ToolList tools = frame.tools();
	//for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
	//const Tool tool = *tl;
	//std::cout << std::string(2, ' ') << "Tool, id: " << tool.id()
	//<< ", position: " << tool.tipPosition()
	//<< ", direction: " << tool.direction() << std::endl;
	//}

	int count = 0;
	Leap::Tool tool = frame.tools()[0];
	if (tool.isValid())
	{
		std::cout << tool.tipPosition().x * 0.005 << " " << (tool.tipPosition().y - 150)*0.005 << " " << tool.tipPosition().z *0.005 << std::endl;
		cor.x = tool.tipPosition().x * 0.005;
		cor.y = (tool.tipPosition().y - 150)*0.005;
		cor.z = tool.tipPosition().z *0.005;
		buf.push_back(glm::vec3(cor.x, cor.y, cor.z));
		// myFile << tool.tipPosition().x * 0.005 << " " << (tool.tipPosition().y - 150)*0.005 << " " << tool.tipPosition().z *0.005 << std::endl;
		// myFile.close();
	}

	// 좌표 구하는 부분
	//if ((int)leapPoint.x % 100 == 0)
	//normal *= 100.0;

	//int appX = normal.x * appWidth;
	//int appY = (1 - normal.y) * appHeight;
	//normal *= 100.0;
	//int appZ = normal.z;

	//cout << appX << " " << appY << " " << appZ << endl;
	//
}	
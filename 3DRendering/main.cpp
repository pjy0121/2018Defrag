// color buffer 필요, 두께 buffer 필요

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <Leap.h>
#include <Windows.h>
#include "math.h"
#include "MyListener.h"
#include <GL/glut.h>
#include <random>


#include <windows.h>
#include <shobjidl.h> 
/*
file 선택 open함수
*/
wchar_t* WINAPI wchar_File_Select_Name()//(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	static wchar_t *ret_wchar;
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog *pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem *pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
						ret_wchar = pszFilePath;
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	return ret_wchar;
}
// const int width_window = 640;
// const int height_window = 480;

const int width_window = 1280;
const int height_window = 960;

using namespace std;
using namespace glm;
using namespace Leap;

///// 파일 입출력 관련
// 파일 쓰기 함수
void saveFile(const MyListener& L)
{
	std::ofstream outputFile("output.txt");
	for (int i = 0; i < L.posBuffer.size(); i++)
		outputFile << L.posBuffer[i].x << " " << L.posBuffer[i].y << " " << L.posBuffer[i].z << " " <<	// 점의 위치 저장
		L.colorBuffer[i].x << " " << L.colorBuffer[i].y << " " << L.colorBuffer[i].z << " " <<		// 점의 색깔 저장
		L.sizeBuffer[i] << std::endl;	// 점의 크기 저장
	outputFile.close();
}

// 파일을 읽어들여 그 안의 좌표를 buffer로 옮겨주기
void loadFile(const MyListener& L)
{
	wchar_t* get_file_name = wchar_File_Select_Name();//
	string line;
	ifstream inputFile(get_file_name);


	if (inputFile.is_open())
	{
		string a, b, c, d, e, f, g;
		while (inputFile >> a >> b >> c >> d >> e >> f >> g)
		{
			vec3 pos(stof(a), stof(b), stof(c));	// 파일 안의 좌표들을 float형으로 바꿔서 vec3로 묶음
			L.posBuffer.push_back(pos);	// buffer에 집어 넣어줌
			vec3 color(stof(d), stof(e), stof(f));		// 파일 안의 색깔 정보들을 vec3로 묶음
			L.colorBuffer.push_back(color);	// color buffer에 집어 넣어줌
			L.sizeBuffer.push_back(stof(g));		// 파일 안의 크기 정보를 size buffer에 집어 넣어줌
		}
		inputFile.close();
	}
}

// global variables
Controller controller;
MyListener listener;

vec3 center(0.0f, 0.0f, 0.0f);
float rotationDegreeY = 0.0f;
float rotationDegreeX = 0.0f;
float scaleSize = 1.0f;

// key board input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_P && action == GLFW_RELEASE)
		listener.isStop = true;	// Listener 제거 => 멈춤(P)
	else if (key == GLFW_KEY_O && action == GLFW_RELEASE)
		listener.isStop = false;	// Listener를 추가 => 그리기 시작(O)
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		saveFile(listener);		// 현재의 그림을 파일로 저장(S)
	else if (key == GLFW_KEY_C && action == GLFW_RELEASE) {		// 버퍼들 비우기 => 화면 지우기(C)
		listener.posBuffer.clear();
		listener.colorBuffer.clear();
		listener.sizeBuffer.clear();
	}
	else if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {		// 종료(Q)
		glfwTerminate();
		exit(0);
	}

	// y축 기준 회전 속도 조절(빠르게 : M, 느리게 : N)
	else if (key == GLFW_KEY_M && action == GLFW_RELEASE)
		rotationDegreeY += 1.0f;
	else if (key == GLFW_KEY_N && action == GLFW_RELEASE)
		rotationDegreeY -= 1.0f;

	// x축 기준 회전 속도 조절(빠르게 : B, 느리게 : V)
	else if (key == GLFW_KEY_B && action == GLFW_RELEASE)
		rotationDegreeX += 1.0f;
	else if (key == GLFW_KEY_V && action == GLFW_RELEASE)
		rotationDegreeX -= 1.0f;

	// 점의 크기(그림 전체의 두께) 설정(굵게 : L, 얇게 : K)
	else if (key == GLFW_KEY_L && action == GLFW_RELEASE)
		listener.size += 1.0f;
	else if (key == GLFW_KEY_K && action == GLFW_RELEASE)
		listener.size -= 1.0f;

	// 그리기 색깔 설정
	else if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
		listener.color = vec3(1.0f, 0.0f, 0.0f);
	else if (key == GLFW_KEY_2 && action == GLFW_RELEASE)
		listener.color = vec3(0.0f, 1.0f, 0.0f);
	else if (key == GLFW_KEY_3 && action == GLFW_RELEASE)
		listener.color = vec3(0.0f, 0.0f, 1.0f);

	// 물체 확대 및 축소(토글식, 확대 : G, 축소 : H)
	else if (key == GLFW_KEY_G && action == GLFW_RELEASE)
	{
		if (scaleSize == 1.0f)
			scaleSize = 1.03f;
		else scaleSize = 1.0f;
	}
	else if (key == GLFW_KEY_H && action == GLFW_RELEASE)
	{
		if (scaleSize == 1.0f)
			scaleSize = 0.97f;
		else scaleSize = 1.0f;
	}

	/*
	// Object 중심점 x, y방향으로 옮기기(방향키)
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
		center.x += 0.1f;
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
		center.x -= 0.1f;
	else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
		center.y += 0.1f;
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
		center.y -= 0.1f;
	*/
}

void drawPoint(vec3 pos, vec3 color, float pointSize)
{
	glPointSize(pointSize);
	glColor3fv(&color[0]);
	glVertex3fv(&pos[0]);
}

// 좌표축 그리기
void drawAxes()
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}

// 정육면체 그리기
void drawHex()
{
	glColor3f(1.0f, 1.0f, 1.0f);

	double range = 0.3f;
	double vertices[8][3] = {
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

void drawScene(GLFWwindow *window)
{
	glPointSize(listener.size);

	glClear(GL_COLOR_BUFFER_BIT);

	glTranslatef(center.x, center.y, center.z);
	glRotatef(rotationDegreeY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotationDegreeX, 1.0f, 0.0f, 0.0f);

	glScalef(scaleSize, scaleSize, scaleSize);	// 확대 및 축소
	
	drawHex();

	////// 그림 그리는 부분
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);	// default color

	// 파일이 없으면 빈 화면에서 시작
	for (int i = 0; i < listener.posBuffer.size(); i++)
	{
		drawPoint(listener.posBuffer[i], listener.colorBuffer[i], listener.sizeBuffer[i]);
	}
	glEnd();

	// 현재 위치 포인터 그리기
	glPointSize(abs(listener.currentPos.z) * 25.0f);	// 포인터 사이즈 조절
	glBegin(GL_POINTS);
	drawPoint(listener.currentPos, vec3(1.0f, 1.0f, 1.0f), 1.0f);	
	glEnd();

	/* Swap front and back buffers(Double buffering) */
	glfwSwapBuffers(window);

	/* OS 이벤트 감지 */
	glfwPollEvents();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main()
{
	srand((unsigned)time(NULL));

	GLFWwindow *window1 = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window1 = glfwCreateWindow(width_window, height_window, "3D Rendering", NULL, NULL);
	/*window2 = glfwCreateWindow(width_window/2, height_window/2, "3D Rendering", NULL, NULL);
	window3 = glfwCreateWindow(width_window / 2, height_window / 2, "3D Rendering", NULL, NULL);
	window4 = glfwCreateWindow(width_window / 2, height_window / 2, "3D Rendering", NULL, NULL);*/

	/*glfwSetWindowPos(window1, width_window/2, 0.0f);
	glfwSetWindowPos(window2, width_window, height_window/4);
	glfwSetWindowPos(window3, 0.0f, height_window / 4);
	glfwSetWindowPos(window4, width_window / 2, height_window / 2);*/


	if (!window1)
	{
		glfwTerminate();
		return -1;
	}

	// callbacks
	// key board input callback
	glfwSetKeyCallback(window1, key_callback);

	////// 선 두께, 점 크기 조정 관련
	GLfloat LineRange[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, LineRange);
	glLineWidth(LineRange[1] / 4);
	
	loadFile(listener);		// 파일 불러오기

	controller.addListener(listener);

	int width, height;
	glfwGetFramebufferSize(window1, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);

	// 윈도우가 닫힐 때까지 반복
	while (!glfwWindowShouldClose(window1))
	{
		/* Make the window's context current */
		glfwMakeContextCurrent(window1);
		glClearColor(0, 0, 0, 1);	// black background

		drawScene(window1);

		///* Make the window's context current */
		//glfwMakeContextCurrent(window2);
		//glClearColor(0, 0, 0, 1);	// black background

		//drawScene(window2);

		///* Make the window's context current */
		//glfwMakeContextCurrent(window3);
		//glClearColor(0, 0, 0, 1);	// black background

		//drawScene(window3);

		///* Make the window's context current */
		//glfwMakeContextCurrent(window4);
		//glClearColor(0, 0, 0, 1);	// black background

		//drawScene(window4);
	}
	glfwTerminate();

	return 0;
}
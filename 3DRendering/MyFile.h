#pragma once
#include "OpenForm.h"
#include "SaveForm.h"
#include "MyListener.h"
#include <string>
#include <fstream>

using namespace System;
using namespace System::Windows::Forms;

class MyFile {
public:
	// 파일 쓰기 함수
	static void saveFile(const MyListener& L);

	// 파일을 읽어들여 그 안의 좌표를 buffer로 옮겨주기
	static void loadFile(const MyListener& L);
};
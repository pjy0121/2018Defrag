#pragma once
#include <windows.h>
#include <shobjidl.h>
#include <string>
#include <fstream>
#include <Leap.h>
#include "MyListener.h"

namespace MyFile
{
	// 파일 선택 창 open
	wchar_t* WINAPI wchar_File_Select_Name();

	// 파일 쓰기 함수
	void saveFile(const MyListener& L);

	// 파일을 읽어들여 그 안의 좌표를 buffer로 옮겨주기
	void loadFile(const MyListener& L);
}
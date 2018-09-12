#pragma once
#include <windows.h>
#include <shobjidl.h>
#include <string>
#include <fstream>
#include <Leap.h>
#include "MyListener.h"

namespace MyFile
{
	// ���� ���� â open
	wchar_t* WINAPI wchar_File_Select_Name();

	// ���� ���� �Լ�
	void saveFile(const MyListener& L);

	// ������ �о�鿩 �� ���� ��ǥ�� buffer�� �Ű��ֱ�
	void loadFile(const MyListener& L);
}
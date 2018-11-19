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
	// ���� ���� �Լ�
	static void saveFile(const MyListener& L);

	// ������ �о�鿩 �� ���� ��ǥ�� buffer�� �Ű��ֱ�
	static void loadFile(const MyListener& L);

	// Ư�� ����� ���� flash ���� �ʰ� load
	static void loadSampleFile(const MyListener& L, const std::string fileName);
};
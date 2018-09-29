#include "stdafx.h"
#include "MyFile.h"

void MyFile::saveFile(const MyListener & L)
{
	My3DRendering::SaveForm saveForm;
	saveForm.ShowDialog();
	std::string filePath = saveForm.Response;
	Console::WriteLine(gcnew String(filePath.c_str()));

	std::ofstream outputFile;
	outputFile.open(filePath, std::ofstream::out);
	

	for (int i = 0; i < L.posBuffer.size(); i++) {
			outputFile << L.posBuffer[i].x << " " << L.posBuffer[i].y << " " << L.posBuffer[i].z << " " <<	// 점의 위치 저장
			L.colorBuffer[i].x << " " << L.colorBuffer[i].y << " " << L.colorBuffer[i].z << " " <<		// 점의 색깔 저장
			L.sizeBuffer[i] << std::endl;	// 점의 크기 저장
	}
	outputFile.close();
	//throw gcnew System::NotImplementedException();
}

void MyFile::loadFile(const MyListener & L)
{
	My3DRendering::OpenForm openForm;
	openForm.ShowDialog();
	std::string filePath = openForm.Response;
	Console::WriteLine(gcnew String(filePath.c_str()));

	std::ifstream inputFile(filePath);

	if (inputFile.is_open())
	{
		std::string a, b, c, d, e, f, g;
		while (inputFile >> a >> b >> c >> d >> e >> f >> g)
		{
			glm::vec3 pos(stof(a), stof(b), stof(c));	// 파일 안의 좌표들을 float형으로 바꿔서 vec3로 묶음
			L.posBuffer.push_back(pos);	// buffer에 집어 넣어줌
			glm::vec3 color(stof(d), stof(e), stof(f));		// 파일 안의 색깔 정보들을 vec3로 묶음
			L.colorBuffer.push_back(color);	// color buffer에 집어 넣어줌
			L.sizeBuffer.push_back(stof(g));		// 파일 안의 크기 정보를 size buffer에 집어 넣어줌
		}
		inputFile.close();
	}
}

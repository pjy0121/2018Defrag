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
			outputFile << L.posBuffer[i].x << " " << L.posBuffer[i].y << " " << L.posBuffer[i].z << " " <<	// ���� ��ġ ����
			L.colorBuffer[i].x << " " << L.colorBuffer[i].y << " " << L.colorBuffer[i].z << " " <<		// ���� ���� ����
			L.sizeBuffer[i] << std::endl;	// ���� ũ�� ����
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
			glm::vec3 pos(stof(a), stof(b), stof(c));	// ���� ���� ��ǥ���� float������ �ٲ㼭 vec3�� ����
			L.posBuffer.push_back(pos);	// buffer�� ���� �־���
			glm::vec3 color(stof(d), stof(e), stof(f));		// ���� ���� ���� �������� vec3�� ����
			L.colorBuffer.push_back(color);	// color buffer�� ���� �־���
			L.sizeBuffer.push_back(stof(g));		// ���� ���� ũ�� ������ size buffer�� ���� �־���
		}
		inputFile.close();
	}
}

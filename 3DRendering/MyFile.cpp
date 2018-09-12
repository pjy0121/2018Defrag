#include "MyFile.h"

// 파일 선택 창 open
wchar_t * MyFile::wchar_File_Select_Name()//(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
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
						//skip message Box
						//MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
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

// 파일 쓰기 함수
void MyFile::saveFile(const MyListener & L)
{
	SYSTEMTIME lst;
	GetLocalTime(&lst);
	std::string now_systime = "[" + std::to_string(lst.wYear);
	now_systime += "-" + std::to_string(lst.wMonth);
	now_systime += "-" + std::to_string(lst.wDay);
	now_systime += "] " + std::to_string(lst.wHour);
	now_systime += "시 " + std::to_string(lst.wMinute);
	now_systime += "분 " + std::to_string(lst.wSecond);
	now_systime += "초.txt";

	std::ofstream outputFile(now_systime);
	for (int i = 0; i < L.posBuffer.size(); i++)
		outputFile << L.posBuffer[i].x << " " << L.posBuffer[i].y << " " << L.posBuffer[i].z << " " <<	// 점의 위치 저장
		L.colorBuffer[i].x << " " << L.colorBuffer[i].y << " " << L.colorBuffer[i].z << " " <<		// 점의 색깔 저장
		L.sizeBuffer[i] << std::endl;	// 점의 크기 저장
	outputFile.close();
}

// 파일을 읽어들여 그 안의 좌표를 buffer로 옮겨주기
void MyFile::loadFile(const MyListener & L)
{
	// 파일 선택
	wchar_t* get_file_name = wchar_File_Select_Name();
	std::string line;
	std::ifstream inputFile(get_file_name);

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